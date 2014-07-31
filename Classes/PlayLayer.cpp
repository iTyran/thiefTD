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
#include "LoadLevelInfo.h"

PlayLayer::PlayLayer()
:isTouchEnable(false)
,spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
,chooseTowerpanel(NULL)
,towerMatrix(NULL)
,groupCounter(0)
,money(0)
,playHpBar(NULL)
,playHpPercentage(100)
,moneyLabel(NULL)
,groupLabel(NULL)
,groupTotalLabel(NULL)
,isSuccessful(false)
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
    auto info = LoadLevelinfo::createLoadLevelinfo("levelInfo_1_0.plist");
    info->readLevelInfo();
    
    instance = GameManager::getInstance();
    Size winSize = Director::getInstance()->getWinSize();
    
    auto gameBg = Sprite::create(instance->getCurBgName());
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
    spriteSheet = SpriteBatchNode::create("Play.png");
    addChild(spriteSheet);
    
    map = TMXTiledMap::create(instance->getCurMapName());
    bgLayer = map->getLayer("bg");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
    this->addChild(map, -10);
    
    initToolLayer();
    
    offX = ( map->getContentSize().width - winSize.width )/ 2;
    initPointsVector(offX);
    schedule(schedule_selector(PlayLayer::logic), 2.0f);
    
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
		runOfPoint->setPosition(Point(x - offX, y ));
		this->pointsVector.pushBack(runOfPoint);
		count++;
		point = objects->getObject( std::to_string(count));
	}
	runOfPoint = NULL;
}

void PlayLayer::initToolLayer()
{
	auto size = Director::getInstance()->getWinSize();
	toolLayer = Layer::create();
	addChild(toolLayer);
    
	auto spritetool = Sprite::createWithSpriteFrameName("toolbg.png");
	spritetool->setAnchorPoint(Point(0.5f, 1));
	spritetool->setPosition (Point(size.width / 2, size.height));
	toolLayer->addChild(spritetool);
    
	//
	money = instance->getMoney();
	moneyLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    moneyLabel->setPosition(Point(spritetool->getContentSize().width / 8, spritetool->getContentSize().height / 2));
	moneyLabel->setAnchorPoint(Point(0, 0.5f));
    auto moneyText = std::to_string(money);
	moneyLabel->setString(moneyText);
    spritetool->addChild(moneyLabel);
    
	//
	playHpBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("playhp.png"));
	playHpBar->setType(ProgressTimer::Type::BAR);
	playHpBar->setMidpoint(Point(0, 0.4f));
	playHpBar->setBarChangeRate(Point(1, 0));
	playHpBar->setPercentage(playHpPercentage);
    playHpBar->setPosition(Point(spritetool->getContentSize().width / 5 *4  , spritetool->getContentSize().height / 2));
    spritetool->addChild(playHpBar);
    
	auto star = Sprite::createWithSpriteFrameName("playstar.png");
    star->setPosition(Point(spritetool->getContentSize().width / 5 *4 , spritetool->getContentSize().height / 2));
	spritetool->addChild(star);
	
	//
	int groupTotal = instance->getGroupNum();
	groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    groupLabel->setPosition(Point(spritetool->getContentSize().width / 8 * 3, spritetool->getContentSize().height / 2 ));
	groupLabel->setAnchorPoint(Point(0.5f , 0.5f));
    auto groupInfoText = std::to_string(groupCounter + 1);
	groupLabel->setString(groupInfoText);
    spritetool->addChild(groupLabel);
    
	groupTotalLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
    groupTotalLabel->setPosition(Point(spritetool->getContentSize().width / 2 , spritetool->getContentSize().height / 2 ));
	groupTotalLabel->setAnchorPoint(Point(0.5f , 0.5f));
    auto groupTotalText = std::to_string(groupTotal);
	groupTotalLabel->setString(groupTotalText);
    spritetool->addChild(groupTotalLabel);
}

GroupEnemy* PlayLayer::currentGroup()
{
	GroupEnemy* groupEnemy;
	if(!instance->groupVector.empty() )
	{
		groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
	}
	else{
		groupEnemy =NULL;
	}
	return groupEnemy;
}

GroupEnemy* PlayLayer::nextGroup()
{
	if(instance->groupVector.empty())
	{
		return NULL;
	}
    
	if (groupCounter < instance->getGroupNum() - 1)
	{
		groupCounter++;
	}
	else{
		isSuccessful = true;
	}
    GroupEnemy* groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
    return groupEnemy;
    
}

void PlayLayer::addEnemy()
{
    GameManager *instance = GameManager::getInstance();

	GroupEnemy* groupEnemy = this->currentGroup();
	if(groupEnemy == NULL)
	{
		return;
	}
	auto restEnemyNum = groupEnemy->getEnemyTotal();
    if( restEnemyNum <= 0){
		groupEnemy->setIsFinishedAddGroup(true);
		return;
	}
    
	restEnemyNum--;
	groupEnemy->setEnemyTotal(restEnemyNum);
    
	EnemyBase* enemy = NULL;
	
	if(groupEnemy->getType1Total() > 0){
		enemy = Thief::createThief(pointsVector, groupEnemy->getType1Hp());
		groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
	}
	else if(groupEnemy->getType2Total() > 0){
		enemy = Pirate::createPirate(pointsVector, groupEnemy->getType2Hp());
		groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
	}
	else if(groupEnemy->getType3Total() > 0){
		enemy = Bandit::createBandit(pointsVector, groupEnemy->getType3Hp());
		groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
	}
    
	this->addChild(enemy, 10);
    instance->enemyVector.pushBack(enemy);
}

