#include "server.hpp"
#include "talker.hpp"

#include <thread.hpp>
#include <socket.hpp>

#include <cassert>
#include <algorithm>

//add_user() ete user goyutyun chuni
void messenger_server::server::login_user(const std::string& user)
{
        auto it = std::find(m_users.begin(), m_users.end(), user);
        if (it == m_users.end()) {
                // m_resronse = "ERROR:No such registered user";
        } else {
                // *it->online;
                //m_response = "UPDATE:user="+user+",status=online";
                //notify(m_response);
        }
}

void messenger_server::server::logout_user()
{
	//user->offline;
}

void messenger_server::server::register_user()
{
	//find_user() -if true than failed.
}

void messenger_server::server::notify()
{
        //for (auto i:m_talkers) {
        //        tx.send(m_respone); //update command
        //}
}

void messenger_server::server::add_user(std::string user)
{
	m_users.push_back(user);
}

void messenger_server::server::insert_talker(messenger_server::talker* t)
{
        // todo add mutex
        m_talkers.push_back(t);
}

void messenger_server::server::run()
{
        assert(m_socket.is_valid());
        while (true) {
                ipc::socket c = m_socket.accept();
                talker* t = new talker(this, c, c/*c.duplicate()*/);
                t->create_thread();
                insert_talker(t);
        }
}

messenger_server::server::server(unsigned short port)
        : m_socket(ipc::socket::TCP)
        , m_users()
        , m_talkers()
{
        assert(m_socket.is_valid());
        m_socket.bind(port);
        m_socket.listen();
}

messenger_server::server::~server()
{
        // delete talkers
}


