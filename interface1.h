#ifndef INTERFACE1_H
#define INTERFACE1_H

#include "client.h"
#include "arduino.h"
#include <QTimer>
#include <QMessageBox>
#include "smtp.h"
#include "employe.h"
#include <QWidget>
#include "voitures.h"
#include <QMainWindow>

#include <QDialog>

namespace Ui {
class interface1;
}

class interface1 : public QMainWindow

{
    Q_OBJECT

public:
    explicit interface1(QWidget *parent = nullptr);
    ~interface1();

private slots:
    void readDataFromArduino();
    void on_pushButton_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_rechercher_textChanged(const QString &arg1);

    void on_comboBoxTri_currentIndexChanged(int index);








    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();
    void on_ajouter_clicked();
    void on_chercher_clicked();
    void on_supprimser_clicked();
    void on_modifier_clicked();
    void on_pushButton_trianne_clicked();
    void on_tritarifs_clicked();
    void on_stat_clicked();
    void on_pdf_sara_clicked();










    void on_pushButton_4_clicked();



    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_qu_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_calendarWidget_selectionChanged();



    void on_pushButton_19_clicked();
    bool isValidEmail(const QString &email);
    void sendMail();
    //void readDataFromArduino();

    void on_pushButton_arduino_clicked();
    void onReadyRead();

    void loop() ;


    void on_pushButton_21_clicked();

    void on_ajouter_vo_clicked();

    void on_supp_sara_clicked();

    void on_modifier_2_clicked();

    void on_chercher_sara_clicked();

    void on_stat_sarah_clicked();

    void on_tarifs_clicked();

    void on_pushButton_trianne_2_clicked();

    void on_kilometrage_clicked();

    void on_pushButton_22_clicked();

signals:
    void signal_arduino(int code);

private:
    QSerialPort *serial;  // Declare QSerialPort object
    Ui::interface1 *ui;
    employe E;
    QSqlQueryModel *model;
smtp *smtpClient;
    client etmp;
    client foundClient;
  arduino myArduino;
  QByteArray data; // variable contenant les données reçues
  QTimer *timer;
  voitures etm;



};
#endif // INTERFACE1_H
