#ifndef MESSENGER_TALKER_CLIENT_HPP
#define MESSENGER_TALKER_CLIENT_HPP

#include <thread.hpp>
#include <socket.hpp>
#include <string>

class messenger;

class talker : public threads::thread
{
public:
        void run();
public:
        talker(messenger* m, ipc::socket rx);
        virtual ~talker();
private:
        messenger* m_messenger;
        ipc::socket m_rx;
};

#endif // MESSENGER_TALKER_HPP
