#include "talker.hpp"
#include "server.hpp"

#include <threads/mutex.hpp>

#include <cassert>
#include <iostream>

const std::string& messenger_server::talker::
get_username() const
{
        return m_user;
}

void messenger_server::talker::handle_users_list()
{
        assert(0 != m_server);
        std::string usr_list = m_server->get_user_list();
        command::command c(m_command.get_cmd_str());
        c.add_value("userlist", usr_list);
        m_response = c.get_cmd_str();
}

void messenger_server::talker::
send_update_command(const std::string& n, bool status)
{
        std::cout << "send update for " << n << std::endl;
        command::command c(command::command::UPDATE);
        c.add_value("username", n);
        c.add_value("status", status ? "online" : "offline");
        send_response(c.get_cmd_str());
}

void messenger_server::talker::set_registration_failed()
{
        command::command r(m_command.get_cmd_str());
        r.add_value("response", "FAILED");
        r.add_value("reason", "User already exists");
        m_response = r.get_cmd_str();
}

void messenger_server::talker::set_login_failed()
{
        assert(0 != m_server);
        assert(! m_server->does_user_exist(m_user) ||
                        m_server->get_status(m_user));
        std::string e = (! m_server->does_user_exist(m_user)) ? 
                "User doesn't exist" : "User is already online";
        command::command r(m_command.get_cmd_str());
        r.add_value("response", "FAILED");
        r.add_value("reason", e);
        m_response = r.get_cmd_str();
}

void messenger_server::talker::set_ok()
{
        command::command r(m_command.get_cmd_str());
        r.add_value("response", "DONE");
        m_response = r.get_cmd_str();
}

// in: { "command" : "REGISTER", "username" : "USER" }
// out:
// { "response" : "DONE"} in case of success
// { "response" : "FAILED", "reason" : "error description"}
void messenger_server::talker::handle_register()
{
        m_user = m_command.get_value("username");
        // std::cout << "handle register user=" << m_user << std::endl;
        assert(! m_user.empty());
        assert(0 != m_server);
        if (m_server->does_user_exist(m_user)) {
                set_registration_failed();
        } else {
                m_server->register_user(m_user);
                set_ok();
        }
}

void messenger_server::talker::handle_login()
{
        assert(command::command::LOGIN == m_command.get_command());
        m_user = m_command.get_value("username");
        assert(! m_user.empty());
        assert(0 != m_server);
        if (m_server->does_user_exist(m_user) &&
                        ! m_server->get_status(m_user)) {
            m_server->login_user(m_user);
            set_ok();
        } else {
            set_login_failed();
        }
}

void messenger_server::talker::handle_logout()
{
        assert(! m_user.empty());
        assert(0 != m_server);
        assert(m_server->get_status(m_user));
        m_server->logout_user(m_user);
        set_ok();
}

void messenger_server::talker::handle_send_file()
{
        assert(command::command::SEND_FILE == m_command.get_command());
        assert(m_command.has_key("from"));
        assert(m_command.has_key("to"));
        std::string to = m_command.get_value("to");
        assert(! to.empty());
        assert(m_server->does_user_exist(to));
        assert(m_server->get_status(to));
        assert(0 != m_server);
        m_server->send_file_to(to, m_command);
        command::command c(m_command.get_cmd_str());
        c.add_value("response", "DONE");
        c.set_value("data", "NONE");
        m_response = c.get_cmd_str();
}

void messenger_server::talker::receive_file(const command::command& c)
{
        assert(command::command::SEND_FILE == c.get_command());
        assert(c.has_key("from"));
        assert(c.has_key("to"));
        assert(c.has_key("filename"));
        assert(c.has_key("data"));
        send_response(c.get_cmd_str());
}

void messenger_server::talker::receive_command()
{
        char message[512];
        memset(message, 0, sizeof(message));
        int r = m_rx.recv((unsigned char*)message, sizeof(message));
        assert(r < (int)sizeof(message));
        assert('\0' == message[r]);
        if ('\0' == message[0]) {
                m_command.set_command();
        } else {
                m_command.set_command(message);
                std::cout << "recv command=" << message << std::endl << std::endl;
                m_response = "";
        }
}

void messenger_server::talker::parse()
{
        command::command::type c = m_command.get_command();
	switch (c) {
                case command::command::REGISTER :
			handle_register();
			break;
                case command::command::LOGIN:
			handle_login();
			break;
                case command::command::LOGOUT:
			handle_logout();
			break;
                case command::command::SEND_FILE:
                        handle_send_file();
                        break;
                case command::command::SEND_USERS :
                        handle_users_list();
                        break;
                default:
                        assert(false);
                        break;
        }
}

void messenger_server::talker::send_response(const std::string& n)
{
        assert(! n.empty());
        assert(m_tx.is_valid());
        std::cout << "response=" << n <<std::endl << std::endl;
        m_mutex.lock();
        try {
                m_tx.send((const unsigned char*)n.c_str(), 
                                (unsigned int)n.size());
        }  catch(const char* s) {
                std::cout << "failed  to send " << std::endl;
        }
        m_mutex.unlock();
}

void messenger_server::talker::run()
{
        try {
                // todo end condition (logout or fail)
                while (1) {
                        receive_command();
                        if (m_command.get_cmd_str() != 
                              command::command().get_cmd_str()) {
                                parse();
                                send_response(m_response);
                        }
                }
        } catch (const char* m) {
                std::cerr << "Talker error: " << m << std::endl;
        }
}

messenger_server::talker::
talker(messenger_server::server* s, ipc::socket r, ipc::socket t)
        : m_server(s)
        , m_rx(r)
        , m_tx(t)
        , m_command()
        , m_response("")
{
        assert(0 != m_server);
        assert(m_rx.is_valid());
        assert(m_tx.is_valid());
}

messenger_server::talker::
~talker()
{}
