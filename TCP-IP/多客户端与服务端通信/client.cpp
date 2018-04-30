#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
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

        char send_buffer[1024];
        char recv_buffer[1024];
        memset(send_buffer, 0, sizeof(send_buffer));
        memset(recv_buffer, 0, sizeof(recv_buffer));

        while (~scanf("%s", send_buffer))
        {
            write(m_client_fd, send_buffer, strlen(send_buffer));
            read(m_client_fd, recv_buffer, sizeof(recv_buffer));
            printf("Client read: %s\n", recv_buffer);
            memset(send_buffer, 0, sizeof(send_buffer));
            memset(recv_buffer, 0, sizeof(recv_buffer));
        }
        
        printf("client itself close!\n");
        close(m_client_fd);
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
