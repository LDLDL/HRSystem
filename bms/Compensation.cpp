#include "Compensation.h"
#include "ui_Compensation.h"

Compensation::Compensation(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::Compensation)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());//固定窗口大小
    db1 = QSqlDatabase::database("a");
//    db2 = QSqlDatabase::database("b");
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    //1
    model = new QSqlTableModel(this,db1);//连了默认数据库
    model->setTable(codec->toUnicode("员工工资"));//view
    model->select();
    ui->Com_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->Com_tableView->setModel(model);
    ui->Com_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->Com_lineEdit->setPlaceholderText("员工编号");
    setComboBox_YEAR();//年框

    //2
    model2 = new QSqlTableModel(this,db1);//连了默认数据库
    model2->setTable(codec->toUnicode("基本薪酬"));//table
    model2->select();
    ui->Com_tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->Com_tableView_2->setModel(model2);
    ui->Com_tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->Com_lineEdit_2->setPlaceholderText("员工编号");
    ui->Com_lineEdit_3->setPlaceholderText("员工编号");
    ui->Com_lineEdit_19->setPlaceholderText("备注");

    //3
    model3 = new QSqlTableModel(this,db1);//连了默认数据库
    model3->setTable(codec->toUnicode("员工调薪"));//view
    model3->select();
    ui->Com_tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->Com_tableView_3->setModel(model3);
    ui->Com_tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->Com_lineEdit_4->setPlaceholderText("员工编号");

    //4
    model4 = new QSqlTableModel(this,db1);//连了默认数据库
    model4->setTable(codec->toUnicode("员工奖惩"));//view
    model4->select();
    ui->Com_tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->Com_tableView_4->setModel(model4);

    ReadOnlyDelegate* readOnlyDelegate = new ReadOnlyDelegate();
    ui->Com_tableView_4->setItemDelegateForColumn(0, readOnlyDelegate); //设置某列只读
    ui->Com_tableView_4->setItemDelegateForColumn(1, readOnlyDelegate); //设置某列只读
    ui->Com_tableView_4->setItemDelegateForColumn(2, readOnlyDelegate); //设置某列只读
    ui->Com_tableView_4->setItemDelegateForColumn(3, readOnlyDelegate); //设置某列只读
    ui->Com_tableView_4->setSelectionBehavior(QAbstractItemView::SelectRows);//选中只能选中行
    ui->Com_lineEdit_5->setPlaceholderText("员工编号");
    ui->Com_lineEdit_6->setPlaceholderText("员工编号");
    ui->Com_lineEdit_7->setPlaceholderText("原因");


    setComboBox_BM();

    //5
    model5 = new QSqlTableModel(this,db1);//连了默认数据库
    model5->setTable(codec->toUnicode("学历津贴"));//table
    model5->select();
    ui->Com_tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->Com_tableView_5->setModel(model5);
    ui->Com_tableView_5->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->Com_lineEdit_8->setPlaceholderText("学历情况");
    ui->Com_lineEdit_20->setPlaceholderText("学历情况");
    setComboBox_XL();

    //6
    model6 = new QSqlTableModel(this,db1);
    model6->setTable(codec->toUnicode("工龄工资"));//table
    model6->select();
    ui->Com_tableView_11->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//使得tableView里内容适应于tableView的大小
    ui->Com_tableView_11->setModel(model6);
}

Compensation::~Compensation()
{
    delete ui;
}


void Compensation::on_Com_listWidget_itemClicked(QListWidgetItem *item)//侧边栏,点击时更新，保证数据同步
{
   int row =  ui->Com_listWidget->currentRow();
    ui->Com_stackedWidget->setCurrentIndex(row);
    if(row == 0){
        model->select();
        ui->Com_tableView->setModel(model);
    }
    if(row == 1){
        model2->select();
        ui->Com_tableView_2->setModel(model2);
    }
    if(row == 2){
        model3->select();
        ui->Com_tableView_3->setModel(model3);
    }
    if(row == 3){
        model4->select();
        ui->Com_tableView_4->setModel(model4);
    }
    if(row == 4){
        model5->select();
        ui->Com_tableView_5->setModel(model5);
    }
    if(row == 5){
        model6->select();
        ui->Com_tableView_11->setModel(model6);
    }
}

