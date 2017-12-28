#include "Weapon.h"

#define BULLET_COUNTS 10

Weapon::~Weapon(void)
{
	CC_SAFE_RELEASE(bullets);
	CC_SAFE_RELEASE(fishNets);
}

Weapon* Weapon::create(CannonType var/* = k_Cannon_Type_1*/){
	Weapon* weapon = new Weapon();
	if(weapon && weapon->init(var)){
		weapon->autorelease();
		return weapon;
	}else{
		CC_SAFE_DELETE(weapon);
		return NULL;
	}
}

bool Weapon::init(CannonType var/* = k_Cannon_Type_1*/){
	do{
		CC_BREAK_IF(!CCNode::init());
		cannon = Cannon::create(var);
		CC_BREAK_IF(!cannon);
		addChild(cannon, 1);

		bullets = CCArray::createWithCapacity(BULLET_COUNTS);
		CC_BREAK_IF(!bullets);
		CC_SAFE_RETAIN(bullets);

		fishNets=CCArray::createWithCapacity(BULLET_COUNTS);
		CC_BREAK_IF(!fishNets);
		CC_SAFE_RETAIN(fishNets);

		for(int i = 0; i < BULLET_COUNTS; i++)
		{
			Bullet* bullet = Bullet::create();
			bullets->addObject(bullet);
			addChild(bullet);
			bullet->setVisible(false);
			
			FishNet* fishNet = FishNet::create();
			fishNets->addObject(fishNet);
			addChild(fishNet);
			fishNet->setVisible(false);
			bullet->setUserObject(fishNet);
		}
		return true;
	}while(0);
	return false;
}

void Weapon::changeCannon(CannonOperate operate)
{
	int type = (int) cannon->getType();
	type += operate;
	cannon->setType((CannonType)type);
}

CCSize Weapon::getCannonSize(){
	return cannon->getSize();
}

void Weapon::aimAt(CCPoint target){
	cannon->aimAt(target);
}
void Weapon:: shootTo (CCPoint target){
	/*bullet->flyTo(target);*/
}