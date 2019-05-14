#include "command.hpp"
#include <cassert>

QJsonObject messenger_server::command::
str_to_json() const
{
	QString s = QString::fromStdString(m_command);
	QJsonDocument d = QJsonDocument::fromJson(s.toUtf8());
	QJsonObject obj = d.object();
	return obj;
}

messenger_server::command::type
messenger_server::command::
get_command() const
{
	QJsonObject obj = str_to_json();
	QString cmd = obj["command"].toString();
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
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
	QString cmd = obj[qkey].toString();
	return cmd.toStdString();
}

void messenger_server::command::
set_value(const std::string& key, const std::string& value)
{
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
	QString qval = QString::fromStdString(value);
	obj[qkey] = qval;
	QJsonDocument qdoc(obj);
	QString s(qdoc.toJson(QJsonDocument::Compact));
	m_command = s.toStdString();
}

void messenger_server::command::
add_value(const std::string& key, const std::string& value)
{
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
	QString qval = QString::fromStdString(value);
	obj.insert(qkey, qval);
	QJsonDocument qdoc(obj);
	QString s(qdoc.toJson(QJsonDocument::Compact));
	m_command = s.toStdString();
}

void messenger_server::command::
remove_key(const std::string& key)
{
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
	obj.remove(qkey);
	QJsonDocument qdoc(obj);
	QString s(qdoc.toJson(QJsonDocument::Compact));
	m_command = s.toStdString();
}

void messenger_server::command::
append(std::string str)
{
	assert(! m_command.empty());
	assert('}' == m_command[m_command.size() - 1]);
	m_command.pop_back();
	assert(! str.empty());
	assert('{' == str[0]);
	str.erase(0, 1);
	m_command = m_command + "," + str;
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
command()
	: m_command("{}")
{}

messenger_server::command::
~command()
{}

