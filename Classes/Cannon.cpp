#include "Cannon.h"
#include <cmath>

using namespace std;

Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}

bool Cannon::init(CannonType var/* = k_Cannon_Type_1*/)
{
	do{
		CC_BREAK_IF(!CCNode::init());
		CannonSprites = CCArray::createWithCapacity(k_Cannon_Count);
		CC_SAFE_RETAIN(CannonSprites);
		for(int i = k_Cannon_Type_1;i < k_Cannon_Count;i++)
		{
			CCString *fileName = CCString::createWithFormat(STATIC_DATA_STRING("cannon_frame_format"),i + 1);
			//CCString* fileName = CCString::createWithFormat("actor_cannon1_%d1.png",i+1);
			CCSprite* cannonSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
			CannonSprites->addObject(cannonSprite);
			cannonSprite->setAnchorPoint(ccp(0.5,0.2));
		}
		this->setType(var);
		return true;
	}while(0);
	return false;
}

void Cannon::setType(CannonType var)
{
	if(Type == var)
	{
		return;
	}
	if(var < k_Cannon_Type_1)
	{
		var = (CannonType)(k_Cannon_Count - 1);
	}
	else if(var > k_Cannon_Count - 1)
	{
		var = k_Cannon_Type_1;
	}
	this->removeChildByTag(Type);
	CCSprite* sprite = (CCSprite*) CannonSprites->objectAtIndex(var);
	this->addChild(sprite,0,var);
	Type = var;
}

Cannon* Cannon::create(CannonType var/* = k_Cannon_Type_1*/)
{
	Cannon* cannon = new Cannon();
	if(cannon && cannon->init(var))
	{
		cannon->autorelease();
		return cannon;
	}
	else
	{
		CC_SAFE_DELETE(cannon);
		return NULL;
	}
}

float Cannon::getFireRange()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	double temp = pow(winSize.width * 0.5,2) + pow(winSize.height * 0.5,2);
	double result = sqrt(temp);
	return result/7 * (Type + 1) + 500;
}

CannonType Cannon::getType()
{
	return Type;
}

CCSize Cannon::getSize()
{
	CCSprite* cannonSprite = (CCSprite*) CannonSprites->objectAtIndex(Type);
	return cannonSprite->getContentSize();
}

void Cannon::aimAt(cocos2d::CCPoint target)
{
	CCPoint location = getParent()->convertToWorldSpace(getPosition());
	float angle = ccpAngleSigned(ccpSub(target, location), CCPointMake(0, 1));
	if(abs(angle)>(3.14/2))
	{
		if(angle>0)
		{
			angle = 3.14/2;
		}
		else
		{
			angle = -3.14/2;
		}
	}
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
}