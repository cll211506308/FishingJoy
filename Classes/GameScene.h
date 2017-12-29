#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "FishLayer.h"
#include "CannonLayer.h"
//#include "MenuLayer.h"
#include "TouchLayer.h"
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
	void cannonAimAt(CCPoint target);
	void cannonShootTo(CCPoint target);
	bool checkOutCollisionBetweenFishesAndBullet(Bullet* bullet);
	void checkOutCollision();
	virtual void update(float delta);
	void checkOutCollisionBetweenFishesAndFishingNet(Bullet* bullet);
	void fishWillBeCaught(Fish* fish);
protected:
	BackgroundLayer* backgroundLayer;
	FishLayer* fishLayer;
	CannonLayer* cannonLayer;
	TouchLayer* touchLayer;
//	MenuLayer* menuLayer;
};

