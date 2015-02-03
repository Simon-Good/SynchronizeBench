#include <osgDragger/DraggerManager>
#include <osgDragger/ClearDepth>
#include <osgDragger/HudCamera>
#include <osgDragger/MyDragger>
#include <osgDragger/ShowBound>


#include <Utils/Utils>
#include <osg/observer_ptr>
#include <osg/ShapeDrawable>
#include <osgGA/GUIEventHandler>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>

#include <iostream>

using namespace std;

class CustomDraggerManager:public osgDragger::DraggerManager{
public:
	CustomDraggerManager(){}

	static CustomDraggerManager *Instence(){
		static osg::ref_ptr<CustomDraggerManager> cdm = new CustomDraggerManager;
		return cdm.get();
	}

protected:
	virtual ~CustomDraggerManager(){};
};

class PickNode: public osgGA::GUIEventHandler{
public:
	//GUIEventHandler::handle的原型的参数列表是(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa），注意const
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
		if(ea.getHandled() == true){
			return true;
		}

		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if(!viewer){
			return false;
		}

		float x = ea.getX();
		float y = ea.getY();
		switch(ea.getEventType()){
		case osgGA::GUIEventAdapter::KEYDOWN:
			{
				if(ea.getKey() == osgGA::GUIEventAdapter::KEY_1){
					CustomDraggerManager::Instence()->setActiveDragger("move");
				}
				if(ea.getKey() == osgGA::GUIEventAdapter::KEY_2){
					CustomDraggerManager::Instence()->setActiveDragger("rotate");
				}
			}
			break;
		case osgGA::GUIEventAdapter::PUSH:
			{
				if(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON & ea.getButtonMask()){
					osg::MatrixTransform* mt = pick(viewer, x, y);
					if(mt){
						if((ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL) == 0){
							//如果没有按下CTRL键，则清空selections
							//&不是逻辑运算，结合性和&& 不同，内层括号必须加。否则不按CTRL时不会清空
							_pickSelections.clear();
						}
						_pickSelections.push_back(mt);
						CustomDraggerManager::Instence()->setSelections(_pickSelections);
						osgDragger::ShowBound::Instence()->setSelections(_pickSelections);
					}
				}
			}
			break;
		}
		return false;
	}

	osg::MatrixTransform* pick(osgViewer::Viewer* viewer, float x, float y){
		osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = 
			new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, x, y);  
		osgUtil::IntersectionVisitor iv(intersector.get());
		iv.setTraversalMask(0x1);
		viewer->getCamera()->accept(iv);

		if(intersector->containsIntersections()){
			const osgUtil::LineSegmentIntersector::Intersection& result = 
				*(intersector->getIntersections().begin());
			int size = result.nodePath.size();

			osg::MatrixTransform* selection = 0;

			for(int index = 0; index < size; index++){
				selection = dynamic_cast<osg::MatrixTransform*>(result.nodePath[index]);
				if(selection){
					std::string str = selection->getName();
					if(!str.empty()){
						return selection;
					}
				}
			}
		}
		return 0;//其他情况必须返回0，否则会劫持其他控制器的消息
	}

	SelectionList _pickSelections;
};

osg::Camera* createMasterCamera(int x, int y, int w, int h){
	osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();
	osg::ref_ptr<osg::GraphicsContext::Traits>traits = new osg::GraphicsContext::Traits;
	traits->windowDecoration = true;
	traits->x = x;
	traits->y = y;
	traits->width = w;
	traits->height = h;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	osg::ref_ptr<osg::Camera> camera = new osg::Camera;
	camera->setGraphicsContext(osg::GraphicsContext::createGraphicsContext(traits.get()));
	camera->setClearColor(osg::Vec4(0.39, 0.39, 0.39, 1.0));
	GLenum buffer = traits->doubleBuffer? GL_BACK:GL_FRONT;
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);
	camera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	camera->setProjectionMatrixAsPerspective(
		30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 1000.0f);
	return camera.release();
}

osg::Camera* createHUD(osg::GraphicsContext* gc){
	if(gc){
		osg::ref_ptr<osg::Camera> camera = new osg::Camera;
		camera->setClearMask(GL_DEPTH_BUFFER_BIT);
		camera->setRenderOrder(osg::Camera::POST_RENDER, 2);
		camera->setAllowEventFocus(true);
		camera->setGraphicsContext(gc);
		const osg::GraphicsContext::Traits *traits = gc->getTraits();
		camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
		GLenum buffer = traits->doubleBuffer? GL_BACK: GL_FRONT;
		camera->setDrawBuffer(buffer);
		camera->setReadBuffer(buffer);

		return camera.release();
	}
	return 0;
}

int main(int argc, char** argv){
	osgViewer::Viewer viewer;
	osg::Camera* camera = createMasterCamera(50, 50, 640, 480);
	viewer.setCamera(camera);
	viewer.addEventHandler(new PickNode());

	osg::ref_ptr<osg::Group> root = new osg::Group;
	viewer.setSceneData(root.get());
	osgDragger::ShowBound::Instence()->setNodeMask(~0x1);
	root->addChild(osgDragger::ShowBound::Instence()->getRoot());


	osg::ref_ptr<osg::MatrixTransform> scene = new osg::MatrixTransform;
	root->addChild(scene.get());
	scene->setNodeMask(0x1);

	CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setAttributeAndModes(new osgDragger::ClearDepth);
	CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
	root->addChild(CustomDraggerManager::Instence()->getRoot());


	osgDragger::MoveDragger* move = new osgDragger::MoveDragger;
	move->setName("move");
	move->setIntersectionMask(0x2);
	move->setupDefaultGeometry();
	move->setHandleEvents(true);
	CustomDraggerManager::Instence()->addDragger(move, true);
	CustomDraggerManager::Instence()->setIntersectionMask(0x2);

	osgDragger::RotateDragger* rotate = new osgDragger::RotateDragger;
	rotate->setName("rotate");
	rotate->setIntersectionMask(0x2);
	rotate->setupDefaultGeometry();
	rotate->setHandleEvents(true);
	CustomDraggerManager::Instence()->addDragger(rotate, false);
	CustomDraggerManager::Instence()->setIntersectionMask(0x2);

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(), 5.0f)));

	SelectionList sl;
	{
		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		mt->setName("mt");
		mt->addChild(geode.get());
		sl.push_back(mt);
		scene->addChild(mt.get());
	}
	{
		osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
		mt->setName("mt");
		mt->setMatrix(osg::Matrix::translate(osg::Vec3(20, 0 , 0)));
		mt->addChild(geode.get());
		scene->addChild(mt.get());
	}

	CustomDraggerManager::Instence()->setSelections(sl);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	while(!viewer.done()){
		viewer.frame();
	}
	return 0;
}
