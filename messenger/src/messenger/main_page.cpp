#include "main_page.hpp"
#include "messenger.hpp"
#include "chat_page.hpp"

#include <QFileInfo>
#include <QFileDialog>
#include <cassert>


void main_page::showEvent( QShowEvent* event )
{
        std::cout << "Updating window" << std::endl;
        QWidget::showEvent( event );
}

void main_page::set_username(const std::string& n)
{
        assert(0 != m_user_label);
        m_user_label->setText(n.c_str());

}
/*
std::string main_page::get_selected_username() const
{
        return "";
}

*/
void main_page::append_message(const std::string& m)
{
        assert(0 != m_chat);
        m_chat->append_message(m);
}

void main_page::create_tool_bar(QBoxLayout* l)
{
        assert(0 != l);
        m_tool_bar = new QToolBar();

        m_user_label = new QLabel(m_messenger->get_username().c_str());
        m_tool_bar->addWidget(m_user_label);
        m_logout_button = new QPushButton("logout");

        m_tool_bar->addWidget(m_logout_button);
        l->addWidget(m_tool_bar);

        // h->addWidget(m_user_label);
        // l->addLayout(h);
        // btn_logout = new QPushButton();
        // ml->addWidget(btn_logout);
}

void main_page::create_table(QBoxLayout* l)
{
        //create QTableView
        tblv = new QTableView();
        tblv->setSelectionBehavior(QAbstractItemView::SelectItems);
        tblv->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tblv->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblv->resizeColumnsToContents();
        tblv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //get number of input row and column

        //create model
        QStandardItemModel* model = new QStandardItemModel(0, 2, this);

        QStringList header;
        header << "Names" << "Status";
        model->setHorizontalHeaderLabels(header);
        tblv->setModel(model);

        //fill model value
        assert(0 != m_messenger);
        nrow = m_messenger->get_list_size();
        std::cout << "user list size is" << nrow << std::endl;
        ncol = 2;
        for (int r = 0; r < nrow; r++ ) {
                QString sstr1 = QString::fromStdString(m_messenger->get_first(r));
                std::cout << m_messenger->get_first(r) << std::endl;
                QStandardItem *item1 = new QStandardItem(sstr1);
                QString sstr2 = QString::fromStdString(m_messenger->get_second(r));
                std::cout << m_messenger->get_second(r) << std::endl;
                QStandardItem *item2 = new QStandardItem(sstr2);
                model->setItem(r, 0, item1);
                model->setItem(r, 1, item2);
        }
}


void main_page::get_selected_username(const QModelIndex& index)
{
        QModelIndex i = index.sibling(index.row(),0);
        QString cell_text = i.data().toString();
        m_select_user = cell_text.toStdString();
        std::cout << "Selected user is " << m_select_user << std::endl;
}

main_page::main_page(messenger* m)
        : QWidget()
        , m_messenger(m)
        , tblv(0)
        , nrow(0)
        , ncol(2)
        , m_user_label(0)
        , m_chat(0)
        , m_select_user()

{
        QHBoxLayout* hl = new QHBoxLayout();

        QVBoxLayout* hll = new QVBoxLayout();
        setLayout(hll);


        QVBoxLayout* ml = new QVBoxLayout();
        hl->addLayout(ml);

        QVBoxLayout* cl = new QVBoxLayout();
        hl->addLayout(cl);

        m_chat = new chat_page(m_messenger);
        cl->addWidget(m_chat);
        
        QVBoxLayout* tb = new QVBoxLayout();
        hll->addLayout(tb);
        hll->addLayout(hl);

        create_tool_bar(tb);
        create_table(ml);
        ml->addWidget(tblv);
        QObject::connect(tblv, SIGNAL(clicked(const QModelIndex&)),
                this, SLOT(get_selected_username(const QModelIndex&)));
}









