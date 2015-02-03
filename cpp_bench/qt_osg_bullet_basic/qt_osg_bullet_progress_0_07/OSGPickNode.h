#pragma once
#include <osgGA/GUIEventHandler>
#include <Utils/Utils>
#include <osgViewer/Viewer>
#include <CustomDraggerManager.h>
#include <osgDragger/ShowBound>
#include <iostream>

using namespace std;

class OSGPickNode: public osgGA::GUIEventHandler{
public:
	OSGPickNode(void){}
	~OSGPickNode(void){}
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
		if(ea.getHandled() == true){
			return true;
		}

		osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
		if(!view){
			return false;
		}

		float x = ea.getX();
		float y = ea.getY();
		switch(ea.getEventType()){
		case osgGA::GUIEventAdapter::KEYDOWN:
			{
				if(ea.getKey() == osgGA::GUIEventAdapter::KEY_1){
					CustomDraggerManager::Instence()->setActiveDragger("move");
				}
				if(ea.getKey() == osgGA::GUIEventAdapter::KEY_2){
					CustomDraggerManager::Instence()->setActiveDragger("rotate");
				}
			}
			break;
		case osgGA::GUIEventAdapter::PUSH:
			{
				if(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON & ea.getButtonMask()){
					osg::MatrixTransform* mt = pick(view, x, y);
					if(mt){
						if((ea.getModKeyMask() & osgGA::GUIEventAdapter::MODKEY_CTRL) == 0){
							//如果没有按下CTRL键，则清空selections
							//&不是逻辑运算，结合性和&& 不同，内层括号必须加。否则不按CTRL时不会清空
							_pickSelections.clear();
						}
						_pickSelections.push_back(mt);
						for(unsigned int i = 0; i< _pickSelections.size(); i++)
							cout<<"pick:"<<_pickSelections.at(i)->getName();
						cout<<endl;
						CustomDraggerManager::Instence()->setSelections(_pickSelections);
						osgDragger::ShowBound::Instence()->setSelections(_pickSelections);
					}
				}
			}
			break;
		}
		return false;
	}
	osg::MatrixTransform* pick(osgViewer::View* view, float x, float y){
		osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector = 
			new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, x, y);  
		osgUtil::IntersectionVisitor iv(intersector.get());
		iv.setTraversalMask(0x1);
		view->getCamera()->accept(iv);

		if(intersector->containsIntersections()){
			const osgUtil::LineSegmentIntersector::Intersection& result = 
				*(intersector->getIntersections().begin());
			int size = result.nodePath.size();

			osg::MatrixTransform* selection = 0;

			for(int index = 0; index < size; index++){
				selection = dynamic_cast<osg::MatrixTransform*>(result.nodePath[index]);
				if(selection){
					std::string str = selection->getName();
					if(!str.empty()){
						return selection;
					}
				}
			}
		}
		return 0;//其他情况必须返回0，否则会劫持其他控制器的消息
	}
	SelectionList _pickSelections;
};