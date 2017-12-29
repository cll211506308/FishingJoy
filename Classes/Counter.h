#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class Counter:
	public CCNode{
public:
	Counter();
	static Counter* create(CCArray* presenters,int digit = 0);
	bool init(CCArray* presenters, int digit);
	CC_PROPERTY(int, Digit, Digit);
	void animation(int digit);	
protected:
	CCNode* Presenters;
	virtual void visit();
};