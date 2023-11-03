#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>


namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menu *ui;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QPropertyAnimation *animation3;
    QPropertyAnimation *animation4;
    QPropertyAnimation *animation5;

    QParallelAnimationGroup *animationGroup;
   };

#endif // MENU_H
