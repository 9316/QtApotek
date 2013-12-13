#include "addmed.h"
#include "ui_addmed.h"

AddMed::AddMed(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMed)
{
    ui->setupUi(this);
}

AddMed::~AddMed()
{
    delete ui;
}

void AddMed::on_pushButton_clicked()
{
    //ამოწმებს ცარიელია თუ არა რომელიმე ველი
    if(ui->lineEdit->text().size()>0 && ui->lineEdit_2->text().size()>0 && ui->lineEdit_3->text().size()>0
            && ui->lineEdit_4->text().size()>0 && ui->lineEdit_5->text().size()>0){
        imgUrl = ui->lineEdit_5->text();
        name = ui->lineEdit->text();
        desc = ui->lineEdit_2->text();
        amount = ui->lineEdit_4->text();
        price = ui->lineEdit_3->text();
        this->close();
    }
    else {
        QMessageBox::information(this, "შეცდომა", "შეავსეთ ყველა ველი!");
    }
}
