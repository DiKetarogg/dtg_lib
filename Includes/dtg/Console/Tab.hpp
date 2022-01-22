#pragma once
#include "Log.hpp"
namespace dtg {

	template<unsigned SIZE, char VAL>
	struct tab_impl : tab_impl<SIZE - 1, VAL> {
		const char t = VAL;	
	};

	template<char VAL>
	struct tab_impl<1u, VAL> {
		operator const char*() {
			return &t;
		}
		const char t = VAL;
	};

	template<unsigned SIZE, char VAL = '\t'>
	struct tab : tab_impl<SIZE, VAL> {
		const char null = 0;
	};
	
}
