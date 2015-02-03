#ifndef QT_CONTEXTMENU_H
#define QT_CONTEXTMENU_H

#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QtOpenGL/QGLWidget>
#include <QtGui/QMouseEvent>
#include "ui_qt_contextmenu.h"

class QT_ContextMenu : public QMainWindow
{
	Q_OBJECT

public:
	QT_ContextMenu();

public:
	//QWidget *my_widget;

public slots:
    //void customMenuRequested(QPoint pos);
};

class My_GLWidget: public QGLWidget
{
	Q_OBJECT
public:
	My_GLWidget(){};

	void mousePressEvent(QMouseEvent *btevent);
};

#endif // QT_CONTEXTMENU_H
