#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

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

        pid_t pid;
        while (1)
        {
            if ((m_client_fd = accept(m_server_fd, (sockaddr*)&client_addr, &len)) < 0)
            {
                printf("server accept function failed!\n");
                return;
            }

            printf("ip = %s, port = %d accepted!\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            pid = fork();
            if (pid < 0)
            {
                printf("server fork function failed!\n");
                return;
            }
            else if (pid == 0)
            {
                close(m_server_fd);

                char recv_buffer[1024];
                while (1)
                {
                    memset(recv_buffer, 0, sizeof(recv_buffer));
                    int ret = read(m_client_fd, recv_buffer, sizeof(recv_buffer));

                    if (ret == 0)
                    {
                        printf("client closed!\n");
                        break;
                    }
                    else if (ret == -1)
                    {
                        printf("server read function failed!\n");
                        break;
                    }

                    printf("Server read: %s\n", recv_buffer);
                    write(m_client_fd, recv_buffer, ret);
                }

                exit(EXIT_SUCCESS);
            }
            else
            {
                close(m_client_fd);
            }
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
