#pragma once
#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "../Entity.h"

class Enemy : public Entity {
private:
	Body<MainBodyElement<Enemy>> _main_body;
public:
	virtual bool damage_this(const Projectile& projectile) override;

};
#endif