//
//  PlayLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#include "PlayLayer.h"
#include "GameManager.h"

PlayLayer::PlayLayer()
:isTouchEnable(false)
,spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
,chooseTowerpanle(NULL)
{
}

PlayLayer::~PlayLayer()
{
}

Scene *PlayLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayLayer::create();
    scene->addChild(layer);
    return scene;
}

bool PlayLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size winSize = Director::getInstance()->getWinSize();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprite.plist");
    spriteSheet = SpriteBatchNode::create("Sprite.png");
    addChild(spriteSheet);
    
    map = TMXTiledMap::create("map1.tmx");
    auto bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
    this->addChild(map, -1);
    
    float offX = ( map->getContentSize().width - winSize.width )/ 2;
    initPointsVector(offX);
    addEnemy();
    
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    return true;
}

void PlayLayer::initPointsVector(float offX)
{
    Node *runOfPoint = NULL;
	int count = 0;
	ValueMap point;
	point = objects->getObject(std::to_string(count));
	while (point.begin()!= point.end())
	{
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();
		runOfPoint = Node::create();
		runOfPoint->setPosition(Point(x - offX , y  ));
		this->pointsVector.pushBack(runOfPoint);
		count++;
		point = objects->getObject( std::to_string(count));
	}
	runOfPoint = NULL;
}

void PlayLayer::addEnemy()
{
    GameManager *instance = GameManager::getInstance();
    
    EnemyBase* enemy = Thief::createThief(pointsVector);
	this->addChild(enemy);
    instance->enemyVector.pushBack(enemy);
    
}


bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{
	this->removeChild(chooseTowerpanle);
	chooseTowerpanle = NULL;
    
    //if(isTouchEnable)
    // {
    auto location = touch->getLocation();
    addTowerChoosePanle(location);
    towerPos = location;
    // }
    
	return true;
}


void PlayLayer::addTowerChoosePanle(Point point)
{
    chooseTowerpanle = TowerPanleLayer::create();
    chooseTowerpanle->setPosition(point);
    this->addChild(chooseTowerpanle);
}

void PlayLayer::update(float dt)
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    auto towerVector = instance->towerVector;
    
    if(chooseTowerpanle != NULL )
	{
		auto type = chooseTowerpanle->getChooseTowerType();
		if( type == TowerType::ARROW_TOWER)
        {
			TowerBase* tower = ArrowTower::create();
			tower->setPosition(towerPos);
			this->addChild(tower);
            instance->towerVector.pushBack(tower);
            
			type =  TowerType::ANOTHER;
			chooseTowerpanle->setChooseTowerType(type);
            
		}
	}
    
    Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
    // 碰撞检测
    for (int i = 0; i < bulletVector.size(); i++)
	{
		auto  bullet = bulletVector.at(i);
        bullet->boundingBox();
		auto  bulletRect = Rect(bullet->getPositionX()+bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
                                bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height );
        
		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			auto enemyRect = enemy->sprite->boundingBox();
            
			if (bulletRect.intersectsRect(enemyRect))
			{
                auto currHp = enemy->getCurrHp();
                currHp--;
                enemy->setCurrHp( currHp );
                
				auto currHpPercentage = enemy->getHpPercentage();
                auto offHp = 100 / enemy->getMaxHp();
				currHpPercentage -= offHp;
                if(currHpPercentage < 0){
                    currHpPercentage = 0;
                }
                enemy->setHpPercentage(currHpPercentage);
				enemy->getHpBar()->setPercentage(currHpPercentage);
                
                if(currHp <= 0)
                {
                    enemyNeedToDelete.pushBack(enemy);
                }
                bulletNeedToDelete.pushBack( bullet);
			}
		}
		for (EnemyBase* enemyTemp : enemyNeedToDelete)
		{
            enemyTemp->enemyExpload();
            instance->enemyVector.eraseObject(enemyTemp);
		}
		enemyNeedToDelete.clear();
	}
	
	for (const auto& bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}


