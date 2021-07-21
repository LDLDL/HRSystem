#ifndef CONNECTION_H
#define CONNECTION_H

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
static bool createConnection(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");//数据库类型
    db.setHostName("localhost");//主机IP
    db.setDatabaseName("test");//数据库名
    db.setUserName("root");//用户名
    db.setPassword("123");//登入密码
    if(!db.open()){
        QMessageBox::critical(0,("警告"),("无法创建数据库连接!"),QMessageBox::Cancel);
        //qDebug()<<db.lastError().text();
        return false;
    }
    return true;
}
#endif // CONNECTION_H
