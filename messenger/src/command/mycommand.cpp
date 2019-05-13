
#include "mycommand.hpp"


messenger_server::command::type
messenger_server::command::
get_command() const
{
    QString qstr = QString::fromStdString(m_command);
    QJsonDocument json_doc = QJsonDocument::fromJson(qstr.toUtf8());
    QJsonObject json_obj = json_doc.object();
    QString cmd = json_obj["command"].toString();
    int n = sizeof(m_cmd_arr)/sizeof(m_cmd_arr[0]);
    auto it = std::find(m_cmd_arr, m_cmd_arr + n, cmd);
    int d = std::distance(m_cmd_arr, it);
    return (type)d;
}

// IN: "username", "status"
// OUT: "USER", "online"
std::string messenger_server::command::
get_value(const std::string& key) const
{
        (void)key;
        return "";
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

