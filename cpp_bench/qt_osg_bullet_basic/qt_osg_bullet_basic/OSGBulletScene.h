#pragma once
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/PolygonMode>
#include <osg/PolygonOffset>
#include <btBulletDynamicsCommon.h>
#include <osg/io_utils>
#include <osgbDynamics/MotionState.h>
#include <osgbCollision/CollisionShapes.h>
#include <osgbCollision/RefBulletObject.h>
#include <osgbDynamics/RigidBodyAnimation.h>
#include <btBulletDynamicsCommon.h>

#include <osgDB/ReadFile>
#include <osgViewer/View>
#include "TravelManipulator.h"
using namespace std;

#define ORIGIN_X 0.0f
#define ORIGIN_Y -200.0f
#define ORIGIN_Z -430.0f

class OSGBulletScene
{
public:
	OSGBulletScene(void);
	~OSGBulletScene(void);
	osg::ref_ptr<osgViewer::View> generateView(void);
	btDynamicsWorld * initPhysics();
	osg::MatrixTransform* createOSGBox( osg::Vec3 size , osg::Vec3 translate);
	btRigidBody * createBTBox( osg::MatrixTransform * box,osg::Vec3 center );
	osg::MatrixTransform * createModel( btDynamicsWorld * dynamicsWorld, const string fileName );
	void runSimulation(double);
private:
	osg::ref_ptr<osg::Group> root;
	osg::ref_ptr<osgViewer::View> view;
	btDynamicsWorld * dynamicsWorld;
};

