#include "PanelLayer.h"
#include "GameScene.h"

bool PanelLayer::init()
{
	do{
		CC_BREAK_IF(!CCLayer::init());
		goldCounterLayer = GoldCounterLayer::create(0);
		this->addChild(goldCounterLayer);
		goldCounterLayer->setPosition(ccp(600, 17));
		ScheduleCountDown* countDown = ScheduleCountDown::create(this,20,true);
		this->addChild(countDown,0, 99);
		ScheduleLabel=CCLabelAtlas::create(CCString::createWithFormat("%d",20)->getCString(),"baoshiyu_shuzi_02-ipadhd.png",50,54,'0');
		addChild(ScheduleLabel);
		ScheduleLabel->setPosition(ccp(100,1200));
		return true;
	}while(0);
	return false;
}

void PanelLayer::setScheduleNumber(int number)
{
	ScheduleLabel->setString(CCString::createWithFormat("%d",number)->getCString());
}

void PanelLayer::scheduleTimeUp()
{
	((GameScene *)getParent())->alterGold(200);
	ScheduleCountDown *countDown =(ScheduleCountDown *)getChildByTag(99);
	if(countDown->getLoop()==false)
	{
		ScheduleLabel->setVisible(false);
	}
}