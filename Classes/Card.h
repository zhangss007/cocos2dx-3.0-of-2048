#ifndef _CARD_H_
#define _CARD_H_

#include "cocos2d.h"

USING_NS_CC;

class CardSprite : public Sprite
{
public:
	static CardSprite* createCardSprite(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	virtual bool init();
	CREATE_FUNC(CardSprite);

	//获取数据
	int getNumber();
	//设置数据
	void setNumber(int num);
private:
	//显示的数字
	int number;
	//初始化
	void enemyInit(int number, int wight, int height, float CardSpriteX, float CardSpriteY);
	//显示数字的控件
	LabelTTF *labelCardNumber;
	//背景
	LayerColor *colorBackground;
};


#endif // _CARD_H_
