#ifndef INTERFACE1_H
#define INTERFACE1_H
#include "employe.h"
#include <QWidget>
#include <QWidget>

#include <QDialog>
/*struct attivita{
    QString tipo;
    QString titolo;
    QTime start;
    QDateTime finish;
    QDate data;
    QString repeats;

    attivita(){
        tipo = "Vuoto";
        titolo = "Vuoto";
        start = QTime();
        finish = QDateTime();
        repeats = "Mai";
    }

    attivita(QString type, QString title, QTime st, QDateTime end, QString rep, QDate date){
        tipo = type;
        titolo = title;
        start = st;
        finish = end;
        repeats = rep;
        data = date;
    }
    attivita(QStringList dati){
        tipo = dati.at(0);
        titolo = dati.at(1);
        QStringList st = dati.at(2).split(':');
        start = QTime(std::stoi(st.at(0).toStdString()), std::stoi(st.at(1).toStdString()));
        QStringList fin = dati.at(3).split(' ');
        QStringList tmp_data = fin.at(0).split(":");
        QStringList ora = fin.at(1).split(":");
        QDate d = QDate(std::stoi(tmp_data.at(0).toStdString()), std::stoi(tmp_data.at(1).toStdString()), std::stoi(tmp_data.at(2).toStdString()));
        QTime t = QTime(std::stoi(ora.at(0).toStdString()), std::stoi(ora.at(1).toStdString()));
        finish = QDateTime(d, t);
        repeats = dati.at(4);
        QStringList dt = dati.at(5).split(':');
        data = QDate(std::stoi(dt.at(0).toStdString()), std::stoi(dt.at(1).toStdString()), std::stoi(dt.at(2).toStdString()));
    }

    const QString getTipo(){
        return tipo;
    }
    const QString getTitolo(){
        return titolo;
    }
    const QString getRepeats(){
        return repeats;
    }

    const QTime getStart(){
        return start;
    }
    const QDateTime getFinish(){
        return finish;
    }
    const QDate getData(){
        return data;
    }

    QStringList getInfo(){
        QStringList info;
        info.append(tipo);
        info.append(titolo);
        info.append(start.toString());
        if(finish.time() != QTime(23, 59))
            info.append(finish.time().toString());
        else
            info.append("");
        info.append(repeats);
        QDate fin_date = finish.date();
        int yf = fin_date.year();
        int mf = fin_date.month();
        int df = fin_date.day();
        QString dt = QString::number(yf)+":"+QString::number(mf)+":"+QString::number(df);
        info.append(dt);
        return info;
    }
};*/
namespace Ui {
class interface1;
}

class interface1 : public QDialog
{
    Q_OBJECT

public:
    explicit interface1(QWidget *parent = nullptr);
    ~interface1();

private slots:
    void on_pushButton_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_rechercher_textChanged(const QString &arg1);

    void on_comboBoxTri_currentIndexChanged(int index);
    void on_stati_clicked();








    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();


    /*void removeActivity();
    void editActivity();*/


   // void on_label_stat_linkActivated();

    void on_pushButton_4_clicked();



    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::interface1 *ui;
    employe E;
    QSqlQueryModel *model;
   /* QString log = "logs.txt";
    int position = 0;

    std::vector<attivita> activities;
    void load();
    void showActivities();*/
};

#endif // INTERFACE1_H
