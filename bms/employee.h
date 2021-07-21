#ifndef EMPLOYEE_H
#define EMPLOYEE_H

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
class Employee;
}

class Employee : public BaseWindow
{
    Q_OBJECT

public:
    Employee(QWidget *parent = nullptr);
    ~Employee();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_back_clicked();

    void on_comboBox_6_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

signals:
    void sendsignal();
private:
    Ui::Employee *ui;
    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlDatabase db1;

    void setComboBox();
};

#endif // EMPLOYEE_H
