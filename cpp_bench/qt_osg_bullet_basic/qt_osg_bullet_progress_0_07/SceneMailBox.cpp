#include "SceneMailBox.h"

vector<SceneMessage*> *SceneMailBox::mailBox = new vector<SceneMessage*>();
vector<string> *SceneMailBox::userList = new vector<string>();
bool SceneMailBox::Accessible = true;
unsigned int SceneMailBox::latestId = 0;

SceneMailBox::SceneMailBox(void)
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(checkBox()));
	timer.start(1000);
	this->moveToThread(&t);
	t.start();
}

SceneMailBox::~SceneMailBox(void)
{
}

SceneMailBox* postMan;
SceneMailBox* SceneMailBox::Instance(){
	if(!postMan){
		postMan = new SceneMailBox();
	}
	return postMan;
}

void SceneMailBox::radioMessage(SceneMessage *msg){
	msg->msgId = latestId;
	latestId++;
	mailBox->push_back(msg);
	cout<<"message number:"<<mailBox->size()<<endl;
}

vector<SceneMessage*>* SceneMailBox::getMailBox(){
	return mailBox;
}

void SceneMailBox::checkBox(){
	if(Accessible == true){
		SceneMailBox::Accessible = false;
		for(int i = 0; i< mailBox->size(); i++){
			if(mailBox->at(i)->stampList.size() == userList->size()){
				cout<<"remove one:"<<mailBox->at(i)->msgId<<endl;
				mailBox->erase(mailBox->begin() + i);
			}else{
				cout<<"cannot remove right now"<<endl;
			}
		}
		SceneMailBox::Accessible = true;
	}
}

void SceneMailBox::stampOn(SceneMessage *msg, string id){
	msg->stampList.push_back(id);
}

bool SceneMailBox::inBox(SceneMessage *msg, string id){
	bool ret = false;
	for(int i = 0; i< msg->stampList.size(); i++){
		if(msg->stampList[i] == id){
			ret = true;
			break;
		}
	}
	return ret;
}

void SceneMailBox::registerUsers(string id){
	userList->push_back(id);
}
