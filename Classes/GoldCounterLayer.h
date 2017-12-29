#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class GoldCounterLayer:
	public CCNode{
public:
	static GoldCounterLayer* create(int number);
	bool init(int number);
	void setNumber(int number, int ceiling =999999);
protected:
	int Number;
};