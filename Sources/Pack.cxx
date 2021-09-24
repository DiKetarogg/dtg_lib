#include <dtg/Pack.hpp>
#include <typeinfo>
#include <string.h>
#include <iostream>
struct ttttt;
/*
template<class T>
struct pack_to_string<T> {
	static constexpr const char* string = typeid(T).name();
};
*/
/*
template<class T, class... Ts>
char* mystrcat(T str, Ts... strs) {
	return strcat(str, mystrcat(strs...));
}
template<>
char* mystrcat<char*, const char*>(char* str1, const char* str2) {
	return strcat(str1, str2);
}

template<size_t size>
constexpr size_t const_strssize(const char (&)[size]) {
	return size;
}

template<class... Ts>
constexpr size_t const_strssize(Ts&&... args) {
	//static const size_t res = (const_strssize((std::forward<Ts>(args))) + ...);// - sizeof...(args);
	return const_sum<(const_strssize(std::forward<Ts>(args)), ...)>::get;
}
*/
/*
template<class... Ts>
constexpr const char* const_strcat(const char* str, size_t size, Ts... args) {
	char temp[]
}
*/
int main() {
	
	//const char tes[] = const_strcat("Hel", "oo", "/");
	using namespace dtg;
	typedef typename revert_pack<char, int, bool>::type test1;
	typedef std::tuple<bool, int, char> result1;
	static_assert(
		std::is_same<
			test1,
			result1
		>::value,
		"Failed"
	);

	typedef typename revert_tuple< std::tuple<char, int, bool, float> >::type test2;
	typedef std::tuple<float, bool, int, char> result2;
	static_assert(
		std::is_same<
			test2,
			result2
		>::value,
		"dtg::revert_pack failed"
	);

	static_assert(
		std::is_same<
			tuple_append<std::tuple<>, int>::type,
			std::tuple<int>
		>::value,
		"dtg::tuple_append failed"
	);

	static_assert(
		std::is_same<
			tuple_append< std::tuple< std::tuple<int, bool> >, ttttt >::type,
			std::tuple<std::tuple<int, bool>, ttttt>
		>::value,
		"dtg::tuple_append failed"
	);

	static_assert(
		std::is_same<
			tuple_adjoin<std::tuple<>, int>::type,
			std::tuple<int>
		>::value,
		"dtg::tuple_append failed"
	);

	static_assert(
		std::is_same<
			tuple_adjoin<std::tuple<std::tuple<int, bool>>, ttttt>::type,
			std::tuple<ttttt, std::tuple<int, bool>>
		>::value,
		"dtg::tuple_append failed"
	);

	static_assert(
		std::is_same<
			tuple_pop_front< std::tuple<std::tuple<int, bool>> >::type,
			std::tuple<>
		>::value,
		"Failed"
		      );

	static_assert(
		std::is_same<
			tuple_pop_front< std::tuple<
				std::tuple<std::tuple<int, bool>, int, double, float>
				>
			>::type,
			std::tuple<>
		>::value,
		"dtg::tuple_pop_front failed"
	);

	static_assert(
		std::is_same<
			tuple_pop_back<
				std::tuple<
					std::tuple<int, bool>,
					int, double, float, int
				>
			>::type,
			std::tuple<std::tuple<int, bool>, int, double, float>
		>::value,
		"dtg::tuple_pop_back failed"
	);

	static_assert(
		std::is_same<
			tuple_pop_back< std::tuple<int,
				double, bool, void*, std::tuple<int, bool> >
			>::type,
			std::tuple<int, double, bool, void*>
		>::value,
		"dtg::tuple_pop_back failed"
	);

	static_assert(
		std::is_same<
			pack_get_back<int, bool, float, ttttt>::type,
			ttttt
		>::value,
		"dtg::pack_get_back failed"
	);

	static_assert(
		std::is_same<
			pack_get_back<float, int, bool, bool, double, uint32_t, void*,
				std::tuple< std::tuple<int, bool>, int > >::type,
			std::tuple< std::tuple<int, bool>, int >
		>::value,
		"dtg::pack_get_back failed"
	);

	static_assert(
		std::is_same<
			pack_get_front<std::tuple<std::tuple<int, bool>>, ttttt>::type,
			std::tuple<std::tuple<int, bool>>
		>::value,
		"dtg::pack_get_front failed"
	);

	static_assert(
		std::is_same<
			pack_get_front<ttttt, std::tuple<std::tuple<int, bool>>, int, bool, char, void*>::type,
			ttttt
		>::value,
		"dtg::pack_get_front failed"
	);
}






