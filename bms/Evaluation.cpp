#include "Evaluation.h"
#include "ui_Evaluation.h"

Evaluation::Evaluation(QWidget *parent) :
    BaseWindow(parent),
    ui(new Ui::Evaluation)
{
    ui->setupUi(this);
    setFixedSize(this->width(), this->height());           //固定窗口大小
    QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    db1 = QSqlDatabase::database("a");
    model = new QSqlTableModel(this, db1);         //连了默认数据库
    model->setTable(codec->toUnicode("绩效评判")); // table
    model->select();
    ui->tableView->horizontalHeader()->setSectionResizeMode(
          QHeaderView::Stretch);
    ui->tableView->setModel(model);

    ui->lineEdit->setPlaceholderText("等级");
}

Evaluation::~Evaluation()
{
    delete ui;
}

void Evaluation::on_KPI_pushButton_clicked()//查询
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //或者"GBK",不分大小写
    QTextCodec::setCodecForLocale(codec);
    model->setTable(codec->toUnicode("绩效评判"));
    double down = ui->doubleSpinBox->value();
    double up = ui->doubleSpinBox_2->value();

    if(down > up){
        QMessageBox::warning(0, "警告", "下限大于上限", QMessageBox::Yes);
        return;
    }

    model->setFilter(QString("得分下限 >= '%1' and 得分上限 <= '%2'").arg(down).arg(up));
    model->select();
    ui->tableView->setModel(model);
}

void Evaluation::on_KPI_pushButton_2_clicked()//增加
{
    double down = ui->doubleSpinBox_3->value();
    double up = ui->doubleSpinBox_4->value();
    QString degree = ui->lineEdit->text();
    double money = ui->doubleSpinBox_5->value();
    if(degree == NULL){
        QMessageBox::warning(0, "警告", "请填入等级", QMessageBox::Yes);
        return;
    }
    QSqlQuery query(db1);
    bool flag = query.exec(QString("insert into 绩效评判 values('%1','%2','%3','%4')").arg(down).arg(up).arg(degree).arg(money));
    if (flag == false) {
        QMessageBox::critical(0, "失败", "可能该等级已存在或上下限已存在", QMessageBox::Cancel);
    } else {
        QMessageBox::about(0, "成功", "记录增加成功");
        model->select();
        ui->tableView->setModel(model);
    }
}

void Evaluation::on_KPI_pushButton_3_clicked()//修改
{
    if (model->submitAll()) {
        model->database().commit();
        QMessageBox::about(0, "恭喜", "修改成功");

    } else {
        model->database().rollback();
        QMessageBox::critical(0, "失败", "修改失败", QMessageBox::Cancel);
    }
    model->select();
    ui->tableView->setModel(model);
}


void Evaluation::on_KPI_pushButton_4_clicked()
{
    int row = ui->tableView->currentIndex().row();

    QString str = QString("你确定删除当前第").append(QString("%1").arg(row+1)).append("行吗?");
    int ok = QMessageBox::warning(this,tr("删除当前行!"),str,QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes)
    {
        model->removeRow(row);
        model->submitAll();

    }
    model->select();
    ui->tableView->setModel(model);
}

void Evaluation::on_back_clicked()
{
    emit sendsignal();
    this->close();
}
