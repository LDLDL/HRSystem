#include "workatt.h"
#include "ui_workatt.h"

WorkAtt::WorkAtt(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::WorkAtt)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());//固定窗口大小
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    db1 = QSqlDatabase::database("a");
    model = new QSqlTableModel(this,db1);//连了默认数据库
    model->setTable(codec->toUnicode("员工考勤"));
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView->setModel(model);

    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->tableView->setItemDelegateForColumn(0, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(1, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(2, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(3, readOnlyDelegate); //设置某列只读

    ui->lineEdit->setPlaceholderText("请输入员工编号");
    ui->lineEdit_2->setPlaceholderText("请输入员工编号");
    ui->lineEdit_3->setPlaceholderText("请输入考勤情况");

    ui->lineEdit_4->setPlaceholderText("请输入情况");
}

WorkAtt::~WorkAtt()
{
    delete ui;
}

void WorkAtt::on_back_clicked(){
    emit sendsignal();
    this->close();
}

void WorkAtt::on_pushButton_clicked(){//查询
    QString emp_id = ui->lineEdit->text();
    QString qk = ui->lineEdit_4->text();

    QString _date = ui->dateEdit->text();

    QString sqlstr;
    if(emp_id != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(emp_id));

    }
    if(qk != NULL){
        sqlstr.append(" and ").append(QString("情况 = '%1'").arg(qk));

    }
    if(_date != NULL){
        sqlstr.append(" and ").append(QString("日期 = '%1'").arg(_date));

    }
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    qDebug()<<sqlstr;
    model->setFilter(sqlstr);
    model->select();
    ui->tableView->setModel(model);
}

void WorkAtt::on_pushButton_2_clicked(){//增加
    QString emp_id = ui->lineEdit_2->text();
    QString qk = ui->lineEdit_3->text();
    QString _date = ui->dateEdit_2->text();

    if(emp_id!=NULL && qk!=NULL && _date!=NULL){
        QSqlQuery query(db1);
        bool flag = query.exec(QString("insert into 考勤记录 values('%1','%2',NULL,NULL,'%3')").arg(emp_id).arg(_date).arg(qk));
        if(flag == false){
            QMessageBox::critical(0,"失败","记录增加失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录增加成功");
            model->select();
            ui->tableView->setModel(model);
        }
    }else{
         QMessageBox::warning(0,"警告","请补全增加的信息",QMessageBox::Yes);
    }
}

void WorkAtt::on_pushButton_3_clicked(){//删除
    int row = ui->tableView->currentIndex().row();

    QString str = QString("你确定删除当前第").append(QString("%1").arg(row+1)).append("行吗?");
    int ok = QMessageBox::warning(this,tr("删除当前行!"),str,QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        QModelIndex index = model->index(row,0);
        QString emp_id = model->data(index).toString();
        QModelIndex index1 = model->index(row,4);
        QString _date = model->data(index1).toString();

        QModelIndex index4 = model->index(row,7);
        QString qk  = model->data(index4).toString();

        QSqlQuery query(db1);

        bool flag = query.exec(QString("delete from 考勤记录 where 员工编号 = '%1' and 日期 = '%2' and 情况 = '%3'").arg(emp_id).arg(_date).arg(qk));
        if(flag == false){
            QMessageBox::critical(0,"失败","记录删除失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录删除成功");
            model->select();
            ui->tableView->setModel(model);
        }
    }
}

void WorkAtt::on_pushButton_4_clicked(){//修改
    if (model->submitAll()) {
        model->database().commit();//提交
        QMessageBox::about(0,"成功","记录修改成功");

    } else {
        model->database().rollback();//回滚
        QMessageBox::critical(0,"失败","修改失败",QMessageBox::Cancel);
    }
    model->select();
    ui->tableView->setModel(model);
}
