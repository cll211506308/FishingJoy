#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class Bullet:
	public CCNode{
public:
	Bullet();
	virtual ~Bullet();
	bool init();
	float getSpeed(int type);
	CREATE_FUNC(Bullet);
protected:
	CCSprite*  bulletSprite;
};