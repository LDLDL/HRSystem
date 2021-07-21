#include "Organization.h"
#include "ui_Organization.h"

Organization::Organization(QWidget *parent)
    : BaseWindow(parent)
    , ui(new Ui::Organization)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());//固定窗口大小
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    db1 = QSqlDatabase::database("a");

    //1
    model = new QSqlTableModel(this,db1);//连了默认数据库
    model->setTable(codec->toUnicode("部门"));
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑



    //2
    model2 = new QSqlTableModel(this,db1);//连了默认数据库
    model2->setTable(codec->toUnicode("部门职位"));
    model2->select();
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    setComboBox();

    ui->lineEdit1->setPlaceholderText("请输入部门编号");
    ui->lineEdit_2->setPlaceholderText("请输入部门名称");
    ui->lineEdit_3->setPlaceholderText("请输入部门名称");
    ui->lineEdit_5->setPlaceholderText("部门修改后名称");
    ui->lineEdit_6->setPlaceholderText("请输入部门编号");

    ui->lineEdit_8->setPlaceholderText("请输入职位名称");
    ui->lineEdit_9->setPlaceholderText("请输入职位名称");
    ui->lineEdit_11->setPlaceholderText("职位修改后名称");
    ui->lineEdit_12->setPlaceholderText("请输入职位名称");

    ui->tableView_2->setModel(model2);

    //3
    model3 = new QSqlTableModel(this,db1);//连了默认数据库
    model3->setTable(codec->toUnicode("员工调岗"));
    model3->select();
    ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->lineEdit_13->setPlaceholderText("请输入员工编号");
    ui->lineEdit_14->setPlaceholderText("请输入员工编号");
    ui->tableView_3->setModel(model3);


}

Organization::~Organization()
{
    delete ui;
}


void Organization::on_listWidget_itemClicked(QListWidgetItem *item) //侧边栏
{
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

}

void Organization::setComboBox(){// 供选中框的数据填充
    QSqlQuery query(db1);
    query.exec("select *from 部门");
    ui->comboBox->clear();
    ui->comboBox->addItem("");
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_7->clear();
    while(query.next()){
        QString str = query.value(0).toString();
        QString str2 = query.value(1).toString();
        str.append("(").append(str2).append(")");

        ui->comboBox->addItem(str);
        ui->comboBox_2->addItem(str);
        ui->comboBox_3->addItem(str);
        ui->comboBox_4->addItem(str);
        ui->comboBox_5->addItem(str);
        ui->comboBox_7->addItem(str);
    }
}

void Organization::on_comboBox_5_currentIndexChanged(int index)//调岗记录部门框，用来实时更新职位框
{
    QString bm = ui->comboBox_5->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);
    QSqlQuery query(db1);
    query.exec(QString("select 职位名称 from 职位 where 部门编号 = '%1'").arg(bm));
    ui->comboBox_6->clear();
    while(query.next()){
        ui->comboBox_6->addItem(query.value(0).toString());
    }
}

void Organization::on_back_clicked()//返回
{
    emit sendsignal();
    this->close();
}

void Organization::on_comboBox_3_currentIndexChanged(int index)//职位管理部门框，用来实时更新职位框
{
    QString bm = ui->comboBox_3->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);
    QSqlQuery query(db1);
    query.exec(QString("select 职位名称 from 职位 where 部门编号 = '%1'").arg(bm));
    ui->comboBox_8->clear();
    while(query.next()){
        ui->comboBox_8->addItem(query.value(0).toString());
    }
}



/*-------------------部门管理---------------------*/

void Organization::on_pushButton_clicked() // 部门管理的查询
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model->setTable(codec->toUnicode("部门"));

    QString no = ui->lineEdit1->text(); //部门编号
    QString name = ui->lineEdit_2->text();//部门名称
    QString sqlstr;
    if(no != NULL){
        sqlstr.append(QString("部门编号 = '%1'").arg(no));
    }

    if(name != NULL){
        sqlstr.append(" and ").append(QString("部门名称 = '%1'").arg(name));
    }
    if (sqlstr.startsWith(" and ")) {
      sqlstr = sqlstr.right(sqlstr.size() - 5);
    }
    model->setFilter(sqlstr);
    qDebug()<<sqlstr;
    model->select();
    ui->tableView->setModel(model);

}

void Organization::on_pushButton_2_clicked() //部门管理的新增
{
    QString name = ui->lineEdit_3->text(); // 部门名称
    QSqlQuery query(db1);
    bool flag = query.exec(QString("CALL 增加部门('%1')").arg(name));
    if(flag == 0){
        QMessageBox::critical(0,"警告","部门设立失败",QMessageBox::Cancel);
    }else{
        QMessageBox::about(0,"恭喜","部门设立成功");
        setComboBox();
        model->select();
        ui->tableView->setModel(model);
    }

}



void Organization::on_pushButton_3_clicked()//部门管理的修改
{
    QString bm = ui->comboBox_7->currentText(); //修改前的编号
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);
    qDebug()<<bm;

    QString aname = ui->lineEdit_5->text(); // 修改后的名称
    QSqlQuery query(db1);
    if(bm != NULL && aname != NULL){
        bool flag = query.exec(QString("update 部门 set 部门名称 = '%1' where 部门编号 = '%2' ").arg(aname).arg(bm));
        if(flag == 0){
            QMessageBox::critical(0,"警告","修改失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"恭喜","修改成功");
            setComboBox();
            model->select();
            ui->tableView->setModel(model);
        }
    }else{
        QMessageBox::critical(0,"警告","信息请输入完整",QMessageBox::Cancel);
    }

}

