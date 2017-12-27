#include "Fish.h"

Fish::Fish(){
}

Fish::~Fish(){
}

bool Fish::init(FishType var/* = k_Fish_Type_SmallFish*/){
	do{
		CC_BREAK_IF(!CCNode::init());
		if (var < k_Fish_Type_SmallFish || var >= k_Fish_Type_Count){
			var = k_Fish_Type_SmallFish;
		}
		type = var;
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", type + 1);
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
		CC_BREAK_IF(!animation);
		CCAnimate* animate = CCAnimate::create(animation);
		fishSprite = CCSprite::create();
		this->addChild(fishSprite);
		fishSprite->runAction(CCRepeatForever::create(animate));
		return true;
	}while(0);
	return false;
}

Fish* Fish::create(FishType var/* = k_Fish_Type_SmallFish*/){
	Fish* fish = new Fish;
	if(fish && fish->init(var)){
		fish->autorelease();
		return fish;
	}
	else{
		CC_SAFE_DELETE(fish);
		return NULL;
	}
}

int Fish::getScore(){
	return 100;
}

int Fish::getSpeed(){
	return 200;
}