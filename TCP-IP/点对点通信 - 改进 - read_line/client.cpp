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

    ssize_t recv_peek(int sockfd, void* buf, size_t len)
    {
        while (1)
        {
            int ret = recv(sockfd, buf, len, MSG_PEEK); // MSG_PEEK : 查看数据,并不从系统缓冲区移走数据

            if (ret == -1 && errno == EINTR)
                continue;

            return ret;
        }
    }

    ssize_t read_line(int sockfd, void* buf, size_t max_len)
    {
        int ret;
        int n_read = 0;
        int n_left = max_len;
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            ret = recv_peek(sockfd, buffer, n_left);

            if (ret < 0)
                return ret;
            else if (ret == 0)
                return 0;

            for (int i = 0; i < ret; i++)
            {
                if (buffer[i] == '\n')
                {
                    ret = read_n(sockfd, buffer, i + 1); // 读出数据（连同换行符一起，并清除缓冲区）

                    if (ret != i + 1)
                        exit(EXIT_FAILURE);

                    return n_read + i + 1;
                }
            }

            n_read += ret;
            n_left -= ret;
            int n = read_n(sockfd, buffer, ret);

            if (n != ret)
                exit(EXIT_FAILURE);

            buffer += ret;
        }

        return -1;
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
            char recv_buffer[1025];
            while (1)
            {
                memset(recv_buffer, 0, sizeof(recv_buffer));
                int ret = read_line(m_client_fd, recv_buffer, 1024);

                if (ret == -1)
                {
                    printf("server read_line function failed!\n");
                    break;
                }

                printf("%s", recv_buffer);
            }

            kill(getppid(), SIGUSR1);
            close(m_client_fd);
            exit(EXIT_SUCCESS);
        }
        else
        {
            signal(SIGUSR1, handler);

            char send_buffer[1025];
            memset(send_buffer, 0, sizeof(send_buffer));
            while (fgets(send_buffer, sizeof(send_buffer), stdin) != NULL)
            {
                write_n(m_client_fd, send_buffer, strlen(send_buffer));
                memset(send_buffer, 0, sizeof(send_buffer));
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
