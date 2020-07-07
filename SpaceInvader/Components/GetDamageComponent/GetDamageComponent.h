#pragma once
#ifndef _GETDAMAGECOMPONENT_H_
#define _GETDAMAGECOMPONENT_H_
#include "../../Projectile/Projectile.h"

class GetDamageComponent {
public:
	virtual bool damage_this(const Projectile& projectile) const = 0;
};
#endif