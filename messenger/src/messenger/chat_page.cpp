#include "chat_page.hpp"

#include <QString>
#include <QShortcut>
#include <QKeyEvent>
#include <QFileDialog>

#include <iostream>

void chat_page::keyPressEvent(QKeyEvent *event)
{
        std::cout << "enter pressed" << std::endl;
        if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
                message_send();
        }
}

void chat_page::message_send()
{
        if (! m_line_edit->text().isEmpty()) {
                m_text_edit->setAlignment(Qt::AlignRight);
                m_text_edit->append(m_line_edit->text());
                m_line_edit->clear();
                m_line_edit->setFocus();
        }
}
void chat_page::open_file()
{
        QString filename =  QFileDialog::getOpenFileName(
                        this,
                        "Open Document",
                        QDir::currentPath(),
                        "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");
        if (! filename.isNull() ) {
                m_text_edit->setAlignment(Qt::AlignRight);
                m_text_edit->append(filename);
        }
}

chat_page::chat_page(QWidget* parent)
        : QWidget(parent)
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
        QObject::connect(m_send, SIGNAL(clicked()), SLOT(message_send()));
        QObject::connect(m_file, SIGNAL(clicked()), SLOT(open_file()));
        m_line_edit->setFocus();
}
