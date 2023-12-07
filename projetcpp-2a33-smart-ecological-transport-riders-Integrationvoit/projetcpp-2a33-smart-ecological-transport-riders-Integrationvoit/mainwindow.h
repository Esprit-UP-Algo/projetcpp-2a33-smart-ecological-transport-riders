#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employe.h"
#include "arduino.h"
#include <QTimer>
#include <QMessageBox>
#include <QDialog>

namespace Ui {
class mainwindow;
}

class mainwindow : public QDialog
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
private slots:
    void readDataFromArduino();
private:
    Ui::mainwindow *ui;
    arduino myArduino;
        employe myEmployee;
        QTimer *timer;
};

#endif // MAINWINDOW_H

