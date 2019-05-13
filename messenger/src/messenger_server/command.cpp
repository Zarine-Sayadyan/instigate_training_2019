
#include "command.hpp"


messenger_server::command::type
messenger_server::command::
get_command() const
{
        return REGISTER;
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

