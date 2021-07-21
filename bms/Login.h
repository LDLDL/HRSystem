#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QWidget>
#include<QListWidgetItem>
#include<QSqlTableModel>
#include<QTextCodec>
#include<QDebug>
#include<QSqlQuery>
#include<QMessageBox>
#include"Menu.h"
namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_clicked();

    void on_quit_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
