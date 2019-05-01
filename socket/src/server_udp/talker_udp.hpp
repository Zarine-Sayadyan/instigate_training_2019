#ifndef TALKER_TCP_HPP
#define TALKER_TCP_HPP

#include <thread.hpp>
#include <socket.hpp>
#include <iostream>

#include <cassert>

class talker : public threads::thread
{
    public:
        void run()
        {
            // server message
            char msg[256] = " ";
            char response[256] = "from udp server";
            unsigned short p = 0;
            int len = 0;
            assert(m_socket.is_valid());
            //send the message
            m_socket.recvfrom((unsigned char*)msg, len, p);
            std::cout << "Clent sent" << msg << std::endl;
            m_socket.sendto((unsigned char*)response, sizeof(response), p);
            m_socket.close();
        }
    private:
        ipc::socket m_socket;

    public:
        talker(ipc::socket socket)
            : m_socket(socket)
        {}
};

#endif //TALKER_HPP
