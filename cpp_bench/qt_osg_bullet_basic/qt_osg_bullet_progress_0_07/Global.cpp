#include "Global.h"

osg::ref_ptr<osg::Node> curSelNode = NULL;
osg::NodePath curPath;
bool highLighted = false;
int memberNum = 0;

void showMatrix(osg::Matrix mt){
	cout<<"mt:"<<endl;
	cout<<mt(0, 0)<<","<<mt(0, 1)<<","<<mt(0, 2)<<","<<mt(0, 3)<<endl;
	cout<<mt(1, 0)<<","<<mt(1, 1)<<","<<mt(1, 2)<<","<<mt(1, 3)<<endl;
	cout<<mt(2, 0)<<","<<mt(2, 1)<<","<<mt(2, 2)<<","<<mt(2, 3)<<endl;
	cout<<mt(3, 0)<<","<<mt(3, 1)<<","<<mt(3, 2)<<","<<mt(3, 3)<<endl;
	cout<<endl;
}

//smatch regexGet(string origin, string cmd){
//	regex reg(cmd);
//	smatch m;
//	regex_match(origin, m, reg);
//	return m;
//}