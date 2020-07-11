#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_
#include <type_traits>

inline constexpr bool use_reference = true;

template<bool _Reference = false>
class Timer {
protected:
	using int_type = std::conditional_t<_Reference, int&, int>;
	mutable int _time;
	int_type _start_time;
public:
	Timer(int_type start_time) : _start_time(start_time), _time(start_time) {}
	bool tick() const { return --_time; }
	void reset() const { _time = _start_time; }
};

template<bool _Reference = false>
class AutoResetTimer : public Timer<_Reference>
{
public:
	AutoResetTimer(Timer<_Reference>::int_type start_time) : Timer<_Reference>(start_time) {}
	bool tick() const {
		bool result = --Timer<_Reference>::_time;
		if (Timer<_Reference>::_time <= 0) { Timer<_Reference>::_time = Timer<_Reference>::_start_time; }
		return result;
	}
};
#endif