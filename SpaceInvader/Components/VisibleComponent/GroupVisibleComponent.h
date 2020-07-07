#pragma once
#ifndef _GROUPVISIBLECOMPONENT_H_
#define _GROUPVISIBLECOMPONENT_H_
#include "../Base/GroupContainer/GroupContainer.h"
#include "VisibleComponent.h"

template<class _Container, bool is_pointer = is_pointer_v<std::remove_reference_t<typename GroupContainer<_Container>::value_type>>>
class GroupVisibleComponent : virtual public GroupContainer<_Container>
{
public:
	void hide() {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { object->hide(); }
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) { object.hide(); } 
		}
	}
	void show() {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { object->show(); }
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) { object.show(); }
		}
	}
	void set_color(int color) {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { object->set_color(color); }
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) { object.set_color(color); }
		}
	}
};
#endif