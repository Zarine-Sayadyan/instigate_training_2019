#ifndef MESSENGER_MAIN_PAGE_HPP
#define MESSENGER_MAIN_PAGE_HPP

#include <iostream>
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
        void set_username(const std::string& n);
        void append_message(const std::string& m);
        void update_table();
private:
        void set_main_page();
        void create_menubar(QBoxLayout* m);
        void create_labels(QBoxLayout* m);
        void create_table();
        void showEvent(QShowEvent* event); 
private:
        std::string m_select_user;
        messenger* m_messenger;
        QTableView* tblv;
        QLabel* m_user_label;
        QPushButton *btn_logout;
        int nrow, ncol;
        chat_page* m_chat;
private slots:
        void get_selected_username(const QModelIndex& index);
public:
        main_page(messenger* m);
};

#endif // MESSENGER_MAIN_PAGE_HPP
