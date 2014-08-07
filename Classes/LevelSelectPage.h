#ifndef __thiefTD__LevelSelectPage__
#define __thiefTD__LevelSelectPage__
  
#include <iostream>  
#include "cocos2d.h"  
  
USING_NS_CC;  
  
class LevelSelectPage: public Node
{
public:
    
    bool initLevelPage(const std::string& bgName, int level);
    static LevelSelectPage* create(const std::string& bgName, int level);
    void menuStartCallback(Ref* pSender);
};

#endif /* defined(__thiefTD__LevelSelectPage__) */