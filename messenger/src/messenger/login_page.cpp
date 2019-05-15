#include "login_page.hpp"

#include <cassert>
#include <iostream>

QPushButton* login_page::get_ok_button() const
{
        assert(0 != m_button);
        return m_button;
}
void login_page::keyPressEvent(QKeyEvent* event)
{
        if(event->key() == Qt::Key_Return || Qt::Key_Enter)
        {
                register_or_login();
        }
}

void login_page::show_error(const std::string& e) 
{
        assert(! e.empty());
	assert(0 != m_text);
        m_text->setPlainText(QString(e.c_str()));
}

void login_page::register_or_login()
{
        assert(0 != m_lineedit);
        assert(0 != m_checkBox);
        assert(0 != m_text);
        std::string u = m_lineedit->text().toStdString();
        assert(! u.empty()); // fix this report error
        bool v = m_checkBox->isChecked();
        std::string t = "{\"command\" : ";
        t += v ? "\"REGISTER\"" : "\"LOGIN\"";
        t += ", \"username\" : \"";
        t += u;
        t += "\"}";
        std::cout << "send command="<< t << std::endl;

        // typedef messenger_server::command C;
        // messenger_server::command c("{\"command\" : \"REGISTER"}
        // c.add_data("username", u);
        // std::string f = c.stringify();
        m_server.send((const unsigned char*)t.c_str(), t.size());
}

login_page::login_page(ipc::socket m)
          : QWidget()
          , m_server(m)
          , m_lineedit(0)
          , m_button(0)
          , m_checkBox(0)
          , m_text(0)
{
        QVBoxLayout* vl = new QVBoxLayout(this);
        setLayout(vl);
        QHBoxLayout* hl = new QHBoxLayout;
        vl->addLayout(hl);
        m_lineedit = new QLineEdit(this);
        m_lineedit->setPlaceholderText("Enter Your Name");
        m_lineedit->setStyleSheet("border: 1 solid black; padding-left: 10px;");
        hl->addWidget(m_lineedit);
        m_button = new QPushButton("OK", this);
        m_button->setStyleSheet("border: 1 solid black; border-radius: 15px; color: black;");
        hl->addWidget(m_button);

        m_checkBox = new QCheckBox("New User?", this);
        vl->addWidget(m_checkBox);

        m_text = new QTextEdit("Message Error", this);
        m_text->setReadOnly(true);
        m_text->setStyleSheet("border: 0.5 solid black; padding: 3px; background: #fff;");
        vl->addWidget(m_text);

        QObject::connect(m_button, SIGNAL(clicked()),
                        this, SLOT(register_or_login()));
        setFixedSize(300, 200);

}

login_page::~login_page()
{
}
