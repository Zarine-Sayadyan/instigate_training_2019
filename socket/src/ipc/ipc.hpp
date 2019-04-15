#ifndef IPC_SOCKET_HPP
#define IPC_SOCKET_HPP
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h> //for accept
#include <sys/socket.h>// for accept
#include <netinet/in.h>
#define MSG_SIZE 256 //for send/recv message size
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
        s.bind(port);
        s.listen();
        socket c = s.accept();

} catch(const std::exception& e) {
}

class ipc::socket
{
public:
        enum protocol { TCP, UDP };
public:
        socket(int domain, protocol p);
        socket(protocol p);//by default AF_INET, SOCK_STREAM
        socket(const socket& other);
        ~socket();
        void bind(unsigned short port);
        void listen(unsigned short queue_len);
        socket& accept();
        void connect();
        //void connect(char* ip);
        void send(char response[MSG_SIZE]);
        void recv(char response[MSG_SIZE]);
        void close();

private:
        int m_socket;
        protocol m_protocol;
        int m_domain;
        unsigned short m_port;
        struct sockaddr_in m_addr;
};

#endif // SOCKETS_SOCKET_HPP
