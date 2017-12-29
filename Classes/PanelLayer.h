#pragma once
#include "cocos2d.h"
#include "GoldCounterLayer.h"
#include "StaticData.h"
#include "ScheduleCounterDelegate.h"
#include "ScheduleCountDown.h"
USING_NS_CC;

class PanelLayer:
	public CCLayer,public ScheduleCounterDelegate
{
public:
	CREATE_FUNC(PanelLayer);
	CC_SYNTHESIZE_READONLY(GoldCounterLayer*, goldCounterLayer, GoldCounterLayer);
	virtual bool init();
	void setScheduleNumber(int number);
	void scheduleTimeUp();
protected:
	CCLabelAtlas* ScheduleLabel;
};