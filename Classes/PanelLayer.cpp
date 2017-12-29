#include "PanelLayer.h"
#include "GameScene.h"

bool PanelLayer::init(){
	do{
		CC_BREAK_IF(!CCLayer::init());
		goldCounterLayer = GoldCounterLayer::create(0);
		this->addChild(goldCounterLayer);
		goldCounterLayer->setPosition(ccp(600, 17));

		
		ScheduleLabel=CCLabelAtlas::create(CCString::createWithFormat("%d",10)->getCString(),"baoshiyu_shuzi_02-ipadhd.png",50,54,'0');
		addChild(ScheduleLabel);
		ScheduleLabel->setPosition(ccp(100,1200));
		return true;
	}while(0);
	return false;
}