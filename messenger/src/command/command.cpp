#include "command.hpp"
#include <algorithm>
#include <cassert>

QJsonObject command::command::
str_to_json() const
{
	QString s = QString::fromStdString(m_command);
	QJsonDocument d = QJsonDocument::fromJson(s.toUtf8());
	QJsonObject obj = d.object();
	return obj;
}

command::command::type
command::command::
get_command() const
{
        QJsonObject obj = str_to_json();
        QString cmd = obj["command"].toString();
        int n = sizeof(m_cmd)/sizeof(m_cmd[0]);
        auto it = std::find(m_cmd, m_cmd + n, cmd);
        int d = (int)std::distance(m_cmd, it);
        return (type)d;
}

bool command::command::has_key(const std::string& c) const
{
        QJsonObject obj = str_to_json();
	QString qstr = QString::fromStdString(c);
	bool k = obj.contains(qstr);
	return k;        
}

std::string command::command::
get_cmd_str() const
{
        return m_command;
}

// IN: "username", "status"
// OUT: "USER", "online"
std::string command::command::
get_value(const std::string& key) const
{
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
	QString cmd = obj[qkey].toString();
	return cmd.toStdString();
}

void command::command::
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

void command::command::
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

void command::command::
remove_key(const std::string& key)
{
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
	obj.remove(qkey);
	QJsonDocument qdoc(obj);
	QString s(qdoc.toJson(QJsonDocument::Compact));
	m_command = s.toStdString();
}

void command::command::
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

command::command::
command()
{
        m_command = "{}";
}

command::command::
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
command::command::
command(const std::string& n)
        : m_command(n)
{
	assert(! m_command.empty());
	assert('{' == m_command[0]);
	assert('}' == m_command[m_command.size() - 1]);
}

command::command::
~command()
{}

