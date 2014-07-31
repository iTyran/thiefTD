//
//  Thief.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-28.
//
//

#include "Thief.h"


bool Thief::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    setRunSpeed(25);
    setVaule(10);
    sprite = Sprite::createWithSpriteFrameName("enemyRight1_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("enemyRight1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright1");
    animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft1");
    animationExplode= createAnimation("explode1", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode1");
    
    createAndSetHpBar();
	schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
	return true;
}

Thief* Thief::createThief(Vector<Node*> points, int hp)
{
    Thief *pRet = new Thief();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
        pRet->runFllowPoint();
        
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void Thief::changeDirection(float dt)
{
    auto curr = currPoint();
    if( curr == NULL )
	{
		return;
	}
    if(curr->getPositionX() > sprite->getPosition().x )
    {
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright1"))) ;
    }else{
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft1"))  );
    }
}
void Thief::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(schedule_selector(Thief::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode1"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}


bool Pirate::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    setRunSpeed(50);
    setVaule(20);
    sprite = Sprite::createWithSpriteFrameName("enemyRight2_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("enemyRight2", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright2");
    animationLeft = createAnimation("enemyLeft2", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft2");
    animationExplode= createAnimation("explode2", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode2");
    
    createAndSetHpBar();
	schedule(schedule_selector(Pirate::changeDirection), 0.4f);
	return true;
}

Pirate* Pirate::createPirate(Vector<Node*> points, int hp)
{
    Pirate *pRet = new Pirate();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
        pRet->runFllowPoint();
        
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
void Pirate::changeDirection(float dt)
{
    auto curr = currPoint();
    if( curr == NULL )
	{
		return;
	}
    if(curr->getPositionX() > sprite->getPosition().x )
    {
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright2"))) ;
    }else{
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft2"))  );
    }
}
void Pirate::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(schedule_selector(Pirate::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode2"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}


bool Bandit::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    setRunSpeed(70);
    setVaule(30);
    sprite = Sprite::createWithSpriteFrameName("enemyRight3_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("enemyRight3", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright3");
    animationLeft = createAnimation("enemyLeft3", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft3");
    animationExplode= createAnimation("explode3", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode3");
    
    createAndSetHpBar();
	schedule(schedule_selector(Bandit::changeDirection), 0.4f);
	return true;
}

Bandit* Bandit::createBandit(Vector<Node*> points, int hp)
{
    Bandit *pRet = new Bandit();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
		pRet->setMaxHp(hp);
		pRet->setCurrHp(hp);
        pRet->runFllowPoint();
        
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
void Bandit::changeDirection(float dt)
{
    auto curr = currPoint();
    if( curr == NULL )
	{
		return;
	}
    if(curr->getPositionX() > sprite->getPosition().x )
    {
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright3"))) ;
    }else{
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft3"))  );
    }
}
void Bandit::enemyExpload()
{
    hpBgSprite->setVisible(false);
    sprite->stopAllActions();
    unschedule(schedule_selector(Bandit::changeDirection));
    sprite->setAnchorPoint(Point(0.5f, 0.25f));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode3"))
                                       ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                                       , NULL));
}

