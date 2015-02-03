#include "FeatureNode.h"
#include "AgentNode.h"

vector<FeatureNode*> *FeatureNode::featureNodeList = new vector<FeatureNode*>();
FeatureNode::FeatureNode(void)
{
}

FeatureNode::FeatureNode(string nodeName, osg::ref_ptr<osg::Geode> geode, bool turnOn){
	this->nodeNm = nodeName;
	this->featureGeode = geode;
	swt = new osg::Switch();
	axisGeode = new osg::Geode();

	this->addChild(swt.get());
	swt->addChild(axisGeode.get(), turnOn);

	op = new OntologyParser();
	vec = new osg::Vec3();
	op->getFeatureParameter(nodeNm, angle, vec);
	belongAgent = op->getFeatureBelong(nodeNm);
	linkedTo = op->getFeatureLink(nodeNm);
	radius = 10.0f;
}

void FeatureNode::setRadius(float r){
	this->radius = r;
}

void FeatureNode::switchOn(bool on){
	if(on)
		this->swt->setAllChildrenOn();
	else 
		this->swt->setAllChildrenOff();
}

void FeatureNode::init(){
	if(vec->valid()){
		linda = new osg::Cylinder(featureGeode->getBound().center(), 0.05f, radius);
		linda->setRotation(osg::Quat((osg::PI*angle/180.0f), *vec));
		this->axisGeode->addDrawable(new osg::ShapeDrawable(linda.get()));
	}
}

FeatureNode::~FeatureNode(void)
{
}
