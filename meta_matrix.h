#ifdef _MSC_VER
#pragma once
#endif
#ifndef META_MATRIX_H
#define META_MATRIX_H

#include "type_list.h"
#include "meta_structs.h"




template<class TL>
struct print_matrix_data_row
{
	static void print()
	{
		std::cout << "(";
		print_();
		std::cout << "  )" << std::endl;
	}
	static void print_()
	{
		std::cout << "  " << get_value<typename TL::head>::evaluate();
		print_matrix_data_row<typename TL::tail>::print_();
	}
};
template<class T>
struct print_matrix_data_row<type_list<T,null_type> >
{
	static void print()
	{
		std::cout << "(";
		print_();
		std::cout << "  )" << std::endl;
	}
	static void print_()
	{
		std::cout << "  " << get_value<T>::evaluate();
	}
};

template<class TL>
struct print_matrix_data
{
	static void print()
	{
		print_matrix_data_row<typename TL::head>::print();
		print_matrix_data<typename TL::tail>::print();
	}
};
template<class T>
struct print_matrix_data<type_list<T,null_type> >
{
	static void print()
	{
		print_matrix_data_row<T>::print();
	}
};

template<bool BOOL, class LP, class RP>
struct meta_inherite_if
	: public LP
{};
template<class LP, class RP>
struct meta_inherite_if<false,LP,RP>
	: public RP
{};


struct meta_matrix_dont_regen{};

template<class TL>
struct meta_matrix_generate_nothing_
{
	typedef typename TL::tail result;
};
template<int M, class TL>
struct meta_matrix_generate_rows_
{
	typedef type_list<typename tl_sub<TL,0,M>::result,
					  typename meta_matrix_generate_rows_<M,typename tl_sub<TL,M,tl_size<TL>::value-M>::result>::result
	> result;

	static void debug()
	{
		DEBUG_PRINT(M)
		DEBUG_PRINT(tl_size<TL>::value)
		meta_matrix_generate_rows_<M,typename tl_sub<TL,M,tl_size<TL>::value-M>::result>::debug();
	}

};

template<int M>
struct meta_matrix_generate_rows_<M,null_type>
{
	typedef null_type result;
	static void debug()
	{
		std::cout << "in null_type mmgr" << std::endl;
	}
};
template<int M, class TL>
struct meta_matrix_generate_rows
	: public meta_inherite_if<
	types_same<typename TL::head,meta_matrix_dont_regen>::value==1,
				meta_matrix_generate_nothing_<TL>,
				meta_matrix_generate_rows_<M,TL>
	> 

{
};




template<int N, int M, class TL>
struct meta_matrix
{
	typedef meta_matrix<N,M,TL> this_type;
	typedef typename meta_matrix_generate_rows<M,TL>::result data;

	static void dummy_function(){
	}

	static void print()
	{
		print_matrix_data<data>::print();
	}

	static void debug()
	{
		DEBUG_PRINT(N)
		DEBUG_PRINT(M)
		DEBUG_PRINT(tl_size<TL>::value)
		DEBUG_PRINT(tl_size<data>::value)

		meta_matrix_generate_rows<M,TL>::debug();

	}

	template<int P>
	struct get_row
	{
		typedef meta_matrix<1,M,typename tl_sub<data,P,1>::result::head> result;
	};
	template<int NP, int MP>
	struct get_element
		: public meta_static_assert<0<=NP&&NP<=N&&0<=MP&&MP<=M>
	{
		typedef typename tl_at<typename get_row<NP>::result::data::head,MP>::result result;
	};
	template<int NN, class T>
	struct insert_row;
	template<int NN, int MM, class TL_PARAM>
	struct insert_row<NN,meta_matrix<1,MM,TL_PARAM> >
	{
		typedef typename tl_sub<data,NN+1,tl_size<data>::value-NN-1>::result meta_end;

		typedef type_list<TL_PARAM,meta_end> meta_middle;

		typedef typename tl_append<typename tl_sub<data,0,NN>::result,meta_middle>::result tl_result;

		typedef meta_matrix<N,M,type_list<meta_matrix_dont_regen,tl_result> > result;

	};

	// creats sub matrix 
	template<int N1, int N2, class LOCAL_TL = null_type>
	struct n_offset
	{
		typedef typename tl_append<LOCAL_TL,typename this_type::get_row<N1>::result::data::head>::result meta_result;

		typedef typename n_offset<N1+1,N2,meta_result>::result result;
	};
	template<int NN, class LOCAL_TL>
	struct n_offset<NN,NN,LOCAL_TL>
	{
		typedef typename tl_append<LOCAL_TL,typename this_type::get_row<NN>::result::data::head>::result meta_result;

		//typedef typename tl_reverse<meta_result>::result meta_resultt;


		typedef meta_matrix<tl_size<meta_result>::value/M,M,meta_result> result;

	};

