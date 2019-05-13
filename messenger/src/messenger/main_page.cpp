#include "main_page.hpp"

QPushButton* main_page::get_logout() const
{
        return btn_logout;
}

main_page::main_page()
    : QWidget()
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
    nrow = 5;
    ncol = 2;

    //create model
    QStandardItemModel *model = new QStandardItemModel( nrow, ncol, this );

    //create QTableview Horizontal Header
    QStringList header;
    header << "Names" << "Status";
    //for (int r=0; r<header.size(); r++)
        model->setHorizontalHeaderLabels( header);

    //fill model value
    for( int r=0; r<nrow; r++ )
    {
        for( int c=0; c<ncol; c++)
        {
            QString sstr = "[ " + QString::number(r) + " , " + QString::number(c) + " ]";
            QStandardItem *item = new QStandardItem(QString("Idx ") + sstr);
            model->setItem(r, c, item);
        }
    }

    //set model

    tblv->setModel(model);
    //setting layout
    mainLayout->setMenuBar(menuBar);
    mainLayout->addLayout(horLayout1);
    mainLayout->addLayout(horLayout2);
    //mainLayout->addWidget(btn_logout);
    mainLayout->addWidget(tblv);
    setLayout(mainLayout);

}
