#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "reservation.h"
#include "QPlainTextEdit"
#include "QrCode.hpp"
#include "arduino.h"
#include <QMainWindow>
#include <QMessageBox>
QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();
    //void on_push_load_clicked();

    void on_pb_supprimer_clicked();

  void on_pb_modifier_clicked();


void initSerial() ;
 void on_search_2_clicked();
void readSerial() ;
 void on_trier_clicked();

void on_sendMail_clicked() ;
 void on_pdf_clicked();
     void readfile();
         void on_tabWidget_currentChanged();
         void on_calendarWidget_clicked(const QDate &date);
         void update_label();   // slot permettant la mise à jour du label état de la lampe 1,
         // ce slot est lancé à chaque réception d'un message de Arduino

         void on_pushButton_clicked();   // bouton ON

         void on_pushButton_2_clicked(); // bouton OFF

         void on_pushButton_3_clicked(); // bouton +

         void on_pushButton_4_clicked(); // bouton -

         void on_verif_clicked();   // bouton ON
          void on_QRcode_clicked();
private:
    Ui::MainWindow *ui;

    reservation C ;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire

       QPlainTextEdit *veri;
       QPushButton *verif;
};

#endif // MAINWINDOW_H