void Organization::on_pushButton_4_clicked()//部门管理的删除
{
    QString no = ui->lineEdit_6->text(); //部门编号
    //        QString name = ui->lineEdit_7->text();//部门名称
    if(no != NULL){
        QSqlQuery query(db1);
        bool flag = query.exec(QString("CALL 部门撤销('%1')").arg(no));
        if(flag == 0){
            QMessageBox::critical(0,"部门撤销失败","该部门还有员工",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"恭喜","部门撤销成功");
            setComboBox();
            model->select();
            ui->tableView->setModel(model);
        }
    }
}

/******************职务管理********************/

void Organization::on_pushButton_5_clicked() //查询
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model2->setTable(codec->toUnicode("部门职位"));
    /*以下是获取部门编号*/
    QString bm = ui->comboBox->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);

    qDebug()<<bm;//编号
    QString sqlstr;

    QString zw = ui->lineEdit_8->text();//职位
    if(bm != NULL){
        sqlstr.append(QString("部门编号 = '%1'").arg(bm));

    }

    if(zw != NULL){
        sqlstr.append(" and ").append(QString("职位名称 = '%1'").arg(zw));
    }

    if (sqlstr.startsWith(" and ")) {
      sqlstr = sqlstr.right(sqlstr.size() - 5);
    }

    model2->setFilter(sqlstr);
    model2->select();
    ui->tableView_2->setModel(model2);
}


void Organization::on_pushButton_6_clicked()//设立职位，并写入薪酬
{
    QString bm = ui->comboBox_2->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);
    qDebug()<<bm;

    QString zw = ui->lineEdit_9->text();
    double gz = ui->doubleSpinBox->value();

    qDebug()<<gz;
    if(bm == NULL){
        QMessageBox::critical(0,"警告","请选择部门",QMessageBox::Cancel);
        return;
    }

    if(zw == NULL){
        QMessageBox::critical(0,"警告","请写入职位名",QMessageBox::Cancel);
        return;
    }
    if(gz == 0){
        ui->label->setText("请写入职位工资");
        return;
    }

    QSqlQuery query(db1);
    query.exec(QString("insert into 职位 values('%1','%2','%3')").arg(zw).arg(bm).arg(gz));
    model2->select();
    ui->tableView_2->setModel(model2);
}

void Organization::on_pushButton_8_clicked()//修改职位名称
{
    QString bm = ui->comboBox_3->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);
    qDebug()<<bm;

    QString bname = ui->comboBox_8->currentText();
    QString aname = ui->lineEdit_11->text();

    if(bname != NULL && aname != NULL){
        QSqlQuery query(db1);
        bool flag = query.exec(QString("update 职位 set 职位名称 = '%1' where 职位名称 = '%2' and 部门编号 = '%3' ").arg(aname).arg(bname).arg(bm));
        if(flag == 0){
            QMessageBox::critical(0,"失败","职位名称修改失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","职位名称修改成功");
            model2->select();
            ui->tableView_2->setModel(model2);
        }
    }else{
        QMessageBox::warning(0,"警告","信息请输入完整",QMessageBox::Cancel);
    }
}

void Organization::on_pushButton_7_clicked()//删除职位
{
    QString bm = ui->comboBox_3->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);
    qDebug()<<bm;
    QString zw = ui->lineEdit_12->text();

    if(zw == NULL){
        QMessageBox::warning(0,"警告","请输入职位",QMessageBox::Cancel);
        return;
    }

    QSqlQuery query(db1);
    bool flag = query.exec(QString("delete from 职位 where 部门编号 = '%1' and 职位名称 = '%2'").arg(bm).arg(zw));
    if(flag == 0){
        QMessageBox::critical(0,"失败","该职位还有员工",QMessageBox::Cancel);
    }else{
        QMessageBox::about(0,"成功","职位删除成功");
        model2->select();
        ui->tableView_2->setModel(model2);
    }
}


/*-----------------调岗记录---------------------*/
void Organization::on_pushButton_9_clicked()//查询
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model3->setTable(codec->toUnicode("员工调岗"));


    QString no = ui->lineEdit_13->text();
    if(no != NULL){
        model3->setFilter(QString("员工编号 = '%1'").arg(no));
    }
    model3->select();
    ui->tableView_3->setModel(model3);
}

void Organization::on_pushButton_10_clicked()//调岗
{
    QString no = ui->lineEdit_14->text();
    if(no == NULL){
        QMessageBox::warning(0,"警告","请输入员工编号",QMessageBox::Cancel);
        return;
    }

    QString bm = ui->comboBox_5->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);

    QString zw = ui->comboBox_6->currentText();

    QSqlQuery query(db1);
    qDebug()<<no;
    qDebug()<<bm;
    qDebug()<<zw;
    bool flag = query.exec(QString("CALL 编号调岗('%1','%2','%3')").arg(no).arg(bm).arg(zw));
    if(flag == true){
        QMessageBox::about(0,"恭喜","调岗成功");
        model3->select();
        ui->tableView_3->setModel(model3);
    }else{
        QMessageBox::critical(0,"失败","调岗失败",QMessageBox::Cancel);
    }
}

