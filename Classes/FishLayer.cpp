#include "FishLayer.h"

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
	for(int i = 0; i < FISH_MAX_COUNT; i++){
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

	CCARRAY_FOREACH(fishes,obj){
		Fish* fish = (Fish*)obj;
		if(fish->isRunning()){
			continue;
		}
		this->addChild(fish);
		fish->setPosition(ccp(CCRANDOM_0_1() * winSize.width, CCRANDOM_0_1() * winSize.height));
		count++;
		if(count == countToAdd){
			break;
		}
	}
}