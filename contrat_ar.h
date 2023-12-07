#ifndef CONTRAT_AR_H
#define CONTRAT_AR_H

#include <QWidget>
#include "arduino.h"
#include "contrat.h"

namespace Ui {
class contrat_ar;
}

class contrat_ar : public QWidget
{
    Q_OBJECT

public:
    explicit contrat_ar(QWidget *parent = nullptr);
    ~contrat_ar();

private slots:
    void on_pushButton_clicked();

    void on_caa_clicked();

private:
    Ui::contrat_ar *ui;
    Arduino A;
     QByteArray data;
     contrat c;

};

#endif // CONTRAT_AR_H
