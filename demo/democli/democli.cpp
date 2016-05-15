#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <fcntl.h>
#include <unistd.h>

void showUsage()
{
    printf("-t ip -p port\n");
}

int set_socket_nonblock(evutil_socket_t& fd)
{
    //设置非阻塞
    int flags = fcntl(fd, F_GETFL, 0);
    if ( flags < 0 )
    {
        printf("socket error");
        return -1;
    }
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return 0;
}

int main(int argc, char** argv)
{
    int port = 0;
    std::string ip = "127.0.0.1";
    
    for ( int i = 0; i < argc; ++i )
    {
        if ( strcmp(argv[i], "-p") == 0 )
        {
            port = atoi(argv[i+1]);
        }
        else if ( strcmp(argv[i], "-i") == 0 )
        {
            ip = argv[i+1];
        }
    }

    if ( port == 0 )
    {
        showUsage();
        return -1;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    //set_socket_nonblock(fd);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = inet_addr(ip);
    int res = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    printf("on loop\n");
	while(1)
	{
		char buf[] = "hello world";
		int length = sizeof(buf);
		write(fd, (char*)&length, 2);
		write(fd, ((char*)&length) + 2, 2);
		write(fd, buf, sizeof(buf));
		sleep(2);
	}
	close(fd);

    return 0;
}
