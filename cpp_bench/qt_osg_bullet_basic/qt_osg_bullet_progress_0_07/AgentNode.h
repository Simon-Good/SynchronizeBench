#pragma once
#include <osg/Node>
#include <osg/Switch>
#include <string>
#include <osgDB/ReadFile>
#include <osgManipulator/Selection>
#include <osgManipulator/CommandManager>
#include <osgManipulator/TranslateAxisDragger>
#include <osgManipulator/TrackballDragger>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <math.h>
#include <QtCore>
#include <QtCore/QTimer>
#include "SceneMailBox.h"
#include "SceneMessage.h"
#include "Global.h"
#include "OntologyParser.h"
#include "FeatureNode.h"

//#ifndef Q_MOC_RUN
//#include <boost/thread.hpp>
//#include <boost/date_time.hpp>
//#endif

using namespace std;
class AgentNode:public QObject, public osg::Group 
{
	Q_OBJECT
public:
	AgentNode(void);
	AgentNode(string name, osg::Matrix mt, osg::ref_ptr<osg::Geode> geode);
	~AgentNode(void);
	void radioPositionMsg();
	osg::ref_ptr<osg::MatrixTransform> getMT(){return mtNode;}
	string getName(){return nodeNm;}
	string getId(){return Id;}
	float getRadius();
	float caculateDistance(osg::Matrix mat);
	static AgentNode* getNodeByName(string nodeNm);
	void addFeature();
	void sendFeatureOnMsg(string featureNm, string receiver);
	void sendFeatureOffMsg(string featureNm, string receiver);
	bool connectable(string sender);
public slots:
	void ownThreadFunc();

private:
	osg::ref_ptr<osg::Geode>geodeNode;
	osg::ref_ptr<osg::MatrixTransform>mtNode;
	osg::ref_ptr<osg::MatrixTransform>mtSubNode;
	string nodeNm;
	string Id;
	float radius;
	vector<string> *feature;
	vector<string> *dependency;
	vector<string> *connected;
	vector<FeatureNode*> *featureList;
	QThread t;
	QTimer timer;
	OntologyParser *op;
	SceneMessage* msg;
public:
	static vector<AgentNode*> *parentMTList;
};

