#ifdef _MSC_VER
#pragma once
#endif
#ifndef TYPE_LIST_H
#define TYPE_LIST_H

#include "meta_structs.h"

template<class T, class U>
struct type_list
{
	typedef T head;
	typedef U tail;
};

struct null_type;

template<class TL>
struct tl_size;

template<class T, class U>
struct tl_size<type_list<T,U> >
{
	static const unsigned value = tl_size<U>::value+1;
};

template<>
struct tl_size<null_type>
{
	static const unsigned value = 0;
};

template<class TL, int N>
struct tl_at
{
	typedef typename tl_at<typename TL::tail,N-1>::result result;
};
template<class TL>
struct tl_at<TL,0>
{
	typedef typename TL::head result;
};



template<class TL>
struct tl_copy
{
	typedef type_list<typename TL::head,typename tl_copy<typename TL::tail>::result> result;
};
template<class T>
struct tl_copy<type_list<null_type,T> >
{
	typedef null_type result;
};
template<>
struct tl_copy<null_type>
{
	typedef null_type result;
};


template<class LP_TL, class RP_TL>
struct tl_append_backend
{
	typedef type_list<typename LP_TL::head,
		typename tl_append_backend<typename LP_TL::tail,RP_TL>::result
	> result;
};

template<class T, class RP_TL>
struct tl_append_backend<type_list<T,null_type>,RP_TL>
{
	typedef type_list<T,RP_TL> result;
};

template<class LP_TL, class RP_TL>
struct tl_append
{
	typedef typename tl_append_backend<typename tl_copy<LP_TL>::result,typename tl_copy<RP_TL>::result>::result result;
};
template<class RP_TL>
struct tl_append<null_type,RP_TL>
{
	typedef RP_TL result;
};;
template<class T, class RP_TL>
struct tl_append<type_list<null_type,T>,RP_TL>
{
	typedef RP_TL result;
};

template<class LP, class RP = null_type>
struct tl_reverse
{
	typedef typename tl_reverse<typename LP::tail,type_list<typename LP::head,RP> >::result result;
};
template<class T, class TL>
struct tl_reverse<type_list<T,null_type>,TL>
{
	typedef type_list<T,TL> result;
};

template<class TL, int LENGH>
struct tl_sub_copy
{
	typedef type_list<typename TL::head,typename tl_sub_copy<typename TL::tail,LENGH-1>::result> result;
};
template<class TL>
struct tl_sub_copy<TL,0>
{
	typedef null_type result;
};

template<class TL, int OFFSET, int LENGH>
struct tl_sub_backend
	: public tl_sub_backend<typename TL::tail,OFFSET-1,LENGH>
{
};

template<class TL, int LENGH>
struct tl_sub_backend<TL,
					  0,
					  LENGH
					  >
	: public tl_sub_copy<TL,meta_min<tl_size<TL>::value,LENGH>::value>
{
};

template<class TL, int OFFSET, int LENGH, bool DUMMY = (types_same<TL,null_type>::value&&(LENGH==0))>
struct tl_sub
	: 
	public meta_static_assert<(tl_size<TL>::value>=(OFFSET+LENGH))>,
		   tl_sub_backend<TL,OFFSET,meta_min<LENGH,tl_size<TL>::value-OFFSET>::value>
{
};
template<class TL, int OFFSET, int LENGH>
struct tl_sub<TL,OFFSET,LENGH,true>
{
	typedef null_type result;
};


template<class TL>
struct print_tl;

template<class T, class U>
struct print_tl<type_list<T,U> >
{
	typedef print_tl<U> impl;

	static void print()
	{
		std::cout << typeid(T).name() << std::endl;
		impl::print();
	}
};

template<>
struct print_tl<null_type>
{
	static void print(){}
};


#endif