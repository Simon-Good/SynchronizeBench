
#include "MoveCallback.h"
#include <osgCollisionDetection/CollisionInterface>
#include <osgDragger/ShowBound>
#include <iostream>

using namespace std;
MoveCallback::MoveCallback(osg::MatrixTransform* mt) : osgManipulator::DraggerTransformCallback(mt)
{
	MT = mt;
	rythem = 0;
}

bool MoveCallback::receive(const osgManipulator::MotionCommand& command)
{
	if (!_transform) return false;

	bool haveCollision = false;
	switch (command.getStage())
	{
	case osgManipulator::MotionCommand::START:
		{
			//也可以考虑把movecallback设计成可以emit QT slot的QOBJECT
			for(int i = 0; i< AgentNode::parentMTList->size(); i++){
				if(AgentNode::parentMTList->at(i)->getName() == MT->getName()){
					currentNode = AgentNode::parentMTList->at(i);
					rythem = 0;
					currentNode->radioPositionMsg();
				}
					
			}

			_startMotionMatrix = _transform->getMatrix();
			_selectionName = _transform->getName();

			osg::NodePath nodePathToRoot;
			osgManipulator::computeNodePathToRoot(*_transform,nodePathToRoot);
			_localToWorld = osg::computeLocalToWorld(nodePathToRoot);
			_worldToLocal = osg::Matrix::inverse(_localToWorld);
			
			osgDragger::ShowBound::Instence()->resetCollision();

			break;
		}
	case osgManipulator::MotionCommand::MOVE:
		{
			rythem++;
			if(rythem%30 == 0){
				currentNode->radioPositionMsg();
			}
			//////////////////////////////////////////
			osg::Matrixf preMatrix;
			preMatrix.identity();

			if(_transform->getNumParents() > 0)
			{
				preMatrix = osg::computeLocalToWorld(_transform->getParentalNodePaths()[0]);
			}

			osg::Matrix selectionMatrix;
			selectionMatrix = _transform->getMatrix();

			////////////////////////////////////////////

			osg::Matrix localMotionMatrix = _localToWorld 
				* command.getWorldToLocal()
				* command.getMotionMatrix()
				* command.getLocalToWorld() 
				* _worldToLocal;

			_transform->setMatrix(localMotionMatrix * _startMotionMatrix);

			//////////////////////////////////////////

			
			osg::Matrixf nowMatrix;
			//nowMatrix.identity();

			if(_transform->getNumParents() > 0)
			{
				nowMatrix = osg::computeLocalToWorld(_transform->getParentalNodePaths()[0]);
			}

			haveCollision = osgCollisionDetection::CollisionInterface::Instence()->updateCollisionOject(_selectionName, nowMatrix, true);
			if (haveCollision)
			{
				OSG_WARN<<"Collision IN"<<std::endl;
				osgDragger::ShowBound::Instence()->collision();

				_transform->setMatrix(selectionMatrix);

				osgCollisionDetection::CollisionInterface::Instence()->updateCollisionOject(_selectionName, preMatrix, false);
			}

			
			
			///////////////////////////////////////////

			/*
			if (AnimationManager::Instence()->getRecord() == true)
			{
				AnimationManager::Instence()->insertControlPoint(_transform.get());
			}
			*/
			break;
		}
	case osgManipulator::MotionCommand::FINISH:
		{
			currentNode->radioPositionMsg();
			rythem = 0;
			break;
		}
	case osgManipulator::MotionCommand::NONE:

	default:
			break;
	}

	return haveCollision;
}
