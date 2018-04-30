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
            char recv_buffer[1024];
            while (1)
            {
                memset(recv_buffer, 0, sizeof(recv_buffer));
                int ret = read(m_client_fd, recv_buffer, sizeof(recv_buffer));

                if (ret == 0)
                {
                    printf("server scanf closed!\n");
                    break;
                }
                else if (ret == -1)
                {
                    printf("client read function failed!\n");
                    break;
                }

                printf("%s\n", recv_buffer);
            }

            kill(getppid(), SIGUSR1);
            close(m_client_fd);
            exit(EXIT_SUCCESS);
        }
        else
        {
            signal(SIGUSR1, handler);
            char send_buffer[1024];
            while (~scanf("%s", send_buffer))
                write(m_client_fd, send_buffer, strlen(send_buffer));

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
