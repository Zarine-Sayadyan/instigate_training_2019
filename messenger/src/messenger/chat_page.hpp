#ifndef CHAT_HPP
#define CHAT_HPP

#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>

class chat_page : public QWidget
{
        Q_OBJECT
private slots:
        void message_send();
        void open_file();
protected:
        virtual void keyPressEvent(QKeyEvent *);
private:
        QTextEdit* m_text_edit;
        QLineEdit* m_line_edit;
        QPushButton* m_send;
        QPushButton* m_file;
public:
        chat_page(QWidget* parent = 0);
};

#endif // NODEPAD_HPP

