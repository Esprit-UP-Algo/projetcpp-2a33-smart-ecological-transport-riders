/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:

    void setupUi(QDialog *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QStringLiteral("mainwindow"));
        mainwindow->resize(963, 548);

        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QDialog *mainwindow)
    {
        mainwindow->setWindowTitle(QApplication::translate("mainwindow", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
