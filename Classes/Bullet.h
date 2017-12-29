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
	void end();
	void flyTo(CCPoint targetInWordSpace, int type =0);
	CCPoint getCollisionPoint();
protected:
	CCSprite*  bulletSprite;
};