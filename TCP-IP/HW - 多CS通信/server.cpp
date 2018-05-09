#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

using namespace std;

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while (0)

struct Packet
{
    int len;
    char buffer[1024];
};

class Server
{
public:

    Server(sa_family_t sin_family, in_port_t sin_port, in_addr_t s_addr)
    {
        memset(&m_server_addr, 0, sizeof(m_server_addr));
        m_server_addr.sin_family      = sin_family;
        m_server_addr.sin_port        = htons(sin_port);
        m_server_addr.sin_addr.s_addr = htonl(s_addr);

        m_fd = -1;
        m_client_num = 0;
        memset(m_client_fd, -1, sizeof(m_client_fd));
    }

    /**
     * 从 fd 读取 count 个字节，保存到 buf 中，并返回已读取的字节数。
     * 循环进行读取，直到读取的字节数为 count；若对方关闭，则
     * 不再读取直接返回已读到的数据。
     */
    ssize_t read_n(int & fd, void* buf, size_t count)
    {
        size_t n_left = count; // 未读的字节数
        ssize_t n_read = 0; // 已读的字节数
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_read = read(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // 被信号中断
                    continue;

                ERR_EXIT("server read function failed! ");
                return -1;
            }
            else if (n_read == 0)
            {
                printf("client closed!\n");
                fd = -1;
                return count - n_left;
            }

            buffer += n_read;
            n_left -= n_read;
        }

        return count;
    }

    /**
     * 向 fd 写入 buffer 的前 count 个字节，并返回已写的字节数。
     */
    ssize_t write_n(int & fd, void* buf, size_t count)
    {
        size_t n_left = count; // 未写的字节数
        ssize_t n_written = 0;  // 已写的字节数
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_written = write(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // 被信号中断
                    continue;

                ERR_EXIT("server write function failed! ");
                return -1;
            }
            else if (n_written == 0)
                continue;

            buffer += n_written;
            n_left -= n_written;
        }

        return count;
    }

    // 开启服务端
    void start()
    {
        // 避免僵尸进程
        signal(SIGCHLD, SIG_IGN);

        // 用 AF_INET 和 PF_INET 都可以，前两个参数已经可确定是 TCP，所以第三个参数可以置 0
        if ((m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            ERR_EXIT("server socket function failed! ");

        // 绑定之前开启地址重复利用
        int on = 1;
        if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
            ERR_EXIT("server setsockopt function failed! ");

        // 接下来进行绑定, 将该套接字与一个本地地址进行绑定, 需要将 IPv4 地址结构强制转换为通用地址结构
        if (bind(m_fd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) < 0)
            ERR_EXIT("server bind function failed! ");

        // 接下来是监听，将 socket 从 close 状态转为监听状态才能够接受连接
        if(listen(m_fd, SOMAXCONN) < 0)
            ERR_EXIT("server listen function failed! ");

        // 定义一个客户端地址
        struct sockaddr_in client_addr;
        socklen_t addr_len;
        int fd; // 一个新的套接字，称为已连接套接字(主动套接字)
        int n_ready = 0;
        int max_fd = m_fd;

        fd_set read_set, all_set;
        FD_ZERO(&read_set);
        FD_ZERO(&all_set);
        FD_SET(m_fd, &all_set);

        while (1)
        {
            read_set = all_set;
            n_ready = select(max_fd + 1, &read_set, NULL, NULL, NULL);

            if (n_ready == -1)
            {
                if (errno == EINTR)
                    continue;
                ERR_EXIT("server select function failed! ");
            }

            if (n_ready == 0)
                continue;

            // 有新的客户端连接了
            if (FD_ISSET(m_fd, &read_set))
            {
                if (m_client_num >= MAX_CLIENT_NUM)
                {
                    fprintf(stderr, "too many clients\n");
                    exit(EXIT_FAILURE);
                }

                addr_len = sizeof(client_addr);

                fd = accept(m_fd, (sockaddr*)&client_addr, &addr_len);

                if (fd == -1)
                    ERR_EXIT("server accept function failed! ");

                m_client_fd[m_client_num] = fd;
                max_fd = max(fd, max_fd);

                m_client_num++;

                // 输出连接的客户端的信息
                printf("client %d connected, its data is ip = %s, port = %d\n", m_client_num, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                FD_SET(fd, &all_set);

                if (--n_ready <= 0)
                    continue;
            }

            // 对已连接套接口产生的事件进行处理
            for (int i = 0; i < m_client_num; i++)
            {
                if (m_client_fd[i] == -1) // 有的客户端可能已经断开了
                    continue;

                if (FD_ISSET(m_client_fd[i], &read_set))
                {
                    // 意味着产生了可读事件
                    Packet recv_packet;
                    memset(&recv_packet, 0, sizeof(recv_packet));

                    // 先读取需要接受的字节总数，确定边界
                    int ret = read_n(m_client_fd[i], &recv_packet.len, sizeof(Packet::len));

                    if (ret == -1)
                    {
                        ERR_EXIT("server read_n function failed! ");
                        continue;
                    }
                    else if (ret < (int)sizeof(Packet::len))
                        continue;

                    // 然后把这些字节全部读进来
                    int n = ntohl(recv_packet.len);
                    ret = read_n(m_client_fd[i], recv_packet.buffer, n);

                    if (ret == -1)
                    {
                        ERR_EXIT("server read_n function failed! ");
                        continue;
                    }
                    else if (ret < n)
                        continue;

                    printf("receive client %d's data: %s", i + 1, recv_packet.buffer);

                    if (--n_ready <= 0)
                        break;
                }
            }
        }
    }

private:

    enum { MAX_CLIENT_NUM = 5 }; // 最多可连接的客户端数目

    sockaddr_in m_server_addr;
    int         m_fd;
    int         m_client_fd[MAX_CLIENT_NUM];
    int         m_client_num; // 已连接的客户端数目
};

int main()
{

    Server server(AF_INET, 5188, INADDR_ANY);
    server.start();

    return 0;
}