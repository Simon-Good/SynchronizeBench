#include "InputNodeVisitor.h"


InputNodeVisitor::InputNodeVisitor(void)
	:osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
		AgentNode::parentMTList->clear();
		FeatureNode::featureNodeList->clear();
}

InputNodeVisitor::~InputNodeVisitor(void)
{
}
void InputNodeVisitor::apply(osg::Node& node){
		osg::Geode* geode = dynamic_cast<osg::Geode*>(&node);
		if(geode){
			cout<<"SceneOrganiserVistor get:"+geode->getName()<<endl;
			string nodeNm = geode->getName();
			size_t pos = nodeNm.find("-GEODE");
			if(pos !=string::npos){
				nodeNm = nodeNm.substr(0, pos);
				pos = nodeNm.find("feature_");
				if(pos != string::npos){
					featureNode = new FeatureNode(nodeNm, geode, false);
					FeatureNode::featureNodeList->push_back(featureNode);
				}else{
					agentNode = new AgentNode(nodeNm, osg::computeLocalToWorld(this->getNodePath()),geode);
					AgentNode::parentMTList->push_back(agentNode);
					memberNum = AgentNode::parentMTList->size();
					SceneMailBox::registerUsers(agentNode->getId());
				}
			}
		}
		traverse(node);
	}

