#pragma once
#include <string>
#include <vector>
#include "Global.h"

using namespace std;
class SceneMessage
{
public:
	enum EventType{
		NONETYPE,
		POSITIONRADIO, 
		REQUIREFEATUREON, 
		REQUIREFEATUREOFF
	};
	SceneMessage(void);
	~SceneMessage(void);

	static SceneMessage* PositionMessage(string nodeNm, osg::Matrix location, float radius);
	static SceneMessage* FeatureOnMessage(string sender, string receiver, string featureNm);
	static SceneMessage* FeatureOffMessage(string sender, string receiver, string featureNm);
public:
	string sender;
	string receiver;
	EventType eventype;
	vector<string> stampList;
	unsigned int msgId;
	string featureNm;
	osg::Matrix position;
	float radius;
};


