#include "agreement.h"
#include "ui_agreement.h"

Agreement::Agreement(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::Agreement)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());//固定窗口大小
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    db1 = QSqlDatabase::database("a");
    model = new QSqlTableModel(this,db1);//连了默认数据库
    model->setTable(codec->toUnicode("员工有效合同"));
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView->setModel(model);

    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->tableView->setItemDelegateForColumn(0, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(1, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(2, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(3, readOnlyDelegate); //设置某列只读

    model2 = new QSqlTableModel(this,db1);//连了默认数据库
    model2->setTable(codec->toUnicode("员工到期合同"));
    model2->select();
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_2->setModel(model2);

    model3 = new QSqlTableModel(this,db1);//连了默认数据库
    model3->setTable(codec->toUnicode("合同即将到期员工"));
    model3->select();
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_3->setModel(model3);

    model4 = new QSqlTableModel(this,db1);//连了默认数据库
    model4->setTable(codec->toUnicode("无合同在职员工"));
    model4->select();
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_4->setModel(model4);

    ui->lineEdit->setPlaceholderText("请输入员工编号");
    ui->lineEdit_2->setPlaceholderText("请输入合同类型");

    ui->lineEdit_3->setPlaceholderText("请输入员工编号");
    ui->lineEdit_4->setPlaceholderText("请输入合同类型");
}

Agreement::~Agreement()
{
    delete ui;
}

void Agreement::on_back_clicked(){
    emit sendsignal();
    this->close();
}

void Agreement::on_listWidget_itemClicked(QListWidgetItem *item){
    int row = ui->listWidget->currentRow();

    ui->stackedWidget->setCurrentIndex(row);
    if(row == 0){
        model->select();
        ui->tableView->setModel(model);
    }
    if(row == 1){
        model2->select();
        ui->tableView_2->setModel(model2);
    }
    if(row == 2){
        model3->select();
        ui->tableView_3->setModel(model3);
    }
    if(row == 3){
        model4->select();
        ui->tableView_4->setModel(model4);
    }
}

void Agreement::on_pushButton_4_clicked(){//到期合同表 刷新
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model2->select();
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_2->setModel(model2);
}

void Agreement::on_pushButton_5_clicked(){//合同即将到期表 刷新
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model3->select();
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_3->setModel(model3);
}

void Agreement::on_pushButton_6_clicked(){//无合同在职员工表 刷新
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model4->select();
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_4->setModel(model4);
}

void Agreement::on_pushButton_2_clicked(){//查询
    QString emp_id = ui->lineEdit_3->text();
    QString agr_type = ui->lineEdit_4->text();

    QString sqlstr;
    if(emp_id != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(emp_id));

    }
    if(agr_type != NULL){
        sqlstr.append(" and ").append(QString("合同类型 = '%1'").arg(agr_type));

    }
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    qDebug()<<sqlstr;
    model->setFilter(sqlstr);
    model->select();
    ui->tableView->setModel(model);
}

void Agreement::on_pushButton_clicked(){//增加
    QString emp_id = ui->lineEdit->text();
    QString agr_type = ui->lineEdit_2->text();

    QString start_date = ui->dateEdit->text();
    QString end_date  = ui->dateEdit_2->text();

    if(emp_id!=NULL && agr_type!=NULL && start_date!=NULL && end_date!=NULL){
        QSqlQuery query(db1);
        bool flag = query.exec(QString("insert into 有效合同 values('%1','%2','%3','%4')").arg(emp_id).arg(agr_type).arg(start_date).arg(end_date));
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

void Agreement::on_pushButton_3_clicked(){//删除
    int row = ui->tableView->currentIndex().row();

    QString str = QString("你确定删除当前第").append(QString("%1").arg(row+1)).append("行吗?");
    int ok = QMessageBox::warning(this,tr("删除当前行!"),str,QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        QModelIndex index = model->index(row,0);
        QString emp_id = model->data(index).toString();
        QModelIndex index1 = model->index(row,4);
        QString agr_type = model->data(index1).toString();
        QModelIndex index2 = model->index(row,5);
        QString start_date = model->data(index2).toString();
        QModelIndex index3 = model->index(row,6);
        QString end_date  = model->data(index3).toString();

        QSqlQuery query(db1);
        bool flag = query.exec(QString("delete from 有效合同 where  员工编号 = '%1' and 合同类型 = '%2' and 生效日期 = '%3' and 结束日期 = '%4'").arg(emp_id).arg(agr_type).arg(start_date).arg(end_date));
        if(flag == false){
            QMessageBox::critical(0,"失败","记录删除失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录删除成功");
            model->select();
            ui->tableView->setModel(model);
        }
    }
}
