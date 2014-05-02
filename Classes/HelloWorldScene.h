#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);

	//触摸事件监听回调函数
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);
private:
	//私有变了记录触摸开始于结束时的坐标
	int beginX,beginY,endX,endY;
	//左滑动
	bool doLeft();
	//右滑动
	bool doRight();
	//上滑动
	bool doUp();
	//下滑动
	bool doDown();
};

#endif // __HELLOWORLD_SCENE_H__
