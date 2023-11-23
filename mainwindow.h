#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"client.h"
#include<QDialog>
#include<QSqlQueryModel>
#include"smtp.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

      void on_pushButton_clicked();
      void on_on_pushButton_ajouter_clicked_clicked();
      void on_pushButton_2_clicked();

      void on_pushButton_3_clicked();


      void on_pushButton_4_clicked();

      void on_pushButton_5_clicked();

      void on_pushButton_6_clicked();
      void sendMail();
      bool isValidEmail(const QString &email);


private:
    Ui::MainWindow *ui;
    client etmp;
    client foundClient;
    smtp* smtpClient;









};

#endif // MAINWINDOW_H
