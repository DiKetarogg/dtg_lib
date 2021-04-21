
#define DTG_CUSTOM_OPERATORS_NO_PREFIX
#include "dtg/CustomOperators.hpp"
#include "dtg/Utilities.hpp"
#include <iostream>

struct Int {
	Int(int i):i(i){}
	Int(const Int& i):i(i.i){}
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
	Int& operator = (int other) {
		i = other;
		return *this;
	}
	DTG_SPACESHIP_OPERATOR(i, other.i,const Int& other);
	DTG_SPACESHIP_OPERATOR(i, other,int other);
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

void CheckCustomOperators() {
	Int i = 2;
	Int j = 4;
	std::cout << "2 < 4 " << (i less_ j) << "\n"
	"2 <= 4 " << (i lesseq_ j) << "\n" 
	"2 == 4 " << (i eq_ j) << "\n"
	"2 != 4 " << (i neq_ j) << "\n"
	"2 > 4 " << (i great_ j) << "\n"
	"2 >= 4 " << (i greateq_ j);
	std::cout << "2 < 4 " << (i < j) << "\n"
	"2 <= 4 " << (i <= j) << "\n" 
	"2 == 4 " << (i == j) << "\n"
	"2 != 4 " << (i != j) << "\n"
	"2 > 4 " << (i > j) << "\n"
	"2 >= 4 " << (i >= j);
}

void CheckSwap() {
	Int i = 2;
	Int j = 4;
	dtg::Swap(i,j);
	std::cout << "test one(4): " << (i == 4) << "\n"
	"test two(2): " << (j == 2);
}

void CheckMergeSort() {
	size_t array[] = {1,2,3,4,5,6,7,8,9,10};
	size_t array2[] = {10,2,5,3,6,7,1,4,9,8};
	size_t array3[] = {10,2,2,3,6,10,1,1,9,1};
	auto Compare = [](const size_t& first, const size_t& second)->bool{
		return first < second;
		};
	auto Swap = [](size_t& first, size_t& second)->void {
		dtg::Swap(first,second);
		};
	dtg::MergeSort<size_t>(array, 10, Compare, Swap);
	dtg::MergeSort<size_t>(array2, 10, Compare, Swap);
	dtg::MergeSort<size_t>(array3, 10, Compare, Swap);
}

int main () {
	//CheckCustomOperators();
	//CheckSwap();
	std::cout << "SSS";
	CheckMergeSort();
}




















