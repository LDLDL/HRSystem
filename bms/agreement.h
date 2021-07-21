#ifndef AGREEMENT_H
#define AGREEMENT_H

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
class Agreement;
}

class Agreement : public BaseWindow
{
    Q_OBJECT

public:
    explicit Agreement(QWidget *parent = nullptr);
    ~Agreement();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_back_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

signals:
    void sendsignal();

private:
    Ui::Agreement *ui;

    QSqlTableModel *model;
    QSqlTableModel *model2;
    QSqlTableModel *model3;
    QSqlTableModel *model4;
    QSqlDatabase db1;

    void setComboBox();
};

#endif // AGREEMENT_H
