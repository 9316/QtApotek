#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <addmed.h>
#include <dialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSqlDatabase db;
    QSqlTableModel *model;
    QString price;
    QString amountAll;
    QString name;
    
private slots:
    void on_actionAdd_triggered();

    void on_actionRemove_triggered();

    void on_actionSearch_triggered();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionAbout_triggered();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
