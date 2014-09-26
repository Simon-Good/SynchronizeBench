#include "TravelManipulator.h"

CTravelManipulator::CTravelManipulator(osgViewer::Viewer* currentViewer):m_fMoveSpeed(5.0f),m_fAngle(2.5f)
{
	m_vPosition = osg::Vec3(0.0f,0.0f,0.0f);//初始位置
	m_vRotation = osg::Vec3(0.0f, 0.0f,0.0f);//初始角度	
	m_viewer = currentViewer;
	m_view = NULL;
}

CTravelManipulator::CTravelManipulator(osgViewer::View* currentView):m_fMoveSpeed(5.0f), m_fAngle(2.5f){
	m_vPosition = osg::Vec3(0.0f,0.0f,0.0f);//初始位置
	m_vRotation = osg::Vec3(0.0f, 0.0f,0.0f);//初始角度	
	m_view = currentView;
	m_viewer = NULL;
}

CTravelManipulator::~CTravelManipulator(void)
{
	//viewer指针是从外部传入的，因此在该类中无需考虑viewer的析构问题，应由CCoreOSG类来完成
}

void CTravelManipulator::setByMatrix(const osg::Matrixd& matrix)
{
}

void CTravelManipulator::setByInverseMatrix(const osg::Matrixd& matrix)
{
}

osg::Matrixd CTravelManipulator::getMatrix(void) const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),

		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),

		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));

	return mat * osg::Matrixd::translate(m_vPosition);
}

osg::Matrixd CTravelManipulator::getInverseMatrix(void) const
{
	osg::Matrixd mat;

	mat.makeRotate(m_vRotation._v[0], osg::Vec3(1.0f, 0.0f, 0.0f),

		m_vRotation._v[1], osg::Vec3(0.0f, 1.0f, 0.0f),

		m_vRotation._v[2], osg::Vec3(0.0f, 0.0f, 1.0f));

	return osg::Matrixd::inverse(mat * osg::Matrixd::translate(m_vPosition));
}

void CTravelManipulator::ChangePosition(osg::Vec3& delta)
{
		m_vPosition += delta; //如果碰撞检测关闭的话就不管怎样都能够前进
}

void CTravelManipulator::renewMyCamera(void)
{
}

bool CTravelManipulator::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us)
{
	switch(ea.getEventType())
	{
		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				if(ea.getKey() == 0XFF50)//home键
				{
					renewMyCamera();
					return true;
				}
				
				if(ea.getKey() == 0XFF52)//向上键，视点向上仰视
				{
					m_vRotation._v[0] += osg::DegreesToRadians(m_fAngle);
					cout<<m_vRotation._v[0]<<" "<<m_vRotation._v[1]<<m_vRotation._v[2]<<endl;
					return true;
				}
				if(ea.getKey () == 0XFF54)//向下键，视点向下俯视
				{
					m_vRotation._v[0] -= osg::DegreesToRadians(m_fAngle);
					cout<<m_vRotation._v[0]<<" "<<m_vRotation._v[1]<<m_vRotation._v[2]<<endl;
					return true;
				}
				if (ea.getKey () == 0x41 || ea.getKey () == 0x61)//大写和小写的A键，视点向左平移（当前朝向向左）
				{
					ChangePosition(osg::Vec3 (0, m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (-m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey () == 0x44||ea.getKey () == 0x64)//大写和小写的d键，视点向右平移（当前朝向向右）
				{
					ChangePosition(osg::Vec3 (0,-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey() == 0xFF53)//Right，向右旋转，旋转点为当时位置
				{
					m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
				}
				if (ea.getKey()== 0xFF51)//Left，向左旋转，旋转点为当时位置
				{
					m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
				}
				if(ea.getKey()==0X57 || ea.getKey()==0X77)//w键，向前
				{
					ChangePosition(osg::Vec3 (0,m_fMoveSpeed * sinf(osg::PI_2+ m_vRotation._v[2]), 0)) ; //sin(pi/2+theta) = cos(theta)
					ChangePosition(osg::Vec3 ( m_fMoveSpeed * cosf(osg::PI_2 + m_vRotation._v[2]),0,0)) ;//cos(pi/2+theta) = -sin(theta)
					return true;
				}
				if(ea.getKey()==0X53 || ea.getKey()==0X73 )//S键，向后退
				{
					ChangePosition(osg::Vec3 (0, -m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				return false;
			}
		case(osgGA::GUIEventAdapter::SCROLL):
			{
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)//鼠标滑轮向上，视点笔直向上走
				{
					ChangePosition(osg::Vec3 (0, 0, m_fMoveSpeed)) ;
					//鼠标滑轮向上，应该处理视点后退事件
					return true;
				}
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)//鼠标滑轮向下，视点笔直向下走
				{
					ChangePosition(osg::Vec3 (0, 0, -m_fMoveSpeed)) ;
					//鼠标滑轮向下，应该处理视点前进事件
					return true;
				}
				
				return false;//默认返回值
			}
		default:
			return false;
	}
}

void CTravelManipulator::setInitialRotation(float x, float y, float z){
	m_vRotation = osg::Vec3(x, y, z);
}

void CTravelManipulator::setInitialPosition(float x, float y, float z){
	m_vPosition = osg::Vec3(x, y, z);
}