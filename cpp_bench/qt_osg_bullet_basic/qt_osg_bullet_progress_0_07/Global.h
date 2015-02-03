#include <osg/Node>
#include <vector>
#include <osg/MatrixTransForm>
#include <iostream>
#include <regex>

using namespace std;
extern osg::ref_ptr<osg::Node> curSelNode;
extern osg::NodePath curPath;
extern bool highLighted;
extern int memberNum;

void showMatrix(osg::Matrix mt);
