#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <thread>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "thread_safe_queue.h"
class Server
{
    typedef union {
        double d;
        char bytes[sizeof(double)];
    } double_bytes;
    ThreadSafeQueue<double> * result_queue;
    int port;
    std::thread running_thread;
    public:
    Server(ThreadSafeQueue<double>*, int);
    void serve();
};
#endif
