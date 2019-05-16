#include "chat_page.hpp"
#include "messenger.hpp"

#include <QString>
#include <QShortcut>
#include <QKeyEvent>
#include <QFileDialog>

#include <iostream>
#include <cassert>

void chat_page::keyPressEvent(QKeyEvent *event)
{
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
                send_message();
        }
}

void chat_page::append_message(const std::string& m)
{
        assert(0 != m_text_edit);
        m_text_edit->setAlignment(Qt::AlignLeft);
        m_text_edit->append(m.c_str());
}

void chat_page::send_message()
{
        if (m_line_edit->text().isEmpty()) {
                return;
        }
        m_text_edit->setAlignment(Qt::AlignRight);
        QString m = m_line_edit->text();
        m_text_edit->append(m);
        m_line_edit->clear();
        m_line_edit->setFocus();
        assert(0 != m_messenger);
        command::command c(command::command::SEND_MESSAGE);
        assert(! m_messenger->get_username().empty());
        assert(! m_messenger->get_selected_username().empty());
        c.add_value("from", m_messenger->get_username());
        c.add_value("to", m_messenger->get_selected_username());
        c.add_value("data", m.toStdString());
        m_messenger->send_command(c.get_cmd_str());
}

// attach file click handler
void chat_page::send_file()
{
        assert(0 != m_messenger);
        command::command c(command::command::SEND_FILE);
        assert(! m_messenger->get_username().empty());
        assert(! m_messenger->get_selected_username().empty());
        c.add_value("from", m_messenger->get_username());
        c.add_value("to", m_messenger->get_selected_username());
        QString f = QFileDialog::getOpenFileName(this, "Select file to send",
                QDir::currentPath(), "All files (*.*)");
        if (! f.isNull() ) {
                c.add_value("filename", 
                                QFileInfo(f).completeBaseName().toStdString());
                QFile file(f);
                file.open(QFile::ReadOnly);
                QByteArray fileBytes = file.readAll();
                c.add_value("data", fileBytes.toBase64().data());
                m_messenger->send_command(c.get_cmd_str());
                assert(m_text_edit);
                m_text_edit->setAlignment(Qt::AlignRight);
                m_text_edit->append(f);
        }
}

chat_page::chat_page(messenger* m, QWidget* parent)
        : QWidget(parent)
        , m_messenger(m)
{
        setWindowTitle("Chat");
        setFixedSize(700, 500);
        m_text_edit = new QTextEdit;
        m_text_edit->setReadOnly(true);
        m_line_edit = new QLineEdit;
        m_line_edit->resize(200, 20);
        m_send = new QPushButton("Send");
        m_file = new QPushButton("Send File");
        // m_file->setIcon(QIcon("images.png"));
        m_file->setFixedSize(80, 30);
        m_send->setFixedSize(80, 30);
        QGridLayout* layout = new QGridLayout;
        layout->addWidget(m_text_edit, 0, 0, 1, 4);
        layout->addWidget(m_line_edit, 1, 1, 1, 2);
        layout->addWidget(m_send, 1, 3);
        layout->addWidget(m_file, 1, 0);
        setLayout(layout);
        QObject::connect(m_send, SIGNAL(clicked()), SLOT(send_message()));
        QObject::connect(m_file, SIGNAL(clicked()), SLOT(send_file()));
        m_line_edit->setFocus();
}
