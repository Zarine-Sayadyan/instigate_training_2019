#ifndef MESSENGER_LOGIN_PAGE_H
#define MESSENGER_LOGIN_PAGE_H


#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QKeyEvent>

class  messenger;

class login_page : public QWidget
{
        Q_OBJECT

public:
	void show_error(const std::string& e);
private:
        void keyPressEvent(QKeyEvent* event);

private slots:
        void register_or_login();
private:
        messenger* m_messenger;
        QLineEdit* m_lineedit;
        QPushButton* m_button;
        QCheckBox* m_checkBox;
        QTextEdit* m_text;

public:
        login_page(messenger* m);
        virtual ~login_page();
};

#endif // MESSENGER_LOGIN_PAGE_H
