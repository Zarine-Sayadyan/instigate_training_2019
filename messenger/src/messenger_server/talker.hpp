#ifndef MESSENGER_SERVER_TALKER_HPP
#define MESSENGER_SERVER_TALKER_HPP

/**
 * @file messenger_server/talker.hpp
 * @brief
 */

#include <thread.hpp>
#include <socket.hpp>

#include <string>

/// @brief 
namespace messenger_server
{
        // forward declaration
        class server;
        /**
         */
        class talker;
}

class messenger_server::talker : public threads::thread
{
public:
        void run();
private:
        void parse();
        void receive_command();
        void send_response();
private:
        messenger_server::server* m_server;
        ipc::socket m_client_socket;
        ipc::socket m_server_socket;
        std::string m_command;
        std::string m_response;
public:
        talker(messenger_server::server* s, ipc::socket r, ipc::socket t);
        virtual ~talker();
};

#endif // MESSENGER_SERVER_TALKER_HPP

