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
	_Container& data() { return _container; }
	const _Container& data() const { return _container; }

	decltype(auto) begin() { return _container.begin(); }
	decltype(auto) end() { return _container.end(); }

	decltype(auto) begin() const { return _container.begin(); }
	decltype(auto) end() const { return _container.end(); }


};
#endif