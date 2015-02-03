/********************************************************************************
** Form generated from reading UI file 'qt_osg_bullet_progress_0_05.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_OSG_BULLET_PROGRESS_0_05_H
#define UI_QT_OSG_BULLET_PROGRESS_0_05_H

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

class Ui_qt_osg_bullet_progress_0_05Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qt_osg_bullet_progress_0_05Class)
    {
        if (qt_osg_bullet_progress_0_05Class->objectName().isEmpty())
            qt_osg_bullet_progress_0_05Class->setObjectName(QString::fromUtf8("qt_osg_bullet_progress_0_05Class"));
        qt_osg_bullet_progress_0_05Class->resize(600, 400);
        menuBar = new QMenuBar(qt_osg_bullet_progress_0_05Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        qt_osg_bullet_progress_0_05Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qt_osg_bullet_progress_0_05Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        qt_osg_bullet_progress_0_05Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(qt_osg_bullet_progress_0_05Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        qt_osg_bullet_progress_0_05Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(qt_osg_bullet_progress_0_05Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        qt_osg_bullet_progress_0_05Class->setStatusBar(statusBar);

        retranslateUi(qt_osg_bullet_progress_0_05Class);

        QMetaObject::connectSlotsByName(qt_osg_bullet_progress_0_05Class);
    } // setupUi

    void retranslateUi(QMainWindow *qt_osg_bullet_progress_0_05Class)
    {
        qt_osg_bullet_progress_0_05Class->setWindowTitle(QApplication::translate("qt_osg_bullet_progress_0_05Class", "qt_osg_bullet_progress_0_05", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class qt_osg_bullet_progress_0_05Class: public Ui_qt_osg_bullet_progress_0_05Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_OSG_BULLET_PROGRESS_0_05_H
