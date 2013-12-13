#ifndef ADDMED_H
#define ADDMED_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddMed;
}

class AddMed : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddMed(QWidget *parent = 0);
    ~AddMed();
    QString imgUrl, name, desc, amount, price;
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddMed *ui;
};

#endif // ADDMED_H
