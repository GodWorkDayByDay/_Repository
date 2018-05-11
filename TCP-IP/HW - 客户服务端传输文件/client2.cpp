#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
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

        while (1)
        {
            Packet send_packet;
            memset(&send_packet, 0, sizeof(send_packet));
            scanf("%s", send_packet.buffer);

            // 客户端打开文件，准备发送文件数据
            if ((m_file = fopen(send_packet.buffer, "r")) == NULL) // /home/hapoa/projects/cplusplus/test.pdf
                ERR_EXIT("file open failed! ");

            // 获取文件信息（其实主要是获取文件大小）
            struct stat file_data;
            if (stat(send_packet.buffer, &file_data) == -1)
                ERR_EXIT("client stat function failed! ");

            // 发送文件名，注意，只是文件名，如果给定的包含路径，需要处理
            int len = strlen(send_packet.buffer);
            int i, j;
            for (i = len - 1; i >= 0; i--)
            {
                if (send_packet.buffer[i] == '/')
                {
                    len = len - i - 1; // 得到文件名长度
                    break;
                }
            }
            if (i >= 0) // 如果有路径，则去除路径，只保留文件名
            {
                for (j = 0, i++; j < len; j++, i++)
                    send_packet.buffer[j] = send_packet.buffer[i];
                send_packet.buffer[j] = '\0'; // 已处理得到文件名（不包含路径）
            }
            send_packet.len = htonl(len);
            write_n(m_fd, &send_packet, sizeof(Packet::len) + len);

            // 得到文件大小,并把这个大小数值发送给服务端
            long int file_size = file_data.st_size;
            printf("file size = %ld\n", file_size);
            memset(&send_packet, 0, sizeof(send_packet));
            send_packet.len = htonl(sizeof(long int));
            memcpy(send_packet.buffer, &file_size, sizeof(long int));
            write_n(m_fd, &send_packet, sizeof(Packet::len) + sizeof(long int));

            // 然后发送文件数据
            int ret;
            memset(&send_packet, 0, sizeof(send_packet));
            while ((ret = fread(send_packet.buffer, sizeof(char), sizeof(send_packet.buffer), m_file)) > 0)
            {
                file_size -= ret;
                send_packet.len = htonl(ret);
                write_n(m_fd, &send_packet, sizeof(Packet::len) + ret);
                memset(&send_packet, 0, sizeof(send_packet));
            }

            printf("file send finished!\n");
            fclose(m_file);
        }
    }

private:

    sockaddr_in m_client_addr;
    int         m_fd;
    FILE*       m_file;
};

int main()
{

    Client client(AF_INET, 5188, "127.0.0.1");
    client.start();

    return 0;
}
