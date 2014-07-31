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
#include "AttackTower.h"
#include "MultiDirTower.h"
#include "TowerPanleLayer.h"
#include "GameManager.h"

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
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    
    GroupEnemy* currentGroup();
	GroupEnemy* nextGroup();
	void addGroupEnemy();
	void logic(float dt);
	void initLabelText();
private:
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
	TMXLayer* bgLayer;
    TMXObjectGroup* objects;
    Vector<Node*> pointsVector;
    
	GameManager* instance;
    float offX;
    
	int groupCounter;
	int money;
    
    Label* moneyLabel;
	Label* groupLabel;
	Label* groupTotalLabel;
	Layer* toolLayer;
	void initToolLayer();
	CC_SYNTHESIZE(float, playHpPercentage, PlayHpPercentage);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, playHpBar, PlayHpBar);
	bool isSuccessful;
    
    bool isTouchEnable;
    TowerPanleLayer* chooseTowerpanel;
    void addTowerChoosePanel(Point position);
    Point convertTotileCoord(Point position);
	Point convertToMatrixCoord(Point position);
	void checkAndAddTowerPanle(Point position);
	void CollisionDetection();
    void enemyIntoHouse();
    
	Point towerPos;
    void initPointsVector(float offX);
    void addEnemy();
    void addTower();
    TowerBase **towerMatrix;
};

#endif /* defined(__thiefTD__PlayLayer__) */
