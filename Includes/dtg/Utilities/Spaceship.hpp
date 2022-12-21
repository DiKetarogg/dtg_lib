#ifndef DTG_UTILITIES_SPACESHIP_HPP
#define DTG_UTILITIES_SPACESHIP_HPP

#define DTG_SPACESHIP_OPERATOR(arg, left, right)\
	bool operator < (arg) const {\
		return (left) < (right);\
	}\
	bool operator <= (arg) const {\
		return (left) <= (right);\
	}\
	bool operator == (arg) const {\
		return (left) == (right);\
	}\
	bool operator != (arg) const {\
		return (left) != (right);\
	}\
	bool operator > (arg) const {\
		return (left) > (right);\
	}\
	bool operator >= (arg) const {\
		return (left) >= (right);\
	}\

#endif
