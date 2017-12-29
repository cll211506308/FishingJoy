#pragma once
#include "cocos2d.h"
#include "Cannon.h"
#include "Bullet.h"
#include "FishNet.h"
#include "StaticData.h"
USING_NS_CC;
class Weapon:
	public CCNode{
public:
	virtual ~Weapon();
	static Weapon* create(CannonType var = k_Cannon_Type_1);
	bool init(CannonType var = k_Cannon_Type_1);
	void changeCannon(CannonOperate operate);
	CCSize getCannonSize();
	void aimAt(CCPoint target);
	void shootTo (CCPoint target);
	Bullet* getBulletToShoot();
	CCRect getCollisionArea(Bullet* bullet);
	CannonType getCannonType();
protected:
	CC_SYNTHESIZE_READONLY(Cannon*, cannon, Cannon);
	CC_SYNTHESIZE_READONLY(CCArray*, bullets, Bullets);
	CC_SYNTHESIZE_READONLY(CCArray*, fishNets, FishNets);
	CC_SYNTHESIZE_READONLY(CCArray*, particles, CCParticleSystemQuad);
};