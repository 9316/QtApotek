#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <mysortfilterproxymodel.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/medicined");
    db.open();
    model = new QSqlTableModel(this, db);  //სქლ-ის ცხრილის მოდელი
    model->setTable("med"); //მედ ცხრილის ამორცევა
    model->select(); //ცხრილი მონიშვნა
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //რედაქტირების მეთოდი (მექანიკური)
    model->removeColumn(0); //პირველი სვეტის წაშლა
    model->removeColumn(0);
    model->setHeaderData(0, Qt::Horizontal, tr("სახელი"));  //სვეტების სახელების დარქმევა
    model->setHeaderData(1, Qt::Horizontal, tr("აღწერა"));
    model->setHeaderData(2, Qt::Horizontal, tr("ფასი"));
    model->setHeaderData(3, Qt::Horizontal, tr("რაოდენობა"));

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //სტრიქონების ამორჩევის ამორჩევის მეთოდი
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection); //ამორჩევის მეთოდი (მხოლოდ ერთის ამორჩევა)
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); //რედაქტირების შეზღუდვა პირდაპირ ცხრილიდან
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionAdd_triggered(){
    QSqlQuery qry(db); 
    AddMed addmed; //AddMed კლასის ობიექტი
    QString sql = "INSERT INTO med (imageurl, name,description,price,amount)"
            "VALUES ('%1', '%2', '%3', %4, %5)"; //სქლ-ის ბრძანების სტრინგი
    addmed.setModal(true);
    addmed.exec(); //წამლის დამატების ფანჯრის გამოჩენა
    qDebug()<<addmed.imgUrl; //
    qry.exec(sql.arg(addmed.imgUrl) //სქლ ბრძანების გაშვება შესაბამისი არგუმენტებით
             .arg(addmed.name)
             .arg(addmed.desc)
             .arg(addmed.price)
             .arg(addmed.amount));
    QSqlRecord rec = model->record(); //სქლიდან დაბრუნებული ინფორმაციის ჩანაწერი
    model->setRecord(model->rowCount(),rec); //სქლ-ის მოდელში მონაცემის ჩამატება ჩანაწერის მიხედვით(rec)
    model->submitAll(); //ჩანაწერის დამტკიცება

}

void MainWindow::on_actionRemove_triggered()
{
    QSqlQuery qry(db);
    int rowid = ui->tableView->selectionModel()->selectedIndexes().at(0).row() + 1; //მონიშნული სტრიქონის ინდექსი
    QString str = "DELETE FROM med WHERE name=%1"; //სქლ ბრძანების სტრინგი (ამოშლა ID-ის მიხედვით)
    qry.exec(str.arg(rowid));
    model->submitAll();

}

void MainWindow::on_actionSearch_triggered()
{
    //ინფუთ დიალოგიდან getText მეთოდით შემოდის სიტყვა და იწერება სტრინგში
    QString search = QInputDialog::getText(this,"ძებნა","შეიყვანეთ საძიებო სიტყვა",QLineEdit::Normal);
    //შემდეგი ობიექტის საშუალებით ჩვენ გვექნება ახალი მოდელი რომელსაც ექნება გაფილტრვის(ძებნის) შესაძლებლობა
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model); //ძველი მოდელი მითითება
    //რის მიხედვით უნდა მოხდეს ძებნა. ამ შემთხვევაში არ აქვს მნიშვნელობა დიდ და პატარა ასოს, ელოდება სტრინგს
    proxyModel->setFilterRegExp(QRegExp(search, Qt::CaseInsensitive, QRegExp::FixedString));
    proxyModel->setFilterKeyColumn(-1); //სვეტების შემოზღუდვა (გათიშულია)
    ui->tableView->setModel(proxyModel); //ცხრილის ახალ მოდელზე დაფუძნება
    ui->tableView->show(); //ახალი მოდელის გამოყენება
    QSortFilterProxyModel *proxyModel_2 = new QSortFilterProxyModel(this);
    proxyModel_2->setSourceModel(proxyModel);
    proxyModel_2->setFilterRegExp(QRegExp("ანალგინი", Qt::CaseInsensitive, QRegExp::FixedString));
    proxyModel_2->setFilterKeyColumn(-1);
    ui->tableView->setModel(proxyModel_2);
    ui->tableView->show();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    //ცხრილის მოდელიდან იღებს ინფორმაციას, ცხრილის მოდელის ინდექსის მიხედვით და გადაყავს სტრინგში
    name = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    QString description = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    price = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString();
    QString amount = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString();
    QString imgurl;
    QSqlQuery qry(db);
    qry.prepare("SELECT imageurl FROM med WHERE name=:name"); //სქლ ბრძანების მომზადება გამოყენებისათვის
    qry.bindValue(":name",name); //:name იცვლება ჩვენი სტრინგით name
    qry.exec(); //გაშვება
    qry.next(); //აუცილებელია გამოძახება რომ დააბრუნოს მნიშვნელობა
    imgurl = qry.value(0).toString();
    Dialog showInfo; //ინფორმაციის დიალოგური ფანჯრის ობიექტის შექმნა
    showInfo.setLabels(name,price,amount,description,imgurl); //ობიექტში მონაცემების გადაცემა ფუნქციით
    showInfo.setModal(true);
    showInfo.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "პროგრამის შესახებ", "პროგრამა დაწერილია ნიკა ფანოზიშვილის მიერ");
}

void MainWindow::on_pushButton_clicked()
{
    double amount = ui->lineEdit->text().toDouble(); // ამოუნტს ენიჭება ტექსტი დობლში გადაყვანილი
    double money  = ui->lineEdit_2->text().toDouble();//
    double sum = amount*price.toDouble(); // რაოდენობა და მოცემული თანხა
    ui->label->setNum(sum); //
    ui->label_2->setNum(money-sum); //
    double amountLeft = amountAll.toDouble() -amount; //amountall რაოდენობას აკლდება ლაინ ედითიდან შემოტანილი რიცხვი
    QSqlQuery qry(db);
    QString sql = "UPDATE med SET amount=%1 WHERE name='%2'";
    if(amountLeft<0){
        QMessageBox::information(this, "შეჩდომა", "დარჩენილია მხოლოდ" + amountAll );
    }
    else{
    qry.exec(sql.arg(amountLeft).arg(name));
    model->submitAll();
     amountAll=QString::number(amountLeft);
    }


    }




void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    name = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),0)).toString();
    QString description = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),1)).toString();
    price = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),2)).toString();
    amountAll = ui->tableView->model()->data(ui->tableView->model()->index(index.row(),3)).toString();
    QString imgurl;
    QSqlQuery qry(db);
    qry.prepare("SELECT imageurl FROM med WHERE name=:name"); //სქლ ბრძანების მომზადება გამოყენებისათვის
    qry.bindValue(":name",name); //:name იცვლება ჩვენი სტრინგით name
    qry.exec(); //გაშვება
    qry.next(); //აუცილებელია გამოძახება რომ დააბრუნოს მნიშვნელობა

}
