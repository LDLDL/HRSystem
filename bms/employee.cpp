#include "employee.h"
#include "ui_employee.h"

Employee::Employee(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::Employee)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());//固定窗口大小
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    db1 = QSqlDatabase::database("a");
    model = new QSqlTableModel(this,db1);//连了默认数据库
    model->setTable(codec->toUnicode("员工"));
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView->setModel(model);


    model2 = new QSqlTableModel(this,db1);//连了默认数据库
    model2->setTable(codec->toUnicode("员工社保"));
    model2->select();
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_2->setModel(model2);

    model3 = new QSqlTableModel(this,db1);//连了默认数据库
    model3->setTable(codec->toUnicode("员工培训"));
    model3->select();
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->tableView_3->setModel(model3);

    ui->lineEdit->setPlaceholderText("请输入员工编号");
    ui->lineEdit_2->setPlaceholderText("员工姓名");

    ui->lineEdit_3->setPlaceholderText("请输入员工编号");
    ui->lineEdit_4->setPlaceholderText("请输入员工姓名");

    ui->lineEdit_5->setPlaceholderText("请输入员工编号");
    ui->lineEdit_6->setPlaceholderText("请输入员工姓名");

    ui->lineEdit_7->setPlaceholderText("请输入姓名");
    ui->lineEdit_9->setPlaceholderText("请输入身份证");
    ui->lineEdit_10->setPlaceholderText("请输入电话");
    ui->lineEdit_11->setPlaceholderText("请输入地址");

    ui->lineEdit_12->setPlaceholderText("请输入员工编号");
    ui->lineEdit_13->setPlaceholderText("请输入培训内容");
    ui->lineEdit_14->setPlaceholderText("请输入表现情况");

    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->tableView->setItemDelegateForColumn(0, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(8, readOnlyDelegate); //设置某列只读
    ui->tableView->setItemDelegateForColumn(9, readOnlyDelegate); //设置某列只读

    ui->tableView_2->setItemDelegateForColumn(0, readOnlyDelegate); //设置某列只读
    ui->tableView_2->setItemDelegateForColumn(1, readOnlyDelegate); //设置某列只读
    ui->tableView_2->setItemDelegateForColumn(2, readOnlyDelegate); //设置某列只读
    ui->tableView_2->setItemDelegateForColumn(3, readOnlyDelegate); //设置某列只读

    ui->tableView_3->setItemDelegateForColumn(0, readOnlyDelegate); //设置某列只读
    ui->tableView_3->setItemDelegateForColumn(1, readOnlyDelegate); //设置某列只读
    ui->tableView_3->setItemDelegateForColumn(2, readOnlyDelegate); //设置某列只读
    ui->tableView_3->setItemDelegateForColumn(3, readOnlyDelegate); //设置某列只读
    setComboBox();
}

Employee::~Employee()
{
    delete ui;
}

void Employee::setComboBox(){
    QSqlQuery query(db1);
    query.exec("select distinct 当值情况 from 员工");
    ui->comboBox_4->addItem("男");
    ui->comboBox_4->addItem("女");
    ui->comboBox->clear();

    ui->comboBox_5->clear();
    ui->comboBox_6->clear();
    while(query.next()){
        QString str = query.value(0).toString();

        ui->comboBox->addItem(str);

    }
    query.exec("select 学历情况 from 学历津贴");
    while(query.next()){
        QString str = query.value(0).toString();

        ui->comboBox_5->addItem(str);
    }
    query.exec("select *from 部门");
    while(query.next()){
        QString str = query.value(0).toString();
        QString str2 = query.value(1).toString();
        str.append("(").append(str2).append(")");
        ui->comboBox_6->addItem(str);
    }

    QString year = QDateTime::currentDateTime().toString("yyyy");
    int num = year.toInt();
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("");

    while(num >= 2018){//年
        QString str = QString("%1").arg(num);
        ui->comboBox_2->addItem(str);

        num -=1;
    }
}

