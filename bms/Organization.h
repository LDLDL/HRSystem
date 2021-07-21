#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QWidget>
#include<QListWidgetItem>
#include<QSqlTableModel>
#include<QTextCodec>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include"BaseWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Organization; }
QT_END_NAMESPACE

class Organization : public BaseWindow
{
    Q_OBJECT

public:
    Organization(QWidget *parent = nullptr);
    ~Organization();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();



    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_back_clicked();
    void on_pushButton_10_clicked();

    void on_comboBox_5_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

signals:
    void sendsignal();

private:
    Ui::Organization *ui;
    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlDatabase db1;

    void setComboBox();
};
#endif // ORGANIZATION_H
