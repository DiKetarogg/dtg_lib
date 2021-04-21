
#define DTG_CUSTOM_OPERATORS_NO_PREFIX
#include "dtg/CustomOperators.hpp"
#include "dtg/Utilities.hpp"
#include <iostream>

struct Int {
	Int(int i):i(i){}
	operator int() const {
		return i;
	}
//	operator const int() const {
//		return i;
//	}
	int i;
	Int& operator = (Int other) {
		i = other.i;
		return *this;
	}
	/*
//	DTG_SPACESHIP_OPERATOR(i, other.i,const Int& other);
//	bool operator < (const Int& other) const {
//		return i < other.i;
//	}
	bool operator <= (const Int& other) const {
		return i <= other.i;
	}
	bool operator == (const Int& other) const {
		return i == other.i;
	}
	bool operator > (const Int& other) const {
		return i > other.i;
	}
	bool operator >= (const Int& other) const {
		return i >= other.i;
	}
	*/
};

inline dtg::CustomOperator<const Int&, decltype(dtg::CUSTOM_OPERATOR_NEQ)> operator !=
(const Int& left, decltype(dtg::CUSTOM_OPERATOR_NEQ)) {\
	return dtg::CustomOperator<const Int&, decltype(dtg::CUSTOM_OPERATOR_NEQ)>(left);\
}
inline auto operator !=
(const dtg::CustomOperator<const Int&, decltype(dtg::CUSTOM_OPERATOR_NEQ)>& left, const Int& right)->bool{
	return left.data != right;
}

//DTG_BUILD_CUSTOM_DTG_SPACESHIP(inline, const Int&, left.data, right);
//DTG_BUILD_CUSTOM_SPACESHIP(inline, Int, left.data, right,
//dtg::CUSTOM_OPERATOR_LESS, dtg::CUSTOM_OPERATOR_LESSEQ, dtg::CUSTOM_OPERATOR_EQ,
//dtg::CUSTOM_OPERATOR_NEQ, dtg::CUSTOM_OPERATOR_GREAT, dtg::CUSTOM_OPERATOR_GREATEQ)
//DTG_BUILD_CUSTOM_BIN_BOTH(inline, const Int&, <, dtg::CUSTOM_OPERATOR_LESS, >)->bool {
//	return left.data < right;
//}
/*
DTG_BUILD_CUSTOM_BIN_LEFT(Int, <, dtg::CUSTOM_OPERATOR_LESS)
DTG_BUILD_CUSTOM_BIN_RIGHT(inline, Int, dtg::CUSTOM_OPERATOR_LESS, >)->bool{
	return left.data < right;
}
*/

int main () {
	Int i = 2;
	Int j = 4;
	std::cout << "i < j " << (i less_ j) << "\n"
	"i <= j " << (i lesseq_ j) << "\n" 
	"i == j " << (i eq_ j) << "\n"
	"i != j " << (i neq_ j) << "\n"
	"i > j " << (i great_ j) << "\n"
	"i >= j " << (i greateq_ j);
	std::cout << "i < j " << (i < j) << "\n"
	"i <= j " << (i <= j) << "\n" 
	"i == j " << (i == j) << "\n"
	"i != j " << (i != j) << "\n"
	"i > j " << (i > j) << "\n"
	"i >= j " << (i >= j);
}




















