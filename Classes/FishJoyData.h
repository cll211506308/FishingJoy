#pragma once
#include "cocos2d.h"
#include "StaticData.h"
USING_NS_CC;

class FishJoyData:
	public CCObject
{
public:
	FishJoyData();
	~FishJoyData();
	CC_SYNTHESIZE(bool, isBeginer, IsBeginer);
	CC_SYNTHESIZE(int, gold, Gold);
	CC_SYNTHESIZE(bool, isMusic, IsMusic)
	CC_SYNTHESIZE(bool, isSound, IsSound)
	void purge();
	void flush();
	bool init();
	void reset();
	static FishJoyData* sharedFishingJoyData();
	static void destroyFishingJoyData();
	void alterGold(int delta);
};