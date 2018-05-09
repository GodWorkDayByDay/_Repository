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

    void start()
    {
        if ((m_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            ERR_EXIT("client socket function failed! ");

        // �ͻ��˲���Ҫ�󶨣�bind��, Ҳ����Ҫ������listen��, ֱ�����ӹ�ȥ�Ϳ���
        if (connect(m_fd, (sockaddr*)&m_client_addr, sizeof(m_client_addr)) < 0)
            ERR_EXIT("client connect function failed! ");

        Packet send_packet;
        memset(&send_packet, 0, sizeof(send_packet));
        while (fgets(send_packet.buffer, sizeof(send_packet.buffer), stdin) != NULL)
        {
            int n = strlen(send_packet.buffer);
            send_packet.len = htonl(n);
            write_n(m_fd, &send_packet, sizeof(Packet::len) + n);
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

