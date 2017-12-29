#include "FishJoyData.h"

static FishJoyData* _sharedFishingJoyData = NULL;

FishJoyData::FishJoyData()
{
}

FishJoyData::~FishJoyData()
{
}

void FishJoyData::purge()
{
	CC_SAFE_RELEASE_NULL(_sharedFishingJoyData);
}

void FishJoyData::flush()
{
	CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
	userDefault->setBoolForKey("isBeginer",isBeginer);
	userDefault->setBoolForKey("music",isMusic);
	userDefault->setBoolForKey("sound",isSound);
	userDefault -> setIntegerForKey("gold",gold);
	userDefault -> flush();
}

void FishJoyData::reset()
{
	this->setGold(100);
	this->setIsBeginer(false);
	this->setIsMusic(true);
	this->setIsSound(true);
}

bool FishJoyData::init()
{
	isBeginer = CCUserDefault::sharedUserDefault()->getBoolForKey("isBeginer",true);
	if(isBeginer)
	{
		this->reset();
		this->flush();
	}
	else
	{
		CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
		this -> setGold(userDefault -> getDoubleForKey("gold"));
		this -> setIsMusic(userDefault -> getBoolForKey("music"));
		this -> setIsSound(userDefault -> getBoolForKey("sound"));
	}
	return true;
}

FishJoyData* FishJoyData::sharedFishingJoyData()
{
	if(NULL == _sharedFishingJoyData )
	{
		_sharedFishingJoyData  = new FishJoyData();
		_sharedFishingJoyData  -> init();
	}
	return _sharedFishingJoyData ;
}

void FishJoyData::destroyFishingJoyData()
{
	CC_SAFE_DELETE(_sharedFishingJoyData );
}

void FishJoyData::alterGold(int delta)
{
	int gold = this->getGold();
	gold += delta;
	this->setGold(gold);
	this->flush();
}