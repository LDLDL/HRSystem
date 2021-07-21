#include "CustomMainWindow.h"
#include "ui_CustomMainWindow.h"
#include<QtDebug>
#include<QMessageBox>
#include<QDateTime>
CustomMainWindow::CustomMainWindow(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::CustomMainWindow)
{
    initTitleBar();
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("输入员工编号");

    db = QSqlDatabase::addDatabase("QMYSQL");//数据库类型
    db.setHostName("localhost");//主机IP
    db.setDatabaseName("bms");//数据库名
    db.setUserName("root");//用户名
    db.setPassword("123");//登入密码
    if(!db.open()){
        QMessageBox::critical(0,("警告"),("无法创建数据库连接!"),QMessageBox::Cancel);
        //qDebug()<<db.lastError().text();
    }else{
        qDebug()<<"ok";
    }

//    ui->label->styleSheet();
}

CustomMainWindow::~CustomMainWindow()
{
    delete ui;
}

void CustomMainWindow::initTitleBar()
{
    // 设置标题栏跑马灯效果，可以不设置;
    m_titleBar->setTitleRoll();
    m_titleBar->setBackgroundColor(56,70,85);
    m_titleBar->setTitleIcon(":/icon.png");
    m_titleBar->setTitleContent(QStringLiteral("~~~~请打卡 (*^_^*) ~~~~"));
    m_titleBar->setButtonType(MIN_MAX_BUTTON);
    m_titleBar->setTitleWidth(this->width());
}

void CustomMainWindow::on_daka_clicked()
{
//    qDebug()<<".";

    QDateTime dateTime(QDateTime::currentDateTime());
    QString b = dateTime.toString("yyyy-MM-dd");

    qDebug()<<b;

    QString a = ui->lineEdit->text();
    if(a == NULL){
        QMessageBox::warning(0,"警告","请输入编号",QMessageBox::Yes);
        return;
    }

    qDebug()<<a;
    QSqlQuery query(db);
    query.exec(QString("SELECT bms.`考勤记录`.`上班时间` FROM bms.`考勤记录` WHERE bms.`考勤记录`.`员工编号` = %1 AND bms.`考勤记录`.`日期` = '%2' ").arg(a).arg(b));
    query.next();
//    QString flag = query.value(0).toString();
//    qDebug()<<flag;
    if(query.value(0).toString() == NULL){
        query.exec(QString("Call 打卡('%1')").arg(a));
        QMessageBox::about(NULL,"恭喜","打卡成功");
    }else{
        QMessageBox::warning(0,"警告","今日已打卡",QMessageBox::Yes);
    }
}

void CustomMainWindow::on_tuiqian_clicked()
{
//    qDebug()<<".";
    QDateTime dateTime(QDateTime::currentDateTime());
    QString b = dateTime.toString("yyyy-MM-dd");
    QString a = ui->lineEdit->text();
    if(a == NULL){
        QMessageBox::warning(0,"警告","请输入编号",QMessageBox::Yes);
        return;
    }
    QSqlQuery query(db);
    query.exec(QString("SELECT bms.`考勤记录`.`下班时间` FROM bms.`考勤记录` WHERE bms.`考勤记录`.`员工编号` = %1 AND bms.`考勤记录`.`日期` = '%2' ").arg(a).arg(b));
    query.next();
//    qDebug()<<"HERE"<<query.value(0).toString();
    if(query.value(0).toString() == NULL){
        query.exec(QString("Call 退签('%1')").arg(a));
        QMessageBox::about(NULL,"恭喜","退签成功");
    }else{
        QMessageBox::warning(0,"警告","今日已退签",QMessageBox::Yes);
    }
}

void CustomMainWindow::on_quit_clicked()
{
    this->close();
}
