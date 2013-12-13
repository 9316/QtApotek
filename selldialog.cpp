#include "selldialog.h"
#include "ui_selldialog.h"
#include <QSqlQuery>
#include <mainwindow.h>

SellDialog::SellDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SellDialog)
{
    ui->setupUi(this);
    setWindowTitle("გაყიდვა");
}

SellDialog::~SellDialog()
{
    delete ui;
}
void SellDialog::getInfo(QString am, QString pr){
    a=am;
    p=pr;
}

void SellDialog::on_pushButton_clicked()
{
    double amount = ui->lineEdit->text().toDouble();
    double money  = ui->lineEdit_2->text().toDouble();
    double sum = amount*p.toDouble();
    ui->label->setNum(sum);
    ui->label_2->setNum(money-sum);


}
