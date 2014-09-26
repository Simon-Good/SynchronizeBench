#pragma once
#include <QTimer>
#include <QGridLayout>
#include <QWidget>
#include <osgViewer/CompositeViewer>
#include <osgQt/GraphicsWindowQt>
#include "OSGBulletScene.h"

using namespace std;
class OSGViewWidget: public QWidget, public osgViewer::CompositeViewer
{
public:
	OSGViewWidget( osgViewer::ViewerBase::ThreadingModel threadingModel=osgViewer::CompositeViewer::SingleThreaded);
	~OSGViewWidget(void);

	void stickViewIntoLayout(osg::ref_ptr<osgViewer::View> givenView);
	QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw);
	osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h, const std::string& name="", bool windowDecoration=false );
	virtual void paintEvent( QPaintEvent* event );
	void setOSGMain(OSGBulletScene* OSGMain);
protected:

	QTimer _timer;
	osg::ref_ptr<osgViewer::View> view;
	OSGBulletScene *osgMain;
	double currSimTime;
	double prevSimTime;
};