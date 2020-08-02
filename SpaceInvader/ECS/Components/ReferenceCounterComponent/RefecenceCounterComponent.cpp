#include "RefecenceCounterComponent.h"

ReferenceCounterComponent::ReferenceCounterComponent(std::size_t& count) :
	_count(count)
{
	++_count;
}

ReferenceCounterComponent::~ReferenceCounterComponent()
{
	--_count;
}

Component* ReferenceCounterComponent::copy() const
{
	return new ReferenceCounterComponent(_count);
}
