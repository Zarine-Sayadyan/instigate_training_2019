#ifndef MESSENGER_SERVER_SERVER_HPP
#define MESSENGER_SERVER_SERVER_HPP

/**
 * @file messenger_server/server.hpp
 * @brief Contains Messenger Server declaration
 */

#include <socket.hpp>
#include <string>
#include <vector>

/// @brief 
namespace messenger_server
{
        struct user;
        /**
         * @brief Server class responsible for accepting connections from
         * clients.
         *
         * The class is responsible for
         * - user registration
         * - user login
         *
         */
        class server;
        // forward declaration
        class talker;
}

struct messenger_server::user
{
        std::string m_name = "";
        bool m_status = true;
};


class messenger_server::server
{
public:
        /// TODO
        void run();
public:
        void login_user(const std::string& user);
        void logout_user(const std::string& user);
        void register_user(const std::string& user);
        void notify();
        void add_user(const std::string& user);
        bool does_user_exist(const std::string& user) const;
        void insert_talker(messenger_server::talker* t);

private:
        typedef std::vector<talker*> talkers;
        typedef std::vector<user> users;

private:
        ipc::socket m_socket;
        users m_users;
        talkers m_talkers;
public:
        server(unsigned short port);
        ~server();
};

#endif // MESSENGER_SERVER_SERVER_HPP
