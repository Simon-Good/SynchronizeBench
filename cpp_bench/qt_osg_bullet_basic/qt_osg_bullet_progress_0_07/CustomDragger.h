
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

#ifndef CUSTOMDRAGGER_H
#define CUSTOMDRAGGER_H

#include <osgCollisionDetection/CollisionInterface>
#include <osgDragger/MyDragger>



typedef osgDragger::TemplateMoveDragger<osgDragger::Move1DDragger, osgDragger::Move2DDragger> MoveDragger;

typedef osgDragger::TemplateRotateDragger<osgDragger::CylinderDragger, osgDragger::SphereDragger> RotateDragger;

class CustomMoveDragger : public MoveDragger
{

public:
	virtual void handleDragMessage(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		if (osgCollisionDetection::CollisionInterface::Instence()->getCollision())
		{

			osgCollisionDetection::CollisionInterface::Instence()->reset();

			(const_cast<osgGA::GUIEventAdapter&>(ea)).setEventType(osgGA::GUIEventAdapter::RELEASE);

			handle(_pointer, ea, aa);

		}
	}

};

class CustomRotateDragger : public RotateDragger
{
public:
	virtual void handleDragMessage(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		if (osgCollisionDetection::CollisionInterface::Instence()->getCollision())
		{

			osgCollisionDetection::CollisionInterface::Instence()->reset();

			(const_cast<osgGA::GUIEventAdapter&>(ea)).setEventType(osgGA::GUIEventAdapter::RELEASE);

			handle(_pointer, ea, aa);

		}
	}

};


#endif