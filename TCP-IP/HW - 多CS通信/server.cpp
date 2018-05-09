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
     * �� fd ��ȡ count ���ֽڣ����浽 buf �У��������Ѷ�ȡ���ֽ�����
     * ѭ�����ж�ȡ��ֱ����ȡ���ֽ���Ϊ count�����Է��رգ���
     * ���ٶ�ȡֱ�ӷ����Ѷ��������ݡ�
     */
    ssize_t read_n(int & fd, void* buf, size_t count)
    {
        size_t n_left = count; // δ�����ֽ���
        ssize_t n_read = 0; // �Ѷ����ֽ���
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_read = read(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // ���ź��ж�
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
     * �� fd д�� buffer ��ǰ count ���ֽڣ���������д���ֽ�����
     */
    ssize_t write_n(int & fd, void* buf, size_t count)
    {
        size_t n_left = count; // δд���ֽ���
        ssize_t n_written = 0;  // ��д���ֽ���
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_written = write(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // ���ź��ж�
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

    // ���������
    void start()
    {
        // ���⽩ʬ����
        signal(SIGCHLD, SIG_IGN);

        // �� AF_INET �� PF_INET �����ԣ�ǰ���������Ѿ���ȷ���� TCP�����Ե��������������� 0
        if ((m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            ERR_EXIT("server socket function failed! ");

        // ��֮ǰ������ַ�ظ�����
        int on = 1;
        if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
            ERR_EXIT("server setsockopt function failed! ");

        // ���������а�, �����׽�����һ�����ص�ַ���а�, ��Ҫ�� IPv4 ��ַ�ṹǿ��ת��Ϊͨ�õ�ַ�ṹ
        if (bind(m_fd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) < 0)
            ERR_EXIT("server bind function failed! ");

        // �������Ǽ������� socket �� close ״̬תΪ����״̬���ܹ���������
        if(listen(m_fd, SOMAXCONN) < 0)
            ERR_EXIT("server listen function failed! ");

        // ����һ���ͻ��˵�ַ
        struct sockaddr_in client_addr;
        socklen_t addr_len;
        int fd; // һ���µ��׽��֣���Ϊ�������׽���(�����׽���)
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

            // ���µĿͻ���������
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

                // ������ӵĿͻ��˵���Ϣ
                printf("client %d connected, its data is ip = %s, port = %d\n", m_client_num, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

                FD_SET(fd, &all_set);

                if (--n_ready <= 0)
                    continue;
            }

            // ���������׽ӿڲ������¼����д���
            for (int i = 0; i < m_client_num; i++)
            {
                if (m_client_fd[i] == -1) // �еĿͻ��˿����Ѿ��Ͽ���
                    continue;

                if (FD_ISSET(m_client_fd[i], &read_set))
                {
                    // ��ζ�Ų����˿ɶ��¼�
                    Packet recv_packet;
                    memset(&recv_packet, 0, sizeof(recv_packet));

                    // �ȶ�ȡ��Ҫ���ܵ��ֽ�������ȷ���߽�
                    int ret = read_n(m_client_fd[i], &recv_packet.len, sizeof(Packet::len));

                    if (ret == -1)
                    {
                        ERR_EXIT("server read_n function failed! ");
                        continue;
                    }
                    else if (ret < (int)sizeof(Packet::len))
                        continue;

                    // Ȼ�����Щ�ֽ�ȫ��������
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

    enum { MAX_CLIENT_NUM = 5 }; // �������ӵĿͻ�����Ŀ

    sockaddr_in m_server_addr;
    int         m_fd;
    int         m_client_fd[MAX_CLIENT_NUM];
    int         m_client_num; // �����ӵĿͻ�����Ŀ
};

int main()
{

    Server server(AF_INET, 5188, INADDR_ANY);
    server.start();

    return 0;
}