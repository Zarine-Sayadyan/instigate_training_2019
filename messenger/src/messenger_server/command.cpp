#include "command.hpp"

QJsonObject messenger_server::command::
str_to_json() const
{
        QString qstr = QString::fromStdString(m_command);
        QJsonDocument json_doc = QJsonDocument::fromJson(qstr.toUtf8());
        QJsonObject json_obj = json_doc.object();
        return json_obj;
}

messenger_server::command::type
messenger_server::command::
get_command() const
{
        QJsonObject json_obj = str_to_json();
        QString cmd = json_obj["command"].toString();
        int n = sizeof(m_cmd)/sizeof(m_cmd[0]);
        auto it = std::find(m_cmd, m_cmd + n, cmd);
        int d = std::distance(m_cmd, it);
        return (type)d;
}

std::string messenger_server::command::
get_cmd_str() const
{
        return m_command;
}

// IN: "username", "status"
// OUT: "USER", "online"
std::string messenger_server::command::
get_value(const std::string& key) const
{
        QJsonObject json_obj = str_to_json();
        QString qkey = QString::fromStdString(key);
        QString cmd = json_obj[qkey].toString();
        return cmd.toStdString();
}

void messenger_server::command::
change_value(const std::string& key, const std::string& value)
{
        QJsonObject json_obj = str_to_json();
        QString qkey = QString::fromStdString(key);
        QString qval = QString::fromStdString(value);
        json_obj[qkey] = qval;
        QJsonDocument qdoc(json_obj);
        QString qstr(qdoc.toJson(QJsonDocument::Compact));
        m_command = qstr.toStdString();
}

void messenger_server::command::
add_value(const std::string& key, const std::string& value)
{
        QJsonObject json_obj = str_to_json();
        QString qkey = QString::fromStdString(key);
        QString qval = QString::fromStdString(value);
        json_obj.insert(qkey,qval);
        QJsonDocument qdoc(json_obj);
        QString qstr(qdoc.toJson(QJsonDocument::Compact));
        m_command = qstr.toStdString();
}

void messenger_server::command::
remove_key(const std::string& key)
{
        QJsonObject json_obj = str_to_json();
        QString qkey = QString::fromStdString(key);
        json_obj.remove(qkey);
        QJsonDocument qdoc(json_obj);
        QString qstr(qdoc.toJson(QJsonDocument::Compact));
        m_command = qstr.toStdString();
}

void messenger_server::command::
append (std::string str)
{
        m_command.pop_back();
        str.erase(0,1);
        m_command = m_command + "," + str;
}


messenger_server::command::
command()
{
        m_command = "{}";
}
messenger_server::command::
command(command::type t)
        : m_command("{}")
{
        int n = sizeof(m_cmd)/sizeof(m_cmd[0]);
        assert(4 == n);
        assert((int)t < n);
        add_value("command", m_cmd[t]);
}

// n is one of these JSON
// { “command” : “REGISTER”, “username” : “USER” }
// { “command” : “LOGIN”, “username” : “USER” }
// { “command” : “UPDATE”, “username” : “USER”, “status” : “online” }
// { “command” : “LOGOUT”, “username” : “USER” }
messenger_server::command::
command(const std::string& n)
        : m_command(n)
{}

messenger_server::command::
~command()
{}

