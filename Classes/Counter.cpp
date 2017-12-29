#include "Counter.h"

enum{
    k_Counter_Action = 0
};

Counter::Counter(){
	Digit = 0;
}

Counter* Counter::create(CCArray* presenters,int digit){
	CCAssert(digit>=0 && digit<=10,"金币数字只能为0至9之间的数字.");
	Counter *counter = new Counter();
	if (counter && counter->init(presenters,digit) ){   
		counter->autorelease();
		return counter;
	}else{
		CC_SAFE_DELETE(counter);
		return NULL;
	}
}

bool Counter::init(CCArray* presenters, int digit){
	do{
		CC_BREAK_IF(!CCNode::init());
		Presenters = CCNode::create();
		CCObject* object = NULL;
		int i = 0;
		CCARRAY_FOREACH(presenters,object){
			CCNode *node = (CCNode *)object;
			Presenters->addChild(node,0,i);
			node->setPosition(ccp(0,node->getContentSize().height * i));
			i++;
		}
		this->addChild(Presenters);
		this->setDigit(digit);
		return true;
	}while(0);
	return  false;
}

void Counter::setDigit(int digit){
	if(Digit != digit){
		Digit = digit;
		this->animation(digit);
	}
}

void Counter::animation(int digit){
	CCNode* node = (CCNode *)Presenters->getChildByTag(Digit);
	CCPoint position = node->getPosition();
	Presenters ->stopActionByTag(k_Counter_Action);
	CCMoveTo* moveTo = CCMoveTo::create(0.5f, ccp(0, -position.y));
	moveTo->setTag(k_Counter_Action);
	Presenters->runAction(moveTo);
}

void Counter::visit(){
	glEnable(GL_SCISSOR_TEST);
	CCNode* presenter = Presenters->getChildByTag(Digit);
	CCSize size = presenter->getContentSize();
	CCPoint location = this->getParent()->convertToWorldSpace(this->getPosition());
	glScissor((location.x - size.width * 0.5) * 0.4,
			(location.y - size.height * 0.5) * 0.4,
			size.width * 0.4,
			size.height * 0.4);
	CCNode::visit();
	glDisable(GL_SCISSOR_TEST);

}

int Counter::getDigit()
{
    return Digit;
}