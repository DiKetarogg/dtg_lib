#pragma once
#include <iostream>
#include "Color.hpp"
#include <tuple>
namespace dtg {
/*
	template<class Stream, class Tuple, class Sequence>
	struct log_tuple;

	template<class Stream, class... Args, size_t... ins>
	struct log_tuple<Stream, std::tuple<Args...>, std::index_sequence<ins...>> {
		static inline void out(Stream& stream, const std::tuple<Args...>& tuple) {
			((stream << std::get<ins>(tuple)) << ...);
		}
	};
	template<class... Args>
	static std::ostream& operator << (std::ostream& stream, const std::tuple<Args...>& tuple) {
		log_tuple<
				std::ostream,
				decltype(tuple),
				std::make_index_sequence<sizeof...(Args)>()
			>::out(stream, tuple);
	return stream;
	}
*/
	template <class Arg, class ...Ts>
	void Log(Arg arg, Ts... args) {
		((std::cout << arg) << ... << args);
	}
/*
	void LogFail(int id) {
		Log(' ', id, '.', color<RED>(), 'X', color<NORMAL>());
	}

	void LogSuccess(int id) {
		Log(' ', id, '.', color<GREEN>(), 'V', color<NORMAL>());
	}
*/
}// namespace dtg
