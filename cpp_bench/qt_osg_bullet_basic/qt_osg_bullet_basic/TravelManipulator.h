#pragma once

#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <osgUtil/IntersectVisitor>
#include <osg/LineSegment>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <cmath>
#include <iostream>

using namespace std;


class CTravelManipulator :
	public osgGA::CameraManipulator
{
public:
	CTravelManipulator(osgViewer::Viewer* currentViewer);
	CTravelManipulator(osgViewer::View* currrentView);
	~CTravelManipulator(void);

protected:
	float   m_fMoveSpeed;
	float m_fAngle;
	osg::Vec3    m_vPosition;
	osg::Vec3    m_vRotation;
	osgViewer::Viewer* m_viewer;
	osgViewer::View* m_view;

public:
	virtual void setByMatrix(const osg::Matrixd& matrix);
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getMatrix(void) const;
	virtual osg::Matrixd getInverseMatrix(void) const;
	void ChangePosition(osg::Vec3& delta);
	void renewMyCamera(void);
	void setInitialPosition(float x, float y, float z);
	void setInitialRotation(float x, float y, float z);
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
};
