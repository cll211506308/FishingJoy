#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class FishNet:
	public CCNode
{
public:
	FishNet();
	virtual ~FishNet();
	bool init();
	CREATE_FUNC(FishNet);
	void showAt(CCPoint pos,int type = 0);
	CCRect getCollisionArea();
protected:
	CCSprite*  FishNetSprite;
};