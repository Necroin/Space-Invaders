#include "ECS.h"

ComponentId Get_component_id() {
	static ComponentId id = 0;
	return id++;
}

Entity& Component::entity() { return *_entity; }

Entity::Entity(const Entity& other) 
{
	for (size_t i = 0; i < _components.size(); ++i) {
		if (static_cast<bool>(other._components[i])) {
			_components[i] = std::move(std::unique_ptr<Component>{ other._components[i]->copy() });
			_components[i]->_entity = this;
		}
	}
}

Entity::Entity(Entity&& other) noexcept 
{
	for (size_t i = 0; i < _components.size(); ++i) {
		if (static_cast<bool>(other._components[i])) {
			_components[i] = std::move(other._components[i]);
			_components[i]->_entity = this;
		}
	}
}

Entity& Entity::operator=(const Entity& other)
{
	if (this == &other) {
		return *this;
	}

	for (size_t i = 0; i < _components.size(); ++i) {
		if (static_cast<bool>(other._components[i])) {
			_components[i] = std::move(std::unique_ptr<Component>{ other._components[i]->copy() });
			_components[i]->_entity = this;
		}
	}

	_destroyed = other._destroyed;

	return *this;
}

Entity& Entity::operator=(Entity&& other) noexcept
{
	if (this == &other) {
		return *this;
	}

	for (size_t i = 0; i < _components.size(); ++i) {
		if (static_cast<bool>(other._components[i])) {
			_components[i] = std::move(other._components[i]);
			_components[i]->_entity = this;
		}
	}

	_destroyed = other._destroyed;

	return *this;
}

bool Entity::is_destroyed() const noexcept
{
	return _destroyed;
}

void Entity::destroy() noexcept
{
	_destroyed = true;
}
