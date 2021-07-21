#ifndef WORKATT_H
#define WORKATT_H

#include <QWidget>
#include<QListWidgetItem>
#include<QSqlTableModel>
#include<QTextCodec>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include"ReadOnlyDelegate.h"
#include"BaseWindow.h"
namespace Ui {
class WorkAtt;
}

class WorkAtt : public BaseWindow
{
    Q_OBJECT

public:
    explicit WorkAtt(QWidget *parent = nullptr);
    ~WorkAtt();

private slots:
    void on_back_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:
    void sendsignal();
private:
    Ui::WorkAtt *ui;
    QSqlTableModel *model;
    QSqlDatabase db1;
};

#endif // WORKATT_H
