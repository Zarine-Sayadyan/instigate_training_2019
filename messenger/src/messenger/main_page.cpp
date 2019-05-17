#include "main_page.hpp"
#include "messenger.hpp"
#include "chat_page.hpp"

#include <QToolBar>
#include <QSpacerItem>
#include <QFileInfo>
#include <QFileDialog>
#include <QSplitter>
#include <cassert>

void main_page::update_table_view()
{
        assert(0 != m_messenger);
        m_messenger->request_user_list();
        assert(0 != m_chat);
        m_chat->enable_buttons(false);
}

void main_page::showEvent(QShowEvent* event)
{
        std::cout << "Updating window" << std::endl;
        update_table_view();
        QWidget::showEvent(event);
}

void main_page::set_username(const std::string& n)
{
        assert(0 != m_user_label);
        m_user_label->setText(n.c_str());
}

void main_page::logout()
{
        command::command c(command::command::LOGOUT);
        //c.add_value("username", m_messenger->get_username());
        m_messenger->send_command(c.get_cmd_str());
}


void main_page::append_message(const std::string& m)
{
        assert(0 != m_chat);
        m_chat->append_message(m);
}

void main_page::create_tool_bar(QBoxLayout* l)
{
        assert(0 != l);
        assert(0 != m_messenger);
        QToolBar* tb = new QToolBar();
        l->addWidget(tb);
        QLabel* user = new QLabel("User: ");
        m_user_label = new QLabel(m_messenger->get_username().c_str());
        
        QPushButton* button = new QPushButton("Logout");
        QObject::connect(button, SIGNAL(clicked()),
                this, SLOT(logout()));
        tb->addWidget(user);
        tb->addWidget(m_user_label);
        tb->addWidget(button);
}

void main_page::fill_model()
{
        assert(0 != m_model);
        m_model->clear();
        QStringList header;
        header << "Names" << "Status";
        m_model->setHorizontalHeaderLabels(header);
        assert(0 != m_table);
        assert(0 != m_messenger);
        int nrow = m_messenger->get_list_size();
        for (int r = 0; r < nrow; r++) {
                QString u = QString::fromStdString(m_messenger->get_first(r));
                QStandardItem* i1 = new QStandardItem(u);
                QString st = QString::fromStdString(m_messenger->get_second(r));
                QStandardItem* i2 = new QStandardItem(st);
                m_model->setItem(r, 0, i1);
                m_model->setItem(r, 1, i2);
        }
}

void main_page::create_table(QBoxLayout* l)
{
        assert(0 == m_table);
        m_table = new QTableView;
        m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
        m_table->setSelectionMode(QAbstractItemView::ExtendedSelection);
        m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        m_table->resizeColumnsToContents();
        m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        assert(0 == m_model);
        m_model = new QStandardItemModel(0, 2, this);
        m_table->setModel(m_model);
        l->addWidget(m_table);
        QObject::connect(m_table, SIGNAL(clicked(const QModelIndex&)),
                this, SLOT(set_selected_username(const QModelIndex&)));
}

const std::string& main_page::get_selected_username() const
{
        return m_select_user;
}

void main_page::clear_messages()
{
        assert(0 != m_chat);
        assert(0 != m_chat->get_text_edit());
        m_chat->get_text_edit()->clear(); 
}

void main_page::set_selected_username(const QModelIndex& index)
{
        QModelIndex i = index.sibling(index.row(), 0);
        QModelIndex si = index.sibling(index.row(), 1);
        QString user_text = i.data().toString();
        QString stat_text = si.data().toString();
        if (m_select_user != user_text.toStdString()) {
                m_select_user = user_text.toStdString();
                assert(! m_select_user.empty());
                assert(0 != m_chat);
                if (stat_text == QString("online")) {
                        m_chat->enable_buttons(true);
                }
                clear_messages();
        }
}

main_page::main_page(messenger* m)
        : QWidget()
        , m_messenger(m)
        , m_table(0)
        , m_model(0)
        , m_user_label(0)
        , m_chat(0)
        , m_select_user("")
{
        QVBoxLayout* ml = new QVBoxLayout;
        setLayout(ml);

        QHBoxLayout* tl = new QHBoxLayout;
        create_tool_bar(tl);
        ml->addLayout(tl);

        QHBoxLayout* l = new QHBoxLayout;
        ml->addLayout(l);
        create_table(l);
        m_chat = new chat_page(m_messenger);
        l->addWidget(m_chat);

}

