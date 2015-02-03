#include "CustomDraggerManager.h"
#include <iostream>

void CustomDraggerManager::addSelectionToDragger(osg::MatrixTransform* mt, osgManipulator::Dragger* dr){
	dr->addDraggerCallback(new MoveCallback(mt));
}
