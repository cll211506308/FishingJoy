#include "FishNet.h"

FishNet::FishNet()
{
}

FishNet::~FishNet()
{
}

bool FishNet::init()
{
	do
	{
		CC_BREAK_IF(!CCNode::init());
		CCString *fileName = CCString::createWithFormat("weapon_net_%03d.png",1);
		fishNetSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
		fishNetSprite->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(fishNetSprite);
		return true;
	}while(0);
	return false;
}

void FishNet::showAt(CCPoint pos,int type /*= 0*/)
{
	setPosition(pos);
	setVisible(true);
	CCString* fishNetFrameName = CCString::createWithFormat("weapon_net_%03d.png", type + 1);
	this->fishNetSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fishNetFrameName->getCString()));
	stopAllActions();
	CCSequence* sequence = CCSequence::create(CCDelayTime::create(1.0), CCHide::create(),NULL);
	runAction(sequence);
	CCParticleSystemQuad* particle = (CCParticleSystemQuad*)getUserObject();
	particle->setPosition(pos);
	particle->resetSystem();
}

CCRect FishNet::getCollisionArea()
{
	CCSize size = fishNetSprite->getContentSize();
	CCPoint pos = getParent()->convertToWorldSpace(getPosition());
	return CCRect(pos.x - size.width / 2, pos.y - size.height/2, size.width, size.height);
}