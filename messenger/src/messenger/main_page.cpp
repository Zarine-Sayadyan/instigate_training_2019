#include "main_page.hpp"
#include "messenger.hpp"
#include "chat_page.hpp"

#include <QFileInfo>
#include <QFileDialog>
#include <cassert>


void main_page::update_table()
{
    set_main_page();
    update();
    std::cout << "updating table" << std::endl;
}

void main_page::showEvent( QShowEvent* event )
{
        std::cout << "Updating window" << std::endl;

        QWidget::showEvent( event );
}

QPushButton* main_page::get_logout() const
{
        return btn_logout;
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

void main_page::create_menubar(QBoxLayout* l)
{
        assert(0 != l);
        QMenuBar* menuBar = new QMenuBar();
        QMenu* fileMenu = new QMenu("Menu");
        menuBar->addMenu(fileMenu);
        fileMenu->addAction("Go Invisible");
        fileMenu->addAction("Logout");
        l->setMenuBar(menuBar);
}

void main_page::create_labels(QBoxLayout* l)
{
        QHBoxLayout* h = new QHBoxLayout;
        QLabel* u = new QLabel("User: ");
        assert(0 != m_messenger);
        m_user_label = new QLabel(m_messenger->get_username().c_str());
        h->addWidget(u);
        h->addWidget(m_user_label);
        l->addLayout(h);
}

void main_page::create_table()
{
        //create QTableView
        tblv = new QTableView();
        tblv->setSelectionBehavior(QAbstractItemView::SelectItems );
        tblv->setSelectionMode( QAbstractItemView::ExtendedSelection );
        tblv->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblv->resizeColumnsToContents();
        tblv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //get number of input row and column
        assert(0 != m_messenger);
        nrow = m_messenger->get_list_size();
        std::cout << "user list size is" << nrow << std::endl;
        ncol = 2;

        //create model
        QStandardItemModel* model = new QStandardItemModel(nrow, ncol, this);

        QStringList header;
        header << "Names" << "Status";
        model->setHorizontalHeaderLabels(header);

        //fill model value
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
        tblv->setModel(model);
}

main_page::main_page(messenger* m)
        : QWidget()
        , m_messenger(m)
{
    set_main_page();
}

void main_page::get_selected_username(const QModelIndex& index)
{
    QModelIndex i = index.sibling(index.row(),0);
    QString cell_text = i.data().toString();
    m_select_user = cell_text.toStdString();
    std::cout << "Selected user is " << m_select_user << std::endl;
}

void main_page::set_main_page()
{
        QHBoxLayout* hl = new QHBoxLayout();
        setLayout(hl);

        QVBoxLayout* ml = new QVBoxLayout();
        hl->addLayout(ml);

        QVBoxLayout* cl = new QVBoxLayout();
        hl->addLayout(cl);

        m_chat = new chat_page(m_messenger);
        cl->addWidget(m_chat);

        create_menubar(hl);
        create_labels(ml);
        create_table();
        ml->addWidget(tblv);
        btn_logout = new QPushButton(tr("Logout"));
        ml->addWidget(btn_logout);
        QObject::connect(tblv, SIGNAL(clicked(const QModelIndex&)),
                this, SLOT(get_selected_username(const QModelIndex&)));
}










