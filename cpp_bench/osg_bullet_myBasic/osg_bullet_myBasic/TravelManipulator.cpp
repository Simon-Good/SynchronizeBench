#include "TravelManipulator.h"

CTravelManipulator::CTravelManipulator(osgViewer::Viewer* currentViewer):m_fMoveSpeed(5.0f),m_fAngle(2.5f)
{
	m_vPosition = osg::Vec3(175.0f,35.0f,90.0f);//��ʼλ��
	m_vRotation = osg::Vec3(osg::PI_2*0.8, 0.0f,osg::PI_2);//��ʼ�Ƕ�	
	m_viewer = currentViewer;
	m_firstFloor = true;//��ʼ��������ӵ����ڵ�һ¥�㼴����һ��
}

CTravelManipulator::~CTravelManipulator(void)
{
	//���viewer�Ǵ��ⲿ����ģ�����ڸ��������迼��viewer���������⣬Ӧ��CCoreOSG�������
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
	osg::Vec3 newPos = m_vPosition + delta; 
	osgUtil::IntersectVisitor iv; 
	osg::ref_ptr<osg::LineSegment> line = new osg::LineSegment(newPos,m_vPosition); 
	iv.addLineSegment (line.get()) ;
	m_viewer->getSceneData()->accept(iv); 
	m_vPosition += delta; //�����ײ���رյĻ��Ͳ����������ܹ�ǰ��
	
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
				if(ea.getKey() == 0XFF50)//home��
				{
					renewMyCamera();
					return true;
				}
				if(ea.getKey() == 0XFF52)//���ϼ����ӵ���������
				{
					m_vRotation._v[0] += osg::DegreesToRadians(m_fAngle);
					return true;
				}
				if(ea.getKey () == 0XFF54)//���¼����ӵ����¸���
				{
					m_vRotation._v[0] -= osg::DegreesToRadians(m_fAngle);
					return true;
				}
				if (ea.getKey () == 0x41 || ea.getKey () == 0x61)//��д��Сд��A�����ӵ�����ƽ�ƣ���ǰ��������
				{
					ChangePosition(osg::Vec3 (0, m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (-m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey () == 0x44||ea.getKey () == 0x64)//��д��Сд��d�����ӵ�����ƽ�ƣ���ǰ�������ң�
				{
					ChangePosition(osg::Vec3 (0,-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if (ea.getKey() == 0xFF53)//Right��������ת����ת��Ϊ��ʱλ��
				{
					m_vRotation._v[2] -= osg::DegreesToRadians(m_fAngle);
				}
				if (ea.getKey()== 0xFF51)//Left��������ת����ת��Ϊ��ʱλ��
				{
					m_vRotation._v[2] += osg::DegreesToRadians(m_fAngle);
				}
				if(ea.getKey()==0X57 || ea.getKey()==0X77)//w������ǰ
				{
					ChangePosition(osg::Vec3 (0, m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3 (m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				if(ea.getKey()==0X53 || ea.getKey()==0X73 )//S���������
				{
					ChangePosition(osg::Vec3 (0, -m_fMoveSpeed * sinf(osg::PI_2+m_vRotation._v[2]), 0)) ; 
					ChangePosition(osg::Vec3(-m_fMoveSpeed * cosf(osg::PI_2+m_vRotation._v[2]), 0, 0)) ;
					return true;
				}
				return false;
			}
		case(osgGA::GUIEventAdapter::SCROLL):
			{
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)//��껬�����ϣ��ӵ��ֱ������
				{
					ChangePosition(osg::Vec3 (0, 0, m_fMoveSpeed)) ;
					return true;
				}
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)//��껬�����£��ӵ��ֱ������
				{
					ChangePosition(osg::Vec3 (0, 0, -m_fMoveSpeed)) ;
					return true;
				}
				
				return false;//Ĭ�Ϸ���ֵ
			}
		default:
			return false;
	}
}
