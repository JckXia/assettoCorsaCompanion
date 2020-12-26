/********************************************************************************
** Form generated from reading UI file 'QtWidgetsApplication2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTWIDGETSAPPLICATION2_H
#define UI_QTWIDGETSAPPLICATION2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication2Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtWidgetsApplication2Class)
    {
        if (QtWidgetsApplication2Class->objectName().isEmpty())
            QtWidgetsApplication2Class->setObjectName(QString::fromUtf8("QtWidgetsApplication2Class"));
        QtWidgetsApplication2Class->resize(600, 400);
        menuBar = new QMenuBar(QtWidgetsApplication2Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtWidgetsApplication2Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtWidgetsApplication2Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtWidgetsApplication2Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtWidgetsApplication2Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtWidgetsApplication2Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtWidgetsApplication2Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtWidgetsApplication2Class->setStatusBar(statusBar);

        retranslateUi(QtWidgetsApplication2Class);

        QMetaObject::connectSlotsByName(QtWidgetsApplication2Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtWidgetsApplication2Class)
    {
        QtWidgetsApplication2Class->setWindowTitle(QCoreApplication::translate("QtWidgetsApplication2Class", "QtWidgetsApplication2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtWidgetsApplication2Class: public Ui_QtWidgetsApplication2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTWIDGETSAPPLICATION2_H
