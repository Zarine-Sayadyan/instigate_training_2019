#include "main_page.hpp"
#include "messenger.hpp"
#include "chat_page.hpp"

#include <QFileInfo>
#include <QFileDialog>

QPushButton* main_page::get_logout() const
{
        return btn_logout;
}

std::string main_page::get_selected_username() const
{
        return "";
}

// attach file click handler
void main_page::send_file()
{
        assert(0 != m_messenger);
        command::command c(command::command::SEND_FILE);
        assert(! m_messenger->get_username().empty());
        assert(! get_selected_username().empty());
        c.add_value("from", m_messenger->get_username());
        c.add_value("to", get_selected_username());
        QString f = QFileDialog::getOpenFileName(this, "Select file to send",
                QDir::currentPath(), "All files (*.*)");
        assert(! f.isEmpty());
        c.add_value("filename", QFileInfo(f).completeBaseName().toStdString());
        QFile file(f);
        file.open(QFile::ReadOnly);
        QByteArray fileBytes = file.readAll();
        c.add_value("data", fileBytes.toBase64().data());
        m_messenger->send_command(c.get_cmd_str());
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
        QHBoxLayout* horLayout1 = new QHBoxLayout;
        label11 = new QLabel("User : ");
        label12 = new QLabel("David");
        horLayout1->addWidget(label11);
        horLayout1->addWidget(label12);
        l->addLayout(horLayout1);
}

void main_page::create_table_headers(QBoxLayout* l)
{
        //create input number of column
        QHBoxLayout* horLayout2 = new QHBoxLayout;
        label21 = new QLabel(tr("Status : "));
        label22 = new QLabel(tr("Connected"));
        horLayout2->addWidget(label21);
        horLayout2->addWidget(label22);
        l->addLayout(horLayout2);
}

void main_page::create_table(QBoxLayout* l)
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
        ncol = 2;

        //create model
        QStandardItemModel* model = new QStandardItemModel(nrow, ncol, this);

        QStringList header;
        header << "Names" << "Status";
        model->setHorizontalHeaderLabels(header);

        //fill model value
        for (int r = 0; r < nrow; r++ ) {
                QString sstr1 = QString::fromStdString(m_messenger->get_first(r));
                QStandardItem *item1 = new QStandardItem(sstr1);
                QString sstr2 = QString::fromStdString(m_messenger->get_second(r));
                QStandardItem *item2 = new QStandardItem(sstr2);
                model->setItem(r, 0, item1);
                model->setItem(r, 1, item2);
        }
        tblv->setModel(model);
        l->addWidget(tblv);
}

main_page::main_page(messenger* m)
        : QWidget()
        , m_messenger(m)
{
        QHBoxLayout* hl = new QHBoxLayout();
        setLayout(hl);

        QVBoxLayout* ml = new QVBoxLayout();
        hl->addLayout(ml);

        QVBoxLayout* cl = new QVBoxLayout();
        hl->addLayout(cl);

        m_chat = new chat_page();
        cl->addWidget(m_chat);

        create_menubar(hl);
        create_labels(ml);
        create_table_headers(ml);
        create_table(ml);
        btn_logout = new QPushButton(tr("Logout"));
        ml->addWidget(btn_logout);
}

