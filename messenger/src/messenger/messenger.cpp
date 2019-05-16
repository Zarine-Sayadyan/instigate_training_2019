
#include "messenger.hpp"
#include <command/command.hpp>

#include <QTimer>

#include <iostream>
#include <cassert>

std::string messenger::get_first(int i)
{
    return m_list[i].first;
}

std::string messenger::get_second(int i)
{
    return m_list[i].second;
}

int messenger::get_list_size()
{
    return (int)m_list.size();
}

void messenger::set_name(std::string name) {
    m_name = name;
}

void messenger::show_login()
{
    assert(0 != m_login);
    assert(0 != m_main);
    // assert(m_main->isVisible()); fails on run
    assert(! m_login->isVisible());
    m_main->hide();
    m_login->show();
}

void messenger::show_main()
{
    assert(0 != m_login);
    assert(0 != m_main);
    assert(! m_main->isVisible());
    assert(m_login->isVisible());
    m_login->hide();
    m_main->show();
}

void messenger::push_command(const std::string& str)
{
    m_queue.push(str);
}

std::string messenger::pop_command()
{
    std::string str = m_queue.front();
    m_queue.pop();
    return str;
}

void messenger::request_user_list()
{
    send_command("{\"command\" : \"SEND_USERS\"}");

}

void messenger::send_command(const std::string& t) 
{
    assert(! t.empty());
    std::cout << "send command=" << t << std::endl;
    m_server.send((const unsigned char*)t.c_str(), t.size());
}

// n can be this JSON
// { “command” : “REGISTER”, “username” : “USER”, "response": "DONE"}
// { “command” : “REGISTER”, “username” : “USER”, "response": "FAILED", "reason": "error"}
void messenger::handle_register(const command::command& c)
{
    assert(0 != m_login);
    assert(0 != m_main);
    assert(! m_main->isVisible()); 
    assert(m_login->isVisible());
    assert(command::command::REGISTER == c.get_command());
    assert(c.has_key("response"));
    std::string r = c.get_value("response");
    assert("DONE" == r || "FAILED" == r);
    assert("FAILED" != r || c.has_key("reason"));
    if ("DONE" == r) {
        show_main();
    } else {
        std::string e = c.get_value("reason"); 
        assert(! e.empty());
        m_login->show_error(e);
    }
}

void messenger::handle_login(const command::command& c)
{
    assert(0 != m_login);
    assert(0 != m_main);
    assert(! m_main->isVisible()); 
    assert(m_login->isVisible());
    assert(command::command::LOGIN == c.get_command());
    assert(c.has_key("response"));
    std::string r = c.get_value("response");
    assert("DONE" == r || "FAILED" == r);
    assert("FAILED" != r || c.has_key("reason"));
    if ("DONE" == r) {
        show_main();
    } else {
        std::string e = c.get_value("reason"); 
        assert(! e.empty());
        m_login->show_error(e);
    }
}

void messenger::handle_logout(const command::command& c)
{
    assert(0 != m_login);
    assert(0 != m_main);
    assert(m_main->isVisible()); 
    assert(!m_login->isVisible());
    assert(command::command::LOGOUT == c.get_command());
    assert(c.has_key("response"));
    std::string r = c.get_value("response");
    assert("DONE" == r || "FAILED" == r);
    assert("FAILED" != r || c.has_key("reason"));
    if ("DONE" == r) {
        show_login();
    } else {
        std::string e = c.get_value("reason"); 
        assert(! e.empty());
        m_login->show_error(e);
    }
}

void messenger::handle_user_list(const command::command& c)
{
    assert(command::command::SEND_USERS == c.get_command());
    assert(c.has_key("userlist"));
    std::string s = c.get_value("userlist");
    command::command k(s);
    m_list.clear();
    k.parse_list(m_list);
}


// n can be this JSON
// { “command” : “REGISTER”, “username” : “USER”, "response": "DONE"}
// { “command” : “REGISTER”, “username” : “USER”, "response": "FAILED", "reason": "error"}
void messenger::parse(const std::string& s)
{
    assert(! s.empty());
    assert('{' == s[0]);
    assert('}' == s[s.size() -1]);
    command::command c(s);
    command::command::type t = c.get_command();
    switch (t) {
        case command::command::REGISTER :
            handle_register(c);
            break;
        case command::command::LOGIN:
            handle_login(c);
            break;
        case command::command::LOGOUT:
            handle_logout(c);
            break;
            // case command::command::SEND_FILE:
            // my name is to
            // open_save_as_dialog("filename", )
            // open file write from base64
        case command::command::SEND_USERS :
            handle_user_list(c);
        default:
            assert(false);
            break;
    }

}

void messenger::handle_messages()
{
    if (! m_queue.empty()) {
        std::string str = pop_command();
        parse(str);
    }
}

//constructor and destructor
messenger::messenger()
    : m_server(ipc::socket::TCP)
    , m_talker(0)
    , m_login(0)
    , m_main(0)
      , m_timer(0)
{
    assert(m_server.is_valid());
    m_server.connect("127.0.0.1", 9000);
    m_login = new login_page(this);
    assert(0 != m_login);
    m_main = new main_page(this);
    assert(0 != m_main);
    m_talker = new talker(this, m_server.duplicate());
    assert(0 != m_talker);
    m_talker->create_thread();
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(handle_messages()));
    m_timer->start(500);

    //QObject::connect(m_login->get_ok_button(), SIGNAL(clicked()),
    //              this, SLOT(show_main()));
    // QObject::connect(m_main->get_logout(), SIGNAL(clicked()),
    //             this, SLOT(show_login()));
}

messenger::~messenger()
{
    delete m_timer;
    delete m_login;
    delete m_main;
}
