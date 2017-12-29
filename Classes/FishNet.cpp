#include "FishNet.h"
#include "PersonalAudioEngine.h"

FishNet::FishNet()
{
}

FishNet::~FishNet()
{
}

bool FishNet::init()
{
	do{
		CC_BREAK_IF(!CCNode::init());
		//CCString *fileName = CCString::createWithFormat(STATIC_DATA_STRING("net_frame_format"),1);
		CCString *fileName = CCString::createWithFormat("weapon_net_%03d.png",1);
		FishNetSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
		FishNetSprite->setAnchorPoint(ccp(0.5, 0.5));
		this->addChild(FishNetSprite);
		return true;
	}while(0);
	return false;
}

void FishNet::showAt(CCPoint pos,int type /*= 0*/)
{
	setPosition(pos);
	setVisible(true);
	PersonalAudioEngine::sharedEngine()->playEffect(kEffectFishNet);
	//CCString* fishNetFrameName = CCString::createWithFormat(STATIC_DATA_STRING("net_frame_format"), type + 1);
	CCString* fishNetFrameName = CCString::createWithFormat("weapon_net_%03d.png", type + 1);
	this->FishNetSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fishNetFrameName->getCString()));
	stopAllActions();
	CCSequence* sequence = CCSequence::create(CCDelayTime::create(1.0), CCHide::create(),NULL);
	runAction(sequence);
	CCParticleSystemQuad* particle = (CCParticleSystemQuad*)getUserObject();
	particle->setPosition(pos);
	particle->resetSystem();
}

CCRect FishNet::getCollisionArea()
{
	CCSize size = FishNetSprite->getContentSize();
	CCPoint position = getParent()->convertToWorldSpace(getPosition());
	return CCRect(position.x - size.width / 2, position.y - size.height/2, size.width, size.height);
}