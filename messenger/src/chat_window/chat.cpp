#include "chat.hpp"
#include <QString>
#include <QShortcut>
#include <QKeyEvent>
#include <QFileDialog>

Chat::Chat(QWidget * parent):
    QWidget(parent)
{
    text_edit = new QTextEdit;
    text_edit->setReadOnly(true);
    this->setFixedSize(700, 500);
    line_edit = new QLineEdit;
    line_edit->resize(200, 20);
    send = new QPushButton("Send");
    file = new QPushButton;
    file->setIcon(QIcon("images.png"));
    file->setFixedSize(30, 30);
    send->setFixedSize(80, 30);
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(text_edit, 0, 0, 1, 4);
    layout->addWidget(line_edit, 1, 1, 1, 2);
    layout->addWidget(send, 1, 3);
    layout->addWidget(file, 1, 0);
    setLayout(layout);
    setWindowTitle("Chat");
    QObject::connect(send, SIGNAL(clicked()), SLOT(msg_send()));
    QObject::connect(file, SIGNAL(clicked()), SLOT(openFile()));
    line_edit->setFocus();
}

void Chat::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        msg_send();
    }
}

void Chat::msg_send()
{
    if (!line_edit->text().isEmpty()) {
        text_edit->setAlignment(Qt::AlignRight);
        text_edit->append(line_edit->text());
        line_edit->clear();
        line_edit->setFocus();
    }
}

void Chat::openFile()
{
    QString filename =  QFileDialog::getOpenFileName(
            this,
            "Open Document",
            QDir::currentPath(),
            "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");
    if ( !filename.isNull() ) {
        text_edit->setAlignment(Qt::AlignRight);
        text_edit->append(filename);
    }
}
