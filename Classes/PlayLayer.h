//
//  PlayLayer.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#ifndef __thiefTD__PlayLayer__
#define __thiefTD__PlayLayer__

#include <iostream>
#include "cocos2d.h"
#include "Thief.h"
#include "ArrowTower.h"
#include "TowerPanleLayer.h"


USING_NS_CC;
class PlayLayer : public Layer
{
public:
    PlayLayer();
    ~PlayLayer();
    
    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(PlayLayer);
    
    virtual void update(float dt) override;
    bool onTouchBegan(Touch *touch, Event *event);
    
private:
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
    TMXObjectGroup* objects;
    Vector<Node*> pointsVector; //enemy移动路径的点集
    
    bool isTouchEnable;
    TowerPanleLayer* chooseTowerpanle;
    void addTowerChoosePanle(Point position);
    
	Point towerPos;
    void initPointsVector(float offX);
    void addEnemy();
    void addTower();
    
};

#endif /* defined(__thiefTD__PlayLayer__) */
