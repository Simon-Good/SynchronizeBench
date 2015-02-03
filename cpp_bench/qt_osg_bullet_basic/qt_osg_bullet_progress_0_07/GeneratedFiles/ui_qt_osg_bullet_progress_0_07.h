/********************************************************************************
** Form generated from reading UI file 'qt_osg_bullet_progress_0_07.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_OSG_BULLET_PROGRESS_0_07_H
#define UI_QT_OSG_BULLET_PROGRESS_0_07_H

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

class Ui_qt_osg_bullet_progress_0_07Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qt_osg_bullet_progress_0_07Class)
    {
        if (qt_osg_bullet_progress_0_07Class->objectName().isEmpty())
            qt_osg_bullet_progress_0_07Class->setObjectName(QString::fromUtf8("qt_osg_bullet_progress_0_07Class"));
        qt_osg_bullet_progress_0_07Class->resize(600, 400);
        menuBar = new QMenuBar(qt_osg_bullet_progress_0_07Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        qt_osg_bullet_progress_0_07Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qt_osg_bullet_progress_0_07Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qt_osg_bullet_progress_0_07Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(qt_osg_bullet_progress_0_07Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qt_osg_bullet_progress_0_07Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qt_osg_bullet_progress_0_07Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qt_osg_bullet_progress_0_07Class->setStatusBar(statusBar);

        retranslateUi(qt_osg_bullet_progress_0_07Class);

        QMetaObject::connectSlotsByName(qt_osg_bullet_progress_0_07Class);
    } // setupUi

    void retranslateUi(QMainWindow *qt_osg_bullet_progress_0_07Class)
    {
        qt_osg_bullet_progress_0_07Class->setWindowTitle(QApplication::translate("qt_osg_bullet_progress_0_07Class", "qt_osg_bullet_progress_0_07", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qt_osg_bullet_progress_0_07Class: public Ui_qt_osg_bullet_progress_0_07Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_OSG_BULLET_PROGRESS_0_07_H
