#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());//固定窗口大小

}

Menu::~Menu()
{
    delete ui;
}
void Menu::on_back_clicked()
{
    emit sendsignal();//向上一个窗口发送信号
    this->close();//然后关闭
}

void Menu::on_pushButton_2_clicked()//组织架构
{
    Organization *o = new Organization;
    o->setWindowTitle("组织架构");
    connect(o,SIGNAL(sendsignal()),this,SLOT(show()));//接收到上一个窗口的信号，然后show
    this->hide();
    o->show();
}


void Menu::on_pushButton_3_clicked()//薪酬管理
{
    Compensation *c = new Compensation;
    c->setWindowTitle("薪酬管理");
    connect(c,SIGNAL(sendsignal()),this,SLOT(show()));//接收到上一个窗口的信号，然后show
    this->hide();
    c->show();
}

void Menu::on_pushButton_6_clicked()//绩效管理
{
    Performance *p = new Performance;
    p->setWindowTitle("绩效管理");
    connect(p,SIGNAL(sendsignal()),this,SLOT(show()));//接收到上一个窗口的信号，然后show
    this->hide();
    p->show();
}

void Menu::on_pushButton_clicked()//人事档案
{
    Employee *e = new Employee;
    e->setWindowTitle("人事档案");
    connect(e,SIGNAL(sendsignal()),this,SLOT(show()));//接收到上一个窗口的信号，然后show
    this->hide();
    e->show();
}




void Menu::on_pushButton_4_clicked()//合同管理
{
    Agreement *ag = new Agreement;
    ag->setWindowTitle("合同管理");
    connect(ag,SIGNAL(sendsignal()),this,SLOT(show()));//接收到上一个窗口的信号，然后show
    this->hide();
    ag->show();
}


void Menu::on_pushButton_5_clicked()//考勤管理
{
    WorkAtt *w = new WorkAtt;
    w->setWindowTitle("考勤管理");
    connect(w,SIGNAL(sendsignal()),this,SLOT(show()));//接收到上一个窗口的信号，然后show
    this->hide();
    w->show();
}
