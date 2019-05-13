#ifndef MESSENGER_LOGIN_PAGE_H
#define MESSENGER_LOGIN_PAGE_H

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

class login_page : public QWidget
{
        Q_OBJECT

public:
        QPushButton* get_ok_button() const;
private:
        QLineEdit* m_lineedit;
        QPushButton* m_button;
        QCheckBox* m_checkBox;
        QTextEdit* m_text;

public:
        explicit login_page();
        virtual ~login_page();
};

#endif // MESSENGER_LOGIN_PAGE_H
