#include "Organization.h"
#include"Login.h"
#include <QApplication>
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    /*到时候由登入界面来实现数据库连接*/
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","a");//BMS
//    db.setHostName("localhost");//主机IP
//    db.setDatabaseName("bms");//数据库名
//    db.setUserName("root");//用户名
//    db.setPassword("123");//登入密码
//    if(!db.open()){
//        //         QMessageBox::critical(0,"警告","无法创建数据库连接!",QMessageBox::Cancel);
//    }else{
//        qDebug()<<"ok";
//    }

//    QSqlDatabase db2 = QSqlDatabase::addDatabase("QMYSQL","b");//BMSO
//    db2.setHostName("localhost");//主机IP
//    db2.setDatabaseName("bmso");//数据库名
//    db2.setUserName("root");//用户名
//    db2.setPassword("123");//登入密码
//    if(!db2.open()){
//        //         QMessageBox::critical(0,"警告","无法创建数据库连接!",QMessageBox::Cancel);
//    }else{
//        qDebug()<<"ok";
//    }

//    qDebug()<<" Login ok";


    QString qss;
    QFile qssFile(":/new1.qss");
    qssFile.open(QFile::ReadOnly);

    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qDebug()<<"ok";
        qssFile.close();
    }

//    Organization o;
//    o.show();
       Login l;
       l.setWindowTitle("登入");
       l.show();
//    Menu m;
//    m.show();

//    Compensation c;
//    c.show();
//    Performance p;
//    p.show();
//       Evaluation e;
//       e.show();

    return a.exec();
}
