
/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2011 Liu zhiyu
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
// Written by Liu zhiyu

#ifndef MOVECALLBACK_H
#define MOVECALLBACK_H

#include <osgManipulator/Dragger>
#include "SceneMailBox.h"
#include "AgentNode.h"
#include "Global.h"

class MoveCallback : public osgManipulator::DraggerTransformCallback
{
public:
	MoveCallback(osg::MatrixTransform* mt);

	virtual bool receive(const osgManipulator::MotionCommand&);
    osg::MatrixTransform* MT;
private:
	std::string _selectionName;
	AgentNode* currentNode;
	int rythem;
};
#endif