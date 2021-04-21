#ifndef DTG_UTILITIES_SORT
#define DTG_UTILITIES_SORT


#include <iostream>

#define deb\
	for (size_t k = 0; k != 10; ++k)\
		std::cout << *(m_Array[k]) << ", ";\
	std::cout << std::endl;
#define deb2\
	for (size_t k = 0; k != 10; ++k)\
		std::cout << (arr[k]) << "; ";\
	std::cout << std::endl;
namespace dtg {

template<class Type>
class MergeSort {
	public:
	MergeSort(Type* arr, size_t size, bool(*Compare)(const Type&, const Type&),
		void(*Swap)(Type&,Type&))
			:L(new Type*[(size + 1)/ 2]),
			R(new Type*[(size + 1)/ 2]),
			m_Array(new Type*[size]),
			m_Compare(Compare){
		
		for (size_t i = 0; i != size; ++i) {
			m_Array[i] = arr + i;
		}
		deb
		Sort(0, size - 1);
		deb
		size_t i = 0;
		for (;;) {
			if (m_Array[i] != arr + i){
				++c;
				Swap(*(m_Array[i]),arr[i]);
				deb
				deb2
				i = (reinterpret_cast<size_t>(m_Array[i])
				- reinterpret_cast<size_t>(arr)) / sizeof(size_t);
				//++j;
			}
			else
				++i;
		}
		deb2
		std::cout <<"\n\n";
	}

	private:

	void Sort(size_t l, size_t r) {
		if (l < r) {
			size_t m = l + (r-l)/2;
			Sort(l, m);
			Sort(m + 1, r);
			Merge(l, m, r);
		}
	}

	 void Merge(size_t l, size_t m, size_t r) {
		size_t n1 = m-l+1;
		size_t n2 = r-m;
		for(size_t i = 0;i < n1; ++i) {
			L[i] = m_Array[l+i]; 
		}
		for(size_t i = 0;i < n2; ++i) {
			R[i] = m_Array[m+1+i];
		}
		size_t i = 0, j = 0, k = l;
		while(i < n1 && j < n2) {
			if(m_Compare(*L[i] , *R[j])) {
				m_Array[k] = L[i];
				++k;
				++i;
			}
			else {
				m_Array[k] = R[j];
				++k;
				++j;
			}
			deb
		}
		while(i < n1) {
			m_Array[k] = L[i];
			++k;
			++i;
		}
		while(j < n2) {
			m_Array[k] = R[j];
			++k;
			++j;
		}
	}
	public:
	~MergeSort() {
		delete[]m_Array;
		delete[]L;
		delete[]R;
	}
	
	private:
	Type** L;
	Type** R;
	Type**	m_Array;
	bool	(*m_Compare)(const Type&, const Type&);
};

}

#endif
