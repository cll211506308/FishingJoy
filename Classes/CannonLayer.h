#pragma once
#include "cocos2d.h"
#include "Weapon.h"
#include "StaticData.h"
USING_NS_CC;

class CannonLayer:
	public CCLayer{
public:
	CannonLayer();
	virtual ~CannonLayer();
	virtual bool init();
	void switchCannon(cocos2d::CCObject *sender);
	CREATE_FUNC(CannonLayer);
	void aimAt(CCPoint target);
	void shootTo (CCPoint target);
protected:
	CC_SYNTHESIZE_READONLY(Weapon*, weapon, Weapon);
	CCMenuItemImage *addItem,*subItem;
};