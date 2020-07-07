#pragma once
#ifndef _TIMER_H_
#define _TIMER_H_

class Timer {
protected:
	mutable int _time;
	int _start_time;
public:
	Timer(int start_time) : _start_time(start_time), _time(start_time) {}
	bool tick() const { return --_time; }
	void reset() const { _time = _start_time; }
};


class AutoResetTimer : public Timer
{
public:
	AutoResetTimer(int start_time) : Timer(start_time) {}
	bool tick() const {
		bool result = --Timer::_time;
		if (Timer::_time <= 0) { Timer::_time = Timer::_start_time; }
		return result;
	}
};

class AutoResetReferenceTimer
{
protected:
	mutable int _time;
	int& _start_time;
public:
	AutoResetReferenceTimer(int& start_time) : _start_time(start_time), _time(start_time) {}
	bool tick() const {
		bool result = --_time;
		if (_time <= 0) { _time = _start_time; }
		return result;
	}
	void reset() const { _time = _start_time; }
};
#endif