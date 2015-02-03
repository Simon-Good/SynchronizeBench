#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgViewer/Viewer>
#include <osg/NodeVisitor>
#include <osg/Matrixtransform>
#include <osg/Geode>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct newNode{
	osg::ref_ptr<osg::MatrixTransform> transformNode;
	string name;
};

vector<newNode> nodeVec;

class mNodeVisitor:public osg::NodeVisitor{
public:
	mNodeVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN){}
	virtual void apply(osg::Node &node){
		osg::Geode* geode = dynamic_cast<osg::Geode*>(&node);
		if(geode){
			osg::Matrix mt = osg::computeLocalToWorld(this->getNodePath());
			osg::ref_ptr<osg::MatrixTransform> upperNode = new osg::MatrixTransform();
			upperNode->setMatrix(mt);
			upperNode->addChild(geode);
			newNode nn;
			nn.name = upperNode->getName();
			nn.transformNode = upperNode;
			nodeVec.push_back(nn);
		}
		traverse(node);
	}
private:
	osg::ref_ptr<osg::MatrixTransform>mtf;
	osg::Matrix mt;
};
void main(void){
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("zhuanluntike_jiangye_shuzhou4.osg");
	mNodeVisitor mnv;
	node->accept(mnv);

	vector<newNode>::iterator it;
	for(it = nodeVec.begin(); it < nodeVec.end(); it++){
		root->addChild(it->transformNode);
	}
	//root->addChild(node.get());
	osgDB::writeNodeFile(*(root.get()), "output.osg");
}