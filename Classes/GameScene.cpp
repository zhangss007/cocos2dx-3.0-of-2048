#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//设置触摸事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//加入游戏背景
	auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	//创建分数
	auto cardNumberTitle = LabelTTF::create("SCORE","Consolas",80);
	cardNumberTitle->setPosition(Point(visibleSize.width/2 + 340, visibleSize.height/2 + 130));
	addChild(cardNumberTitle);

	score = 0;
	cardNumberTTF = LabelTTF::create("0", "Consolas", 70);
	cardNumberTTF->setPosition(Point(visibleSize.width/2 + 340, visibleSize.height/2 - 100));
	addChild(cardNumberTTF);

	//创建4X4卡片
	createCardSprite(visibleSize);

	//初始时生成两个2
	createCardNumber();
	createCardNumber();

	return true;
}

//根据屏幕大小创建卡片
void GameScene::createCardSprite(Size size)
{
	//求出单元格的宽和高
	int cardSize = (size.height - 36) / 4;
	//绘制出4X4的单元格
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//需要屏幕分辨率适配
			CardSprite *card = CardSprite::createCardSprite(0, cardSize, cardSize, cardSize*i+80, cardSize*j+20);
			cardArr[i][j] = card;
			addChild(card);
		}
	}
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	//得到触摸时坐标
	Point beginTouch = touch->getLocation();  //获取OpenGL坐标，以左下角为原点
	beginX = beginTouch.x;
	beginY = beginTouch.y;

	return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	//得到触摸结束时坐标
	Point endTouch = touch->getLocation();  //获取OpenGL坐标，以左下角为原点
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
			createCardNumber();
			doCheck();
			setScore(score);
		}
		else
		{
			//向右移动
			doRight();
			createCardNumber();
			doCheck();
			setScore(score);
		}
	}
	else //否则是上下移动
	{
		if (endY + 5 > 0)
		{
			//向下移动
			doDown();
			createCardNumber();
			doCheck();
			setScore(score);
		}
		else
		{
			//向上移动
			doUp();
			createCardNumber();
			doCheck();
			setScore(score);
		}
	}
}

//创建生成随机卡片
void GameScene::createCardNumber()
{
	int i = CCRANDOM_0_1() * 4;        //生成0~3随机数
	int j = CCRANDOM_0_1() * 4;

	//判断是否已经存在
	if (cardArr[i][j]->getNumber() > 0)
	{
		createCardNumber();
	}
	else
	{
		//2和4的生成率为9:1
		cardArr[i][j]->setNumber(CCRANDOM_0_1()*10 < 1 ? 4 : 2);
	}
}

//检测游戏是否结束
void GameScene::doCheck()
{
	bool isGameOver = true;
	//判断每一个的上下左右和自己是否相同
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (cardArr[x][y]->getNumber() == 0 ||
				(x<3 && cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber()) ||
				(x>0 && cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber()) ||
				(y<3 && cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber()) ||
				(y>0 && cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber()) )
			{
				isGameOver = false;
			}
		}
	}
	if (isGameOver)
	{
		//重来
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene()));
	}
}

//左滑动
bool GameScene::doLeft()
{
	//判断有没有发生移动
	bool isMove = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x+1; x1<4; x1++)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						 cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						 cardArr[x1][y]->setNumber(0);

						 //改变分数
						 score += cardArr[x][y]->getNumber();
						 isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//右滑动
bool GameScene::doRight()
{
	//判断有没有发生移动
	bool isMove = false;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x-1; x1>=0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);
						//改变分数
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//上滑动
bool GameScene::doUp()
{
	//判断有没有发生移动
	bool isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y-1; y1>=0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						//改变分数
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//下滑动
bool GameScene::doDown()
{
	//判断有没有发生移动
	bool isMove = false;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y <4; y++)
		{
			for (int y1 = y+1; y1<4; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isMove = true;
					}
					else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);
						//改变分数
						score += cardArr[x][y]->getNumber();
						isMove = true;
					}
					break;
				}
			}
		}
	}

	return isMove;
}

//设置分数
void GameScene::setScore(int score)
{
	cardNumberTTF->setString(__String::createWithFormat("%i",score)->getCString());
}