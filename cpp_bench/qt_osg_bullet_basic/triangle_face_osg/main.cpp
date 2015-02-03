#include <osgViewer/Viewer>
#include <osg/TriangleFunctor>
#include <osg/NodeVisitor>
#include <osgDB/ReadFile>
#include <iostream>

using namespace std;
struct FaceCollector{
	void operator()(const osg::Vec3& v1, const osg::Vec3& v2, const osg::Vec3& v3, bool){
		cout<<"Face vertices: ";
		cout<<v1.x()<<","<<v1.y()<<","<<v1.z();
		cout<<";";
		cout<<v2.x()<<","<<v2.y()<<","<<v2.z();
		cout<<";";
		cout<<v3.x()<<","<<v3.y()<<","<<v3.z();
		cout<<";"<<endl;;
	}
};

class NdVisitor: public osg::NodeVisitor{
	public:
		NdVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN){}
		~NdVisitor(){}
	virtual void apply(osg::Node& node){
		cout<<"in apply"<<endl;
		osg::Geode* geode = dynamic_cast<osg::Geode*>(&node);
		if(geode){
			int num = geode->getNumDrawables();
			cout<<"num:"<<num<<endl;
			for(unsigned int i = 0; i< num; i++){
				osg::ref_ptr<osg::Geometry>geom = geode->getDrawable(i)->asGeometry();
				osg::TriangleFunctor<FaceCollector> functor;
				geom->accept( functor );
				osg::ref_ptr<osg::Vec3Array> vertices = dynamic_cast<osg::Vec3Array*>(geom->getVertexArray());
				osg::ref_ptr<osg::Vec3Array> normal = dynamic_cast<osg::Vec3Array*>(geom->getNormalArray());
				cout<<"index:"<<i<<endl;
				cout<<"vertices size:"<<vertices->size()<<endl;
				cout<<"normal size:"<<normal->size()<<endl;
			}
			

		}
		traverse(node);
	}
};

void main(void){
	//osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	//vertices->push_back( osg::Vec3(0.0f, 0.0f, 0.0f) );
	//vertices->push_back( osg::Vec3(0.0f, 0.0f, 1.0f) );
	//vertices->push_back( osg::Vec3(1.0f, 0.0f, 0.0f) );
	//vertices->push_back( osg::Vec3(1.0f, 0.0f, 1.5f) );
	//vertices->push_back( osg::Vec3(2.0f, 0.0f, 0.0f) );
	//vertices->push_back( osg::Vec3(2.0f, 0.0f, 1.0f) );
	//vertices->push_back( osg::Vec3(3.0f, 0.0f, 0.0f) );
	//vertices->push_back( osg::Vec3(3.0f, 0.0f, 1.5f) );
	//vertices->push_back( osg::Vec3(4.0f, 0.0f, 0.0f) );
	//vertices->push_back( osg::Vec3(4.0f, 0.0f, 1.0f) );
	//osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array;
	//normals->push_back( osg::Vec3(0.0f,-1.0f, 0.0f) );
	//osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	//geom->setVertexArray( vertices.get() );
	//geom->setNormalArray( normals.get() );
	//geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	//geom->addPrimitiveSet( new osg::DrawArrays(GL_QUAD_STRIP, 0, 10));
	//osg::TriangleFunctor<FaceCollector> functor;
 //   geom->accept( functor );

	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
	root->addChild(node.get());
	NdVisitor NdVis;
	node->accept(NdVis);
	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );
	viewer.run();
}