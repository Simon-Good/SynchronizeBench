#pragma once
#include <osg/Geode>
#include <osg/Node>
#include <osg/Group>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/View>
#include <osgGA/TrackBallManipulator>
#include <osgManipulator/Selection>
#include <osgManipulator/CommandManager>
#include <osgManipulator/TranslateAxisDragger>

#include <osgDragger/ClearDepth>
#include <osgDragger/HudCamera>
#include <osgDragger/MyDragger>
#include <osgDragger/ShowBound>
#include <osgDragger/DraggerManager>
#include <osgDragger/SceneManipulator>
#include <osgCollisionDetection/CollisionInterface>
#include <osgCollisionDetection/DebugDraw>

#include "AgentNode.h"
#include "OSGPickNode.h"
#include "Global.h"
#include "CustomDragger.h"
#include "InputNodeVisitor.h"

class OSGScene
{
public:
	OSGScene(void);
	~OSGScene(void);

	osg::ref_ptr<osgViewer::View> createView();
	void turnOnCollisionDebug(bool on);
	void turnOnHudAxis(bool on, osg::Camera* camera);
private:
	osg::ref_ptr<osgDragger::HudCamera>_hudCamera;
	osg::observer_ptr<osg::Geode> _debugGeode;
	osg::ref_ptr<osg::Group> root;
};
