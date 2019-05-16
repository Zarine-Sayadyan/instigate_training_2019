#ifndef MESSENGER_MESSENGER_HPP
#define MESSENGER_MESSENGER_HPP

#include "login_page.hpp"
#include "main_page.hpp"
#include "talker_client.hpp"

#include <ipc/socket.hpp>
#include <command/command.hpp>

#include <QObject>
#include <QTimer>

#include <queue>
#include <string>
#include <vector>
#include <utility>

class messenger : public QObject
{
        Q_OBJECT
public slots:
        void show_login();
        void show_main();
private:
        ipc::socket m_server;
        talker* m_talker;
        login_page* m_login;
        main_page* m_main;
        QTimer* m_timer;
        std::queue<std::string> m_queue;
        std::vector<std::pair<std::string, std::string>> m_list;
        std::string m_name;
public:
        void set_name (std::string str);
        void push_command(const std::string& str);
        std::string pop_command();
        void send_command(const std::string& t);
        int get_list_size();
        std::string get_first(int i);
        std::string get_second(int i);

private slots:
        void handle_messages();
private:
        void parse(const std::string& str);
        void handle_register(const command::command& c);
        void handle_login(const command::command& c);
        void handle_logout(const command::command& c);
        void handle_user_list(const command::command& c);
        void request_user_list();

public:
        messenger();
        virtual ~messenger();
};

#endif // MESSENGER_MESSENGER_HPP

