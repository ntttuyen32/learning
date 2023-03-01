#pragma once
#include <thread>
#include <map>
#include <string>
#include <thread>
using namespace std;
class SomeServer
{
public:
    SomeServer();
    virtual ~SomeServer();
};

class ChatServer:public SomeServer
{
private:
    map<int, string> chatList_;
    string listeningPort_;
    int serverfd_;
    bool isListenning_;
    int maxConnectionCnt_;
    thread listenThread_;

    int listeningProc();
public:
    ChatServer(string port = "5555");
    ~ChatServer();
    int listen();
    int stopListenning();
};