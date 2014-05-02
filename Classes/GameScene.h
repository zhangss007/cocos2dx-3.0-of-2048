#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "cocos2d.h"
#include "Card.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(GameScene);

	//触摸事件监听回调函数
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	//根据屏幕大小创建卡片
	void createCardSprite(Size size);
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
	//储存卡片类
	CardSprite *cardArr[4][4];
	//分数
	int score;
	//显示分数控件
	LabelTTF *cardNumberTTF;
	//创建生成随机卡片
	void createCardNumber();
	//检测游戏是否结束
	void doCheck();
	//设置分数
	void setScore(int score);
};

#endif // _GAME_SCENE_H
