#include <iostream>
#include <stdlib.h>
#include <stdio.h>
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

class Server
{
public:
    Server(sa_family_t sin_family, in_port_t sin_port, in_addr_t s_addr)
    {
        memset(&m_server_addr, 0, sizeof(m_server_addr));

        m_server_addr.sin_family      = sin_family;
        m_server_addr.sin_port        = htons(sin_port);
        m_server_addr.sin_addr.s_addr = htonl(s_addr);

        m_client_fd = m_server_fd = -1;
    }

    static void handler(int)
    {
        printf("server close scanf by signal!\n");
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
        if ((m_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("server socket function failed!\n");
            return;
        }

        int on = 1;
        if (setsockopt(m_server_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        {
            printf("server setsocketopt function failed!\n");
            return;
        }

        if (bind(m_server_fd, (sockaddr*)&m_server_addr, sizeof(m_server_addr)) < 0)
        {
            printf("server bind function failed!\n");
            return;
        }

        if (listen(m_server_fd, SOMAXCONN) < 0)
        {
            printf("server listen function failed!\n");
            return;
        }

        sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        if ((m_client_fd = accept(m_server_fd, (sockaddr*)&client_addr, &len)) < 0)
        {
            printf("server accept function failed!\n");
            return;
        }

        printf("ip = %s, port = %d accepted!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        pid_t pid = fork();
        if (pid < 0)
        {
            printf("server fork function failed!\n");
            return;
        }
        else if (pid == 0)
        {
            signal(SIGUSR1, handler);
            close(m_server_fd);

            Packet send_packet;
            memset(&send_packet, 0, sizeof(send_packet));
            while (~scanf("%s", send_packet.buffer))
            {
                int n = strlen(send_packet.buffer);
                send_packet.len = htonl(n);
                write_n(m_client_fd, &send_packet, sizeof(Packet::len) + n);
            }

            printf("server itself close scanf!\n");
            close(m_client_fd);
            exit(EXIT_SUCCESS);
        }
        else
        {
            close(m_server_fd);

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

            kill(pid, SIGUSR1);
            close(m_client_fd);
            exit(EXIT_SUCCESS);
        }
    }

private:
    sockaddr_in m_server_addr;
    int         m_server_fd;
    int         m_client_fd;
};

int main()
{
    Server server(AF_INET, 5188, INADDR_ANY);
    server.open();

    return 0;
}
