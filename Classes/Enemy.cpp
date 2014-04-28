//
//  Enemy.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#include "Enemy.h"
#include "CCVector.h"


EnemyBase::EnemyBase()
:pointCounter(0)
,animationRight(NULL)
,animationLeft(NULL)
,animationExplode(NULL)
,pointsVector(NULL)
,runSpeed(0)
,maxHp(0)
,currHp(0)
,hpPercentage(100)
,hpBar(NULL)
{
}

EnemyBase::~EnemyBase()
{}

bool EnemyBase::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void EnemyBase::createAndSetHpBar()
{
    hpBgSprite = Sprite::createWithSpriteFrameName("hpBg1.png");
    hpBgSprite->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height ));
    sprite->addChild(hpBgSprite);
    
	hpBar = CCProgressTimer::create(Sprite::createWithSpriteFrameName("hp1.png"));
	hpBar->setType(ProgressTimer::Type::BAR);
	hpBar->setMidpoint(Point(0, 0.5f));
	hpBar->setBarChangeRate(Point(1, 0));
	hpBar->setPercentage(hpPercentage);
    hpBar->setPosition(Point(hpBgSprite->getContentSize().width / 2, hpBgSprite->getContentSize().height / 3 * 2 ));
    hpBgSprite->addChild(hpBar);
}

Animation* EnemyBase::createAnimation(std::string prefixName, int framesNum, float delay)
{
    Vector<SpriteFrame*> animFrames;
    
	for (int i = 1; i <= framesNum; i++)
    {
        char buffer[20] = { 0 };
        sprintf(buffer, "_%i.png",  i);
        std::string str =  prefixName + buffer;
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    return Animation::createWithSpriteFrames(animFrames, delay);
}

void EnemyBase::changeDirection(float dt)
{
    auto curr = currPoint();
    
    if(curr->getPositionX() > sprite->getPosition().x )
    {
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runright"))) ;
    }else{
        sprite->runAction( Animate::create(AnimationCache::getInstance()->getAnimation("runleft"))  );
    }
}

Node* EnemyBase::currPoint()
{
    return this->pointsVector.at(pointCounter);
}

Node* EnemyBase::nextPoint()
{
    int maxCount = this->pointsVector.size();
	pointCounter++;
	if (pointCounter < maxCount  ){
		auto node =this->pointsVector.at(pointCounter);
        return node;
    }
    else{
        pointCounter = maxCount -1 ;
    }
    return NULL;
}

void EnemyBase::runFllowPoint()
{
    auto point = currPoint();
    sprite->setPosition(point->getPosition());
    point = nextPoint();
    
    if( point!= NULL ){
        sprite->runAction(Sequence::create(MoveTo::create(getRunSpeed(), point->getPosition())
                                   , CallFuncN::create(CC_CALLBACK_0(EnemyBase::runFllowPoint, this))
                                   , NULL));
    }
}

void EnemyBase::enemyExpload()
{
    hpBgSprite->removeFromParent();
    sprite->stopAllActions();
    unschedule(schedule_selector(EnemyBase::changeDirection));
    sprite->runAction(Sequence::create(Animate::create(AnimationCache::getInstance()->getAnimation("explode"))
                               ,CallFuncN::create(CC_CALLBACK_0(EnemyBase::removeFromParent, this))
                               , NULL));
}

void EnemyBase::removeEnemy()
{
    this->removeFromParent();
}

void EnemyBase::setPointsVector(Vector<Node*> points)
{
    this->pointsVector = points;
}

//==================Thief class====================//

bool Thief::init()
{
	if (!Sprite::init())
	{
		return false;
	}
    setRunSpeed(9);
    setMaxHp(10);
    setCurrHp(10);
    sprite = Sprite::createWithSpriteFrameName("enemyRight1_1.png");
    this->addChild(sprite);
    animationRight = createAnimation("enemyRight1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationRight, "runright");
    animationLeft = createAnimation("enemyLeft1", 4, 0.1f);
	AnimationCache::getInstance()->addAnimation(animationLeft, "runleft");
    animationExplode= createAnimation("explode", 6, 0.15f);
	AnimationCache::getInstance()->addAnimation(animationExplode, "explode");
    
    createAndSetHpBar();
	schedule(schedule_selector(EnemyBase::changeDirection), 0.4f);
	return true;
}

Thief* Thief::createThief(Vector<Node*> points)
{
    Thief *pRet = new Thief();
    if (pRet && pRet->init())
    {
        pRet->setPointsVector(points);
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