void PlayLayer::logic(float dt)
{
	GroupEnemy* groupEnemy = this->currentGroup();
    
	if(groupEnemy == NULL)
	{
		return;
	}
	if(groupEnemy->getIsFinishedAddGroup() ==true  && instance->enemyVector.size() == 0 && groupCounter < instance->getGroupNum())
	{
		groupEnemy = this->nextGroup();
		int groupTotal = instance->getGroupNum();
		auto groupInfoText =std::to_string(groupCounter + 1);
		groupLabel->setString(groupInfoText);
		auto groupTotalText = std::to_string(groupTotal);
		groupTotalLabel->setString(groupTotalText);
	}
	this->addEnemy();
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{
	this->removeChild(chooseTowerpanel);
	chooseTowerpanel = NULL;
    auto location = touch->getLocation();
    
	checkAndAddTowerPanle(location);
	return true;
}

void PlayLayer::addTowerChoosePanel(Point point)
{
    chooseTowerpanel = TowerPanleLayer::create();
    chooseTowerpanel->setPosition(point);
    this->addChild(chooseTowerpanel);
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
		addTowerChoosePanel(towerPos);
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
    if(chooseTowerpanel != NULL  )
	{
		auto type = chooseTowerpanel->getChooseTowerType();
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
			if( money >= 500 )
			{
				tower = MultiDirTower::create();
				money -= 500;
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
        chooseTowerpanel->setChooseTowerType(type);
        this->removeChild(chooseTowerpanel);
        chooseTowerpanel = NULL;
        
		auto moneyText = std::to_string(money);
        moneyLabel->setString(moneyText);
        
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
    auto bulletVector = instance->bulletVector;
    auto enemyVector = instance->enemyVector;
    
	if(bulletVector.empty() || enemyVector.empty() ){
		return;
	}
	Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
    for (int i = 0; i < bulletVector.size(); i++)
	{
		auto bullet = bulletVector.at(i);
        if(bullet->getParent() == NULL )
        {
            return;
        }
		auto  bulletRect = Rect(bullet->getPositionX() +bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
                                bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
                                bullet->getContentSize().width,
                                bullet->getContentSize().height );
        
		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			//auto enemyRect = enemy->sprite->getBoundingBox();
            auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
                                  enemy->sprite->getPositionY()  - enemy->sprite->getContentSize().height / 4,
                                  enemy->sprite->getContentSize().width / 2,
                                  enemy->sprite->getContentSize().height / 2 );
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
                    auto valueMoney = enemy->getVaule();
                    money += valueMoney;
                    auto moneyText = std::to_string(money);
                    moneyLabel->setString(moneyText);
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
	
	for (Sprite* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
        bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}

void PlayLayer::enemyIntoHouse()
{
    auto enemyVector = instance->enemyVector;
    for (int i = 0; i < enemyVector.size(); i++)
    {
        auto enemy = enemyVector.at(i);
        if( enemy->getEnemySuccessful())
        {
            instance->enemyVector.eraseObject(enemy);
            enemy->removeFromParent();
			auto playHp = getPlayHpPercentage() - 10;
            if(playHp > 0){
                setPlayHpPercentage(playHp);
                playHpBar->setPercentage(playHp);
            }
            else{
                instance->clear();
                // 应该跳转到失败界面
                this->removeAllChildren();
                // unscheduleAllSelectors();
                Size winSize = Director::getInstance()->getWinSize();
                auto putOutLabel = Label::createWithBMFont("fonts/boundsTestFont.fnt", "Game Over");
                putOutLabel->setPosition(Point(winSize.width / 2, winSize.height / 2 ));
                putOutLabel->setScale(4);
                this->addChild(putOutLabel);
            }
        }
    }
}

void PlayLayer::update(float dt)
{
    addTower();
    CollisionDetection();
    enemyIntoHouse();
    if(isSuccessful)
	{
		isSuccessful = false;
		auto star = 0;
		auto playHp = this->getPlayHpPercentage();
        
		if( playHp > 0 && playHp <= 30){ star = 1;}
		else if(playHp > 30 && playHp <= 60 ){ star = 2;}
		else if(playHp > 60 && playHp <= 100 ){ star = 3;}
        
        if( star > UserDefault::getInstance()->getIntegerForKey(instance->getCurrLevelFile().c_str()))
		{
			UserDefault::getInstance()->setIntegerForKey(instance->getCurrLevelFile().c_str(), star);
		}
        
		instance->clear();
        // 应该跳转到成功界面
        Size winSize = Director::getInstance()->getWinSize();
        auto putOutLabel = Label::createWithBMFont("fonts/boundsTestFont.fnt", "Congratulations!");
        putOutLabel->setPosition(Point(winSize.width / 2, winSize.height / 2 ));
        putOutLabel->setScale(4);
        this->addChild(putOutLabel);
	}
}


