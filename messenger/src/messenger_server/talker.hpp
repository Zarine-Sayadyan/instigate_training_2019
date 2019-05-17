#ifndef MESSENGER_SERVER_TALKER_HPP
#define MESSENGER_SERVER_TALKER_HPP

/**
 * @file messenger_server/talker.hpp
 * @brief
 */

#include <command/command.hpp>
#include <threads/mutex.hpp>
#include <threads/thread.hpp>
#include <ipc/socket.hpp>

#include <string>

/**
  *@namespace messenger_server
  *@brief contains type used for server. 
  */ 
namespace messenger_server
{
        /**
         * @class messenger_server::server
         * @brief to check the name is unique.
         */
        class server;
        /**
         * @class messenger_server::talker
         * @brief respectively to talk to clients.
         */
        class talker;
}

class messenger_server::talker : public threads::thread
{
public:
        void run();
	
        /** 
         * @fn send_update_command
         * @brief sending users status updates
         */
        void send_update_command(const std::string& n, bool status);
        const std::string& get_username() const;
        void receive_data(const command::command& c);
private:
        /** 
         *  @fn set_registration_failed
         * @brief informs that user already exist.
         */
        void set_registration_failed();
        /** @fn set_login_failed
          * @brief inform that user doesn't exist
          */
        void set_login_failed();
        /// On success, user get DONE
        void set_ok();
        /// Parsing commands
        void parse();
        /// Receice commands
        void receive_command();
        /// Send response to user
        void send_response(const std::string&);
        void send_update_status();
        /** @fn handle_register
          * @brief In case if success, user registration is organized,
          * otherwise fails
          */
        void handle_register();
        /** @fn handle_login
          * @brief organized user login if success
          */
        void handle_login();
        /**
         * @fn handle_send_file
         * @brief handle SEND_FILE command  
         */
        void handle_send_request();
        /** @fn handle_logout
          * @brief organized user logout if success
          */
        void handle_logout();
        void handle_users_list();
private:
        messenger_server::server* m_server;
        ipc::socket m_rx;
        ipc::socket m_tx;
        command::command m_command;
        std::string m_response;
        std::string m_user;
        threads::mutex m_mutex;
        bool m_update_required;

public:
	/**
	  *@fn talker
	  *@brief constructor creates talker thread with socket and
	  *socket's duplicates.
	  */
        talker(messenger_server::server* s, ipc::socket r, ipc::socket t);
        virtual ~talker();
};

#endif // MESSENGER_SERVER_TALKER_HPP

