#ifndef MESSENGER_SERVER_MYCOMMAND_HPP
#define MESSENGER_SERVER_MYCOMMAND_HPP

/**
 * @file messenger_server/command.hpp
 * @brief
 */
#include <QObject>
#include <string>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <algorithm>

namespace messenger_server {
        class command;
}

class messenger_server::command : public QObject
{

    Q_OBJECT

public:
       enum  type {REGISTER, LOGIN, LOGOUT};
public:
       type get_command() const;

       std::string get_value(const std::string& key) const;
private:
       std::string m_command;
       QString m_cmd_arr[3] = {"REGISTER", "LOGIN", "LOGOUT"};
public:
       command(const std::string& n);
       ~command();
};

#endif // MESSENGER_SERVER_MYCOMMAND_HPP
