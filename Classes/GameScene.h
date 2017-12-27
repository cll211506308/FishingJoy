#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "FishLayer.h"
#include "CannonLayer.h"
//#include "MenuLayer.h"
USING_NS_CC;

class GameScene :
	public CCScene
{
public:
	GameScene(void);
	CREATE_FUNC(GameScene)
	virtual bool init();
	virtual ~GameScene();
	void preloadResources();
protected:
	BackgroundLayer* backgroundLayer;
	FishLayer* fishLayer;
	CannonLayer* cannonLayer;
//	MenuLayer* menuLayer;
};

