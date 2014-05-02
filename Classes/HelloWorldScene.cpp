#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	//设置触摸事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	Point beginTouch = touch->getLocation();
	beginX = beginTouch.x;
	beginY = beginTouch.y;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	Point endTouch = touch->getLocation();
	//计算手指在X，Y移动的距离
	endX = beginX - endTouch.x;
	endY = beginY - endTouch.y;
	if (abs(endX) > abs(endY))
	{
		//如果X轴移动的距离大于Y轴，则是左右移动
		if (endX + 5 > 0)
		{
			//向左移动
			doLeft();
		}
		else
		{
			//向右移动
			doRight();
		}
	}
	else //否则是上下移动
	{
		if (endY + 5 > 0)
		{
			//向下移动
			doDown();
		}
		else
		{
			//向上移动
			doUp();
		}
	}
}

//左滑动
bool HelloWorld::doLeft()
{
	CCLOG("向左");

	return true;
}

//右滑动
bool HelloWorld::doRight()
{
	CCLOG("向右");

	return true;
}

//上滑动
bool HelloWorld::doUp()
{
	CCLOG("向上");

	return true;
}

//下滑动
bool HelloWorld::doDown()
{
	CCLOG("向下");

	return true;
}
