#include "server.hpp"
#include "talker.hpp"

#include <thread.hpp>
#include <socket.hpp>
#include <cstring>
#include <cassert>
#include <algorithm>

bool messenger_server::server::does_user_exist(const std::string& name) const
{
    for (auto it = m_users.begin(); it != m_users.end(); ++it) {
        if (name == (*it).m_name) {
            return true;
        }
    }
    return false;

}

//add_user() ete user goyutyun chuni
void messenger_server::server::login_user(const std::string& user)
{
    if (!does_user_exist(user)) {
        // m_response = "ERROR:No such registered user";
    } else {
            for (auto it = m_users.begin(); it != m_users.end(); ++it) {
                    if (user == (*it).m_name) {
                            (*it).m_status = true;
                            break;
                    }
    }
        // *it->online;
        //m_response = "UPDATE:user="+user+",status=online";
        //notify(m_response);
    }
}

void messenger_server::server::logout_user(const std::string& user)
{
        for (auto it = m_users.begin(); it != m_users.end(); ++it) {
                if (user == (*it).m_name) {
                        (*it).m_status = false;
                        break;
                }
        }
        //user->offline;
}

void messenger_server::server::register_user(const std::string& username)
{
        if (! does_user_exist(username)) {
                user u;
                u.m_name = username;
                u.m_status = true;
                m_users.push_back(u);
        }  else {
                //error
        }
}

void messenger_server::server::notify()
{
    //for (auto i:m_talkers) {
    //        tx.send(m_respone); //update command
    //}
}

void messenger_server::server::add_user(const std::string& user)
{
        (void)user;
    //m_users.push_back(user);
    // m_users[user] = true;
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


