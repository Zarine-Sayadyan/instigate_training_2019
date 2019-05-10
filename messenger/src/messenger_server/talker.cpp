
#include "talker.hpp"
#include "server.hpp"

#include <cassert>
#include <iostream>

void messenger_server::talker::parse()
{
        /*
	switch (command_name) {
		case REGISTER :
			handle_register(); // m_server->register_user();
			break;
		case LOGIN:
			handle_login(); // m_server->login_user();
			break;
		case LOGOUT:
			handle_logout(); //m_server->logout_user();
			break;
	}*/
}

void messenger_server::talker::receive_command()
{}

void messenger_server::talker::send_response()
{}


void messenger_server::talker::run()
{
        try {
                // todo end condition (logout or fail)
                while (1) {
                        receive_command();
                        parse();
                        send_response();
                }
        } catch(const char* m) {
                std::cerr << "Talker error: " << m << std::endl;
        }
}

messenger_server::talker::
talker(messenger_server::server* s, ipc::socket r, ipc::socket t)
        : m_server(s)
        , m_client_socket(r)
        , m_server_socket(t)
{
        assert(0 != m_server);
        assert(m_client_socket.is_valid());
        assert(m_server_socket.is_valid());
}

messenger_server::talker::
~talker()
{}
