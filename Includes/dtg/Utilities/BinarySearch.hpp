#ifndef DTG_UTILITIES_BINARY_SEARCH_HPP
#define DTG_UTILITIES_BINARY_SEARCH_HPP

#include <cstddef>

namespace dtg {
	
	template<class T1, class SizeType, class T3>
	T1* binarySearch(const T1* first, SizeType elems, const T3& searched) {
		SizeType l;
		SizeType r = elems;
		SizeType m;

		l = 0;
		m = r / 2;
		do {
			if (searched < first[m]) {
				r = m;
				m -= (m - l + 1) / 2;
			}
			else if (searched > first[m]) {
				l = m;
				m += (r - m + 1) / 2;
			}
			else
				return const_cast<T1*>(first + m);
		} while(m != r);
		return 0;
	}

	template<class T1, class SizeType, class T3, class CMP>
	T1* binarySearch(const T1* first
	, SizeType elems
	, const T3& searched
	, CMP cmp) {
		SizeType l;
		SizeType r = elems;
		SizeType m;

		l = 0;
		m = r / 2;
		do {
			int c = cmp(searched, &first[m]);
			if (c < 0) {
				r = m;
				m -= (m - l + 1) / 2;
			}
			else if (c > 0) {
					l = m;
					m += (r - m + 1) / 2;
			}
			else
				return const_cast<T1*>(first + m);
		} while(m != r);
		return 0;
	}

	template<class T1, class SizeType, class T3>
	T1* binarySearchFirst(const T1* first, SizeType elems, const T3& searched) {
		SizeType l;
		SizeType r = elems;
		SizeType m;

		l = 0;
		m = r / 2;
		do {
			if (searched <= first[m]) {
				r = m;
				m -= (m - l + 1) / 2;
			}
			else {
				l = m;
				m += (r - m + 1) / 2;
			}
		} while(m != r);
		if (r != elems && searched == first[r])
			return const_cast<T1*>(&first[r]);
		return 0;
	}

	template<class T1, class SizeType, class T3, class CMP>
	T1* binarySearchFirst(const T1* first
	, SizeType elems
	, const T3& searched
	, CMP cmp) {
		SizeType l;
		SizeType r = elems;
		SizeType m;

		l = 0;
		m = r / 2;
		do {
			int c = cmp(searched, &first[m]);
			if (c <= 0) {
				r = m;
				m -= (m - l + 1) / 2;
			}
			else {
					l = m;
					m += (r - m + 1) / 2;
			}
		} while(m != r);
		if (r != elems && searched == first[r])
			return const_cast<T1*>(&first[r]);
		return 0;
	}

	template<class T1, class SizeType, class T3>
	T1* binarySearchLast(const T1* first, SizeType elems, const T3& searched) {
		SizeType l;
		SizeType r = elems;
		SizeType m;

		l = 0;
		m = r / 2;
		do {
			if (searched < first[m]) {
				r = m;
				m -= (m - l + 1) / 2;
			}
			else {
				l = m;
				m += (r - m + 1) / 2;
			}
		} while(m != r);
		if (r != elems && searched == first[l])
			return const_cast<T1*>(&first[l]);
		return 0;
	}

	template<class T1, class SizeType, class T3, class CMP>
	T1* binarySearchLast(const T1* first
	, SizeType elems
	, const T3& searched
	, CMP cmp) {
		SizeType l;
		SizeType r = elems;
		SizeType m;

		l = 0;
		m = r / 2;
		do {
			int c = cmp(searched, &first[m]);
			if (c < 0) {
				r = m;
				m -= (m - l + 1) / 2;
			}
			else {
				l = m;
				m += (r - m + 1) / 2;
			}
		} while(m != r);
		if (r != elems && searched == first[l])
			return const_cast<T1*>(&first[l]);
		return 0;
	}
}// namespace dtg

#endif
