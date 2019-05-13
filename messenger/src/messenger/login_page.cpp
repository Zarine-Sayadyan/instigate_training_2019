#include "login_page.hpp"

#include <cassert>

QPushButton* login_page::get_ok_button() const
{
        assert(0 != m_button);
        return m_button;
}

login_page::login_page()
          : QWidget()
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

        setFixedSize(700, 500);
        // connect push -> slot sending REGISTER or LOGIN commands
}

login_page::~login_page()
{
}
