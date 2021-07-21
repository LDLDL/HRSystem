#include "Performance.h"
#include "ui_Performance.h"

Performance::Performance(QWidget *parent)
    : BaseWindow(parent), ui(new Ui::Performance) {
  ui->setupUi(this);

  setFixedSize(this->width(), this->height());           //固定窗口大小
  QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //或者"GBK",不分大小写
  QTextCodec::setCodecForLocale(codec);
  db1 = QSqlDatabase::database("a");
  model = new QSqlTableModel(this, db1);         //连了默认数据库
  model->setTable(codec->toUnicode("员工绩效")); // view
  model->select();
  ui->KPI_tableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch); //使得tableView里内容适应于tableView的大小
  ui->KPI_tableView->setModel(model);
  ReadOnlyDelegate *readOnlyDelegate = new ReadOnlyDelegate();
  ui->KPI_tableView->setItemDelegateForColumn(0,
                                              readOnlyDelegate); //设置某列只读
  ui->KPI_tableView->setItemDelegateForColumn(1,
                                              readOnlyDelegate); //设置某列只读
  ui->KPI_tableView->setItemDelegateForColumn(2,
                                              readOnlyDelegate); //设置某列只读
  ui->KPI_tableView->setItemDelegateForColumn(3,
                                              readOnlyDelegate); //设置某列只读
  ui->KPI_tableView->setItemDelegateForColumn(7,
                                              readOnlyDelegate); //设置某列只读

  ui->KPI_lineEdit->setPlaceholderText("员工编号");
  ui->KPI_lineEdit_2->setPlaceholderText("员工姓名");
  ui->KPI_lineEdit_3->setPlaceholderText("员工编号");

  model->setEditStrategy(
      QSqlTableModel::
          OnManualSubmit); //设置保存策略为手动提交，OnManualSubmit表明我们要提交修改才能使其生效。

  setComboBox();
}

Performance::~Performance() { delete ui; }

void Performance::setComboBox() { //部门选框设置，年份框设置，绩效框设置
  QSqlQuery query(db1);
  query.exec("select *from 部门");
  ui->KPI_comboBox->clear();
  ui->KPI_comboBox->addItem("");

  //获取部门编号+名称
  while (query.next()) {
    QString str = query.value(0).toString();
    QString str2 = query.value(1).toString();
    str.append("(").append(str2).append(")");
    qDebug() << str;
    ui->KPI_comboBox->addItem(str);
  }
  //获取当前年份
  QString year = QDateTime::currentDateTime().toString("yyyy");
  int num = year.toInt();

  //框设值
  ui->KPI_comboBox_3->clear();
  ui->KPI_comboBox_3->addItem("");
  ui->KPI_comboBox_6->clear();
  ui->KPI_comboBox_6->addItem("");
  while (num >= 2018) { //年
    QString str = QString("%1").arg(num);
    ui->KPI_comboBox_3->addItem(str);
    ui->KPI_comboBox_6->addItem(str);
    num -= 1;
  }

  //绩效框KPI_comboBox_5
  query.exec("select 绩效等级 from 绩效评判");
  ui->KPI_comboBox_5->addItem("");
  while(query.next()){
      ui->KPI_comboBox_5->addItem(query.value(0).toString());
  }
}

void Performance::on_KPI_comboBox_currentIndexChanged(int index) //职位选框设置，在部门选框信号槽设置
{
  QString bm = ui->KPI_comboBox->currentText();
  QString end = "(";
  int num = bm.lastIndexOf(end);
  bm = bm.left(num);
  QSqlQuery query(db1);
  query.exec(
      QString("select 职位名称 from 职位 where 部门编号 = '%1'").arg(bm));
  ui->KPI_comboBox_2->clear();
  ui->KPI_comboBox_2->addItem("");
  while (query.next()) {
    ui->KPI_comboBox_2->addItem(query.value(0).toString());
  }
}

