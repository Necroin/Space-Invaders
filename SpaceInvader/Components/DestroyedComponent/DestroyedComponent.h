#pragma once
#ifndef _DESTROYEDCOMPONENT_H_
#define _DESTROYEDCOMPONENT_H_

class DestroyedComponent {
protected:
	bool _destroyed = false;
public:
	bool is_destroyed() const noexcept { return _destroyed; }
	void destroy() noexcept { _destroyed = true; }
};
#endif