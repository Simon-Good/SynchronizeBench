#include "OSGViewWidget.h"

OSGViewWidget::OSGViewWidget( osgViewer::ViewerBase::ThreadingModel threadingModel) : QWidget()
{
	setThreadingModel(threadingModel);
	view = new osgViewer::View;
	// disable the default setting of viewer.done() by pressing Escape.
	setKeyEventSetsDone(0);
	connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
	_timer.start( 10 );	
}

OSGViewWidget::~OSGViewWidget(void)
{
}

void OSGViewWidget::stickViewIntoLayout(osg::ref_ptr<osgViewer::View> givenView){
	view = givenView;
	addView(view);
	//set root and view for addViewWidget to invoke
	QWidget* widget1 = addViewWidget(createGraphicsWindow(0, 0, 100, 100));
	QGridLayout* grid = new QGridLayout;
	grid->addWidget( widget1, 0, 0 );
	setLayout( grid );
}

QWidget* OSGViewWidget::addViewWidget(osgQt::GraphicsWindowQt* gw)
{
	addView( view );
	osg::Camera* camera = view->getCamera();
	camera->setGraphicsContext( gw );

	const osg::GraphicsContext::Traits* traits = gw->getTraits();

	camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
	camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
	camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );
	return gw->getGLWidget();
}

osgQt::GraphicsWindowQt* OSGViewWidget::createGraphicsWindow( int x, int y, int w, int h, const std::string& name, bool windowDecoration )
{
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->windowName = name;
	traits->windowDecoration = windowDecoration;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	return new osgQt::GraphicsWindowQt(traits.get());
}

void OSGViewWidget::setOSGMain(OSGBulletScene* OSGMain){
	osgMain = OSGMain;
	this->stickViewIntoLayout(osgMain->generateView());
	currSimTime = this->view->getFrameStamp()->getSimulationTime();
	prevSimTime = this->view->getFrameStamp()->getSimulationTime();
}

void OSGViewWidget::paintEvent( QPaintEvent* event )
{  
	currSimTime = this->getFrameStamp()->getSimulationTime();
	osgMain->runSimulation(currSimTime - prevSimTime);
	prevSimTime = currSimTime;
	frame();
}