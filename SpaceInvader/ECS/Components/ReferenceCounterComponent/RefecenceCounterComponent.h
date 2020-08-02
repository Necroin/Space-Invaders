#pragma once
#ifndef _REFERENCECOUNTERCOMPONENT_H_
#define _REFERENCECOUNTERCOMPONENT_H_
#include "../../ECS.h"

class ReferenceCounterComponent :
	public Component
{
private:
	std::size_t& _count;
public:
	ReferenceCounterComponent(std::size_t& count);
	~ReferenceCounterComponent();
	virtual Component* copy() const override;
};
#endif