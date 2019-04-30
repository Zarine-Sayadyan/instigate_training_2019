#ifndef IPC_SOCKET_HPP
#define IPC_SOCKET_HPP

/**
 * @file socket.hpp
 * @brief Contains ipc::socket class declaration
 */

/**
 * @namespace ipc
 * @brief Contains types used for inter-process communication.
 */
namespace ipc {
        /**
         * @class ipc::socket
         * @brief POSIX socket wrapper, to hide messy socket programming and
         * provide minimum functionality required for sockets.
         *
         * The class holds only socket descriptor, so it can be copied as an
         * integer. All errors make the class throw an exception. So it is best
         * to enclose it in try/catch clauses
         * @verbatim
         * try {
         *      do something with sockets
         * } catch (TODO& e) {
         *      std::cerr << e.what();
         * }
         * @endverbatim
         */
        class socket;
}

class ipc::socket
{
public:
        enum protocol { NONE, TCP, UDP };
public:
        /// Bind a socket to a local port
        void bind(unsigned short port);
        /// Mark a socket as a listening socket (must be TCP)
        void listen();
        /**
         * @brief Accept a connection request and return new socket to use for
         * communication
         */
        socket accept() const;
        /// Connect to remote server
        void connect(const char* ip, unsigned short p);
        /// Data transmission for TCP
        void send(const unsigned char* m, unsigned int c);
        /// @return actual number of bytes received for TCP
        int recv(unsigned char* m, int s);
        /// Data transmission for UDP
        void sendto(const unsigned char* m, unsigned int c, unsigned short p);
        ///@return actual number of bytes recieved for UDP
        int recvfrom (unsigned char* m, int s, unsigned short p);
        /// Explicit close the socket
        void close();
        /// Test the socket is open
        bool is_valid() const;
        /// Return socket protocol
        protocol get_protocol() const;
private:
        int m_socket;
private:
        static const int MAX_CONNECTIONS = 10;
        int id() const;
public:
        /**
         * Socket must be created with a protocol TCP or UDP. NONE for unused
         * socket.
         */
        explicit socket(protocol p);
        /// Copy constructor, copy as an integer
        socket(const socket& s);
        /// Do not close socket in destructor
        ~socket();
};

#endif // IPC_SOCKET_HPP
