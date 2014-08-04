#ifndef __thiefTD__LevelSelectPage1__
#define __thiefTD__LevelSelectPage1__
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class LevelSelectPage1: public Node
{  
public:
      
    virtual bool init();
    CREATE_FUNC(LevelSelectPage1);
    void menuStartCallback(Ref* pSender);
};

class LevelSelectPage2: public Node
{
public:
    
    virtual bool init();
    CREATE_FUNC(LevelSelectPage2);
    void menuStartCallback(Ref* pSender);
};

class LevelSelectPage3: public Node
{
public:
    
    virtual bool init();
    CREATE_FUNC(LevelSelectPage3);
    void menuStartCallback(Ref* pSender);
};
  
#endif /* defined(__thiefTD__LevelSelectPage1__) */