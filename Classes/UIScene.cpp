//
//  UIScene.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-5-7.
//
//

#include "UIScene.h"
#include "LevelScene.h"

#include "SimpleAudioEngine.h"  
using namespace CocosDenshion; 

USING_NS_CC;

Scene* UIScene::createScene()
{
    auto scene = Scene::create();
    auto layer = UIScene::create();

    scene->addChild(layer);
    return scene;
}

bool UIScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    Size size = CCDirector::getInstance()->getWinSize();  

    Sprite* sprite =Sprite::create("playbg.png");  
    sprite->setPosition(Point(size.width / 2,size.height / 2));  
    addChild(sprite, -1);

	auto titleSprite = Sprite::createWithSpriteFrameName("title.png");
	titleSprite->setPosition(Point(size.width / 3,size.height / 3 * 2));
	this->addChild(titleSprite);
	auto move = MoveBy::create(1.0f, Point(0, 10));
	titleSprite->runAction(RepeatForever::create(Sequence::create( move, move->reverse(), NULL)));
    
    auto startItem = MenuItemImage::create(
                                           "start_1.png",  
                                           "start_2.png",  
                                           CC_CALLBACK_1(UIScene::menuStartCallback, this));
    startItem->setPosition(Point((size.width -  startItem->getContentSize().width)/ 2, size.height / 6));
	startItem->setAnchorPoint(Point(0, 0));
    auto menu = Menu::create(startItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1); 
	
	auto starSprite = Sprite::createWithSpriteFrameName("star.png");
	starSprite->setScale(0.7f);
	this->addChild(starSprite, 11);

	auto _emitter = ParticleSystemQuad::create("button.plist");
    _emitter->retain();
    ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(_emitter->getTexture());
    batch->addChild(_emitter);
	starSprite->setPosition(Point(startItem->getPosition().x, startItem->getPosition().y));
	
	_emitter->setPosition(Point(startItem->getPosition().x, startItem->getPosition().y ));
	auto path = MyPathFun( 1, startItem->getContentSize().height, startItem->getContentSize().width /*+ starSprite->getContentSize().width*/);
	starSprite->runAction(path);
	_emitter->runAction(path->clone());
    addChild(batch, 10);
    _emitter->release();

    return true;
}

RepeatForever* UIScene::MyPathFun(float controlX, float controlY, float w)
{
	ccBezierConfig bezier1;
	bezier1.controlPoint_1 = Point(-controlX, 0);
	bezier1.controlPoint_2 = Point(-controlX, controlY);
	bezier1.endPosition = Point(0, controlY);
	auto bezierBy1 = BezierBy::create(0.6f, bezier1);

	auto move1 = MoveBy::create(0.7f, Point(w, 0));

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = Point(controlX, 0);
	bezier2.controlPoint_2 = Point(controlX, -controlY);
	bezier2.endPosition = Point(0, -controlY);
	auto bezierBy2 = BezierBy::create(0.6f, bezier2);
	auto move2 = MoveBy::create(0.7f, Point(-w, 0));
	auto path = RepeatForever::create(Sequence::create(bezierBy1, move1, bezierBy2, move2, NULL));
	return path;
}

void UIScene::menuStartCallback(Ref* pSender)
{
	SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
    Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelScene::create()));
}

void UIScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}