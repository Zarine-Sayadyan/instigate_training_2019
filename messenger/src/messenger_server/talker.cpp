#include "talker.hpp"
#include "server.hpp"

#include <cassert>
#include <iostream>


void messenger_server::talker::
send_update_command(const std::string& n, bool status)
{
        // m_server_socket.send();
}

void messenger_server::talker::set_registration_failed()
{
        m_response = "{ \"response\" : \"FAILED\", \"reason\" : \"User already exists\"}";
}

void messenger_server::talker::set_login_failed()
{
        /// add already login fault
        m_response = "{ \"response\" : \"FAILED\", \"reason\" : \"User doesn't exist\"}";
}

void messenger_server::talker::set_ok()
{
        m_response = "{ \"response\" : \"DONE\"}";
}



// in: { "command" : "REGISTER", "username" : "USER" }
// out:
// { "response" : "DONE"} in case of success
// { "response" : "FAILED", "reason" : "error description"}
void messenger_server::talker::handle_register()
{
        m_user = m_command.get_value("username");
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

void messenger_server::talker::receive_command()
{
        char message[512];
        int r = m_client_socket.recv((unsigned char*)message, sizeof(message));
        assert(r < (int)sizeof(message));
        assert('\0' == message[r]);
        m_command.append(message);
}

void messenger_server::talker::parse()
{
        command::type c = m_command.get_command();
	switch (c) {
                case command::REGISTER :
			handle_register();
			break;
		case command::LOGIN:
			handle_login();
			break;
                case command::LOGOUT:
			handle_logout();
			break;
                default:
                        assert(false);
                        break;
        }
}

void messenger_server::talker::send_response()
{
        assert(! m_response.empty());
        assert(m_client_socket.is_valid());
        // m_response.size();
}

void messenger_server::talker::run()
{
        try {
                // todo end condition (logout or fail)
                while (1) {
                        receive_command();
                        parse();
                        send_response();
                }
        } catch (const char* m) {
                std::cerr << "Talker error: " << m << std::endl;
        }
}

messenger_server::talker::
talker(messenger_server::server* s, ipc::socket r, ipc::socket t)
        : m_server(s)
        , m_client_socket(r)
        , m_server_socket(t)
        , m_command()
        , m_response("")
{
        assert(0 != m_server);
        assert(m_client_socket.is_valid());
        assert(m_server_socket.is_valid());
}

messenger_server::talker::
~talker()
{}
