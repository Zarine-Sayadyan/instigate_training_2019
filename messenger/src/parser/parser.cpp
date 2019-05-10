#include "parser.hpp"
#include <cstring>

parser::parser(std::string &str)
		: m_string(str)
{
}
std::string parser::get_command()
{
	std::size_t pos = m_string.find(m_command_delimiter);
	if(string::npos == pos){
		return "";
	}
	return m_string.substr(0, pos);
}

std::vector<std::string> parser::get_data()
{
	std::vector<std::string> str_vec;
	std::string str = "";
	std::size_t pos_from = m_string.find(m_command_delimiter);
	std::size_t pos_to;
	if(std::string::npos == pos_from){
	    str_vec.push_back("");
	}
	do
	{
	    pos_to = m_string.find(m_data_separator, ++pos_from);
	    str_vec.push_back(m_string.substr(pos_from, pos_to - pos_from));
	    pos_from = pos_to;
	} while (std::string::npos != pos_to);
	return str_vec;
}

std::string parser::get_value(std::string &key)
{
}