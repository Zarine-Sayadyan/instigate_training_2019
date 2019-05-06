#ifndef SECOND_SCREEN_HPP
#define SECOND_SCREEN_HPP

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

class second_screen : public QWidget
{
    Q_OBJECT
public:
    second_screen(QWidget *parent = 0);

private:
    QTableView *tblv;
    QLabel *label11, *label12, *label21, *label22;
    QPushButton *btn_logout;
    int nrow, ncol;

private slots:
//    void btnApply_clicked();
};

#endif // SECOND_SCREEN_HPP
