#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <QtCore>
#include "Global.h"
#include "SceneMessage.h"

using namespace std;
class SceneMailBox:public QObject
{
	Q_OBJECT
public:
	SceneMailBox(void);
	~SceneMailBox(void);
	static SceneMailBox* Instance();
	static void radioMessage(SceneMessage *msg);
	static vector<SceneMessage*>* getMailBox();
	//static void visitorCheck(string name);
	static void registerUsers(string id);
	static void stampOn(SceneMessage *msg, string id);
	static bool inBox(SceneMessage *msg, string id);
public:
	static bool Accessible;
	static vector<SceneMessage*> *mailBox;
	QThread t;
	QTimer timer;
public slots:
	static void checkBox();
private:
	static vector<string> *userList;
	static unsigned int latestId;
};

