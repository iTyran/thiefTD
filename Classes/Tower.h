//
//  Tower.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-22.
//
//

#ifndef __thiefTD__Tower__
#define __thiefTD__Tower__

#include <iostream>
#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

class TowerBase: public Sprite
{
public:
    TowerBase();
    virtual bool init() override;
    CREATE_FUNC(TowerBase);
    
    Vector<EnemyBase*> getEnemysWithinScope();
    void checkNearestEnemy();
    void setEnemyVector(Vector<EnemyBase*> enemys);
    
    CC_SYNTHESIZE(int, scope, Scope);
    
protected:
    EnemyBase* nearestEnemy;
    Vector<EnemyBase*> enemyVector; //从PlayLayer得到
private:
    
    Vector<EnemyBase*> scopeEnemys;
    
};


class ArrowTower: public TowerBase
{
public:
    
    virtual bool init() override;
    virtual void update(float dt) override;
    static ArrowTower* createArrowTower(Vector<EnemyBase*> enemys);
    
    void rotateAndShoot(float dt);
    void shoot();
    void removeBullet(Node* pSender);
    
    Sprite* createBullet();
    
private:
    Vector<Sprite*> bulletVector;
    Sprite* currBullet;
    Sprite* arrow;
    
};

#endif /* defined(__thiefTD__Tower__) */
