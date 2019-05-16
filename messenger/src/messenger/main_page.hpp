#ifndef MESSENGER_MAIN_PAGE_HPP
#define MESSENGER_MAIN_PAGE_HPP

#include <QtGui>
#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QString>
#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QHeaderView>
#include <QToolBar>
#include <QMenuBar>

class messenger;
class chat_page;

class main_page : public QWidget
{
        Q_OBJECT
public:
        QPushButton* get_logout() const;
private:
        std::string get_selected_username() const;
        void create_menubar(QBoxLayout* m);
        void create_labels(QBoxLayout* m);
        void create_table_headers(QBoxLayout* m);
        void create_table(QBoxLayout* m);
private:
        messenger* m_messenger;
        QTableView* tblv;
        QLabel *label11, *label12, *label21, *label22;
        QPushButton *btn_logout;
        int nrow, ncol;
        chat_page* m_chat;

private slots:
        void send_file();
public:
        main_page(messenger* m);
};

#endif // MESSENGER_MAIN_PAGE_HPP
