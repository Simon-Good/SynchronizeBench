#include "OSGBulletScene.h"


OSGBulletScene::OSGBulletScene(void)
{
		root = new osg::Group();
		view = new osgViewer::View;
		dynamicsWorld = initPhysics();
}


OSGBulletScene::~OSGBulletScene(void)
{
}

osg::ref_ptr<osgViewer::View> OSGBulletScene::generateView(){
	root->addChild(createModel(dynamicsWorld, "bigbigmodel3.3ds"));
	osg::ref_ptr<osg::MatrixTransform> ground = new osg::MatrixTransform();
    btRigidBody * groundBody;

    float thin = .01;
	osg::Vec3 translate(ORIGIN_X, ORIGIN_Y, ORIGIN_Z-50.0f);
    ground = createOSGBox( osg::Vec3( 800, 800, thin ), translate);
    root->addChild( ground );//先创建一个osg节点

    groundBody = createBTBox( ground, osg::Vec3( 0, 0, ORIGIN_Z-50.0f ) );//再根据节点，创建物理性质，刚体
    dynamicsWorld->addRigidBody( groundBody );

	view->setSceneData(root);

	CTravelManipulator *tm = new CTravelManipulator(view);
	tm->setInitialPosition(ORIGIN_X, ORIGIN_Y, ORIGIN_Z);
	tm->setInitialRotation(osg::PI_2, 0.0f, 0.0f);
	view->setCameraManipulator(tm);
	return view;
}

void OSGBulletScene::runSimulation(double timeStep){
	dynamicsWorld->stepSimulation(timeStep);
}

btDynamicsWorld* OSGBulletScene::initPhysics()
{
    btDefaultCollisionConfiguration * collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher * dispatcher = new btCollisionDispatcher( collisionConfiguration );
    btConstraintSolver * solver = new btSequentialImpulseConstraintSolver;

    btVector3 worldAabbMin( -10000, -10000, -10000 );// 进行aabb算法的范围？
    btVector3 worldAabbMax( 10000, 10000, 10000 );
    btBroadphaseInterface * inter = new btAxisSweep3( worldAabbMin, worldAabbMax, 1000 );//采用的碰撞检测算法

    btDynamicsWorld * dynamicsWorld = new btDiscreteDynamicsWorld( dispatcher, inter, solver, collisionConfiguration );

    dynamicsWorld->setGravity( btVector3( 0, 0, -500 ) );

    return( dynamicsWorld );
}

osg::MatrixTransform* OSGBulletScene::createOSGBox( osg::Vec3 size , osg::Vec3  translate)
{
    osg::Box * box = new osg::Box();
	osg::Matrix trans;
	trans.makeTranslate(translate);

    box->setHalfLengths( size );

    osg::ShapeDrawable * shape = new osg::ShapeDrawable( box );

    osg::Geode * geode = new osg::Geode();
    geode->addDrawable( shape );

    osg::MatrixTransform * transform = new osg::MatrixTransform();
	transform->setMatrix(trans);
    transform->addChild( geode );

    return( transform );
}

btRigidBody * OSGBulletScene::createBTBox( osg::MatrixTransform * box,
										   osg::Vec3 center )
{
    btCollisionShape * collision = osgbCollision::btBoxCollisionShapeFromOSG( box );

    osgbDynamics::MotionState * motion = new osgbDynamics::MotionState();
    motion->setTransform( box );
    motion->setParentTransform( osg::Matrix::translate( center ) );

    btScalar mass( 0.0 );
    btVector3 inertia( 0, 0, -10 );
    btRigidBody::btRigidBodyConstructionInfo rb( mass, motion, collision, inertia );
    btRigidBody * body = new btRigidBody( rb );

    return( body );
}

osg::MatrixTransform* OSGBulletScene::createModel( btDynamicsWorld * dynamicsWorld, const string fileName )
{
/*
 * BEGIN: Create physics object code.
 *  OSG CODE
 */
    osg::ref_ptr< osg::MatrixTransform > node;
    osg::ref_ptr< osg::Node > nodeDB = osgDB::readNodeFile( fileName );
	if( !nodeDB.valid() )
	{
		osg::notify( osg::FATAL ) << "Can't find \"" << fileName << "\". Make sure OSG_FILE_PATH includes the OSG sample data directory." << std::endl;
		exit( 0 );
	}

    if( ( node = dynamic_cast< osg::MatrixTransform * >( nodeDB.get() ) ) == NULL )
    {
        node = new osg::MatrixTransform;
        node->addChild( nodeDB.get() );
    }

    /*  osgBullet code */
    osgbDynamics::MotionState * motion = new osgbDynamics::MotionState;
    motion->setTransform( node.get() );
    btCollisionShape * collision = osgbCollision::btConvexTriMeshCollisionShapeFromOSG( node.get() );
    // Create an OSG representation of the Bullet shape and attach it.
    // This is mainly for debugging.
    osg::Node* debugNode = osgbCollision::osgNodeFromBtCollisionShape( collision );
    node->addChild( debugNode );

    // Set debug node state.
    osg::StateSet* state = debugNode->getOrCreateStateSet();
    osg::PolygonMode* pm = new osg::PolygonMode( osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE );
    state->setAttributeAndModes( pm );
    osg::PolygonOffset* po = new osg::PolygonOffset( -1, -1 );
    state->setAttributeAndModes( po );
    state->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

    /*  BULLET CODE */
    btTransform bodyTransform;
    bodyTransform.setIdentity();
    bodyTransform.setOrigin( btVector3( 0, 0, 5 ) );
    motion->setWorldTransform( bodyTransform );

    btScalar mass( 1.0 );
    btVector3 inertia;
    collision->calculateLocalInertia( mass, inertia );
    btRigidBody::btRigidBodyConstructionInfo rbinfo( mass, motion, collision, inertia );
    btRigidBody * body = new btRigidBody( rbinfo );
    body->setLinearVelocity( btVector3( -5, -1, 0 ) );
    body->setAngularVelocity( btVector3( 1, 0, 0 ) );
    dynamicsWorld->addRigidBody( body );
        
    return( node.release() );
}