#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <selldialog.h>


namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setLabels(QString name, QString price, QString amount, QString desc, QString imgurl);
    QString a,p;
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