void  Compensation::setComboBox_BM(){//部门下拉框
    QSqlQuery query(db1);
    query.exec("select *from 部门");
    ui->Com_comboBox->clear();
    ui->Com_comboBox_3->clear();
     ui->Com_comboBox->addItem("");
     ui->Com_comboBox_3->addItem("");

    while (query.next()) {
        QString str = query.value(0).toString();
        QString str2 = query.value(1).toString();
        str.append("(").append(str2).append(")");
        ui->Com_comboBox->addItem(str);
        ui->Com_comboBox_3->addItem(str);
    }
}

void Compensation::setComboBox_YEAR(){//年框
    QString year = QDateTime::currentDateTime().toString("yyyy");
    int num = year.toInt();
    ui->Com_comboBox_10->clear();
    ui->Com_comboBox_10->addItem("");

    while(num >= 2018){//年
        QString str = QString("%1").arg(num);
        ui->Com_comboBox_10->addItem(str);

        num -=1;
    }
}
void  Compensation::setComboBox_XL(){//学历框
    QSqlQuery query(db1);
    query.exec("select 学历情况 from 学历津贴");
    ui->Com_comboBox_7->clear();
    ui->Com_comboBox_8->clear();
    while (query.next()) {
        QString str = query.value(0).toString();
        ui->Com_comboBox_7->addItem(str);
        ui->Com_comboBox_8->addItem(str);
    }
}

void Compensation::on_Com_comboBox_currentIndexChanged(int index)//职位框
{
    QString bm = ui->Com_comboBox->currentText();
        QString end = "(";
        int num = bm.lastIndexOf(end);
        bm = bm.left(num);
        QSqlQuery query(db1);
        query.exec(QString("select 职位名称 from 职位 where 部门编号 = '%1'").arg(bm));
        ui->Com_comboBox_2->clear();
        ui->Com_comboBox_2->addItem("");
        while(query.next()){
            ui->Com_comboBox_2->addItem(query.value(0).toString());
        }
}

void Compensation::on_Com_comboBox_3_currentIndexChanged(int index)//职位框
{
    QString bm = ui->Com_comboBox_3->currentText();
        QString end = "(";
        int num = bm.lastIndexOf(end);
        bm = bm.left(num);
        QSqlQuery query(db1);
        query.exec(QString("select 职位名称 from 职位 where 部门编号 = '%1'").arg(bm));
        ui->Com_comboBox_4->clear();
        ui->Com_comboBox_4->addItem("");
        while(query.next()){
            ui->Com_comboBox_4->addItem(query.value(0).toString());
        }
}

/*---------------------税前薪酬------------------------*/

void Compensation::on_Com_pushButton_clicked()//查询
{

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model->setTable(codec->toUnicode("员工工资"));//view

    //年，月，编号
    QString year = ui->Com_comboBox_10->currentText();
    QString month = ui->Com_comboBox_9->currentText();
    QString no = ui->Com_lineEdit->text();
    qDebug()<<"年"<<year;

    QString sqlstr;
    if(no != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(no));

    }
    if(year != NULL){
        sqlstr.append(" and ").append(QString("年份 = '%1'").arg(year));

    }

    if(month != NULL){
        sqlstr.append(" and ").append(QString("月份 = '%1'").arg(month));

    }
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    qDebug()<<sqlstr;
    model->setFilter(sqlstr);
    model->select();
    ui->Com_tableView->setModel(model);

}

/*--------------------基本薪酬------------------------*/

