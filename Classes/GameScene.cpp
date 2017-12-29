#include "GameScene.h"

GameScene::GameScene()
{
}

bool GameScene::init()
{
	do{
		this->preloadResources();
		if (!CCScene::init())
		{
			break;
		}
		backgroundLayer = BackgroundLayer::create();
		CC_BREAK_IF(!backgroundLayer);
		this->addChild(backgroundLayer);
		fishLayer = FishLayer::create();
		CC_BREAK_IF(!fishLayer);
		this->addChild(fishLayer);
		cannonLayer = CannonLayer::create();
		CC_BREAK_IF(!cannonLayer);
		this->addChild(cannonLayer);
		touchLayer = TouchLayer::create();
		CC_BREAK_IF(!touchLayer);
		this->addChild(touchLayer);
		paneLayer = PanelLayer::create();
		CC_BREAK_IF(!paneLayer);
		this->addChild(paneLayer);
		paneLayer->getGoldCounterLayer()->setNumber(FishJoyData::sharedFishingJoyData()->getGold());
		/*menuLayer = MenuLayer::create();
		CC_BREAK_IF(!menuLayer);
		CC_SAFE_RETAIN(menuLayer);*/
		scheduleUpdate();
		return true;
	} while (0);
	return false;
}

GameScene::~GameScene()
{
//	CC_SAFE_RELEASE_NULL(menuLayer);
}

void GameScene::preloadResources()
{
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
/*	spriteFrameCache->addSpriteFramesWithFile("FishActor-Large-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Marlin-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Shark-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Small-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Mid-ipadhd.plist");*/
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_01"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_02"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_03"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_04"));
	spriteFrameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("fish_plist_05"));
	spriteFrameCache->addSpriteFramesWithFile("cannon-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("Item-chaojiwuqi-ipadhd.plist");

	CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("cannon_plist"));
	frameCache->addSpriteFramesWithFile(STATIC_DATA_STRING("bullet_plist"));


	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS",	
		"Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout",	
		"GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};

	for(int i = 0;i < 18;i++)
	{
		CCArray* array = CCArray::createWithCapacity(10);
		for(int j = 0;j < 10;j++)
		{
			CCString* string = CCString::createWithFormat(STATIC_DATA_STRING("fish_frame_format"),str[i],j+1);
			//CCString* string = CCString::createWithFormat("%s_actor_%03d.png",str[i],j+1);
			CCSpriteFrame* spriteFrame = spriteFrameCache->spriteFrameByName(string->getCString());
			CC_BREAK_IF(!spriteFrame);
			array->addObject(spriteFrame);
		}
		if (array->count() == 0){continue;}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(array,0.15f);
		//CCString* animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation_format"), i + 1);
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", i + 1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,animationName->getCString());
	}
}

void GameScene::cannonAimAt(CCPoint target)
{
	cannonLayer->aimAt(target);
}

void GameScene::cannonShootTo(CCPoint target)
{
	int cost = (cannonLayer->getWeapon()->getCannonType() + 1) * 1;
	int currentGold = FishJoyData::sharedFishingJoyData()->getGold();
	if(currentGold >= cost)
	{
		cannonLayer->shootTo(target);
		this->alterGold(-cost);
	}
}

bool GameScene::checkOutCollisionBetweenFishesAndBullet(Bullet* bullet)
{
	Weapon* weapon = cannonLayer->getWeapon();
	CCPoint bulletPosition = bullet->getCollisionPoint();
	CCArray* fishArray = fishLayer->getFishArray();
	CCObject* object = NULL;
	CCARRAY_FOREACH(fishArray,object)
	{
		Fish* fish =(Fish*)object;
		if(fish->isRunning() && fish->getCollisionArea().containsPoint(bulletPosition))
		{
			bullet->end();
			return true;
		}
	}
	return false;
}

void GameScene::checkOutCollision()
{
	CCArray* bullets = cannonLayer->getWeapon()->getBullets();
	CCObject* object = NULL;
	CCARRAY_FOREACH(bullets, object)
	{
		Bullet* bullet = (Bullet*)object;
		if(bullet->isVisible())
		{
			if(checkOutCollisionBetweenFishesAndBullet(bullet))
			{
				checkOutCollisionBetweenFishesAndFishingNet(bullet);
			}
		}
	}
}

void GameScene::update(float delta)
{
	this->checkOutCollision();
}

void GameScene::fishWillBeCaught(Fish* fish)
{
	int weaponType = cannonLayer->getWeapon()->getCannonType();
	int fishType = fish->getType();
	float fishPer = STATIC_DATA_FlOAT(CCString::createWithFormat(STATIC_DATA_STRING("fish_percentage_format"),fishType)->getCString());
	//float fishPer[k_Fish_Type_Count] = { 1, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4 };
	float weaponPer = STATIC_DATA_FlOAT(CCString::createWithFormat(STATIC_DATA_STRING("weapon_percentage_format"),fishType)->getCString());
	//float weaponPer[k_Cannon_Count] = { 0.3, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1 };
	if(CCRANDOM_0_1() < fishPer * weaponPer)
	{
		fish->beCaught();
		int reward = STATIC_DATA_INT(CCString::createWithFormat(STATIC_DATA_STRING("reward_format"),fishType)->getCString());
		alterGold(reward);
	}
}

void GameScene::checkOutCollisionBetweenFishesAndFishingNet(Bullet *bullet)
{
	Weapon* weapon = cannonLayer->getWeapon();
	CCRect rect = weapon->getCollisionArea(bullet);
	CCArray* fishesArray = fishLayer->getFishArray();
	CCObject* object = NULL;
	CCARRAY_FOREACH(fishesArray,object)
	{
		Fish* fish = (Fish*)object;
		if(fish->isRunning() && rect.intersectsRect(fish->getCollisionArea()))
		{
			this->fishWillBeCaught(fish);
		}
	}
}

void GameScene::alterGold(int delta)
{
	FishJoyData::sharedFishingJoyData()->alterGold(delta);
	paneLayer->getGoldCounterLayer()->setNumber(FishJoyData::sharedFishingJoyData()->getGold());
}

void GameScene::scheduleTimeUp()
{
	this->alterGold(STATIC_DATA_INT("recovery_gold"));
}

void GameScene::onEnter()
{
	CCScene::onEnter();
	PersonalAudioEngine::sharedEngine()->playBackgroundMusic(3);
}