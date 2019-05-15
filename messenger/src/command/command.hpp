#ifndef COMMAND_COMMAND_HPP
#define COMMAND_COMMAND_HPP

/**
 * @file src/command/command.hpp
 * @brief
 */

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

#include <string>

namespace command {
        class command;
}

class command::command : public QObject
{
        Q_OBJECT
public:
       enum  type {REGISTER, LOGIN, LOGOUT, UPDATE};
public:
       bool has_key(const std::string& c) const;
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

#endif // COMMAND_COMMAND_HPP
