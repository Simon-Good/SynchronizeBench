#include "qt_contextmenu.h"

QT_ContextMenu::QT_ContextMenu()
{
	//QGLWidget* my_glwidget = new QGLWidget();
	//QWidget *another = new My_GLWidget(0, my_glwidget, 0);
	QWidget *another = new My_GLWidget();
	setCentralWidget(another);
	setMinimumSize(160, 160);
    resize(480, 320);

	/*my_widget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(my_widget, SIGNAL(customContextMenuRequested(QPoint)),
            SLOT(customMenuRequested(QPoint)));*/
}

//void QT_ContextMenu::customMenuRequested(QPoint pos){
//	QMenu *menu=new QMenu(this);
//    menu->addAction(new QAction("Action 1", this));
//    menu->addAction(new QAction("Action 2", this));
//    menu->addAction(new QAction("Action 3", this));
//    menu->popup(my_widget->mapToGlobal(pos));
//}

void My_GLWidget::mousePressEvent(QMouseEvent* btevent){
	if(btevent->button() == Qt::RightButton){
		QMenu menu;
		QAction* openAct = new QAction("open", this);
		menu.addAction(openAct);
		menu.exec(mapToGlobal(btevent->pos()));
	}
}
