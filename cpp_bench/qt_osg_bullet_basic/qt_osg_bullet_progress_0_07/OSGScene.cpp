#include "OSGScene.h"

OSGScene::OSGScene(void)
{
}

OSGScene::~OSGScene(void)
{
}

void OSGScene::turnOnCollisionDebug(bool on){
	if(on == true){
		osgCollisionDetection::CollisionInterface::Instence();
		_debugGeode = new osg::Geode;
		_debugGeode->setCullingActive(false);
		osg::ref_ptr<osgCollisionDetection::DebugDraw> drawable = new osgCollisionDetection::DebugDraw();
		drawable->setCollisionWorld(osgCollisionDetection::CollisionInterface::Instence()->getCollisionWorld());
		_debugGeode->addDrawable(drawable.get());
		_debugGeode->setNodeMask(0x2);
		root->addChild(_debugGeode.get());
	}
}

void OSGScene::turnOnHudAxis(bool on, osg::Camera* camera){
	if(on == true){
		CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setAttributeAndModes(new osgDragger::ClearDepth);
		CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
		root->addChild(CustomDraggerManager::Instence()->getRoot());
		_hudCamera = new osgDragger::HudCamera(camera, 60, 60);
	}
}

osg::ref_ptr<osgViewer::View> OSGScene::createView(){
	osg::ref_ptr<osgViewer::View> view  = new osgViewer::View();
	root = new osg::Group();

	view->setSceneData(root.get());
	osg::ref_ptr<osgDragger::SceneManipulator> manipulator = 
		new osgDragger::SceneManipulator(osgGA::OrbitManipulator::DEFAULT_SETTINGS | 
		                                 osgGA::OrbitManipulator::COMPUTE_HOME_USING_BBOX);
	view->setCameraManipulator(manipulator.get());
	view->addEventHandler(new OSGPickNode());
	osgDragger::ShowBound::Instence()->setNodeMask(~0x1);
	root->addChild(osgDragger::ShowBound::Instence()->getRoot());

	osg::ref_ptr<osg::MatrixTransform> scene = new osg::MatrixTransform;
	root->addChild(scene.get());
	scene->setNodeMask(0x1);

	CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setAttributeAndModes(new osgDragger::ClearDepth);
	CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	CustomDraggerManager::Instence()->getRoot()->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
	root->addChild(CustomDraggerManager::Instence()->getRoot());

	
	turnOnHudAxis(true, view->getCamera());
	
	CustomMoveDragger* move = new CustomMoveDragger;
	move->setName("move");
	move->setIntersectionMask(0x2);
	move->setupDefaultGeometry();
	move->setHandleEvents(true);
	CustomDraggerManager::Instence()->addDragger(move, true);
	CustomDraggerManager::Instence()->setIntersectionMask(0x2);

	CustomRotateDragger* rotate = new CustomRotateDragger;
	rotate->setName("rotate");
	rotate->setIntersectionMask(0x2);
	rotate->setupDefaultGeometry();
	rotate->setHandleEvents(true);
	CustomDraggerManager::Instence()->addDragger(rotate, false);
	CustomDraggerManager::Instence()->setIntersectionMask(0x2);

	//initialize an only instance of mailbox, and start a thread to check box
	SceneMailBox::Instance();
	InputNodeVisitor inv;
	SelectionList sl;
	osg::ref_ptr<osg::Node> readInScene = osgDB::readNodeFile("models_and_features9.osg");
	readInScene->accept(inv);
	if(!AgentNode::parentMTList->empty()){
		for(unsigned int i = 0; i< AgentNode::parentMTList->size(); i++){
			scene->addChild(AgentNode::parentMTList->at(i));
			osgCollisionDetection::CollisionInterface::Instence()->addCollisionObject(AgentNode::parentMTList->at(i)->getName(),
																						AgentNode::parentMTList->at(i)->getMT());
			if(!FeatureNode::featureNodeList->empty()){
				AgentNode::parentMTList->at(i)->addFeature();			
			}
		}
	}
	turnOnCollisionDebug(true);
	osgCollisionDetection::CollisionInterface::Instence()->setDoCollisionTest(true);
	return view;
}

