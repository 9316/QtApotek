#include "dialog.h"
#include "ui_dialog.h"
#include <QInputDialog>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}
//იღებს მონაცემებს და აყენებს შესაბამის ლეიბლებზე
void Dialog::setLabels(QString name, QString price, QString amount, QString desc, QString imgurl){
    ui->labelName->setText("<b><font size=4>"+name + "</font></b>");
    ui->labelDesc->setText("<b><font size=4>"+desc + "</font></b>");
    ui->labelAmount->setText("<b><font size=4>"+amount + "</font></b>");
    ui->labelPrice->setText("<b><font size=4>"+price + "</font></b>");
    if(name=="გრიპოსადი (ჩაი)"){
        ui->webView->setUrl(QUrl::fromLocalFile("/home/alex/Pictures/Selection_011.png"));
    }
   else{ QUrl url(imgurl); //მისამართის ობიექტის შექმნა imgurl ცვლადით

    ui->webView->setUrl(url); //ვებ მისამართის ჩატვირთვა
    }
    p=price;
    a=amount;
}

void Dialog::on_pushButton_clicked()
{
    SellDialog d; //გაყიდვის დიალოგური ფანრჯის გახსნა
    d.getInfo(a,p);
    d.setModal(true);
    d.exec();
}