void Compensation::on_Com_pushButton_2_clicked()//查询
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model2->setTable(codec->toUnicode("基本薪酬"));//table
    QString no = ui->Com_lineEdit_2->text();
    if(no != NULL){
        model2->setFilter(QString("员工编号 = '%1'").arg(no));
    }
    model2->select();
    ui->Com_tableView->setModel(model2);
}

void Compensation::on_Com_pushButton_3_clicked()//修改
{
    QString no = ui->Com_lineEdit_3->text();
    QString bz = ui->Com_lineEdit_19->text();
    if(no == NULL){
        QMessageBox::warning(0,"警告","请输入员工编号",QMessageBox::Cancel);
        return;
    }

    double gz = ui->Com_doubleSpinBox->value();
    QSqlQuery query(db1);
    bool flag = query.exec(QString("CALL 编号调薪('%1','%2','%3')").arg(no).arg(gz).arg(bz));
    if(flag == false){
        QMessageBox::critical(0,"失败","基本薪酬修改失败",QMessageBox::Cancel);
    }else{
        QMessageBox::about(0,"成功","基本薪酬修改成功");
        model2->select();
        ui->Com_tableView_2->setModel(model2);

    }
}
/*--------------------调薪记录------------------------*/

void Compensation::on_Com_pushButton_4_clicked()//查询
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
        QTextCodec::setCodecForLocale(codec);
        model3->setTable(codec->toUnicode("员工调薪"));//table


    QString start = ui->Com_dateEdit_2->text();
    QString end = ui->Com_dateEdit_3->text();
    QString no = ui->Com_lineEdit_4->text();


    qDebug()<<start;
    qDebug()<<end;
    QString bmname = ui->Com_comboBox_3->currentText();
    int bstart = bmname.lastIndexOf("(");
    int bend = bmname.lastIndexOf(")");
    bmname = bmname.mid(bstart+1,bend-bstart-1);
    qDebug()<<bmname;

    QString zw = ui->Com_comboBox_4->currentText();
    qDebug()<<zw;

    QString sqlstr;
    if(no != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(no));
    }
    if(bmname != NULL){
        sqlstr.append(" and ").append(QString("部门名称 = '%1'").arg(bmname));
    }
    if(zw != NULL){
        sqlstr.append(" and ").append(QString("职位名称 = '%1'").arg(zw));
    }

    sqlstr.append(" and ").append(QString("日期 between '%1' and  '%2' ").arg(start).arg(end));
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    model3->setFilter(sqlstr);
    model3->select();
    ui->Com_tableView_3->setModel(model3);
}

/*--------------------奖惩记录------------------------*/

void Compensation::on_Com_pushButton_6_clicked()//修改
{
    if(model4->submitAll()){//提交所有更改
        model4->database().commit();
        QMessageBox::about(0,"恭喜","修改成功");
    }else{
        model4->database().rollback();//回滚
        QMessageBox::critical(0,"失败","修改失败",QMessageBox::Cancel);
    }
    model4->select();
    ui->Com_tableView_4->setModel(model4);

}

void Compensation::on_Com_pushButton_7_clicked()//删除
{

    int row = ui->Com_tableView_4->currentIndex().row();

    QString str = QString("你确定删除当前第").append(QString("%1").arg(row+1)).append("行吗?");
    int ok = QMessageBox::warning(this,tr("删除当前行!"),str,QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::Yes)
    {
        QModelIndex index = model4->index(row,0);
        QString no = model4->data(index).toString();
        QModelIndex index2 = model4->index(row,4);
        QString day = model4->data(index2).toString();
        QModelIndex index3 = model4->index(row,5);
        QString money = model4->data(index3).toString();
        QModelIndex index4 = model4->index(row,6);
        QString reason = model4->data(index4).toString();

        QSqlQuery query(db1);
        bool flag = query.exec(QString("delete from 奖惩记录 where  员工编号 = '%1' and 日期 = '%2' and 奖惩金额 = '%3' and 原因 = '%4'").arg(no).arg(day).arg(money).arg(reason));
        if(flag == false){
            QMessageBox::critical(0,"失败","记录删除失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录删除成功");
            model4->select();
            ui->Com_tableView_4->setModel(model4);
        }
    }


}

