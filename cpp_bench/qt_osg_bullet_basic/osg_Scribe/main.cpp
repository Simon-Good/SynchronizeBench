#include <osgViewer/Viewer>
#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgFX/Scribe>
#include <osg/Switch>

int main(){
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	osg::ref_ptr<osg::Group>root = new osg::Group();
	osg::ref_ptr<osg::Switch>sw = new osg::Switch();

	osg::ref_ptr<osg::Node>node = osgDB::readNodeFile("cow.osg");
	osg::ref_ptr<osgFX::Scribe>scribe = new osgFX::Scribe();

	scribe->setWireframeColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	scribe->setWireframeLineWidth(2.0f);

	scribe->addChild(node.get());
	root->addChild(scribe.get());
	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
	return 0;
}