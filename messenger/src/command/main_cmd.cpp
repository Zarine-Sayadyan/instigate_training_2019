#include "mycommand.hpp"

int main()
{
    std::string a = "{ \"command\" : \"REGISTER\", \"username\" : \"USER\"}";
    // messenger_server::command::type b = messenger_server::command::get_command(a);
    // std::cout<< (int) b << std::endl;
    (void)a;
    return 0;
}
