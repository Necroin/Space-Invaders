#pragma once
#ifndef _GROUPMOVECOMPONENT_H_
#define _GROUPMOVECOMPONENT_H_
#include "../Base/GroupContainer/GroupContainer.h"
#include "MoveComponent.h"

template<class _Container, bool is_pointer = is_pointer_v<std::remove_reference_t<typename GroupContainer<_Container>::value_type>>>
class GroupMoveComponent : virtual public GroupContainer<_Container>
{
public:
	void move_left() {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { object->move_left(); }
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) { object.move_left(); }
		}
	}
	void move_right() {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { object->move_right(); }
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) { object.move_right(); }
		}
	}
	void move_up() {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { object->move_up(); }
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) { object.move_up(); }
		}
	}
	void move_down() {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { object->move_down(); }
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) { object.move_down(); }
		}
	}
};
#endif