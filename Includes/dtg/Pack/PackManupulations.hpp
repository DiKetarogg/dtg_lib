#ifndef DTG_PACK_PACKMANIPULATIONS_HPP
#define DTG_PACK_PACKMANIPULATIONS_HPP
#include <tuple>

namespace dtg {

template<class T, class... Ts> 
struct pack_get_back : pack_get_back<Ts...> {}; 

template<class T>
struct pack_get_back<T> {
        typedef T type;
};

template<class T, class... Ts> 
struct pack_get_front {
        typedef T type;
};

template<class, class>
struct tuple_append;

template<class T, class... Ts> 
struct tuple_append<std::tuple<Ts...>, T> {
        typedef std::tuple<Ts..., T> type;
};

template<class, class>
struct tuple_adjoin;

template<class T, class... Ts> 
struct tuple_adjoin<std::tuple<Ts...>, T> {
        typedef std::tuple<T, Ts...> type;
};

template<class> 
struct tuple_pop_front;

template<class T, class... Ts> 
struct tuple_pop_front<std::tuple<T, Ts...>> {
        typedef std::tuple<Ts...> type;
};

template<class T>
struct tuple_pop_front<std::tuple<T>> {
        typedef std::tuple<> type;
};

template<class... Ts>
struct pack_pop_back;

template<class T, class... Ts>
struct pack_pop_back<T, Ts...> {
	typedef typename tuple_adjoin<
		typename pack_pop_back<Ts...>::type,
		T
	>::type type;
};


template<class T, class T1>
struct pack_pop_back<T, T1> {
	typedef std::tuple<T> type;
};

template<class T>
struct pack_pop_back<T> {
	typedef std::tuple<> type;
};

template<class>
struct tuple_pop_back;

template<class... Ts>
struct tuple_pop_back<std::tuple<Ts...>> : pack_pop_back<Ts...> {};



template<class T, class... Ts>
struct revert_pack {
        typedef typename tuple_append<
                typename revert_pack<Ts...>::type,
                T
                >::type type;
};

template<class T>
struct revert_pack<T> {
        typedef std::tuple<T> type;
};

template<class>
struct revert_tuple;

template<class... Ts>
struct revert_tuple<std::tuple<Ts...>> {
        typedef typename revert_pack<Ts...>::type type;
};

}//namespace dtg


#endif
