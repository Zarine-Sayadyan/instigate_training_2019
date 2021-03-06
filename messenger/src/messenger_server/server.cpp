#include "server.hpp"
#include "talker.hpp"

#include <threads/mutex.hpp>
#include <threads/thread.hpp>
#include <ipc/socket.hpp>

#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>

// {"USER1" : "ONLINE", "USER2" : "OFFLINE" } 
std::string messenger_server::server::get_user_list()
{
        std::string l = "";
        for (auto it = m_users.begin(); it != m_users.end(); ++it) {
                l += " , \"" + it->name +"\" : ";
                if (true  == it->status) {
                        l += "\"online\"";
                } else {
                        l += "\"offline\"";
                }
        }
        l.erase(0, 3);
        l = "{" + l + "}";
        std::cout << "user_list_line= " << l << std::endl;
        return l;
}

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

void messenger_server::server::login_user(const std::string& s)
{
        assert(does_user_exist(s));
        m_mutex.lock();
        for (auto i = m_users.begin(); i != m_users.end(); ++i) {
                if (s == i->name) {
                        assert(false == i->status);
                        i->status = true;
                        break;
                }
        }
        m_mutex.unlock();
}

bool messenger_server::server::get_status(const std::string& s)
{
        assert(does_user_exist(s));
        auto i = m_users.begin();
        for (; i != m_users.end(); ++i) {
                if (s == i->name) {
                        break;
                }
        }
        return i->status;
}

void messenger_server::server::logout_user(const std::string& s)
{
        assert(does_user_exist(s));
        m_mutex.lock();
        for (auto i = m_users.begin(); i != m_users.end(); ++i) {
                if (s == i->name) {
                        assert(true == i->status);
                        i->status = false;
                        break;
                }
        }
        m_mutex.unlock();
}

void messenger_server::server::
send_data_to(const std::string& u, const command::command& c)
{
        assert(command::command::SEND_FILE == c.get_command() || 
               command::command::SEND_MESSAGE == c.get_command());
        assert(does_user_exist(u));
        assert(get_status(u));
        talker* t = 0;
        m_mutex.lock();
        for (auto i = m_talkers.begin(); i != m_talkers.end(); ++i) {
                if ((*i)->get_username() == u) {
                        t = *i;
                        break;
                }
        }
        m_mutex.unlock();
        t->receive_data(c);
}

void messenger_server::server::register_user(const std::string& s)
{
        assert(! does_user_exist(s));
        user u;
        u.name = s;
        u.status = true;
        insert_user(u);
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

void messenger_server::server::insert_user(const messenger_server::user& u)
{
        m_mutex.lock();
        m_users.push_back(u);
        m_mutex.unlock();
        std::cout << "add new user " << u.name << std::endl;
}

void messenger_server::server::insert_talker(messenger_server::talker* t)
{
        m_mutex.lock();
        m_talkers.push_back(t);
        m_mutex.unlock();
}

void messenger_server::server::remove_talker(talker* t)
{
        std::cout << "Delete talker" << std::endl;
        m_mutex.lock();
        auto i = m_talkers.begin();
        for (; i != m_talkers.end(); ++i) {
                if (t == *i) {
                        break;
                }
        }
        assert(t == *i);
        m_talkers.erase(i);
        delete t;
        m_mutex.unlock();
}

void messenger_server::server::run()
{
        assert(m_socket.is_valid());
        while (true) {
                try {
                        ipc::socket c = m_socket.accept();
                        talker* t = new talker(this, c, c.duplicate());
                        t->create_thread(threads::thread::DETACHABLE);
                        insert_talker(t);
                } catch (const char* e) {
                        std::cout << "accept error: " << e << std::endl;
                }
        }
}

messenger_server::server::server(unsigned short port)
        : m_socket(ipc::socket::TCP)
        , m_users()
        , m_talkers()
{
        assert(m_socket.is_valid());
        std::cout << "Server listening on port " << port << std::endl;
        m_socket.bind(port);
        m_socket.listen();
}

messenger_server::server::~server()
{
    // delete talkers
}
