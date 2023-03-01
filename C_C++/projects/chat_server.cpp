#include "common_utils.h"
#include "chat_server.h"
#include <memory>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>
SomeServer::SomeServer()
{
    LOGF();
}
SomeServer::~SomeServer()
{
    LOGF();
}

int ChatServer::listeningProc()
{
    int ret = 0;
    struct timeval selectinterval;
    fd_set activefds, readfds;
    int n = 1;
    
    FD_ZERO(&activefds);
    FD_SET(serverfd_, &activefds);
    isListenning_ = true;
    selectinterval.tv_sec = 1;
    selectinterval.tv_usec = 0;
    while(isListenning_)
    {
        readfds = activefds;
        ret = select(maxConnectionCnt_ + 1, &readfds, nullptr, nullptr, &selectinterval);
        if(ret < 0)
        {
            LOG("Error occurs while server is listenning %s\n", strerror(errno));
            break;
        }
        else if(ret > 0)
        {
            for(int fd = 1; fd < maxConnectionCnt_ + 1; fd++)
            if(FD_ISSET(serverfd_, &readfds))
            {
                sockaddr clientaddr;
                socklen_t clientaddr_len;
                ret = accept(serverfd_, &clientaddr, &clientaddr_len);
                if(ret < 0)
                {
                    LOG("Failed to accept connection from client %s\n", strerror(errno));                    
                }
            }
            
        }
    }
}

ChatServer::ChatServer(string port)
{
    LOGF();
    listeningPort_ = port;
    serverfd_ = -1;
    isListenning_ = false;
    maxConnectionCnt_ = 10;

}

ChatServer::~ChatServer()
{
    LOGF();
    if(serverfd_ >= 0)
    {
        close(serverfd_);
    }
}

int ChatServer::listen()
{
    int ret = 0;
    struct addrinfo anetif, *servers, *server;
    memset(&anetif, 0, sizeof(anetif));
    anetif.ai_family = AF_INET;
    anetif.ai_socktype = SOCK_STREAM;
    anetif.ai_protocol = 0;
    anetif.ai_flags = AI_PASSIVE;

    do
    {
        ret = getaddrinfo(nullptr, listeningPort_.c_str(), &anetif, &servers);
        if(0 != ret)
        {
            LOG("Failed to get address info: %s\n", strerror(ret));
            break;
        }
        for(server = servers; server != nullptr; server = server->ai_next)
        {
            serverfd_ = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
            if(serverfd_ == -1)
            {
                continue;
            }
            break;
        }
        if(serverfd_ == -1 || server == nullptr)
        {

            LOG("Failed to create a server socket: %s\n", strerror(errno));
            ret = errno;
            break;
        }

        ret = bind(serverfd_, server->ai_addr, server->ai_addrlen);
        if(ret < 0)
        {
            LOG("Failed to bind socket: %s\n", strerror(errno));
            ret = errno;
            break;
        }

    } while (0);
    
    if(servers != nullptr)
    {
        freeaddrinfo(servers);
    }    
    return ret;
}

int main()
{
    unique_ptr<SomeServer> pserver = unique_ptr<SomeServer>(new ChatServer());
        
}
