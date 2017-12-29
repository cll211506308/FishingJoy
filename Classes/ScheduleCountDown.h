#pragma once
#include "cocos2d.h"
#include "ScheduleCounterDelegate.h"
#include "StaticData.h"
USING_NS_CC;

class ScheduleCountDown:
	public CCNode
{
public:
	CC_SYNTHESIZE(ScheduleCounterDelegate *,Target,Target);
	CC_SYNTHESIZE(int,CurrentTime,CurrentTime);
	CC_SYNTHESIZE(int,MaxTime,MaxTime);
	CC_SYNTHESIZE(bool,Loop,Loop);
	static ScheduleCountDown* create(ScheduleCounterDelegate* target,int perimeter,bool loop);
	bool init(ScheduleCounterDelegate* target,int perimeter,bool loop);
	void schedulePerSecond(float delta);
};