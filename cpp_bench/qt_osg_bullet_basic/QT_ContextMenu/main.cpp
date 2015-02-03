#include "qt_contextmenu.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QT_ContextMenu w;
	w.show();
	return a.exec();
}
