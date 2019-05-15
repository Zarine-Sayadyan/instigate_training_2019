#ifndef MESSENGER_SERVER_TALKER_HPP
#define MESSENGER_SERVER_TALKER_HPP

/**
 * @file messenger_server/talker.hpp
 * @brief
 */

#include "command.hpp"

#include <mutex.hpp>
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

        void send_update_command(const std::string& n, bool status);
private:
        void set_registration_failed();
        void set_login_failed();
        void set_ok();
        void parse();
        void receive_command();
        void send_response(const std::string&);
        void handle_register();
        void handle_login();
        void handle_logout();
private:
        messenger_server::server* m_server;
        ipc::socket m_rx;
        ipc::socket m_tx;
        messenger_server::command m_command;
        std::string m_response;
        std::string m_user;
        threads::mutex m_mutex;

public:
        talker(messenger_server::server* s, ipc::socket r, ipc::socket t);
        virtual ~talker();
};

#endif // MESSENGER_SERVER_TALKER_HPP

