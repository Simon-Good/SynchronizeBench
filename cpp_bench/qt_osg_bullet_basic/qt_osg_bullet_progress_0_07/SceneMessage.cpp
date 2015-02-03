#include "SceneMessage.h"


SceneMessage::SceneMessage(void)
{
	eventype = SceneMessage::NONETYPE;
}

SceneMessage::~SceneMessage(void)
{
}

SceneMessage* SceneMessage::PositionMessage(string nodeNm, osg::Matrix nodePos, float radius){
	SceneMessage *msg = new SceneMessage();
	msg->eventype = SceneMessage::POSITIONRADIO;
	msg->sender = nodeNm;
	msg->receiver = "none";
	msg->position = nodePos;
	msg->radius = radius;
	return msg;
}

SceneMessage* SceneMessage::FeatureOffMessage(string sender, string receiver, string featureNm){
	SceneMessage *msg = new SceneMessage();
	msg->eventype = SceneMessage::REQUIREFEATUREOFF;
	msg->sender = sender;
	msg->receiver = receiver;
	msg->featureNm = featureNm;
	return msg;
}

SceneMessage* SceneMessage::FeatureOnMessage(string sender, string receiver, string featureNm){
	SceneMessage *msg = new SceneMessage();
	msg->eventype = SceneMessage::REQUIREFEATUREON;
	msg->sender = sender;
	msg->receiver = receiver;
	msg->featureNm = featureNm;
	return msg;
}