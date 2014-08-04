//
//  FailedScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-12.
//
//

#include "FailedScene.h"
#include "LevelScene.h"
#include "GameManager.h"

USING_NS_CC;
#include "SimpleAudioEngine.h" 
using namespace CocosDenshion; 

bool FailedScene::init()  
{  
	if ( !Scene::init() )
    {
        return false;
    }
    Size size = CCDirector::getInstance()->getWinSize();  
    
    GameManager* instance = GameManager::getInstance();
    instance->clear();
    
    Sprite* spriteBg =Sprite::create("playbg.png");
    spriteBg->setPosition(Point( size.width / 2,size.height / 2));  
    addChild(spriteBg, -1);

	auto sprite = Sprite::createWithSpriteFrameName("failedPanel.png");
    sprite->setPosition(Point(-size.width/2 , size.height / 2 ));
    this->addChild(sprite, -1);
    
    Sprite *backItem = CCSprite::createWithSpriteFrameName("btnBack.png");
    MenuItemSprite *back = MenuItemSprite::create(backItem, backItem, CC_CALLBACK_1(FailedScene::menuBackCallback, this));
    
    back->setPosition(Point(sprite->getContentSize().width / 2, sprite->getContentSize().height / 6));

    auto menu = Menu::create(back, NULL);
    menu->setPosition(Point::ZERO);  
    sprite->addChild(menu);  

    sprite->runAction(CCSequence::create(DelayTime::create( 0.5f ),
										EaseElasticOut::create(MoveBy::create(0.8f, Point( size.width, 0)), 0.5f),
										NULL) 
					);

	ParticleSystem* m_emitter1 = ParticleSystemQuad::create("changjing.plist");
	m_emitter1->retain();
	ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(m_emitter1->getTexture());
	batch->addChild(m_emitter1);
	m_emitter1->setPosition(Point(size.width/2, 0));
	addChild(batch, 10);
	m_emitter1->release();

    return true;  
}  
  
void FailedScene::menuBackCallback(Ref* pSender)
{  
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, LevelScene::create()));
}