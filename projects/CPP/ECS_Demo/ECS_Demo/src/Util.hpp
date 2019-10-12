#pragma once

// contains macros used in different parts of the application
#define BIT(x) (1 << x)
#define BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)
#define NULL_COPY_AND_ASSIGN(T) \
	T(const T& other) {(void)other;} \
	void operator=(const T& other) { (void)other; }
