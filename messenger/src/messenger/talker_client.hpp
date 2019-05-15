#ifndef MESSENGER_TALKER_CLIENT_HPP
#define MESSENGER_TALKER_CLIENT_HPP

#include <threads/thread.hpp>
#include <ipc/socket.hpp>

#include <string>

class messenger;

class talker : public threads::thread
{
public:
        void run();
private:
        messenger* m_messenger;
        ipc::socket m_rx;
public:
        talker(messenger* m, ipc::socket rx);
        virtual ~talker();
};

#endif // MESSENGER_TALKER_HPP
