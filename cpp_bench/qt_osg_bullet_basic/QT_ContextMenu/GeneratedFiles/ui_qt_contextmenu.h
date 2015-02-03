/********************************************************************************
** Form generated from reading UI file 'qt_contextmenu.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_CONTEXTMENU_H
#define UI_QT_CONTEXTMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QT_ContextMenuClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QT_ContextMenuClass)
    {
        if (QT_ContextMenuClass->objectName().isEmpty())
            QT_ContextMenuClass->setObjectName(QString::fromUtf8("QT_ContextMenuClass"));
        QT_ContextMenuClass->resize(600, 400);
        menuBar = new QMenuBar(QT_ContextMenuClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QT_ContextMenuClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QT_ContextMenuClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QT_ContextMenuClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QT_ContextMenuClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QT_ContextMenuClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QT_ContextMenuClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QT_ContextMenuClass->setStatusBar(statusBar);

        retranslateUi(QT_ContextMenuClass);

        QMetaObject::connectSlotsByName(QT_ContextMenuClass);
    } // setupUi

    void retranslateUi(QMainWindow *QT_ContextMenuClass)
    {
        QT_ContextMenuClass->setWindowTitle(QApplication::translate("QT_ContextMenuClass", "QT_ContextMenu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QT_ContextMenuClass: public Ui_QT_ContextMenuClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_CONTEXTMENU_H
