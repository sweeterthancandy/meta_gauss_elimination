#ifdef _MSC_VER
#pragma once
#endif
#ifndef META_STRUCTS_H
#define META_STRUCTS_H


template<bool ASSERTION>
struct meta_static_assert;

template<>
struct meta_static_assert<true>
{
	static const bool value = true;
};

template<int L_PARAM, int R_PARAM, bool DUMMY = (L_PARAM < R_PARAM)>
struct meta_min
{
	static const int value = L_PARAM;
};
template<int L_PARAM, int R_PARAM>
struct meta_min<L_PARAM,R_PARAM,false>
{
	static const int value = R_PARAM;
};

template<int PARAM, bool DUMMY = (PARAM < 0)>
struct meta_abs
{
	static const int value = PARAM;
};
template<int PARAM>
struct meta_abs<PARAM,true>
{
	static const int value = -PARAM;
};



template<int L_PARAM, int R_PARAM, bool DUMMY = (L_PARAM < R_PARAM)>
struct meta_max
{
	static const int value = R_PARAM;
};
template<int L_PARAM, int R_PARAM>
struct meta_max<L_PARAM,R_PARAM,false>
{
	static const int value = L_PARAM;
};

template<int PARAM>
struct int_type
{
	//static const int value = PARAM;

	static const int evaluate()
	{
		return(PARAM);
	};
};

template<class T>
struct is_scalar
{
	static const bool value = false;
};

template<class T, class U>
struct types_same
{
	static const bool value = false;
};
template<class T>
struct types_same<T,T>
{
	static const bool value = true;
};


template<class T>
struct get_value;

template<int PARAM>
struct is_scalar<int_type<PARAM> >
{
	static const bool value = true;
};



template<int PARAM>
struct get_value<int_type<PARAM> >
{
	//static const int value = PARAM;

	static const int evaluate()
	{
		return(PARAM);
	}
};

template<int NUME, int DENO = 1>
struct rational_type
{
	static const int nume = NUME;
	static const int deno = DENO;
	static const double evaluate()
	{
		return(static_cast<const double>(NUME)/DENO);
	}
};

template<int NUME, int DENO>
struct get_value<rational_type<NUME,DENO> >
{
	static const double evaluate()
	{
		return(static_cast<const double>(NUME)/DENO);
	}
};



template<class T>
struct scalar_operations;



template<int PARAM>
struct scalar_operations<int_type<PARAM> >
{
	template<class T, class U>
	struct addition;
	template<int LP, int RP>
	struct addition<int_type<LP>,int_type<RP> >
	{
		typedef int_type<LP+RP> result;
	};
	template<class T, class U>
	struct multiplication;
	template<int LP, int RP>
	struct multiplication<int_type<LP>,int_type<RP> >
	{
		typedef int_type<LP*RP> result;
	};
	template<class T, class U>
	struct division;
	template<int LP, int RP>
	struct division<int_type<LP>,int_type<RP> >
	{
		typedef int_type<LP/RP> result;
	};
	template<class T, class U>
	struct subtraction;
	template<int LP, int RP>
	struct subtraction<int_type<LP>,int_type<RP> >
	{
		typedef int_type<LP-RP> result;
	};
};


template<class T>
struct number_node
{
	typedef T impl;
	static const double evaluate()
	{
		return(impl::evaluate());
	}
};

template<class T>
struct get_value<number_node<T> >
{
	static const double evaluate()
	{
		return(T::evaluate());
	}
};

template<class LP, class RP>
struct number_node_add;
template<class LPT, class RPT>
struct number_node_add<number_node<LPT>,number_node<RPT> >
{
	typedef number_node<LPT> left_param;
	typedef number_node<RPT> right_param;
	static const double evaluate()
	{
		return(left_param::evaluate()+right_param::evaluate());
	}
};
template<class LP, class RP>
struct number_node_sub;
template<class LPT, class RPT>
struct number_node_sub<number_node<LPT>,number_node<RPT> >
{
	typedef number_node<LPT> left_param;
	typedef number_node<RPT> right_param;
	static const double evaluate()
	{
		return(left_param::evaluate()-right_param::evaluate());
	}
};

template<class LP, class RP>
struct number_node_mul;
template<class LPT, class RPT>
struct number_node_mul<number_node<LPT>,number_node<RPT> >
{
	typedef number_node<LPT> left_param;
	typedef number_node<RPT> right_param;
	static const double evaluate()
	{
		return(left_param::evaluate()*right_param::evaluate());
	}
};

template<class LP, class RP>
struct number_node_div;
template<class LPT, class RPT>
struct number_node_div<number_node<LPT>,number_node<RPT> >
{
	typedef number_node<LPT> left_param;
	typedef number_node<RPT> right_param;
	static const double evaluate()
	{
		return(left_param::evaluate()/right_param::evaluate());
	}
};


template<class P>
struct scalar_operations<number_node<P> >
{
	template<class T, class U>
	struct addition;
	template<class LP, class RP>
	struct addition<number_node<LP>,number_node<RP> >
	{
		typedef number_node<LP> left_param;
		typedef number_node<RP> right_param;
		typedef number_node<number_node_add<left_param,right_param> > result;
	};
	template<class T, class U>
	struct multiplication;
	template<class LP, class RP>
	struct multiplication<number_node<LP>,number_node<RP> >
	{
		typedef number_node<LP> left_param;
		typedef number_node<RP> right_param;
		typedef number_node<number_node_mul<left_param,right_param> > result;
	};
	template<class T, class U>
	struct division;
	template<class LP, class RP>
	struct division<number_node<LP>,number_node<RP> >
	{
		typedef number_node<LP> left_param;
		typedef number_node<RP> right_param;
		typedef number_node<number_node_div<left_param,right_param> > result;
	};
	template<class T, class U>
	struct subtraction;
	template<class LP, class RP>
	struct subtraction<number_node<LP>,number_node<RP> >
	{
		typedef number_node<LP> left_param;
		typedef number_node<RP> right_param;
		typedef number_node<number_node_sub<left_param,right_param> > result;
	};
};

template<class T>
struct is_scalar<number_node<T> >
{
	static const int value = true;
};
#endif
