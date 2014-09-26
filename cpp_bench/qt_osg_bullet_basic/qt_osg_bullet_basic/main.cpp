/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * osgBullet is (C) Copyright 2009-2012 by Kenneth Mark Bryden
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/
#include <QTimer>
#include <QApplication>
#include "OSGBulletScene.h"
#include "OSGViewWidget.h"

using namespace std;


int main(int argc, char** argv){
	QApplication app(argc, argv);

	OSGBulletScene *osgMain = new OSGBulletScene();
	OSGViewWidget* viewerWidget = new OSGViewWidget();
	viewerWidget->setOSGMain(osgMain);
	viewerWidget->setGeometry(100, 100, 800, 600);
	viewerWidget->realize();//必须放在show()前面执行，否则物理模拟会出问题
	viewerWidget->show();
	
	return app.exec();

}