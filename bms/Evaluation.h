#ifndef EVALUATION_H
#define EVALUATION_H

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

namespace Ui {
class Evaluation;
}

class Evaluation : public BaseWindow
{
    Q_OBJECT

public:
    explicit Evaluation(QWidget *parent = nullptr);
    ~Evaluation();
signals:
     void sendsignal();
private slots:
    void on_KPI_pushButton_clicked();

    void on_KPI_pushButton_2_clicked();

    void on_KPI_pushButton_3_clicked();

    void on_KPI_pushButton_4_clicked();

    void on_back_clicked();

private:
    Ui::Evaluation *ui;
    QSqlTableModel *model;
    QSqlDatabase db1;
};

#endif // EVALUATION_H
