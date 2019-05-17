#ifndef CHAT_PAGE_HPP
#define CHAT_PAGE_HPP

#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>

class messenger;

class chat_page : public QWidget
{
        Q_OBJECT
public:
        void append_message(const std::string& m);
        void enable_buttons(bool b);

private slots:
        void send_message();
        void send_file();
protected:
        virtual void keyPressEvent(QKeyEvent *);
private:
        messenger* m_messenger;
        QTextEdit* m_text_edit;
        QLineEdit* m_line_edit;
        QPushButton* m_send;
        QPushButton* m_file;
public:
        chat_page(messenger* m, QWidget* parent = 0);

};

#endif

