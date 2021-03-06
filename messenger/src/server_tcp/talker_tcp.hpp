#ifndef TALKER_TCP_HPP
#define TALKER_TCP_HPP

#include <threads/thread.hpp>
#include <ipc/socket.hpp>

#include <cassert>

class talker : public threads::thread
{
public:
        void run()
        {
                // server message
                char msg[256] = "barev";
                assert(m_socket.is_valid());
                //send the message
                m_socket.send((unsigned char*)msg, sizeof(msg));
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
