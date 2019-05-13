#ifndef MESSENGER_SERVER_COMMAND_HPP
#define MESSENGER_SERVER_COMMAND_HPP

/**
 * @file messenger_server/command.hpp
 * @brief
 */
#include <string>

namespace messenger_server {
        class command;
}

class messenger_server::command
{
public:
       enum  type {REGISTER, LOGIN, LOGOUT};
public:
       type get_command() const;

       std::string get_value(const std::string& key) const;
private:
       std::string m_command;
public:
       command(const std::string& n);
       ~command();
};

#endif // MESSENGER_SERVER_COMMAND_HPP
