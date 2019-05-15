#include <command/command.hpp>
#include <iostream>
#include <cassert>

int main()
{
        std::string a = "{ \"command\" : \"LOGIN\", \"username\" : \"USER\"}";
        messenger_server::command cmd(a);
        messenger_server::command::type t = cmd.get_command();
        //assert(t = messenger_server::command::type::LOGIN);
        std::cout << t << std::endl;
        std::cout << cmd.get_value("username") << std::endl;
        cmd.set_value("username", "David");
        std::cout << cmd.get_value("username") << std::endl;
        cmd.add_value("age", "sdas");
        std::cout << cmd.get_value("age") << std::endl;
        cmd.remove_key("age");
        std::cout << cmd.get_value("age") << std::endl;
        cmd.append(a);
        std::cout << cmd.get_cmd_str() << std::endl;
        return 0;
}
