//
//  PlayLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#include "PlayLayer.h"
#include "Enemy.h"


PlayLayer::PlayLayer()
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
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprite.plist");
    auto spriteSheet = CCSpriteBatchNode::create("Sprite.png");
    addChild(spriteSheet);
    
    map = TMXTiledMap::create("map.tmx");
	objects = map->getObjectGroup("obj");
    this->addChild(map, -1);
	
    instance = GameManager::getInstance();
    
    initPointsVector();
    addEnemy();
    
    return true;
}

void PlayLayer::initPointsVector()
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
		runOfPoint->setPosition(Point(x, y));
		instance->pointsVector.pushBack(runOfPoint);
		count++;
		point = objects->getObject( std::to_string(count));
	}
	runOfPoint = NULL;
}

void PlayLayer::runFllowPoint(Node* node)
{
    EnemyBase *enemy = (EnemyBase *)node;
    auto point = enemy->nextPoint();
    
    enemy->runAction(CCSequence::create(MoveTo::create(enemy->runSpeed, point->getPosition())
                                        , CallFuncN::create(CC_CALLBACK_1(PlayLayer::runFllowPoint, this))
                                        , NULL));
}

void PlayLayer::addEnemy()
{
    EnemyBase* enemy = EnemyFast::createEnemy();
	this->addChild(enemy);
    
    Node* point = enemy->currPoint();
    enemy->setPosition(point->getPosition());
    point = enemy->nextPoint();
    
    enemy->runAction(CCSequence::create(MoveTo::create(enemy->runSpeed, point->getPosition())
                                        , CallFuncN::create(CC_CALLBACK_1(PlayLayer::runFllowPoint, this))
                                        , NULL));
}
