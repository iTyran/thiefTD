//
//  LevelInfoScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-21.
//
//
#include "LevelInfoScene.h"

#include "PlayLayer.h"
#include "LevelScene.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"  
using namespace CocosDenshion; 

#define STAR_NUMBER (3)

LevelInfoScene::LevelInfoScene()
:info(NULL)
,fileName("")
{
}

Scene* LevelInfoScene::createScene()
{
    Scene *scene = Scene::create(); 
    LevelInfoScene *layer = LevelInfoScene::create();
    scene->addChild(layer);
    return scene;
}

bool LevelInfoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    auto instance = GameManager::getInstance();
    instance->clear();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Play.plist");
	fileName =  UserDefault::getInstance()->getStringForKey("nextLevelFile");
	if( fileName ==""){
		fileName = "levelInfo_1_0.plist";
	}

	Size size = Director::getInstance()->getWinSize();
	auto starWidth = Sprite::createWithSpriteFrameName("starbg.png")->getContentSize().width;
	auto startPosX = (size.width - STAR_NUMBER * starWidth) / 2 ;
	for(int i = 1; i <= STAR_NUMBER; i++)
	{
		auto sprite = Sprite::createWithSpriteFrameName("starbg.png");
		sprite->setPosition(Point(startPosX + (i - 1) * starWidth, size.height/ 3 * 2 ));
		sprite->setAnchorPoint(Point(0, 0.5f));
		this->addChild(sprite, 0);
	}

	auto star = UserDefault::getInstance()->getIntegerForKey(fileName.c_str());
	for(int i = 1; i <= star; i++)
	{
		auto sprite = Sprite::createWithSpriteFrameName("star.png");
		sprite->setPosition(Point(startPosX + (i - 1) * starWidth, size.height/ 3 * 2  ));
		sprite->setAnchorPoint(Point(0, 0.5f));
		this->addChild(sprite, 0);
	}
	
	addBackGround();          
	
	return true;
}

void LevelInfoScene::addBackGround()
{
	Size size = Director::getInstance()->getWinSize();
	auto sprite = Sprite::create("playbg.png");
    sprite->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(sprite, -1);

	auto spritePanel = Sprite::create("LevelInfoPanel.png");
    spritePanel->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(spritePanel, -1);

    Sprite *start = CCSprite::createWithSpriteFrameName("btnStart.png");
    MenuItemSprite *startItem = MenuItemSprite::create(start, start, CC_CALLBACK_1(LevelInfoScene::menuStartCallback, this));
    Sprite *back= CCSprite::createWithSpriteFrameName("btnBack.png");
    MenuItemSprite *backItem = MenuItemSprite::create(back, back, CC_CALLBACK_1(LevelInfoScene::menuBackCallback, this));

    auto menu = Menu::create(startItem, backItem, NULL);  
	menu->alignItemsHorizontally();

    menu->setPosition(Point(size.width / 2,size.height / 6));  


    this->addChild(menu); 
}

void LevelInfoScene::menuBackCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, LevelScene::create()));
}

void LevelInfoScene::menuStartCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	info = LoadLevelinfo::createLoadLevelinfo(fileName.c_str());
	info->readLevelInfo();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, PlayLayer::createScene()));
}