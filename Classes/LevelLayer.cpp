//
//  LevelScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "LevelScene.h"
#include "LevelLayer.h"
USING_NS_CC;

LevelLayer::LevelLayer()
:pageNode(0)
,curPageNode(0)
{
}

LevelLayer::~LevelLayer()
{  
}
  
bool LevelLayer::init()
{  
    if (!Layer::init())
	{
		return false;
	}
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(LevelLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(LevelLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(LevelLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
	WINDOW_WIDTH = Director::getInstance()->getWinSize().width;  
	WINDOW_HEIGHT = Director::getInstance()->getWinSize().height;
    
    return true;
}  
  
void LevelLayer::goToCurrNode()
{
    MoveTo *moveTo = MoveTo::create(0.4f, Point::Point(-curPageNode * WINDOW_WIDTH, 0));
    this->runAction(moveTo);
}

void LevelLayer::addNode(Node *level)
{
    if (level)
    {
        level->setContentSize(Size::Size(WINDOW_WIDTH, WINDOW_HEIGHT));
        level->setPosition(Point(WINDOW_WIDTH * pageNode, 0));
        this->addChild(level);
        pageNode++;
    }
}

bool LevelLayer::onTouchBegan(Touch *pTouch, Event  *pEvent)
{
    touchDownPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
    touchCurPoint = touchDownPoint;
    return true;
}

void LevelLayer::onTouchMoved(Touch *pTouch, Event  *pEvent)
{
    Point touchPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
    Point posPoint = Point::Point(getPositionX() + touchPoint.x - touchCurPoint.x, getPositionY());
    auto dis= touchUpPoint.getDistance(touchDownPoint);
    if (dis >= TOUCH_DELTA ) {
        setPosition(posPoint);
    }
    touchCurPoint = touchPoint;
}

void LevelLayer::onTouchEnded(Touch *pTouch, Event  *pEvent)
{
    touchUpPoint = Director::getInstance()->convertToGL(pTouch->getLocationInView());
    auto dis= touchUpPoint.getDistance(touchDownPoint);
    auto sprite1 =Sprite::createWithSpriteFrameName("page_mark1.png");
    auto width = sprite1->getContentSize().width;
    if (dis >= TOUCH_DELTA )
    {
        int offset = getPositionX() - curPageNode * (-WINDOW_WIDTH);
        if (offset > width) {
            if (curPageNode > 0) {
                --curPageNode;
                Sprite *sprite =  (Sprite *)LevelScene::getInstance()->getChildByTag(888);
                sprite->setPosition(Point(sprite->getPositionX()-width,sprite->getPositionY()));
            }
        }
        else if (offset < -width) {
            if (curPageNode < (pageNode - 1)) {
                ++curPageNode;
                Sprite *sprite =  (Sprite *)LevelScene::getInstance()->getChildByTag(888);
                sprite->setPosition(Point(sprite->getPositionX()+width,sprite->getPositionY()));
            }
        }
        goToCurrNode();
    }
}
