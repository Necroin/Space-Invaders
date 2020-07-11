#pragma once
#ifndef _GROUPVISIBLECOMPONENT_H_
#define _GROUPVISIBLECOMPONENT_H_
#include "../../Base/GroupContainer/GroupContainer.h"


template<class _Container, bool is_pointer = is_pointer_v<std::remove_reference_t<typename GroupContainer<_Container>::value_type>>>
class GroupVisibleComponent : virtual public GroupContainer<_Container>
{
public:
	void hide() const {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) { 
				if (object->has_component<VisibleComponent>()) {
					object->get_component<VisibleComponent>().hide();
				}
			}
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) {
				if (object.has_component<VisibleComponent>()) {
					object.get_component<VisibleComponent>().hide();
				}
			}
		}
	}
	void show() const {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) {
				if (object->has_component<VisibleComponent>()) {
					object->get_component<VisibleComponent>().show();
				}
			}
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) {
				if (object.has_component<VisibleComponent>()) {
					object.get_component<VisibleComponent>().show();
				}
			}
		}
	}
	void set_color(int color) {
		if constexpr (is_pointer) {
			for (auto&& object : GroupContainer<_Container>::_container) {
				if (object->has_component<VisibleComponent>()) {
					object->get_component<VisibleComponent>().set_color(color);
				}
			}
		}
		else {
			for (auto&& object : GroupContainer<_Container>::_container) {
				if (object.has_component<VisibleComponent>()) {
					object.get_component<VisibleComponent>().set_color(color);
				}
			}
		}
	}
};
#endif