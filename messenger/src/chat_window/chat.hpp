#ifndef CHAT_HPP
#define CHAT_HPP

#include <QObject>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>

class Chat : public QWidget
{
    Q_OBJECT

    public:
        Chat(QWidget * parent = 0);

    private slots:
        void msg_send();
        void openFile();
    protected:
        virtual void keyPressEvent(QKeyEvent *);

    private:
        QLineEdit* line_edit;
        QPushButton* send;
        QPushButton* file;
        QTextEdit* text_edit;
        QTextEdit* send_text;
};

#endif // NODEPAD_HPP