void Performance::on_KPI_pushButton_clicked() //查询
{
  QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //或者"GBK",不分大小写
  QTextCodec::setCodecForLocale(codec);
  model->setTable(codec->toUnicode("员工绩效"));

  QString no = ui->KPI_lineEdit->text();
  QString name = ui->KPI_lineEdit_2->text();
  qDebug() << no;
  //部门内容
  QString bmname = ui->KPI_comboBox->currentText();
  int start = bmname.lastIndexOf("(");
  int end = bmname.lastIndexOf(")");
  bmname = bmname.mid(start + 1, end - start - 1);
  qDebug() << bmname;
  QString zw = ui->KPI_comboBox_2->currentText();
  QString year = ui->KPI_comboBox_3->currentText();
  QString month = ui->KPI_comboBox_4->currentText();
  QString degree = ui->KPI_comboBox_5->currentText();

  QString sqlstr;
  if (no != NULL) {
    sqlstr.append(QString("员工编号 = '%1'").arg(no));
  }
  if (name != NULL) {
    sqlstr.append(" and ").append(QString("员工姓名 = '%1'").arg(name));
  }
  if (bmname != NULL) {
    sqlstr.append(" and ").append(QString("部门名称 = '%1'").arg(bmname));
  }
  if (zw != NULL) {
    sqlstr.append(" and ").append(QString("职位名称 = '%1'").arg(zw));
  }
  if (year != NULL) {
    sqlstr.append(" and ").append(QString("年份 = '%1'").arg(year));
  }
  if (month != NULL) {
    sqlstr.append(" and ").append(QString("月份 = '%1'").arg(month));
  }
  if (degree != NULL) {
    sqlstr.append(" and ").append(QString("绩效等级 = '%1'").arg(degree));
  }
  if (sqlstr.startsWith(" and ")) {
    sqlstr = sqlstr.right(sqlstr.size() - 5);
  }
  qDebug() << sqlstr;
  model->setFilter(sqlstr);
  model->select();
  ui->KPI_tableView->setModel(model);
}

void Performance::on_KPI_pushButton_2_clicked() //增加
{
  QString no = ui->KPI_lineEdit_3->text();
  QString year = ui->KPI_comboBox_6->currentText();
  QString month = ui->KPI_comboBox_7->currentText();
  QString score = ui->KPI_doubleSpinBox->text();
  if (no != NULL && year != NULL && month != NULL && score != NULL) {
    QSqlQuery query(db1);
    bool flag =
        query.exec(QString("insert into 绩效记录 values('%1','%2','%3','%4')")
                       .arg(no)
                       .arg(year)
                       .arg(month)
                       .arg(score));
    if (flag == false) {
      QMessageBox::critical(0, "失败", "记录增加失败", QMessageBox::Cancel);
    } else {
      QMessageBox::about(0, "成功", "记录增加成功");
      model->select();
      ui->KPI_tableView->setModel(model);
    }
  } else {
    QMessageBox::warning(0, "警告", "请补全增加的信息", QMessageBox::Yes);
  }
}

void Performance::on_KPI_pushButton_3_clicked() //修改
{
  if (model->submitAll()) {
    model->database().commit();
    QMessageBox::about(0, "恭喜", "修改成功");

  } else {
    model->database().rollback();
    QMessageBox::critical(0, "失败", "修改失败", QMessageBox::Cancel);
  }
  model->select();
  ui->KPI_tableView->setModel(model);
}

void Performance::on_KPI_pushButton_4_clicked() // view的删除
{
  int row = ui->KPI_tableView->currentIndex().row();

  QString str = QString("你确定删除当前第")
                    .append(QString("%1").arg(row + 1))
                    .append("行吗?");
  int ok = QMessageBox::warning(this, tr("删除当前行!"), str, QMessageBox::Yes,
                                QMessageBox::No);
  if (ok == QMessageBox::Yes) {

    QModelIndex index = model->index(row, 0);
    QString no = model->data(index).toString();
    QModelIndex index2 = model->index(row, 4);
    QString year = model->data(index2).toString();
    QModelIndex index3 = model->index(row, 5);
    QString month = model->data(index3).toString();

    QSqlQuery query(db1);
    bool flag = query.exec(QString("delete from 绩效记录 where  员工编号 = "
                                   "'%1' and 年份 = '%2' and 月份 = '%3'")
                               .arg(no)
                               .arg(year)
                               .arg(month));
    if (flag == false) {
      QMessageBox::critical(0, "失败", "记录删除失败", QMessageBox::Cancel);
    } else {
      QMessageBox::about(0, "成功", "记录删除成功");
    }
    model->select();
    ui->KPI_tableView->setModel(model);
  }
}

void Performance::on_KPI_back_clicked()//返回
{
    emit sendsignal();
    this->close();
}

void Performance::initTitleBar()
{
    // 设置标题栏跑马灯效果，可以不设置;
    m_titleBar->setTitleRoll();
    m_titleBar->setBackgroundColor(56,70,85);
    m_titleBar->setTitleIcon(":/bms.ico");
    m_titleBar->setTitleContent(QStringLiteral("~~~~~~这里是绩效管理 (*^_^*) ~~~~"));
    m_titleBar->setButtonType(MIN_MAX_BUTTON);
    m_titleBar->setTitleWidth(this->width());
}

void Performance::on_pushButton_clicked()
{
    Evaluation *e = new Evaluation;
    e->setWindowTitle("绩效评判");
    connect(e,SIGNAL(sendsignal()),this,SLOT(show()));//接收到上一个窗口的信号，然后show
    this->hide();
    e->show();
}
