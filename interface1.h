#ifndef INTERFACE1_H
#define INTERFACE1_H
#include "employe.h"

#include <QDialog>

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

    void on_le_nom_textChanged(const QString &arg1);
    
private:
    Ui::interface1 *ui;
    employe E;
    QSqlQueryModel *model;
};

#endif // INTERFACE1_H
