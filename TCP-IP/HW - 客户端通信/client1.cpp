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

class Client
{
public:

    Client(sa_family_t sin_family, in_port_t sin_port, char* cp)
    {
        memset(&m_client_addr, 0, sizeof(m_client_addr));

        m_client_addr.sin_family      = sin_family;
        m_client_addr.sin_port        = htons(sin_port);
        m_client_addr.sin_addr.s_addr = inet_addr(cp);

        m_fd = -1;
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

    void start()
    {
        if ((m_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            ERR_EXIT("client socket function failed! ");

        // 客户端不需要绑定（bind）, 也不需要监听（listen）, 直接连接过去就可以
        if (connect(m_fd, (sockaddr*)&m_client_addr, sizeof(m_client_addr)) < 0)
            ERR_EXIT("client connect function failed! ");

        fd_set read_set;
        FD_ZERO(&read_set);

        // 检测标准输入是否产生了可读事件
        int n_ready;
        int max_fd;
        int stdin_fd = fileno(stdin); // 标准输入
        Packet send_packet, recv_packet;

        // 有两个文件描述符，fd_stdin 和 m_fd
        max_fd = max(stdin_fd, m_fd);

        while (1)
        {
            FD_SET(stdin_fd, &read_set);
            FD_SET(m_fd, &read_set);

            n_ready = select(max_fd + 1, &read_set, NULL, NULL, NULL);

            if (n_ready == -1)
                ERR_EXIT("client select function failed! ");

            if (n_ready == 0)
                continue;

            // 检测到可读事件
            if (FD_ISSET(m_fd, &read_set))
            {
                memset(&recv_packet, 0, sizeof(recv_packet));

                // 先读取需要接受的字节总数，确定边界
                int ret = read_n(m_fd, &recv_packet.len, sizeof(Packet::len));

                if (ret == -1)
                {
                    ERR_EXIT("client read_n function failed! ");
                    continue;
                }
                else if (ret < (int)sizeof(Packet::len))
                    continue;

                // 然后把这些字节全部读进来
                int n = ntohl(recv_packet.len);
                ret = read_n(m_fd, recv_packet.buffer, n);

                if (ret == -1)
                {
                    ERR_EXIT("client read_n function failed! ");
                    continue;
                }
                else if (ret < n)
                    continue;

                printf("%s", recv_packet.buffer);
            }

            // 检测到标准输入产生事件
            if (FD_ISSET(stdin_fd, &read_set))
            {
                memset(&send_packet, 0, sizeof(send_packet));

                // 获取缓冲区的字符并发送
                if (fgets(send_packet.buffer, sizeof(send_packet.buffer), stdin) != NULL)
                {
                    int n = strlen(send_packet.buffer);
                    send_packet.len = htonl(n);
                    write_n(m_fd, &send_packet, sizeof(Packet::len) + n);
                }
            }
        }
    }

private:

    sockaddr_in m_client_addr;
    int         m_fd;
};

int main()
{

    Client client(AF_INET, 5188, "127.0.0.1");
    client.start();

    return 0;
}
