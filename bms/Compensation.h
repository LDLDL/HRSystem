#ifndef COMPENSATION_H
#define COMPENSATION_H

#include <QWidget>
#include<QListWidgetItem>
#include<QSqlTableModel>
#include<QSqlDatabase>
#include<QTextCodec>
#include<QMessageBox>
#include<QDateTime>
#include<QDebug>
#include<QSqlQuery>
#include"ReadOnlyDelegate.h"
#include"BaseWindow.h"

namespace Ui {
class Compensation;
}

class Compensation : public BaseWindow
{
    Q_OBJECT

public:
    explicit Compensation(QWidget *parent = nullptr);
    ~Compensation();

private slots:




    void on_Com_pushButton_clicked();



    void on_Com_listWidget_itemClicked(QListWidgetItem *item);

    void on_Com_pushButton_2_clicked();

    void on_Com_pushButton_3_clicked();

    void on_Com_pushButton_4_clicked();

    void on_Com_pushButton_6_clicked();

    void on_Com_pushButton_7_clicked();

    void on_Com_pushButton_8_clicked();

    void on_Com_comboBox_currentIndexChanged(int index);

    void on_Com_pushButton_9_clicked();

    void on_Com_pushButton_10_clicked();

    void on_Com_pushButton_11_clicked();

    void on_Com_pushButton_12_clicked();

    void on_Com_pushButton_13_clicked();

    void on_Com_pushButton_27_clicked();

    void on_Com_pushButton_29_clicked();

    void on_Com_pushButton_28_clicked();

    void on_Com_pushButton_30_clicked();

    void on_Com_comboBox_3_currentIndexChanged(int index);

    void on_Com_back_clicked();



signals:
    void sendsignal();

private:
    Ui::Compensation *ui;
    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlTableModel *model4;
    QSqlTableModel *model5;
    QSqlTableModel *model6;
    QSqlDatabase db1;
    QSqlDatabase db2;

    void setComboBox_BM();
    void setComboBox_XL();
    void setComboBox_YEAR();
};

#endif // COMPENSATION_H
