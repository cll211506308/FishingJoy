#include "CannonLayer.h"

CannonLayer::CannonLayer(){
}

CannonLayer::~CannonLayer(){
}

bool CannonLayer::init(){
	do{
		CC_BREAK_IF(!CCLayer::init());
		weapon = Weapon::create((CannonType)0);
		this->addChild(weapon,1);
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		weapon->setPosition(ccp(winSize.width/2 - 18, 0));

		addItem = CCMenuItemImage::create(
		"ui_button_65-ipadhd.png",
		"ui_button_65-ipadhd.png",
		this,menu_selector(CannonLayer::switchCannon));

		subItem = CCMenuItemImage::create(
		"ui_button_63-ipadhd.png",
		"ui_button_63-ipadhd.png",
		this,menu_selector(CannonLayer::switchCannon));

		CCMenu* menu = CCMenu::create(subItem, addItem, NULL);
		menu->alignItemsHorizontallyWithPadding(120);
		this->addChild(menu);
		menu->setPosition(ccp(winSize.width/2-20, addItem->getContentSize().height/2));
		return true;
	}while(0);
	return false;
}

void CannonLayer::switchCannon(cocos2d::CCObject *sender){
	CannonOperate operate = k_Cannon_Operate_Down;
	if((CCMenuItemImage*)sender == addItem)
	{
		operate = k_Cannon_Operate_Up;
	}
	weapon->changeCannon(operate);
}