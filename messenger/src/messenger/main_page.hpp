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

class main_page : public QWidget
{
    Q_OBJECT
public:
    QPushButton* get_logout() const;

private:
    messenger* m_messenger;
    QTableView *tblv;
    QLabel *label11, *label12, *label21, *label22;
    QPushButton *btn_logout;
    int nrow, ncol;

private slots:
//    void btnApply_clicked();
public:
    main_page(messenger* m);
};

#endif // MESSENGER_MAIN_PAGE_HPP
