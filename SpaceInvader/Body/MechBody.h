#pragma once
#ifndef _MECHBODY_H_
#define _MECHBODY_H_
#include "../ECS/ECS.h"
#include "../ECS/Components.h"
#include <list>
#include <memory>

class MechBody : public Entity {
private:
	friend bool is_collide(const MechBody&, const MechBody&);

protected:
	class BodyElement : public Entity {
	public:
		virtual ~BodyElement() {}
		virtual void action() {}
		virtual void update() {}
	};


	class BodyElementsList : 
		public GroupVisibleComponent<std::list<std::unique_ptr<BodyElement>>>,
		public GroupMoveComponent<std::list<std::unique_ptr<BodyElement>>>
	{
	public:
		void action() { for (auto&& body_element : this->_container) { body_element->action(); } }
		void update() { for (auto&& body_element : this->_container) { body_element->update(); } }
		template<class _BodyElement, class... Args>
		_BodyElement& add_element(Args&&... args) {
			_container.emplace_back(std::make_unique<_BodyElement>(std::forward<Args>(args)...));
			return static_cast<_BodyElement&>(*_container.back());
		}
	};
protected:
	BodyElementsList _body;
};
#endif