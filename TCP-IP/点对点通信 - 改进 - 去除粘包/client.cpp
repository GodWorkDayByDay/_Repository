#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

using namespace std;

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

        m_client_fd = -1;
    }

    static void handler(int)
    {
        printf("client close scanf by signal!\n");
        exit(EXIT_SUCCESS);
    }

    ssize_t read_n(int fd, void* buf, size_t count)
    {
        size_t n_left = count;
        ssize_t n_read = 0;
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_read = read(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // 被信号中断
                    continue;

                printf("server read function failed!\n");
                return -1;
            }
            else if (n_read == 0)
            {
                printf("client closed!\n");
                return count - n_left;
            }

            buffer += n_read;
            n_left -= n_read;
        }

        return count;
    }

    ssize_t write_n(int fd, void* buf, size_t count)
    {
        size_t n_left = count;
        ssize_t n_written = 0;
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_written = write(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // 被信号中断
                    continue;

                printf("server write function failed!\n");
                return -1;
            }
            else if (n_written == 0)
                continue;

            buffer += n_written;
            n_left -= n_written;
        }

        return count;
    }

    void open()
    {
        if ((m_client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("client socket function failed!\n");
            return;
        }

        if (connect(m_client_fd, (sockaddr*)&m_client_addr, sizeof(m_client_addr)) < 0)
        {
            printf("client connect function failed!\n");
            return;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            printf("client fork function failed!\n");
            return;
        }
        else if (pid == 0)
        {
            Packet recv_packet;
            while (1)
            {
                memset(&recv_packet, 0, sizeof(recv_packet));
                int ret = read_n(m_client_fd, &recv_packet.len, sizeof(Packet::len));

                if (ret == -1)
                {
                    printf("server read function failed!\n");
                    break;
                }
                else if (ret < sizeof(Packet::len))
                {
                    printf("client closed!\n");
                    break;
                }

                int n = ntohl(recv_packet.len);
                ret = read_n(m_client_fd, recv_packet.buffer, n);

                if (ret == -1)
                {
                    printf("server read function failed!\n");
                    break;
                }
                else if (ret < n)
                {
                    printf("client closed!\n");
                    break;
                }

                printf("%s\n", recv_packet.buffer);
            }

            kill(getppid(), SIGUSR1);
            close(m_client_fd);
            exit(EXIT_SUCCESS);
        }
        else
        {
            signal(SIGUSR1, handler);

            Packet send_packet;
            memset(&send_packet, 0, sizeof(send_packet));
            while (~scanf("%s", send_packet.buffer))
            {
                int n = strlen(send_packet.buffer);
                send_packet.len = htonl(n);
                write_n(m_client_fd, &send_packet, sizeof(Packet::len) + n);
            }

            printf("client itself close scanf!\n");
            close(m_client_fd);
            exit(EXIT_SUCCESS);
        }
    }

private:
    sockaddr_in m_client_addr;
    int         m_client_fd;
};

int main()
{
    Client client(AF_INET, 5188, "127.0.0.1");
    client.open();

    return 0;
}
