#include "AgentNode.h"

vector<AgentNode*> *AgentNode::parentMTList = new vector<AgentNode*>();

AgentNode::AgentNode(void)
{
}

AgentNode::AgentNode(string name,osg::Matrix mt, osg::ref_ptr<osg::Geode> geode){
	feature = new vector<string>();
	dependency = new vector<string>();
	connected = new vector<string>();
	featureList = new vector<FeatureNode*>();
	msg = NULL;

	radius = geode->getBoundingBox().radius();
	geodeNode = geode;
	nodeNm = name;
	this->setName(name);

	osg::Vec3 translate;
	osg::Quat rotate;
	osg::Vec3 scale;
	osg::Quat so;
	mt.decompose(translate, rotate, scale, so);

	mtNode = new osg::MatrixTransform(osg::Matrix::translate(translate));
	mtSubNode = new osg::MatrixTransform(osg::Matrix::rotate(rotate)*osg::Matrix::scale(scale));
	mtNode->addChild(mtSubNode.get());
	mtNode->setName(name);
	this->addChild(mtNode.get());
	mtSubNode->addChild(geode.get());

	op = new OntologyParser();
	op->getFeature(nodeNm, feature);
	op->getDependencies(nodeNm, dependency);
	op->getConnectedTo(nodeNm, connected);
	Id = op->getId(nodeNm);
	
	connect(&timer, SIGNAL(timeout()), this, SLOT(ownThreadFunc()));
	timer.start(200);//自带restart功能
	this->moveToThread(&t);
	t.start();
}

AgentNode::~AgentNode(void)
{
}

void AgentNode::ownThreadFunc(){
	for(int i = 0; i< SceneMailBox::mailBox->size(); i++){
		if(!SceneMailBox::inBox(SceneMailBox::mailBox->at(i), Id)){
			if(SceneMailBox::Accessible == true){
				SceneMailBox::Accessible = false;
				msg = SceneMailBox::mailBox->at(i);
				SceneMailBox::stampOn(SceneMailBox::mailBox->at(i), Id);
				cout<<nodeNm<<":checked message"<<SceneMailBox::mailBox->at(i)->msgId<<endl;
				SceneMailBox::Accessible = true;
				break;
			}else{
				cout<<nodeNm<<":can't check right now, wait next turn"<<endl;
			}
		}
	}
	string sender;
	string linkNm;
	string belongAgent;
	if(msg!=NULL){
		if((msg->eventype == SceneMessage::POSITIONRADIO)&&(msg->sender != nodeNm)){
			osg::Matrix mat = msg->position;
			float distance = caculateDistance(mat);
			if(distance< (radius + msg->radius)*1.2f){
				cout<<"close enough"<<endl;
				sender = msg->sender;
				if(connectable(sender)){
					for(unsigned int i = 0; i< featureList->size(); i++){
						linkNm = featureList->at(i)->getLink();
						for(unsigned int j = 0; j< FeatureNode::featureNodeList->size(); j++){
							if(FeatureNode::featureNodeList->at(j)->getFeatureName() == linkNm){
								belongAgent = FeatureNode::featureNodeList->at(j)->getBelongAgent();
								if(sender == belongAgent){
									featureList->at(i)->switchOn(true);
									sendFeatureOnMsg(linkNm, belongAgent);
								}
							}
						}
					}
				}
			}else{
				sender = msg->sender;
				if(connectable(sender)){
					for(unsigned int i = 0; i< featureList->size(); i++){
						linkNm = featureList->at(i)->getLink();
						for(unsigned int j = 0; j< FeatureNode::featureNodeList->size(); j++){
							if(FeatureNode::featureNodeList->at(j)->getFeatureName() == linkNm){
								belongAgent = FeatureNode::featureNodeList->at(j)->getBelongAgent();
								if(sender == belongAgent){
									featureList->at(i)->switchOn(false);
									sendFeatureOffMsg(linkNm, belongAgent);
								}
							}
						}
					}
				}
			}
		}else if((msg->eventype == SceneMessage::REQUIREFEATUREON)&&(msg->sender != nodeNm)){
			for(unsigned int i = 0; i< featureList->size(); i++){
				if(featureList->at(i)->getFeatureName() == msg->featureNm){
					featureList->at(i)->switchOn(true);
					break;
				}
			}
		}else if((msg->eventype == SceneMessage::REQUIREFEATUREOFF)&&(msg->sender != nodeNm)){
			for(unsigned int i = 0; i< featureList->size(); i++){
				if(featureList->at(i)->getFeatureName() == msg->featureNm){
					featureList->at(i)->switchOn(false);
				}
			}
		}
	}
}

bool AgentNode::connectable(string sender){
	bool ret = false;
	for(unsigned int i = 0; i< connected->size(); i++){
		if(connected->at(i) == sender){
			ret = true;
			break;
		}
	}
	return ret;
}

float AgentNode::caculateDistance(osg::Matrix mat){
	osg::Vec3 mTranslate = mtNode->getMatrix().getTrans();
	osg::Vec3 translate = mat.getTrans();
	float distance = pow((float)(mTranslate.x()-translate.x()), (float)2.0) + pow((float)(mTranslate.y() - translate.y()), (float)2.0) + pow((float)(mTranslate.z() - translate.z()), (float)2.0);
	distance = sqrt(distance);
	return distance;
}

void AgentNode::radioPositionMsg(){
	if(SceneMailBox::Accessible){
		SceneMailBox::Accessible = false;
		SceneMailBox::radioMessage(SceneMessage::PositionMessage(nodeNm, mtNode->getMatrix(), radius));
		SceneMailBox::Accessible = true;
	}
}

void AgentNode::sendFeatureOnMsg(string featureNm, string receiver){
	if(SceneMailBox::Accessible){
		SceneMailBox::Accessible = false;
		SceneMailBox::radioMessage(SceneMessage::FeatureOnMessage(nodeNm, receiver, featureNm));
		SceneMailBox::Accessible = true;
	}
}

void AgentNode::sendFeatureOffMsg(string featureNm, string receiver){
	if(SceneMailBox::Accessible){
		SceneMailBox::Accessible = false;
		SceneMailBox::radioMessage(SceneMessage::FeatureOffMessage(nodeNm, receiver, featureNm));
		SceneMailBox::Accessible = true;
	}
}

void AgentNode::addFeature(){
	for(unsigned int i = 0;i < feature->size(); i++){
		for(unsigned int j = 0; j< FeatureNode::featureNodeList->size(); j++){
			if(FeatureNode::featureNodeList->at(j)->getFeatureName() == feature->at(i)){
				FeatureNode *fn = FeatureNode::featureNodeList->at(j);
				fn->setRadius(radius);
				fn->init();
				mtNode->addChild(fn);
				featureList->push_back(fn);
				break;
			}
		}
	}
}

AgentNode* AgentNode::getNodeByName(string nodeNm){
	AgentNode* ret;
	for(unsigned int i = 0; i< parentMTList->size(); i++){
		if(parentMTList->at(i)->getName() == nodeNm){
			ret = parentMTList->at(i);
			break;
		}
	}
	return ret;
}

float AgentNode::getRadius(){
	return radius;
}
