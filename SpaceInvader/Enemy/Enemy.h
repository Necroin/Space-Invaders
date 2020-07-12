#pragma once
#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "../Body/MechBody.h"

class Enemy : public MechBody {
public:
	virtual void action() = 0;
	virtual void update() = 0;
};
#endif