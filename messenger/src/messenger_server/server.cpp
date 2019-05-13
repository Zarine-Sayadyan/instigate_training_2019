#include "server.hpp"
#include "talker.hpp"

#include <mutex.hpp>
#include <thread.hpp>
#include <socket.hpp>
#include <cstring>
#include <cassert>
#include <algorithm>

bool messenger_server::server::does_user_exist(const std::string& name)
{

        m_mutex.lock();
        for (auto i = m_users.begin(); i != m_users.end(); ++i) {
                if (name == i->name) {
                        m_mutex.unlock();
                        return true;
                }
        }
        m_mutex.unlock();
        return false;
}

//add_user() ete user goyutyun chuni
void messenger_server::server::login_user(const std::string& s)
{
        assert(does_user_exist(s));
        m_mutex.lock();
        for (auto i = m_users.begin(); i != m_users.end(); ++i) {
                if (s == i->name) {
                        i->status = true;
                        break;
                }
        }
        m_mutex.unlock();
        update_status(s);
}

void messenger_server::server::logout_user(const std::string& s)
{
        m_mutex.lock();
        for (auto i = m_users.begin(); i != m_users.end(); ++i) {
                if (s == i->name) {
                        i->status = false;
                        break;
                }
        }
        m_mutex.unlock();
        update_status(s);
}

void messenger_server::server::register_user(const std::string& s)
{
        assert(! does_user_exist(s));
        user u;
        m_mutex.lock();
        u.name = s;
        u.status = true;
        insert_user(u);
        m_mutex.unlock();
        update_status(u.name);
}

void messenger_server::server::update_status(const std::string& s)
{
        assert(! s.empty());
        assert(does_user_exist(s));
        user u;
        m_mutex.lock();
        for (auto i = m_users.begin(); i != m_users.end(); ++i) {
                if (s == i->name) {
                        u = *i;
                        break;
                }
        }
        for (auto i = m_talkers.begin(); i != m_talkers.end(); ++i) {
                (*i)->send_update_command(u.name, u.status);
        }
        m_mutex.unlock();
}

void messenger_server::server::insert_talker(messenger_server::talker* t)
{
        m_mutex.lock();
        m_talkers.push_back(t);
        m_mutex.unlock();
}

void messenger_server::server::insert_user(const messenger_server::user& u)
{
        m_mutex.lock();
        m_users.push_back(u);
        m_mutex.unlock();
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


