#ifndef SELLDIALOG_H
#define SELLDIALOG_H

#include <QDialog>

namespace Ui {
class SellDialog;
}

class SellDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SellDialog(QWidget *parent = 0);
    ~SellDialog();
    void getInfo(QString, QString);
    QString a,p;
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::SellDialog *ui;
};

#endif // SELLDIALOG_H
