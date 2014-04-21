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
:spriteSheet(NULL)
,map(NULL)
,objects(NULL)
,pointsVector(NULL)
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
    EnemyBase* enemy = Thief::createThief(pointsVector);
	this->addChild(enemy);
    
}