void Employee::on_comboBox_6_currentIndexChanged(int index){
    QString bm = ui->comboBox_6->currentText();
    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.left(num);
    QSqlQuery query(db1);
    query.exec(QString("select 职位名称 from 职位 where 部门编号 = '%1'").arg(bm));
    ui->comboBox_7->clear();
    while(query.next()){
        ui->comboBox_7->addItem(query.value(0).toString());
    }
}

void Employee::on_listWidget_itemClicked(QListWidgetItem *item) //侧边栏
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

void Employee::on_back_clicked(){
    emit sendsignal();
    this->close();
}

/****员工管理****/
void Employee::on_pushButton_clicked(){//查询
    QString emp_id = ui->lineEdit->text();
    QString _name = ui->lineEdit_2->text();

    QString _qk = ui->comboBox->currentText();

    QString sqlstr;
    if(emp_id != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(emp_id));

    }
    if(_name != NULL){
        sqlstr.append(" and ").append(QString("员工姓名 = '%1'").arg(_name));

    }
    if(_qk != NULL){
        sqlstr.append(" and ").append(QString("当值情况 = '%1'").arg(_qk));

    }
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    qDebug()<<sqlstr;
    model->setFilter(sqlstr);
    model->select();
    ui->tableView->setModel(model);
}

