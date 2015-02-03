#include "OSGViewWidget.h"
#include <QtGui/QApplication>
#include "OSGScene.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OSGScene* osgMain = new OSGScene();
	OSGViewWidget* viewerWidget = new OSGViewWidget();
	viewerWidget->setOSGMain(osgMain);
	viewerWidget->setGeometry(100, 100, 800, 600);
	viewerWidget->realize();//�������show()ǰ��ִ�У���������ģ��������
	viewerWidget->show();
	return a.exec();
}
