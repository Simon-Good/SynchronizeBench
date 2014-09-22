#pragma once

#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <osgUtil/IntersectVisitor>
#include <osg/LineSegment>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <cmath>

class CTravelManipulator :
	public osgGA::CameraManipulator
{
public:
	CTravelManipulator(osgViewer::Viewer* currentViewer);
	~CTravelManipulator(void);

protected:
	float   m_fMoveSpeed;
	osg::Vec3    m_vPosition;
	osg::Vec3    m_vRotation;
	float m_fAngle;
	osgViewer::Viewer* m_viewer;
	bool m_firstFloor;

public:
	virtual void setByMatrix(const osg::Matrixd& matrix);
	virtual void setByInverseMatrix(const osg::Matrixd& matrix);
	virtual osg::Matrixd getMatrix(void) const;
	virtual osg::Matrixd getInverseMatrix(void) const;
	void ChangePosition(osg::Vec3& delta);
	void renewMyCamera(void);
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us);
};