void Employee::on_pushButton_2_clicked(){//增加
    QString name = ui->lineEdit_7->text();
    QString birth = ui->dateEdit_3->text();
    QString sfz = ui->lineEdit_9->text();
    QString tel = ui->lineEdit_10->text();
    QString addr = ui->lineEdit_11->text();

    QString sex = ui->comboBox_4->currentText();
    QString xl = ui->comboBox_5->currentText();
    QString bm = ui->comboBox_6->currentText();
    QString zw = ui->comboBox_7->currentText();

    QString end = "(";
    int num = bm.lastIndexOf(end);
    bm = bm.right(num-1);

    end = ")";
    num = bm.lastIndexOf(end);
    bm = bm.left(num);

    if(name!=NULL && birth!=NULL && sfz!=NULL && tel!=NULL && addr!=NULL && sex!=NULL && xl!=NULL && bm!=NULL && zw!=NULL){
        QSqlQuery query(db1);
        QString sqlstr("CALL 增加员工('%1','%2','%3','%4','%5','%6','%7','%8','%9')");
        sqlstr = sqlstr.arg(name).arg(sex).arg(birth).arg(sfz).arg(tel).arg(addr).arg(bm).arg(zw).arg(xl);
        bool flag = query.exec(sqlstr);
        qDebug()<<sqlstr;
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

void Employee::on_pushButton_3_clicked(){//删除
    int row = ui->tableView->currentIndex().row();

    QString str = QString("你确定删除当前第").append(QString("%1").arg(row+1)).append("行吗?");
    int ok = QMessageBox::warning(this,tr("删除当前行!"),str,QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        QModelIndex index = model->index(row,0);
        QString emp_id = model->data(index).toString();

        QSqlQuery query(db1);
        bool flag = query.exec(QString("delete from 员工记录 where  员工编号 = '%1'").arg(emp_id));
        if(flag == false){
            QMessageBox::critical(0,"失败","记录删除失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录删除成功");
            model->select();
            ui->tableView->setModel(model);
        }
    }
}

void Employee::on_pushButton_4_clicked(){//修改
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

/****社保管理****/
void Employee::on_pushButton_5_clicked(){//查询
    QString emp_id = ui->lineEdit_3->text();
    QString _name = ui->lineEdit_4->text();

    QString year = ui->comboBox_2->currentText();
    QString month = ui->comboBox_3->currentText();

    QString sqlstr;
    if(emp_id != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(emp_id));

    }
    if(_name != NULL){
        sqlstr.append(" and ").append(QString("员工姓名 = '%1'").arg(_name));

    }
    if(year != NULL){
        sqlstr.append(" and ").append(QString("年份 = %1").arg(year));

    }

    if(month != NULL){
        sqlstr.append(" and ").append(QString("月份 = %1").arg(month));

    }
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    qDebug()<<sqlstr;
    model2->setFilter(sqlstr);
    model2->select();
    ui->tableView->setModel(model2);
}

void Employee::on_pushButton_6_clicked(){//修改
    if (model2->submitAll()) {
        model2->database().commit();//提交
        QMessageBox::about(0,"成功","记录修改成功");

    } else {
        model2->database().rollback();//回滚
        QMessageBox::critical(0,"失败","修改失败",QMessageBox::Cancel);
    }
    model2->select();
    ui->tableView->setModel(model2);
}

/****培训记录****/
void Employee::on_pushButton_7_clicked(){//查询
    QString emp_id = ui->lineEdit_5->text();
    QString _name = ui->lineEdit_6->text();

    QString sqlstr;
    if(emp_id != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(emp_id));

    }
    if(_name != NULL){
        sqlstr.append(" and ").append(QString("员工姓名 = '%1'").arg(_name));

    }
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    qDebug()<<sqlstr;
    model3->setFilter(sqlstr);
    model3->select();
    ui->tableView->setModel(model3);
}

void Employee::on_pushButton_8_clicked(){//增加
    QString emp_id = ui->lineEdit_12->text();
    QString nr = ui->lineEdit_13->text();
    QString pj = ui->lineEdit_14->text();

    QString start_date = ui->dateEdit->text();
    QString end_date = ui->dateEdit_2->text();

    if(emp_id!=NULL && nr!=NULL && pj!=NULL){
        QSqlQuery query(db1);
        QString sqlstr("INSERT INTO 培训记录 VALUES('%1','%2','%3','%4','%5')");
        sqlstr = sqlstr.arg(emp_id).arg(nr).arg(start_date).arg(end_date).arg(pj);
        bool flag = query.exec(sqlstr);
        qDebug()<<sqlstr;
        if(flag == false){
            QMessageBox::critical(0,"失败","记录增加失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录增加成功");
            model3->select();
            ui->tableView_3->setModel(model3);
        }
    }else{
         QMessageBox::warning(0,"警告","请补全增加的信息",QMessageBox::Yes);
    }
}

void Employee::on_pushButton_9_clicked(){//删除
    int row = ui->tableView_3->currentIndex().row();

    QString str = QString("你确定删除当前第").append(QString("%1").arg(row+1)).append("行吗?");
    int ok = QMessageBox::warning(this,tr("删除当前行!"),str,QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        QModelIndex index = model3->index(row,0);
        QString emp_id = model3->data(index).toString();
        QModelIndex index2 = model3->index(row,4);
        QString px_type = model3->data(index2).toString();
        QModelIndex index3 = model3->index(row,5);
        QString start_date = model3->data(index3).toString();
        QModelIndex index4 = model3->index(row,6);
        QString end_date = model3->data(index4).toString();

        QSqlQuery query(db1);
        bool flag = query.exec(QString("delete from 培训记录 where  员工编号 = '%1' and 培训内容 = '%2' and 开始时间 = '%3' and 结束时间 = '%4'").arg(emp_id).arg(px_type).arg(start_date).arg(end_date));
        if(flag == false){
            QMessageBox::critical(0,"失败","记录删除失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录删除成功");
            model3->select();
            ui->tableView->setModel(model3);
        }
    }
}

void Employee::on_pushButton_10_clicked(){//修改
    if (model3->submitAll()) {
        model3->database().commit();//提交
        QMessageBox::about(0,"成功","记录修改成功");

    } else {
        model3->database().rollback();//回滚
        QMessageBox::critical(0,"失败","修改失败",QMessageBox::Cancel);
    }
    model3->select();
    ui->tableView->setModel(model3);
}
