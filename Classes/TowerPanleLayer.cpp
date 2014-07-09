//
//  TowerPanleLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#include "TowerPanleLayer.h"

bool TowerPanleLayer::init()
{
    if (!Layer::init())
	{
		return false;
	}
    chooseTowerType = ANOTHER;
    
    auto sprite = Sprite::createWithSpriteFrameName("towerPos.png");
    sprite->setPosition(Point(0, 0));
    this->addChild(sprite);

    sprite1 = Sprite::createWithSpriteFrameName("arrowTower.png");
	sprite1->setAnchorPoint( Point(0.5f, 0));
    sprite1->setPosition(Point(-sprite->getContentSize().width, sprite->getContentSize().height/2));
    this->addChild(sprite1);
    
    sprite2 = Sprite::createWithSpriteFrameName("mftower.png");
	sprite2->setAnchorPoint( Point(0.5f, 0));
    sprite2->setPosition(Point(0, sprite->getContentSize().height/2));
    this->addChild(sprite2);
    
	sprite3 = Sprite::createWithSpriteFrameName("deceleratetower.png");
	sprite3->setAnchorPoint( Point(0.5f, 0));
    sprite3->setPosition(Point(sprite->getContentSize().width, sprite->getContentSize().height/2));
    this->addChild(sprite3);
    
    auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(TowerPanleLayer::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(TowerPanleLayer::onTouchEnded, this);
    
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, sprite1);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener->clone(), sprite3);
    
	return true;
}


bool TowerPanleLayer::onTouchBegan(Touch *touch, Event *event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
    
    Point locationInNode = target->convertTouchToNodeSpace(touch);
    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    
    if (rect.containsPoint(locationInNode))
    {
        target->setOpacity(180);
        return true;
    }
    return false;
}


void TowerPanleLayer::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	if (target == sprite1)
    {
        chooseTowerType = ARROW_TOWER;
    }
    else if(target == sprite2)
    {
        chooseTowerType = DECELERATE_TOWER;
    }
	else if(target == sprite3)
    {
        chooseTowerType = MULTIDIR_TOWER;
    }
    else{
        chooseTowerType = ANOTHER;
    }
}

