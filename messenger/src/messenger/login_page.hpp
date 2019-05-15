#ifndef MESSENGER_LOGIN_PAGE_H
#define MESSENGER_LOGIN_PAGE_H

#include <ipc/socket.hpp>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QKeyEvent>

class login_page : public QWidget
{
        Q_OBJECT

public:
        QPushButton* get_ok_button() const;
	void show_error(const std::string& e);
private:
        void keyPressEvent(QKeyEvent* event);

private slots:
        void register_or_login();
private:
        ipc::socket m_server;
        QLineEdit* m_lineedit;
        QPushButton* m_button;
        QCheckBox* m_checkBox;
        QTextEdit* m_text;

public:
        login_page(ipc::socket s);
        virtual ~login_page();
};

#endif // MESSENGER_LOGIN_PAGE_H
