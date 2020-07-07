#pragma once
#ifndef _ENTITY_H_
#define _ENTITY_H_
#include "../Components/VisibleComponent/GroupVisibleComponent.h"
#include "../Components/HealthComponent/HealthComponent.h"
#include "../Components/DamageComponent/DamageComponent.h"
#include "../Components/MoveComponent/GroupMoveComponent.h"
#include "../Components/DestroyedComponent/DestroyedComponent.h"
#include "../Components/GetDamageComponent/GetDamageComponent.h"
#include "../Map/Map.h"
#include "../Projectile/Projectile.h"
#include <vector>
#include <list>
#include <memory>

class Entity : public HealthComponent, public Coordinates, public DestroyedComponent
{
protected:
	class BodyElement : public MoveComponent, public VisibleComponent {
	public:
		BodyElement(int x, int y, char symbol, int color = Color::White) :
			MoveComponent(x, y), 
			VisibleComponent(x, y, symbol, color),
			Coordinates(x, y)
		{}
		virtual ~BodyElement() {}
		virtual void action() {}
		virtual void update() {}
	};


	template<class _Parent>
	class MainBodyElement : public BodyElement, public GetDamageComponent
	{
	protected:
		_Parent& _parent;
	public:
		MainBodyElement(_Parent& parent, int x, int y, char symbol, int color = Color::White) :
			BodyElement(x, y, symbol, color),
			Coordinates(x, y),
			_parent(parent)
		{}
		virtual bool damage_this(const Projectile& projectile) const override {
			return projectile.damage()(_parent._health_points, _parent._shield);
		}
	};

	template<class _BaseElement>
	class Body : 
		public GroupMoveComponent<std::vector<std::unique_ptr<_BaseElement>>>,
		public GroupVisibleComponent<std::vector<std::unique_ptr<_BaseElement>>>
	{
	public:
		void action() { for (auto&& body_element : this->_container) { body_element->action(); } }
		void update() { for (auto&& body_element : this->_container) { body_element->update(); } }
		template<class _BodyElement, class... Args>
		void add_element(Args&&... args) {
			this->_container.push_back(std::make_unique<_BodyElement>(std::forward<Args>(args)...));
		}
	};

	Map& _map;
public:
	Entity(Map& map, int HP, int x , int y);
};
#endif