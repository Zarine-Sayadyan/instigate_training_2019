#ifndef IPC_SOCKET_HPP
#define IPC_SOCKET_HPP
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h> //for accept
#include <sys/socket.h>// for accept
#include <netinet/in.h>

/**
 * @file ipc.hpp
 * @brief Contains ipc::socket class declaration
 */

/**
 * @namespace ipc
 * @brief socket's namespace
 */
namespace ipc
{
        /**
          @class ipc::socket
          @brief abstract class incapsulating POSIX socket functionality
          */
        class socket;
}

try {
        socket s(socket::TCP);
        s.bind(9002);
        s.listen();
        socket c = s.accept();

} catch(const std::exception& e) {
}

class ipc::socket
{
public:
        enum protocol { TCP, UDP};
public:
        socket(int domain, int type, protocol p); 
        socket(const socket& other); 
        ~socket();
        void bind(unsigned short port);
        void init_addr(struct sockaddr_in);
        void listen(unsigned short queue_len);
        socket& accept();
        void connect(char *ip);
        void send(char response[25], int flag);
        void recv(char response[25], int flag);
        void close();

private:
        int m_socket;
        struct sockaddr_in m_addr;
        protocol p;
        int m_domain;
        int m_type;
        unsigned short m_port;
};


#endif // SOCKETS_SOCKET_HPP
