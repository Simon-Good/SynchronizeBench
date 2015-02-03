#pragma once
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Switch>
#include <osg/Matrix>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <iostream>
#include <vector>
#include <string>
#include <osg/ShapeDrawable>
#include "OntologyParser.h"

class AgentNode;

using namespace std;
class FeatureNode: public osg::Group
{
public:
	FeatureNode(void);
	FeatureNode(string nodeName, osg::ref_ptr<osg::Geode> geode, bool turnOn = false);
	~FeatureNode(void);
	string getFeatureName(){return nodeNm;}
	string getBelongAgent(){return belongAgent;}
	string getLink(){return linkedTo;}
	void setRadius(float radius);
	void init();
	void switchOn(bool on);
public:
	static vector<FeatureNode*> *featureNodeList;

private:
	string nodeNm;
	string belongAgent;
	string linkedTo;
	osg::ref_ptr<osg::MatrixTransform> mt;
	osg::ref_ptr<osg::Geode> featureGeode;
	osg::ref_ptr<osg::Geode> axisGeode;
	osg::ref_ptr<osg::Switch> swt;
	osg::ref_ptr<osg::Cylinder> linda;
	OntologyParser* op;
	AgentNode *an;
	osg::Vec3 *vec;
	float angle;
	float radius;
};

