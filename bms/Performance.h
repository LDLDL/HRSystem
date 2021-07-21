#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <QWidget>
#include<QListWidgetItem>
#include<QSqlTableModel>
#include<QTextCodec>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include"ReadOnlyDelegate.h"
#include<QDateTime>
#include"BaseWindow.h"
#include"Evaluation.h"
namespace Ui {
class Performance;
}

class Performance : public BaseWindow
{
    Q_OBJECT

public:
    explicit Performance(QWidget *parent = nullptr);
    ~Performance();

private slots:
    void on_KPI_comboBox_currentIndexChanged(int index);

    void on_KPI_pushButton_clicked();

    void on_KPI_pushButton_2_clicked();

    void on_KPI_pushButton_3_clicked();

    void on_KPI_pushButton_4_clicked();

    void on_KPI_back_clicked();

    void on_pushButton_clicked();

signals:
    void sendsignal();

private:
    void initTitleBar();
    Ui::Performance *ui;
    QSqlTableModel *model;
    QSqlDatabase db1;
    void setComboBox();

};

#endif // PERFORMANCE_H
