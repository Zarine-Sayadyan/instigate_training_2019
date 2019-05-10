#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>
#include <cstring>

class parser
{
private:
	std::string m_string = "";
	char m_command_delimiter = '?';
	char m_data_separator = '&';
	char m_key_value_separator = '=';

public:
	parser(std::string &str);
	std::string get_command();
	std::vector<std::string> get_data();
	std::string get_value(std::string &key);
};

#endif //PARSER_HPP
