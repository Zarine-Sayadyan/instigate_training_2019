#include "command.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>


void command::command::parse_list(std::vector<std::pair<std::string, std::string>>& list)
{
        QJsonObject obj = str_to_json();
        foreach(const QString& key, obj.keys()) {
            QJsonValue val = obj.value(key);
            QString q_val_string = val.toString();
            std::string val_string = q_val_string.toStdString();
            std::pair<std::string,std::string> p;
            p.first = key.toStdString();
            p.second = val_string;
            list.push_back(p);
        }
}

void command::command::set_command(const std::string& s)
{
        m_command = s;
	assert(! m_command.empty());
	assert('{' == m_command[0]);
	assert('}' == m_command[m_command.size() - 1]);
}

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
        // std::cout << "get_command=" << m_command << std::endl;
        assert(has_key("command"));
        QJsonObject obj = str_to_json();
        QString cmd = obj["command"].toString();
        int n = sizeof(m_cmd)/sizeof(m_cmd[0]);
        assert(7 == n);
        auto it = std::find(m_cmd, m_cmd + n, cmd.toStdString());
        int d = (int)std::distance(m_cmd, it);
        // std::cout << "command number is " << d << std::endl;
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

QJsonObject command::command::
get_json_value(const std::string& key) const
{
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
        return obj[qkey].toObject();
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
add_json(const std::string& key, const std::string& value)
{
	QString str = QString::fromStdString(value);
	QJsonDocument d = QJsonDocument::fromJson(str.toUtf8());
	QJsonObject val_obj = d.object();
	QJsonObject obj = str_to_json();
	QString qkey = QString::fromStdString(key);
	obj.insert(qkey, val_obj);
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
	assert(! str.empty());
	assert('{' == str[0]);
	assert('}' == m_command[m_command.size() - 1]);
	QJsonObject obj = str_to_json(); // yet valid object
	m_command.pop_back(); // invalid json
	str.erase(0, 1);
        if (! obj.isEmpty()) {
	        m_command += ",";
        }
	m_command += str;
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
        assert(7 == n);
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

