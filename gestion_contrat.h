#ifndef gestion_contrat_H
#define gestion_contrat_H
#include "statistic.h"
#include <QMainWindow>
#include "contrat_ar.h"
QT_BEGIN_NAMESPACE
namespace Ui { class gestion_contrat; }
QT_END_NAMESPACE

class gestion_contrat : public QMainWindow
{
    Q_OBJECT

public:
    gestion_contrat(QWidget *parent = nullptr);
    ~gestion_contrat();
private slots:
    void on_ajouter_clicked();
    void on_afficher_clicked();
    void on_supprimer_clicked();
    void on_modifier_clicked();
    void on_affiche_tab_activated(const QModelIndex &index);

    void on_tri_clicked();

    void on_pdf_clicked();

    void on_chercher_textChanged(const QString &arg1);

    void on_stat_clicked();

    void on_historique_clicked();

    void on_tableViewHistorique_activated(const QModelIndex &index);

    void on_contrat_a_clicked();

private:
    Ui::gestion_contrat *ui;
    Statistic * statistic;
    contrat_ar *ca;
};
#endif // gestion_contrat_H
