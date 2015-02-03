#pragma once
#include <osg/NodeVisitor>
#include <osg/Matrixtransform>
#include <iostream>
#include "AgentNode.h"
#include "SceneMailBox.h"
#include "FeatureNode.h"

using namespace std;
class InputNodeVisitor: public osg::NodeVisitor{
public:
	InputNodeVisitor();
	~InputNodeVisitor();
	virtual void apply(osg::Node& node);
private:
	osg::ref_ptr<osg::MatrixTransform> directParent;
	AgentNode* agentNode;
	FeatureNode* featureNode;
};

