#include "main_page.hpp"
#include "messenger.hpp"

#include <QFileInfo>
#include <QFileDialog>


void main_page::showEvent( QShowEvent* event )
{
        std::cout << "Updating window" << std::endl;
        assert(0 != m_messenger);
        m_messenger->request_user_list();
        QWidget::showEvent( event );
}

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

main_page::main_page(messenger* m)
        : QWidget()
        , m_messenger(m)
{
        //create toolbar
        QMenuBar* menuBar = new QMenuBar();
        QMenu *fileMenu = new QMenu("Menu");
        menuBar->addMenu(fileMenu);
        fileMenu->addAction("Go Invisible");
        fileMenu->addAction("Logout");

        //create layout
        QVBoxLayout *mainLayout = new QVBoxLayout();
        QHBoxLayout *horLayout1 = new QHBoxLayout;
        QHBoxLayout *horLayout2 = new QHBoxLayout;

        //create input number of row
        label11 = new QLabel(tr("User : "));
        label12 = new QLabel(tr("David"));
        horLayout1->addWidget(label11);
        horLayout1->addWidget(label12);

        //create input number of column
        label21 = new QLabel(tr("Status : "));
        label22 = new QLabel(tr("Connected"));
        horLayout2->addWidget(label21);
        horLayout2->addWidget(label22);

        btn_logout = new QPushButton(tr("Logout"));

        //create QTableView
        tblv = new QTableView();
        tblv->setSelectionBehavior(QAbstractItemView::SelectItems );
        tblv->setSelectionMode( QAbstractItemView::ExtendedSelection );
        tblv->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tblv->resizeColumnsToContents();
        tblv->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //get number of input row and column
        nrow = m_messenger->get_list_size();
        ncol = 2;

        //create model
        QStandardItemModel *model = new QStandardItemModel( nrow, ncol, this );

        //create QTableview Horizontal Header
        QStringList header;
        header << "Names" << "Status";
        //for (int r=0; r<header.size(); r++)
        model->setHorizontalHeaderLabels( header);

        //fill model value
        for (int r = 0; r < nrow; r++ ) {
                QString sstr1 = QString::fromStdString(m_messenger->get_first(r));
                QStandardItem *item1 = new QStandardItem(sstr1);
                QString sstr2 = QString::fromStdString(m_messenger->get_second(r));
                QStandardItem *item2 = new QStandardItem(sstr2);
                model->setItem(r, 0, item1);
                model->setItem(r, 1, item2);
        }

        //set model
        tblv->setModel(model);
        //setting layout
        mainLayout->setMenuBar(menuBar);
        mainLayout->addLayout(horLayout1);
        mainLayout->addLayout(horLayout2);
        mainLayout->addWidget(btn_logout);
        mainLayout->addWidget(tblv);
        setLayout(mainLayout);
}

