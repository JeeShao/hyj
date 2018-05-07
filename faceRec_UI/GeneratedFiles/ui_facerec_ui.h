/********************************************************************************
** Form generated from reading UI file 'facerec_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FACEREC_UI_H
#define UI_FACEREC_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_faceRec_UIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *faceRec_UIClass)
    {
        if (faceRec_UIClass->objectName().isEmpty())
            faceRec_UIClass->setObjectName(QStringLiteral("faceRec_UIClass"));
        faceRec_UIClass->resize(600, 400);
        menuBar = new QMenuBar(faceRec_UIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        faceRec_UIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(faceRec_UIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        faceRec_UIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(faceRec_UIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        faceRec_UIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(faceRec_UIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        faceRec_UIClass->setStatusBar(statusBar);

        retranslateUi(faceRec_UIClass);

        QMetaObject::connectSlotsByName(faceRec_UIClass);
    } // setupUi

    void retranslateUi(QMainWindow *faceRec_UIClass)
    {
        faceRec_UIClass->setWindowTitle(QApplication::translate("faceRec_UIClass", "faceRec_UI", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class faceRec_UIClass: public Ui_faceRec_UIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FACEREC_UI_H