	template<int M1, int M2, int NI = 0, class LOCAL_TL = null_type, bool dummy = (NI==N)>
	struct m_offset
	{
		typedef typename tl_append<LOCAL_TL,
			typename tl_sub<typename this_type::get_row<NI>::result::data::head,M1,M2-M1+1>::result>::result meta_result;
		typedef typename m_offset<M1,M2,NI+1,meta_result>::result result;
	};
	template<int M1, int M2, int NI, class LOCAL_TL>
	struct m_offset<M1,M2,NI,LOCAL_TL,true>
	{
		typedef meta_matrix<N,tl_size<LOCAL_TL>::value/N,LOCAL_TL> result;
	};

	template<class T>
	struct get_raw;
	template<int P, int Q, class LOCAL_TL>
	struct get_raw<meta_matrix<P,Q,LOCAL_TL> >
	{
		static const int N_ = P;
		static const int M_ = Q;
		typedef LOCAL_TL TL_;
	};

	template<int N1, int M1, int N2, int M2>
	struct sub_matrix
	{
		typedef typename this_type::n_offset<N1,N2>::result meta_result;
		typedef typename meta_result::template m_offset<M1,M2>::result result;
	};
	
	template<int MI, bool = MI == M>
	struct transpose_gen_tl
	{
		typedef typename transpose_gen_tl<MI+1>::result impl_result;
		typedef typename get_raw<typename this_type::m_offset<MI,MI>::result>::TL_ meta_result;
		//typedef typename get_raw<typename this_type::m_offset<MI-1,M>::result>::TL_ meta_result;
		typedef typename tl_append<meta_result,impl_result>::result result;
		static void debug()
		{
			std::cout << "transpose_gen_tl<" << MI << ">" << std::endl;
			this_type::m_offset<MI,MI>::result::print();
			meta_matrix<N,1,meta_result>::print();
			DEBUG_PRINT(tl_size<result>::value)
			std::cout << "<---" << std::endl;
			DEBUG_PRINT(N*M-MI*N)
				meta_matrix<N*M-MI*N,1,result>::print();
			std::cout << "----" << std::endl;
			transpose_gen_tl<MI+1>::debug();
		}
	};
	template<int MI>
	struct transpose_gen_tl<MI, true>
	{
		typedef null_type result;
		static void debug()
		{
			std::cout << "at end" << std::endl;
			DEBUG_PRINT(M)
		}
	};
	struct transpose
	{
		typedef typename transpose_gen_tl<0>::result meta_result;
		typedef meta_matrix<M,N,meta_result> result;

		static void debug()
		{
			transpose_gen_tl<0>::debug();
			result::print();
			DEBUG_PRINT(tl_size<meta_result>::value)
		}

	};

};



template<class LP_TL, class RP_TL>
struct meta_row_matrix_add_impl
{ 
	typedef type_list<
		typename scalar_operations<typename LP_TL::head>::template addition<typename LP_TL::head,typename RP_TL::head>::result,
		typename meta_row_matrix_add_impl<typename LP_TL::tail,typename RP_TL::tail>::result
	>	result;
};

template<>
struct meta_row_matrix_add_impl<null_type,null_type>
{
	typedef null_type result;
};

template<class T, class U>
struct meta_row_matrix_add;

template<class LP_TL, class RP_TL, int M>
struct meta_row_matrix_add<meta_matrix<1,M,LP_TL>,meta_matrix<1,M,RP_TL> >
{
	typedef meta_matrix<1,M,typename meta_row_matrix_add_impl<LP_TL,RP_TL>::result> result;
};

//

template<class LP_TL, class RP_TL>
struct meta_row_matrix_sub_impl
{ 
	typedef type_list<
		typename scalar_operations<typename LP_TL::head>::template subtraction<typename LP_TL::head,typename RP_TL::head>::result,
		typename meta_row_matrix_sub_impl<typename LP_TL::tail,typename RP_TL::tail>::result
	>	result;
};

template<>
struct meta_row_matrix_sub_impl<null_type,null_type>
{
	typedef null_type result;
};

template<class T, class U>
struct meta_row_matrix_sub;

template<class LP_TL, class RP_TL, int M>
struct meta_row_matrix_sub<meta_matrix<1,M,LP_TL>,meta_matrix<1,M,RP_TL> >
{
	typedef meta_matrix<1,M,typename meta_row_matrix_sub_impl<LP_TL,RP_TL>::result> result;
};


//


template<class LP, class RP>
struct meta_row_matrix_mul_impl_scalar
{
	typedef LP TL;
	
	typedef type_list<
		typename scalar_operations<typename TL::head>::template multiplication<typename TL::head,RP>::result,
		typename meta_row_matrix_mul_impl_scalar<typename LP::tail,RP>::result
	> result;
};

template<class T, class RP>
struct meta_row_matrix_mul_impl_scalar<type_list<T,null_type>,RP>
{
	//typedef int_type<T::value> MLP;
	typedef T MLP;
	typedef type_list<
		typename scalar_operations<MLP>::template multiplication<MLP,RP>::result,
		null_type
	> result;
};


template<class T, class U, bool DUMMY = is_scalar<U>::value>
struct meta_row_matrix_mul;

template<class LP_TL, class RP, int M>
struct meta_row_matrix_mul<meta_matrix<1,M,LP_TL>,RP,true>
{
	typedef meta_matrix<1,M,
		typename meta_row_matrix_mul_impl_scalar<LP_TL,RP>::result
	> result;
};


#endif
