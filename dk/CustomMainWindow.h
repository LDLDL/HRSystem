#ifndef CUSTOMMAINWINDOW_H
#define CUSTOMMAINWINDOW_H

#include <QWidget>
#include<QSqlQuery>
#include "BaseWindow.h"
namespace Ui {
class CustomMainWindow;
}

class CustomMainWindow : public BaseWindow
{
    Q_OBJECT

public:
    explicit CustomMainWindow(QWidget *parent = 0);
    ~CustomMainWindow();

private slots:
    void on_daka_clicked();


    void on_tuiqian_clicked();

    void on_quit_clicked();

private:
    void initTitleBar();

    Ui::CustomMainWindow *ui;
    QSqlDatabase db;
};

#endif // CUSTOMMAINWINDOW_H
