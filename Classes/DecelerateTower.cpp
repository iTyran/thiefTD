//
//  DecelerateTower.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "DecelerateTower.h"
#include "GameManager.h"

bool DecelerateTower::init()
{
    if (!TowerBase::init())
	{
		return false;
	}
    
    setScope(90);
    setTowerValue(200);
    setLethality(1);
    setRate(2);
    tower= Sprite::createWithSpriteFrameName("mftower.png");
    addChild(tower);
    
    schedule(schedule_selector(DecelerateTower::shoot), 0.8f);
	return true;
}


Sprite* DecelerateTower::DecelerateTowerBullet()
{
    Sprite* bullet = Sprite::createWithSpriteFrameName("bullet1.png");
    bullet->setPosition(0, tower->getContentSize().height /4 );
    addChild(bullet);
    
    return bullet;
}


void DecelerateTower::shoot(float dt)
{
    GameManager *instance = GameManager::getInstance();
    auto bulletVector = instance->bulletVector;
    
    checkNearestEnemy();
    if(nearestEnemy!=NULL && nearestEnemy->getCurrHp() > 0 )
    {
        auto currBullet = DecelerateTowerBullet();
        instance->bulletVector.pushBack(currBullet);
        
        auto moveDuration = getRate();
        Point shootVector = nearestEnemy->sprite->getPosition() - this->getPosition();
		Point normalizedShootVector = -shootVector.normalize();
        
        auto farthestDistance = Director::getInstance()->getWinSize().width;
		Point overshotVector = normalizedShootVector * farthestDistance;
		Point offscreenPoint = (currBullet->getPosition() - overshotVector);
        
		currBullet->runAction(Sequence::create(MoveTo::create(moveDuration, offscreenPoint),
                                               CallFuncN::create(CC_CALLBACK_1(DecelerateTower::removeBullet, this)),
                                               NULL));
        currBullet = NULL;
    }
}

void DecelerateTower::removeBullet(Node* pSender)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    
	Sprite *sprite = (Sprite *)pSender;
    instance->bulletVector.eraseObject(sprite);
    sprite->removeFromParent();
}