void Compensation::on_Com_pushButton_8_clicked()//查询
{

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model4->setTable(codec->toUnicode("员工奖惩"));//view

    /*员工编号*/
    QString no = ui->Com_lineEdit_5->text();

    /*部门名称*/
    QString bmname = ui->Com_comboBox->currentText();
    int start = bmname.lastIndexOf("(");
    int end = bmname.lastIndexOf(")");
    bmname = bmname.mid(start+1,end-start-1);
    qDebug()<<bmname;

    /*职位名称*/
    QString zw = ui->Com_comboBox_2->currentText();
    qDebug()<<zw;

     QString sqlstr;
    if(no != NULL){
        sqlstr.append(QString("员工编号 = '%1'").arg(no));
    }
    if(bmname != NULL){
        sqlstr.append(" and ").append(QString("部门名称 = '%1'").arg(bmname));
    }
    if(zw != NULL){
        sqlstr.append(" and ").append(QString("职位名称 = '%1'").arg(zw));

    }
    if(sqlstr.startsWith(" and ")){
        sqlstr = sqlstr.right(sqlstr.size()-5);
    }
    qDebug()<<sqlstr;
    model4->setFilter(sqlstr);
    model4->select();
    ui->Com_tableView_4->setModel(model4);
}



void Compensation::on_Com_pushButton_9_clicked()//增加记录
{
    QString no = ui->Com_lineEdit_6->text();//员工编号
    QString day = ui->Com_dateEdit->text(); //日期
    QString money = ui->Com_doubleSpinBox_2->text();//金额
    QString reason = ui->Com_lineEdit_7->text();

    if(no!=NULL && day!=NULL && money!=NULL && reason!=NULL){
        QSqlQuery query(db1);
        bool flag = query.exec(QString("insert into 奖惩记录 values('%1','%2','%3','%4')").arg(no).arg(day).arg(money).arg(reason));
        if(flag == false){
            QMessageBox::critical(0,"失败","记录增加失败",QMessageBox::Cancel);
        }else{
            QMessageBox::about(0,"成功","记录增加成功");
            model4->select();
            ui->Com_tableView_4->setModel(model4);
        }
    }else{
         QMessageBox::warning(0,"警告","请补全增加的信息",QMessageBox::Yes);
    }
}

/*--------------------学历津贴------------------------*/

void Compensation::on_Com_pushButton_10_clicked()//查询
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model5->setTable(codec->toUnicode("学历津贴"));//table

    QString xl = ui->Com_lineEdit_8->text();
    if(xl != NULL){
        model5->setFilter(QString("学历情况 = '%1'").arg(xl));
    }
    model5->select();
    ui->Com_tableView_5->setModel(model5);
}

void Compensation::on_Com_pushButton_11_clicked()//增加
{
    QString xl = ui->Com_lineEdit_20->text();
    double money = ui->Com_doubleSpinBox_3->value();

    if(xl == NULL){
        QMessageBox::warning(0,"警告","请输入学历情况",QMessageBox::Yes);
        return;
    }

    if(money == 0.00){
        QMessageBox::warning(0,"警告","请输入津贴金额",QMessageBox::Yes);
        return;
    }

    QSqlQuery query(db1);
    bool flag = query.exec(QString("insert into 学历津贴 values('%1','%2')").arg(xl).arg(money));
    if(flag == false){
        QMessageBox::critical(0,"失败","记录增加失败",QMessageBox::Cancel);
    }else{
        QMessageBox::about(0,"成功","记录增加成功");
        model5->select();
        ui->Com_tableView_5->setModel(model5);

        /*下拉框增加数据*/
        ui->Com_comboBox_8->addItem(xl);
        ui->Com_comboBox_7->addItem(xl);
    }
}

