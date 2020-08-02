#pragma once
#ifndef _ECS_H_
#define _ECS_H_
#include <array>
#include <type_traits>

class Entity;
class Component;

using ComponentId = std::size_t;

ComponentId Get_component_id();

template<class _Ty>
ComponentId Get_component_id() {
	static ComponentId id = Get_component_id();
	return id;
}

inline constexpr std::size_t max_components = 32;
using ComponentsArray = std::array<std::unique_ptr<Component>, max_components>;

class Component {
private:
	friend class Entity;
protected:
	Entity* _entity;
public:
	virtual ~Component();

	Entity& entity() const;

	virtual void action() {}
	virtual void update() {}

	template<class _Component, class... Args>
	_Component& add_component(Args&&...args);

	virtual Component* copy() const = 0;
};

class Entity {
protected:
	ComponentsArray _components;
	bool _destroyed = false;
public:
	constexpr Entity() = default;
	Entity(const Entity& other);
	Entity(Entity&& other) noexcept;

	Entity& operator=(const Entity& other);
	Entity& operator=(Entity&& other) noexcept;
public:
	template<class _Component, class... Args>
	_Component& add_component(Args&&...args);

	template<class _Component>
	bool has_component() const;

	template<class _Component>
	_Component& get_component() const;

	bool is_destroyed() const noexcept;
	void destroy() noexcept;

};
#endif

template<class _Component, class ...Args>
inline _Component& Component::add_component(Args&& ...args)
{
	return _entity->add_component<_Component>(std::forward<Args>(args)...);
}

template<class _Component, class ...Args>
inline _Component& Entity::add_component(Args&& ...args)
{
	decltype(auto) component = std::make_unique<_Component>(std::forward<Args>(args)...);
	component->_entity = this;
	_components[Get_component_id<_Component>()] = std::move(component);
	return get_component<_Component>();
}

template<class _Component>
inline bool Entity::has_component() const
{
	return static_cast<bool>(_components[Get_component_id<_Component>()]);
}

template<class _Component>
inline _Component& Entity::get_component() const
{
	return static_cast<_Component&>(*_components[Get_component_id<_Component>()]);
}
