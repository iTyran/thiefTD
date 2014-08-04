//
//  SuccessfulScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "SuccessfulScene.h"
#include "LevelInfoScene.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"  
#include "GameManager.h"

USING_NS_CC;
using namespace CocosDenshion; 

bool SuccessfulScene::init()  
{  
	if ( !Scene::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    GameManager* instance = GameManager::getInstance();
    instance->clear();
	auto sprite = Sprite::create("successfulBg.png");
    sprite->setPosition(Point(size.width/2 , size.height/2 ));
    this->addChild(sprite, -1);

    // back
	Sprite *backItem1 = CCSprite::createWithSpriteFrameName("btnNext.png");
	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("btnBack.png");
	MenuItemSprite *pPauseItem1 = MenuItemSprite::create(backItem1, backItem1, CC_CALLBACK_1(SuccessfulScene::menuNextCallback, this));
    MenuItemSprite *pPauseItem2 = MenuItemSprite::create(backItem2, backItem2, CC_CALLBACK_1(SuccessfulScene::menuCloseCallback, this));

    auto menu = Menu::create(pPauseItem1, pPauseItem2, NULL);
	menu->alignItemsHorizontally();

    menu->setPosition(Point(size.width / 2,size.height / 6));  
    this->addChild(menu);  

    return true;  
}  

void SuccessfulScene::menuNextCallback(Ref* pSender)
{  
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.5, LevelInfoScene::createScene()));  
}

void SuccessfulScene::menuCloseCallback(Ref* pSender)
{  
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFadeBL::create(0.1f, LevelScene::create()));
}