void Compensation::on_Com_pushButton_12_clicked()//删除
{
     QString xl = ui->Com_comboBox_7->currentText();
     int index = ui->Com_comboBox_7->currentIndex();
     QSqlQuery query(db1);
     bool flag = query.exec(QString("delete from 学历津贴 where 学历情况 = '%1'").arg(xl));
     if(flag == false){
         QMessageBox::critical(0,"失败","记录删除失败",QMessageBox::Cancel);
     }else{
         QMessageBox::about(0,"成功","记录删除成功");
         model5->select();
         ui->Com_tableView_5->setModel(model5);

         /*下拉框删除数据*/
         ui->Com_comboBox_7->removeItem(index);
         ui->Com_comboBox_8->removeItem(index);
     }
}

void Compensation::on_Com_pushButton_13_clicked()//修改
{
    QString xl = ui->Com_comboBox_8->currentText();
    double money = ui->Com_doubleSpinBox_8->value();
    if(money == 0.00){
        QMessageBox::warning(0,"警告","请输入津贴金额",QMessageBox::Yes);
        return;
    }
    QSqlQuery query(db1);
    bool flag = query.exec(QString("update 学历津贴 set 津贴 = '%1' where 学历情况 = '%2'").arg(money).arg(xl));
    if(flag == false){
        QMessageBox::critical(0,"失败","记录修改失败",QMessageBox::Cancel);
    }else{
        QMessageBox::about(0,"成功","记录修改成功");
    }
    model5->select();
    ui->Com_tableView_5->setModel(model5);

}

/*--------------------工龄工资------------------------*/

void Compensation::on_Com_pushButton_27_clicked()//查找
{

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");//或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model6->setTable(codec->toUnicode("工龄工资"));

    QString down = ui->Com_spinBox->text();
    QString up = ui->Com_spinBox_2->text();

    model6->setFilter(QString("工龄下限 >= '%1' and 工龄上限 <= '%2'").arg(down).arg(up));
    model6->select();
    ui->Com_tableView_11->setModel(model6);
}

void Compensation::on_Com_pushButton_29_clicked()//增加
{
    QString down = ui->Com_spinBox_3->text();
    QString up = ui->Com_spinBox_4->text();
    QString money = ui->Com_doubleSpinBox_7->text();
    if(down.toInt() > up.toInt()){
        QMessageBox::warning(0,"警告","上限不能小于下限",QMessageBox::Yes);
        return;
    }
    QSqlQuery query(db1);
    bool flag = query.exec(QString("insert into 工龄工资 values('%1','%2','%3')").arg(down).arg(up).arg(money));
    if(flag == false){
        QMessageBox::critical(0,"失败","下限或上限已经存在",QMessageBox::Cancel);
    }else{
        QMessageBox::about(0,"成功","记录增加成功");
        model6->select();
        ui->Com_tableView_11->setModel(model6);
    }  
}

void Compensation::on_Com_pushButton_28_clicked()//删除 对table
{
    int row = ui->Com_tableView_11->currentIndex().row();

        QString str = QString("你确定删除当前第").append(QString("%1").arg(row+1)).append("行吗?");
        int ok = QMessageBox::warning(this,tr("删除当前行!"),str,QMessageBox::Yes,QMessageBox::No);
        if(ok == QMessageBox::Yes)
        {
            model6->removeRow(row);
            model6->submitAll();

        }
        model6->select();
        ui->Com_tableView_11->setModel(model6);
}

void Compensation::on_Com_pushButton_30_clicked()//修改
{
    if (model6->submitAll()) {
        model6->database().commit();//提交
        QMessageBox::about(0,"成功","记录修改成功");

    } else {
        model6->database().rollback();//回滚
        QMessageBox::critical(0,"失败","下限或上限已经存在",QMessageBox::Cancel);
    }
    model6->select();
    ui->Com_tableView_11->setModel(model6);
}



void Compensation::on_Com_back_clicked()//返回
{
    emit sendsignal();
    this->close();
}

