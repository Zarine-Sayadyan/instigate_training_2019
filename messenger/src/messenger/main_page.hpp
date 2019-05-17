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
        void set_username(const std::string& n);
        void append_message(const std::string& m);
        void fill_model();
        void update_table_view();
        const std::string& get_selected_username() const;
        void clear_messages();
private:
        void create_tool_bar(QBoxLayout* m);
        void create_table(QBoxLayout* m);
        void showEvent(QShowEvent* event); 
private:
        messenger* m_messenger;
        QTableView* m_table;
        QStandardItemModel* m_model;
        QLabel* m_user_label;
        chat_page* m_chat;
        std::string m_select_user;
private slots:
        void logout();
        void set_selected_username(const QModelIndex& index);
public:
        main_page(messenger* m);
};

#endif // MESSENGER_MAIN_PAGE_HPP
