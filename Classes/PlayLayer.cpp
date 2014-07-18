//
//  PlayLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//
#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "PlayLayer.h"
#include "GameManager.h"

PlayLayer::PlayLayer()
:isTouchEnable(false)
,spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
,chooseTowerpanle(NULL)
,towerMatrix(NULL)
,money(0)
{
}

PlayLayer::~PlayLayer()
{
    if (towerMatrix) {
        free(towerMatrix);
    }
	pointsVector.clear();
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
    
    auto gameBg = Sprite::create("playbg.png");
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
    spriteSheet = SpriteBatchNode::create("Play.png");
    addChild(spriteSheet);
    
    money =2000;
    
    map = TMXTiledMap::create("map.tmx");
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
    this->addChild(map, -10);
    
    offX = ( map->getContentSize().width - winSize.width )/ 2;
    initPointsVector(offX);
    addEnemy();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    
    int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
    towerMatrix = (TowerBase **)malloc(arraySize);
    memset((void*)towerMatrix, 0, arraySize);
    
	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
            towerMatrix[row * MAP_WIDTH + col] = NULL;
        }
    }
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
    
    EnemyBase* enemy = Thief::createThief(pointsVector,10);
	this->addChild(enemy, -1);
    instance->enemyVector.pushBack(enemy);
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{
    if(chooseTowerpanle != NULL)
    {
        this->removeChild(chooseTowerpanle);
    }

    auto location = touch->getLocation();
    checkAndAddTowerPanle(location);
	return true;
}

void PlayLayer::addTowerChoosePanle(Point point)
{
    chooseTowerpanle = TowerPanleLayer::create();
    chooseTowerpanle->setPosition(point);
    this->addChild(chooseTowerpanle);
}

Point PlayLayer::convertTotileCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y =map->getMapSize().height- position.y / map->getContentSize().height * map->getMapSize().height;
    
	return Point(x, y);
}
Point PlayLayer::convertToMatrixCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y = position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}

void PlayLayer::checkAndAddTowerPanle(Point position)
{
	Point towerCoord = convertTotileCoord(position);
	Point matrixCoord = convertToMatrixCoord(position);
    
	int gid = bgLayer->getTileGIDAt(towerCoord);
	auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
    int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );

	int TouchVaule;
	if (tileTemp.empty())
	{
		TouchVaule = 0;
	}else
	{
		TouchVaule = tileTemp.at("canTouch").asInt();
	}
    auto tileWidth = map->getContentSize().width / map->getMapSize().width;
	auto tileHeight = map->getContentSize().height / map->getMapSize().height;
	towerPos = Point((towerCoord.x * tileWidth) + tileWidth/2 -offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);
    
    if (1 == TouchVaule && towerMatrix[MatrixIndex]==NULL)
	{
		addTowerChoosePanle(towerPos);
	}
	else
	{
		auto tips = Sprite::createWithSpriteFrameName("no.png");
		tips->setPosition(towerPos);
		this->addChild(tips);
		tips->runAction(Sequence::create(DelayTime::create(0.8f),
                                         CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                         NULL));
	}
}

void PlayLayer::addTower()
{
    if(chooseTowerpanle != NULL  )
	{
		auto type = chooseTowerpanle->getChooseTowerType();
        if(type == TowerType::ANOTHER)
        {
            return;
        }
		Point matrixCoord = convertToMatrixCoord(towerPos);
		int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
		bool noMoneyTips = false;
        TowerBase* tower = NULL;
		if( type == TowerType::ARROW_TOWER )
        {
			if( money >= 200 )
			{
				tower = ArrowTower::create();
				money -= 200;
			}
            else
            noMoneyTips = true;
		}
        else if( type == TowerType::ATTACK_TOWER )
        {
			if( money >= 150 )
			{
				tower = AttackTower::create();
				money -= 150;
			}
            else
            noMoneyTips = true;
		}
		else if( type == TowerType::MULTIDIR_TOWER )
        {
			if( money >= 200 )
			{
				tower = MultiDirTower::create();
				money -= 200;
			}else
            noMoneyTips = true;
		}
        if(tower != NULL)
        {
            tower->setPosition(towerPos);
            tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
            this->addChild(tower);
            towerMatrix[MatrixIndex] =  tower;
        }
        type =  TowerType::ANOTHER;
        chooseTowerpanle->setChooseTowerType(type);
        this->removeChild(chooseTowerpanle);
        chooseTowerpanle = NULL;
        
		if( noMoneyTips == true )
		{
            auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
			tips->setPosition(towerPos);
			this->addChild(tips);
			tips->runAction(Sequence::create(DelayTime::create(0.5f),
                                             CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
                                             NULL));
		}
	}
}

void PlayLayer::CollisionDetection()
{
    GameManager *instance = GameManager::getInstance();
    
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    
	if(bulletVector.empty() || enemyVector.empty() ){
		return;
	}
	Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
    for (int i = 0; i < bulletVector.size(); i++)
	{
		auto  bullet = bulletVector.at(i);
        bullet->getBoundingBox();
		auto  bulletRect = Rect(bullet->getPositionX() +bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
                                bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height );
        
		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			auto enemyRect = enemy->sprite->getBoundingBox();
            
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
				break;
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

void PlayLayer::update(float dt)
{
    
    addTower();
    CollisionDetection();
}


