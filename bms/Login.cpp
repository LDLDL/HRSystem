#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());//固定窗口大小
    ui->lineEdit_3->setText("localhost");
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();
    QString userpassword = ui->lineEdit_2->text();
    QString dbip = ui->lineEdit_3->text();

    if(username == NULL){
        ui->label_3->setText("请输入用户名");
        return;
    }

    if(userpassword == NULL){
        ui->label_4->setText("请输入密码");
        return;
    }

    /*到时候由登入界面来实现数据库连接*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL","a");//BMS
    db.setHostName(dbip);//主机IP
    db.setDatabaseName("bms");//数据库名
    db.setUserName(username);//用户名
    db.setPassword(userpassword);//登入密码
    if(!db.open()){
        //         QMessageBox::critical(0,"警告","无法创建数据库连接!",QMessageBox::Cancel);
    }else{
        qDebug()<<"ok";
    }

//    QSqlDatabase db2 = QSqlDatabase::addDatabase("QMYSQL","b");//BMSO
//    db2.setHostName("localhost");//主机IP
//    db2.setDatabaseName("bmso");//数据库名
//    db2.setUserName(username);//用户名
//    db2.setPassword(userpassword);//登入密码
//    if(!db2.open()){
//        //         QMessageBox::critical(0,"警告","无法创建数据库连接!",QMessageBox::Cancel);
//    }else{
//        qDebug()<<"ok";
//    }

//    qDebug()<<" Login ok";


    /*************************进入菜单********************************/
    Menu *m = new Menu;
    m->setWindowTitle("菜单");
    m->show();
    this->hide();
    qDebug()<<" Menu ok";
    connect(m,SIGNAL(sendsignal()),this,SLOT(show()));

}

void Login::on_quit_clicked()
{
    this->close();
}
