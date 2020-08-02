#pragma once
#ifndef _GROUPCONTAINER_H_
#define _GROUPCONTAINER_H_
#include <memory>
#include <type_traits>

template<class>
inline constexpr bool is_pointer_v = false;

template<class _Type>
inline constexpr bool is_pointer_v<_Type*> = true;

template<class _Type>
inline constexpr bool is_pointer_v<std::unique_ptr<_Type>> = true;

template<class _Type>
inline constexpr bool is_pointer_v<std::shared_ptr<_Type>> = true;

template<class _Container>
class GroupContainer {
protected:
	_Container _container;
public:
	using value_type = decltype(*_Container().begin());
public:
	      _Container& data()       noexcept { return _container; }
	const _Container& data() const noexcept { return _container; }

	decltype(auto) begin() noexcept { return _container.begin(); }
	decltype(auto) end  () noexcept { return _container.end();   }

	decltype(auto) begin() const noexcept { return _container.begin(); }
	decltype(auto) end  () const noexcept { return _container.end();   }
};
#endif