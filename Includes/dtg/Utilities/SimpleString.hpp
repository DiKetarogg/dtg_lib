#ifndef DTG_SIMPLESTRING_HPP
#define DTG_SIMPLESTRING_HPP

#include <stdexcept>

#include "ArrayCopy.hpp"
#include "ArrayCompare.hpp"
#include "CountElems.hpp"
#include "Spaceship.hpp"

//exceptions may be removed in future

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
			constexpr BasicSimpleString()
			: m_Length(0)
			, m_String(0) {}

			template<class Iterator>
			BasicSimpleString(Iterator begin, Iterator end)
				: m_Length(CalculateSize(begin, end))
				, m_String(new value_type[m_Length + 1]) {
				if (m_String) {
					pointer l = m_String;
					for (Iterator i = begin; i != end; ++i)
						l = ArrayCopyLast(l, static_cast<const_pointer>(*i), i->m_Length);
					m_String[m_Length] = 0;
				}
				else {
					DTG_STRING_OUT_OF_MEMORY;
				}
			}

			BasicSimpleString(const BasicSimpleString& other)
				: m_Length(countElems(other.m_String))
				, m_String(new value_type[m_Length + 1]) {
				if (m_String) {
					m_String[m_Length] = 0;
					TerminatedArrayCopy(m_String, other.m_String);
				}
				else {
					DTG_STRING_OUT_OF_MEMORY;
					m_Length = 0;
				}
			}

			BasicSimpleString(BasicSimpleString&& other) noexcept
				: m_Length(other.m_Length)
				, m_String(other.m_String) {
				other.m_String = 0;
			}

			/*explicit*/ BasicSimpleString(const_pointer string)
				: m_Length(countElems(string))
				, m_String(new value_type[m_Length + 1]) {
				if (m_String) {
					*TerminatedArrayCopyLast(m_String, string) = 0;
				}
				else {
					DTG_STRING_OUT_OF_MEMORY;
					m_Length = 0;
				}
			}

			BasicSimpleString(const_pointer string, size_t length)
				: m_Length(length)
				, m_String(new value_type[length + 1]) {
				if (m_String) {
					ArrayCopy(m_String, string, length);
					m_String[length] = 0;
				}
				else {
					DTG_STRING_OUT_OF_MEMORY;
					m_Length = 0;
				}
			}

			BasicSimpleString& operator = (const BasicSimpleString& other) {
				if (!Reallocate(other.m_Length))
					return *this;
				*TerminatedArrayCopyLast(m_String, other.m_String) = 0;
				return *this;
			}

			BasicSimpleString& operator = (BasicSimpleString&& other) noexcept {
				if (this != &other) {
					delete[] m_String;

					m_String = other.m_String;
					m_Length = other.m_Length;
					other.m_Length = 0;
					other.m_String = 0;
				}
				return *this;
			}

			BasicSimpleString& operator = (const_pointer string) {
				if (!Reallocate(countElems(string)))
					return *this;
				*TerminatedArrayCopy(m_String, string) = 0;
				return *this;
			}

			void Set(const_pointer string, size_t length) {
				if (!Reallocate(length))
					return;
				dtg::ArrayCopy(m_String, string, length);
				m_String[m_Length] = 0;
			}

			inline BasicSimpleString& Set(const_pointer str) {
				return operator=(str);
			}

			inline const_pointer Get() const {
				return m_String;
			}

			inline pointer Get() {
				return m_String;
			}

			inline size_t Length() const {
				return m_Length;
			}

			BasicSimpleString& Append(const_pointer* begin,
			const_pointer* end) {
				size_t size = 0;
				for (const_pointer* i = begin; i != end; ++i)
					size += countElems(*i);
				if (!size)
					return *this;
				return AppendIterator(begin, end, size + m_Length);
			}

			BasicSimpleString& Append(const BasicSimpleString* begin,
			const BasicSimpleString* end) {
				size_t size = 0;
				for (const BasicSimpleString* i = begin; i != end; ++i)
					size += i->m_Length;
				if (!size)
					return *this;
				return AppendIterator(begin, end, size + m_Length);
			}

			template<class Iterator>
			BasicSimpleString& Append(Iterator begin, Iterator end) {
				size_t size = 0;
				for (Iterator i = begin; i != end; ++i)
					size += i->m_Length;
				if (!size)
					return *this;
				return AppendIterator(begin, end, size + m_Length);
			}

			template<class... Args>
			BasicSimpleString& Append(const BasicSimpleString& firstArg, Args... args) {
				size_t size = CalculateAppendSize(firstArg, args...) + m_Length;
				if (size == m_Length)
					return *this;
				pointer tempHolder = m_String;
				m_String = new value_type[size + 1];
				if (m_String) {
					if (tempHolder) {
						AppendRecursively(m_String, tempHolder, firstArg, args...);
						delete[] tempHolder;
					}
					else
						AppendRecursively(m_String, firstArg, args...);
					m_String[size] = 0;
					m_Length = size;
				}
				else {
					DTG_STRING_OUT_OF_MEMORY;
					m_String = tempHolder;
				}
				return *this;
			}
			template<class... Args>
			BasicSimpleString& Append(const_pointer firstArg, Args... args) {
				size_t size = CalculateAppendSize(firstArg, args...) + m_Length;
				if (size == m_Length)
					return *this;
				pointer tempHolder = m_String;
				m_String = new value_type[size + 1];
				if (m_String) {
					AppendRecursively(m_String, tempHolder, firstArg, args...);
					m_String[size] = 0;
					m_Length = size;
					delete[] tempHolder;
				}
				else {
					DTG_STRING_OUT_OF_MEMORY;
					m_String = tempHolder;
				}
				return *this;
			}

			DTG_SPACESHIP_OPERATOR(pointer second
				, TerminatedArrayCompare(m_String, second)
				, value_type(0))

			DTG_SPACESHIP_OPERATOR(const BasicSimpleString& other
				, TerminatedArrayCompare(m_String, other.m_String)
				, value_type(0))

			operator const_pointer() const noexcept {
				return m_String;
			}

			operator pointer() noexcept {
				return m_String;
			}

			constexpr void Lose() {
				m_String = 0;
			}
			//If you steal, make sure you lose it (will seg fault otherwise).
			constexpr void Steal(pointer string, size_t size) {
				m_String = string;
				m_Length = size;
			}

			static constexpr BasicSimpleString StealingConstructor(pointer string, size_t size) {
				return BasicSimpleString(size, string);
			}

			~BasicSimpleString() {
				delete[] m_String;
			}
		private:
			template<class Iterator>
			size_t CalculateSize(Iterator begin, Iterator end) {
				size_t size = 0;
				for (Iterator i = begin; i != end; ++i)
					size += i->m_Length;
				return size;
			}
			template<class Iterator>
			inline BasicSimpleString& AppendIterator(Iterator begin,
			Iterator end, size_t size) {
				pointer tempHolder = m_String;
				m_String = new value_type[size + 1];
				if (m_String) {
					pointer l;
					if (tempHolder) {
						l = TerminatedArrayCopyLast(m_String, tempHolder);
						delete[] tempHolder;
					}
					else
						l = m_String;
					for (Iterator i = begin; i != end; ++i)
						l = TerminatedArrayCopyLast(l, static_cast<const_pointer>(*i));
					m_String[size] = 0;
					m_Length = size;
				}
				else {
					m_String = tempHolder;
				}
				return *this;
			}

			inline size_t CalculateAppendSize(void) {
				return 0;
			}
			
			template<class... Args>
			inline size_t CalculateAppendSize(const_pointer string, Args... args) {
				return countElems(string) + CalculateAppendSize(args...);
			}
			
			template<class... Args>
			inline size_t CalculateAppendSize(const BasicSimpleString& string, Args... args) {
				return string.m_Length + CalculateAppendSize(args...);
			}
			
			inline void AppendRecursively(pointer) {
				return;
			}

			template<class... Args>
			inline void AppendRecursively(pointer container,
			const BasicSimpleString& string, Args... args) {
				return AppendRecursively
				(TerminatedArrayCopyLast(container, string.m_String),
				args...);
			}

			template<class... Args>
			inline void AppendRecursively(pointer container,
			const_pointer string, Args... args) {
				return AppendRecursively
				(dtg::TerminatedArrayCopyLast(container, string),
				args...);
			}

			bool Reallocate(size_t size) {
				if (m_Length == size)
					return 1;
				delete[] m_String;
				m_String = new value_type[size + 1];
				if (!m_String) {
					m_Length = 0;
					DTG_STRING_OUT_OF_MEMORY;
					return 0;
				}
				m_Length = size;
				return 1;
			}

			//stealing constructor
			constexpr BasicSimpleString(size_t length, pointer string)
			: m_Length(length)
			, m_String(string){}
		private:
		size_t m_Length;
		pointer m_String;
	};

	using SimpleString   = BasicSimpleString<char>;
	//using SimpleString8  = BasicSimpleString<char8_t>;
	using SimpleString16 = BasicSimpleString<char16_t>;
	using SimpleString32 = BasicSimpleString<char32_t>;
	using WSimpleString  = BasicSimpleString<wchar_t>;
	namespace detail {
		template <class String>
		struct HashSimpleString
		: public std::__hash_base<size_t, String> {
			size_t operator()(const String& str) const noexcept {
				return std::_Hash_impl::hash(str.Get(), str.Length());
			}
		};
	}
}

namespace std {
	template<>
	struct hash<dtg::SimpleString>
	: public dtg::detail::HashSimpleString<dtg::SimpleString>
	{};
/*
	template<>
	struct hash<dtg::SimpleString8>
	: public dtg::detail::HashSimpleString<dtg::SimpleString8>
	{};
*/
	template<>
	struct hash<dtg::SimpleString16>
	: public dtg::detail::HashSimpleString<dtg::SimpleString16>
	{};
	template<>
	struct hash<dtg::SimpleString32>
	: public dtg::detail::HashSimpleString<dtg::SimpleString32>
	{};
	template<>
	struct hash<dtg::WSimpleString>
	: public dtg::detail::HashSimpleString<dtg::WSimpleString>
	{};
}

#undef DTG_DTG_STRING_OUT_OF_MEMORY

#endif
