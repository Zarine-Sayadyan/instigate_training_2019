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
        std::string m_username;
        std::queue<std::string> m_queue;
public:
        void push_command(const std::string& str);
        std::string pop_command();
        void send_command(const std::string& t);
	const std::string& get_username() const;
	void set_username(const std::string& u);

private slots:
        void handle_messages();
private:
        void parse(const std::string& str);
        void handle_register(const command::command& c);
        void handle_login(const command::command& c);
        void handle_logout(const command::command& c);

public:
        messenger();
        virtual ~messenger();
};

#endif // MESSENGER_MESSENGER_HPP

