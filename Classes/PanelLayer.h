#pragma once
#include "cocos2d.h"
#include "GoldCounterLayer.h"
#include "StaticData.h"
USING_NS_CC;

class PanelLayer:
	public CCLayer{
public:
	CREATE_FUNC(PanelLayer);
	CC_SYNTHESIZE_READONLY(GoldCounterLayer*, goldCounterLayer, GoldCounterLayer);
	virtual bool init();
protected:
	CCLabelAtlas* ScheduleLabel;
};