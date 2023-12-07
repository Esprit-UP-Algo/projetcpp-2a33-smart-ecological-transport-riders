/********************************************************************************
** Form generated from reading UI file 'statistic.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATISTIC_H
#define UI_STATISTIC_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_Statistic
{
public:
    QCustomPlot *customPlot;

    void setupUi(QDialog *Statistic)
    {
        if (Statistic->objectName().isEmpty())
            Statistic->setObjectName(QStringLiteral("Statistic"));
        Statistic->resize(1012, 603);
        customPlot = new QCustomPlot(Statistic);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(180, 120, 591, 351));

        retranslateUi(Statistic);

        QMetaObject::connectSlotsByName(Statistic);
    } // setupUi

    void retranslateUi(QDialog *Statistic)
    {
        Statistic->setWindowTitle(QApplication::translate("Statistic", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Statistic: public Ui_Statistic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATISTIC_H
