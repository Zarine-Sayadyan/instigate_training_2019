#ifndef MESSENGER_SERVER_COMMAND_HPP
#define MESSENGER_SERVER_COMMAND_HPP

/**
 * @file messenger_server/command.hpp
 * @brief
 */

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

#include <algorithm>
#include <string>

namespace messenger_server {
        class command;
}

class messenger_server::command : public QObject
{

    Q_OBJECT

public:
       enum  type {REGISTER, LOGIN, LOGOUT, UPDATE};
public:
       type get_command() const;
       std::string get_value(const std::string& key) const;
       void set_value(const std::string& key, const std::string& value);
       void add_value(const std::string& key, const std::string& value);
       void remove_key(const std::string& key);
       void append(std::string str);
       std::string get_cmd_str() const;
private:
       std::string m_command;
       const char* m_cmd[4] = {"REGISTER", "LOGIN", "LOGOUT", "UPDATE"};
private:
       QJsonObject str_to_json() const;
public:
       command();
       command(type t);
       command(const std::string& n);
       ~command();
};

#endif // MESSENGER_SERVER_COMMAND_HPP
