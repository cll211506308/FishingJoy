#include "FishLayer.h"

enum{
	k_Direction_Left =0,
	k_Direction_Right,
	k_Direction_Count
};


FishLayer::FishLayer(void)
{
}

bool FishLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	fishes = CCArray::createWithCapacity(FISH_MAX_COUNT);
	CC_SAFE_RETAIN(fishes);
	for(int i = 0; i < FISH_MAX_COUNT; i++)
	{
		int type = CCRANDOM_0_1() * k_Fish_Type_Count - 1;
		Fish* fish = Fish::create((FishType)type);
		fishes->addObject(fish);
	}
	srand((unsigned)time(0));
	this->schedule(schedule_selector(FishLayer::addFish), 3.0f);
	return true;
}

FishLayer::~FishLayer(void)
{
	CC_SAFE_RELEASE(fishes);
}

void FishLayer::addFish(float delta)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int countToAdd = CCRANDOM_0_1()*10 + 1;
	int count = 0;
	CCObject* obj;

	CCARRAY_FOREACH(fishes,obj)
	{
		Fish* fish = (Fish*)obj;
		if(fish->isRunning()){continue;}
		count++;
		this->resetFish(fish);
		if(count == countToAdd){break;}
	}
}

CCArray* FishLayer::getFishArray()
{
	return fishes;
}

void FishLayer::resetFish(Fish* fish)
{
	fish->reset();
	float startX,startY,endX,endY;
	int direction = CCRANDOM_0_1() * k_Direction_Count;
	CCSize winSize =CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize =fish->getSize();
	if(direction == k_Direction_Left)
	{
		startX = winSize.width + fishSize.width * 0.5;
		endX = -fishSize.width * 0.5;
	}
	else
	{
		endX = winSize.width + fishSize.width * 0.5;
		fish -> setRotation(180);
		startX = -fishSize.width * 0.5;
	}
	endY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height * 0.5;
	startY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height * 0.5;
	addChild(fish);
	fish->setPosition(ccp(startX,startY));
	fish->moveTo(ccp(endX,endY));
}