#pragma once
#include <osgDragger/DraggerManager>
#include "MoveCallback.h"

class CustomDraggerManager:public osgDragger::DraggerManager{
public:
	CustomDraggerManager(){}

	static CustomDraggerManager *Instence(){
		static osg::ref_ptr<CustomDraggerManager> cdm = new CustomDraggerManager;
		return cdm.get();
	}

	virtual void addSelectionToDragger(osg::MatrixTransform* mt, osgManipulator::Dragger* dr);
protected:
	virtual ~CustomDraggerManager(){};
};

