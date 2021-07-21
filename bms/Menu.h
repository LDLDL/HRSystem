#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include"Organization.h"
#include"Compensation.h"
#include "Performance.h"
#include"employee.h"
#include"workatt.h"
#include"agreement.h"
namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_2_clicked();

    void on_back_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

signals:
    void sendsignal();//这个函数用户向主界面通知关闭的消息
private:
    Ui::Menu *ui;
};

#endif // MENU_H
