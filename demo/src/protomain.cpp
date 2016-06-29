#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include "reactor.h"
#include "acceptor.h"
#include "test.pb.h"

using namespace CM;
using namespace hello;

void showUsage()
{
    printf("[-t ip] <-p port> [-d] \n");
}

void test();

int main(int argc, char** argv)
{
	//test(args, argv);
    int port = 0;
    std::string ip = "127.0.0.1";
    bool deamon = false;
    for (int i = 0; i < argc; ++i)
    {
        if ( strcmp(argv[i], "-p") == 0 )
        {
            port = atoi(argv[++i]);
        }
        else if ( strcmp(argv[i], "-t") == 0 )
        {
            ip = argv[++i];
        }
        else if ( strcmp(argv[i], "-d") == 0 )
        {
            deamon = true;
        }
    }

    if ( 0 == port )
    {
        showUsage();
        exit(0);
    }
    printf("listen port %d\n", port);

    if (deamon)
    {
        if ( fork() > 0 )
        {
            //parent
            exit(0);
        }

        close(0);
        close(1);
        close(2);
        int fd = open("/dev/null", O_WRONLY);
        chdir("./");
        //dup2(fd, 0);
        dup2(fd, 1);
        dup2(fd, 2);

        setsid();
    }

    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    CAcceptor acceptor(listenFd, port);

    test();

    CReactor reactor;
    reactor.RegisterHandler(listenFd, &acceptor);
    reactor.OnLoop();

	return 0;
}

class RpcServer : public Hello
{
public:
  virtual void Echo(::google::protobuf::RpcController* controller,
                       const ::hello::HelloWorldReq* request,
                       ::hello::HelloWorldResp* response,
                       ::google::protobuf::Closure* done)
  {
      printf("req:%s\b", request->ShortDebugString().c_str());

      response->set_code(11);
      printf("resp:%s\b", response->ShortDebugString().c_str());
      done->Run();
  }

  int Init()
  {
      return 0;
  }

private:

};


void test()
{
    printf("on test \n");
    RpcServer();
}
