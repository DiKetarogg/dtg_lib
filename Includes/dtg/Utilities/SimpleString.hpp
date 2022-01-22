#ifndef DTG_SIMPLESTRING_HPP
#define DTG_SIMPLESTRING_HPP

#include <stdexcept>
#include "ArrayCopy.hpp"
#include "ArrayCompare.hpp"
#include "CountElems.hpp"
#include "Spaceship.hpp"


#ifndef DTG_NO_EXCEPT
#define DTG_STRING_OUT_OF_MEMORY throw std::runtime_error("dtg::SimpleString out of memory")
#else
#define DTG_STRING_OUT_OF_MEMORY
#endif


namespace dtg {

	template <class CharType>
	class BasicSimpleString {
		public:
			using value_type	= CharType;
			using pointer		= value_type*;
			using const_pointer	= const value_type*;
		public:
			BasicSimpleString():m_String(0){}

			BasicSimpleString(const BasicSimpleString& other):
				m_String(new value_type[countElems(other.m_String) + 1]) {
				if (m_String)
					dtg::TerminatedArrayCopy(m_String, other.m_String);
				else
					DTG_STRING_OUT_OF_MEMORY;

			}

			BasicSimpleString(BasicSimpleString&& other) noexcept
				:m_String(other.m_String) {
				other.m_String = 0;
			}

			explicit BasicSimpleString(const_pointer string)
				:m_String(new value_type[countElems(string) + 1]) {
				if (m_String)
					dtg::TerminatedArrayCopy(m_String, string);
				else
					DTG_STRING_OUT_OF_MEMORY;
			}

			BasicSimpleString(const_pointer string, size_t length)
				:m_String(new value_type[length + 1]) {
				if (m_String) {
					dtg::ArrayCopy(m_String, string, length);
					m_String[length] = 0;
				}
				else
					DTG_STRING_OUT_OF_MEMORY;
			}


			BasicSimpleString& operator = (const BasicSimpleString& other) {
				m_String = new value_type[countElems(other.m_String) + 1];
				if (m_String)
					dtg::TerminatedArrayCopy(m_String, other.m_String);
				else
					DTG_STRING_OUT_OF_MEMORY;
				return *this;
			}

			BasicSimpleString& operator = (BasicSimpleString&& other) noexcept {
				if (this != &other) {
					delete[] m_String;

					m_String = other.m_String;
					other.m_String = 0;
				}
				return *this;
			}

			BasicSimpleString& operator = (const_pointer string) {
				delete[] m_String;
				m_String = new value_type[countElems(string) + 1];
				if (m_String)
					dtg::TerminatedArrayCopy(m_String, string);
				else
					DTG_STRING_OUT_OF_MEMORY;

				return *this;
			}
			~BasicSimpleString() {
				delete[] m_String;
			}

			void Set(const_pointer string, size_t length) {
				delete[] m_String;

				m_String = new value_type[length];
				if (m_String)
					dtg::ArrayCopy(m_String, string, length);
				else
					DTG_STRING_OUT_OF_MEMORY;
				m_String[length - 1] = 0;
			}

			auto Set(const_pointer str) {
				return operator=(str);
			}

			template<class... Args>
			BasicSimpleString& Append(const_pointer firstArg, Args... args) {
				size_t size = 1 + CalculateAppendSize(firstArg, args...);
				if (size == 1)
					return *this;
				pointer tempHolder = m_String;
				m_String = new value_type[size];
				if (m_String)
					AppendRecursively(m_String, tempHolder, firstArg, args...);
				delete[] tempHolder;
				return *this;
			}

			template<class... Args>
			BasicSimpleString& Append(const BasicSimpleString& firstArg, Args... args) {
				size_t size = 1 + CalculateAppendSize(firstArg, args...);
				if (size == 1)
					return *this;
				pointer tempHolder = m_String;
				m_String = new value_type[size];
				if (m_String)
					AppendRecursively(m_String, tempHolder, firstArg, args...);
				delete[] tempHolder;
				return *this;
			}

			BasicSimpleString& Append(const_pointer const* first,
			const_pointer const* last) {
				size_t size = countElems(m_String) + 1;
				for (pointer* i = const_cast<pointer*>(first); i != last; ++i)
					size += countElems(*i);
				if (size == 1)
					return *this;
				pointer tempHolder = m_String;
				m_String = new value_type[size];
				if (m_String) {
				pointer l = TerminatedArrayCopyLast(m_String, tempHolder);
				delete[] tempHolder;
				for (pointer* i = const_cast<pointer*>(first); i != last; ++i)
					l = TerminatedArrayCopyLast(l, *i);
				}
				else {
					m_String = tempHolder;
				}
				return *this;
			}

			BasicSimpleString& Append(const BasicSimpleString* first,
			const BasicSimpleString* last) {
				return Append(&first->m_String, &last->m_String);
			}
			DTG_SPACESHIP_OPERATOR(TerminatedArrayCompare(m_String, second),
					value_type(0), pointer second)

			DTG_SPACESHIP_OPERATOR(TerminatedArrayCompare(m_String, other.m_String),
					value_type(0), const BasicSimpleString& other)

			operator const_pointer() const noexcept {
				return m_String;
			}

			operator pointer() noexcept {
				return m_String;
			}

		private:
			size_t CalculateAppendSize(void) {
				return 0;	
			}
			template<class... Args>
			size_t CalculateAppendSize(const_pointer string, Args... args) {
				return countElems(string) + CalculateAppendSize(args...);
			}
			template<class... Args>
			size_t CalculateAppendSize(const BasicSimpleString& string, Args... args) {
				return countElems(string.m_String) + CalculateAppendSize(args...);
			}
			void AppendRecursively(pointer) {
				return;
			}
			template<class... Args>
			void AppendRecursively(pointer container,
			const BasicSimpleString& string, Args... args) {
				return AppendRecursively
				(TerminatedArrayCopyLast(container, string.m_String),
				args...);
			}
			template<class... Args>
			void AppendRecursively(pointer container,
			const_pointer string, Args... args) {
				return AppendRecursively
				(dtg::TerminatedArrayCopyLast(container, string),
				args...);
			}
		private:
	
		pointer m_String;
	};
	typedef BasicSimpleString<char>		SimpleString;
	typedef BasicSimpleString<wchar_t>	WSimpleString;
}

#undef DTG_DTG_STRING_OUT_OF_MEMORY

#endif
