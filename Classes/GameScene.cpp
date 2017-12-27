#include "GameScene.h"

GameScene::GameScene()
{
}

bool GameScene::init()
{
	do
	{
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
		/*menuLayer = MenuLayer::create();
		CC_BREAK_IF(!menuLayer);
		CC_SAFE_RETAIN(menuLayer);*/
		return true;
	} while (0);
	return false;
}

GameScene::~GameScene()
{
//	CC_SAFE_RELEASE_NULL(menuLayer);
}

void GameScene::preloadResources(){
	CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Large-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Marlin-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Shark-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Small-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("FishActor-Mid-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("cannon-ipadhd.plist");
	spriteFrameCache->addSpriteFramesWithFile("Item-chaojiwuqi-ipadhd.plist");

	char str[][50] = {"SmallFish","Croaker","AngelFish","Amphiprion","PufferS",	
		"Bream","Porgy","Chelonian","Lantern","Ray","Shark","GoldenTrout",	
		"GShark","GMarlinsFish","GrouperFish","JadePerch","MarlinsFish","PufferB"};

	for(int i = 0;i < 18;i++){
		CCArray* array = CCArray::createWithCapacity(10);
		for(int j = 0;j < 10;j++){
			CCString* string = CCString::createWithFormat("%s_actor_%03d.png",str[i],j+1);
			CCSpriteFrame* spriteFrame = spriteFrameCache->spriteFrameByName(string->getCString());
			CC_BREAK_IF(!spriteFrame);
			array->addObject(spriteFrame);
		}
		if (array->count() == 0)
		{
			continue;
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(array,0.15f);
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", i + 1);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,animationName->getCString());
	}
}