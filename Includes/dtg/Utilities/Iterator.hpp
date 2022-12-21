#pragma once
#ifndef DTG_DTG_ITERATOR_HPP
#define DTG_DTG_ITERATOR_HPP
#endif

namespace dtg {
	template<class Ptr>
	size_t length(const Ptr* first, const Ptr* last) {
		return (reinterpret_cast<size_t>(last) - reinterpret_cast<size_t>(first)) / sizeof(Ptr);
	}
}
