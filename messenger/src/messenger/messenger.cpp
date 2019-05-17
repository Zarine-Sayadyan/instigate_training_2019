
#include "messenger.hpp"
#include <command/command.hpp>

#include <QTimer>
#include <QFileDialog>

#include <iostream>
#include <cassert>

std::string messenger::get_first(int i)
{
        assert(i < (int)m_list.size());
        return m_list[i].first;
}

std::string messenger::get_second(int i)
{
        assert(i < (int)m_list.size());
        return m_list[i].second;
}

int messenger::get_list_size()
{
        return (int)m_list.size();
}

std::string messenger::get_selected_username() const
{
        assert(0 != m_main);
        return m_main->get_selected_username();
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
        command::command c(command::command::SEND_USERS);
        send_command(c.get_cmd_str());
}

void messenger::send_command(const std::string& t)
{
        assert(! t.empty());
        std::cout << "send command=" << t << std::endl;
        m_server.send((const unsigned char*)t.c_str(), (unsigned int)t.size());
}

void messenger::set_username(const std::string& u)
{
        assert(! u.empty());
        m_username = u;
        assert(0 != m_main);
        m_main->set_username(u);
}

std::string messenger::get_username()
{
        return m_username;
}
const std::string& messenger::get_username() const
{
        return m_username;
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
        assert(c.has_key("username"));
        assert(c.has_key("response"));
        std::string r = c.get_value("response");
        assert("DONE" == r || "FAILED" == r);
        assert("FAILED" != r || c.has_key("reason"));
        if ("DONE" == r) {
                set_username(c.get_value("username"));
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
                set_username(c.get_value("username"));
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
        QJsonObject s = c.get_json_value("userlist");
        QJsonDocument doc(s);
        QString str_json(doc.toJson(QJsonDocument::Compact));
        std::cout << "Recieve user list is " <<
                str_json.toStdString() << std::endl;
        command::command k(str_json.toStdString());
        m_list.clear();
        k.parse_list(m_list);
        assert(0 != m_main);
        m_main->fill_model();
        m_main->update();
}

void messenger::handle_update_message(const command::command& c)
{
        (void)c;
        assert(0 != m_main);
        m_main->update_table_view();
}

void messenger::handle_send_message(const command::command& c)
{
        assert(command::command::SEND_MESSAGE == c.get_command());
        assert(c.has_key("to"));
        assert(c.has_key("from"));
        assert(c.has_key("data"));
        assert(0 != m_main);
        if (m_username == c.get_value("to")) {
                std::string data = c.get_value("data");
                m_main->append_message(data);
        } else {
                assert(c.has_key("response"));
                // inform user about message delivery
        }
}

void messenger::receive_file(const command::command& c)
{
        assert(c.has_key("filename"));
        assert(c.has_key("data"));
        std::string f = c.get_value("filename");
        assert(! f.empty());
        assert(0 != m_main);
        QString filepath = QFileDialog::getSaveFileName(m_main, 
                "Save File As...", QString(f.c_str()));
        if (! filepath.isEmpty()) {
                QFile file(filepath);
                std::string data = c.get_value("data");
                QByteArray fileBytes(data.c_str());
                if (file.open(QIODevice::WriteOnly)) {
                        QTextStream stream(&file);
                        stream << QByteArray::fromBase64(fileBytes);
                }
        }
}

/// to handle send file command, it must receive the file
void messenger::handle_send_file(const command::command& c)
{
        assert(command::command::SEND_FILE == c.get_command());
        assert(c.has_key("to"));
        assert(c.has_key("from"));
        assert(c.has_key("filename"));
        assert(c.has_key("data"));
        if (m_username == c.get_value("to")) {
                receive_file(c);
        } else {
                assert(c.has_key("response"));
                // inform user about file delivery
        }
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
                case command::command::SEND_FILE:
                        handle_send_file(c);
                        break;
                case command::command::SEND_USERS:
                        handle_user_list(c);
                        break;
                case command::command::SEND_MESSAGE:
                        handle_send_message(c);
                        break;
                case command::command::UPDATE:
                        handle_update_message(c);
                        break;
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
        , m_username("")
{
        assert(m_server.is_valid());
        m_server.connect("127.0.0.1", 9000);
        m_login = new login_page(this);
        assert(0 != m_login);
        m_main = new main_page(this);
        assert(0 != m_main);
        m_talker = new talker(this, m_server.duplicate());
        assert(0 != m_talker);
        m_talker->create_thread(threads::thread::DETACHABLE);
        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(handle_messages()));
        m_timer->start(500);
}

messenger::~messenger()
{
    delete m_timer;
    delete m_login;
    delete m_main;
}
