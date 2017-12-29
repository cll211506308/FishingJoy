#include "ScheduleCountDown.h"

ScheduleCountDown* ScheduleCountDown::create(ScheduleCounterDelegate* target,int perimeter,bool loop)
{
	ScheduleCountDown* counter = new ScheduleCountDown();
	if(counter && counter->init(target,perimeter,loop))
	{
		counter->autorelease();
		return counter;
	}
	else
	{
		CC_SAFE_DELETE(counter);
		return NULL;
	}
}

bool ScheduleCountDown::init(ScheduleCounterDelegate* target,int perimeter,bool loop)
{
	do{
		CC_BREAK_IF(!CCNode::init());
		Target = target;
		MaxTime = perimeter;
		CurrentTime = perimeter;
		Loop = loop;
		schedule(schedule_selector(ScheduleCountDown::schedulePerSecond),1.0f);
		return true;
	}while(0);
	return false;
}

void ScheduleCountDown::schedulePerSecond(float delta)
{
	CurrentTime--;
	if(CurrentTime <0)
	{
		if(Loop==true)
		{
			CurrentTime =MaxTime;
		}
		else
		{
			this->unschedule(schedule_selector(ScheduleCountDown::schedulePerSecond));
		}
		Target->scheduleTimeUp();
	}
	else
	{
		Target->setScheduleNumber(CurrentTime);
	}
}