#ifdef _MSC_VER
#pragma once
#endif
#ifndef META_SOLVER_H
#define META_SOLVER_H

#include "type_list.h"
#include "meta_matrix.h"


/*
	row operation on row TN of matrix so that element (COL,TN) is equal to zero by doing arthmetic with row 

	COl := subject column
	SUB := subject row
	ARG := argument row to use  
*/

template<int COL, int ROW_SUB, int ARG,class T>
struct meta_solve_equate_rows_addition;

template<int COL, int ROW_SUB, int ARG, int N, int M, class TL>
struct meta_solve_equate_rows_addition<COL,ROW_SUB,ARG,meta_matrix<N,M,TL> >
{
	typedef meta_matrix<N,M,TL> matrix_param;

	typedef typename matrix_param::template get_element<ARG,COL>::result P;
	typedef typename matrix_param::template get_element<ROW_SUB,COL>::result Q;

	typedef typename matrix_param::template get_row<ROW_SUB>::result subject_row;
	typedef typename matrix_param::template get_row<ARG>::result arg_row;
	typedef          scalar_operations<Q> scalar_ops;

	typedef typename meta_row_matrix_mul<subject_row,P>::result meta_new_row;
	typedef typename meta_row_matrix_mul<arg_row,Q>::result meta_arg_row;
	// ------------------------------------------------------------------------

	typedef typename meta_row_matrix_sub<meta_new_row,meta_arg_row>::result new_row;
	typedef typename matrix_param::template insert_row<ROW_SUB,new_row> meta_row_op;
	typedef typename meta_row_op::result result;

	static void debug()
	{
		subject_row::print();
		arg_row::print();
		meta_new_row::print();
		meta_arg_row::print();
		new_row::print();
		result::print();
		DEBUG_PRINT(tl_size<TL>::value)
		DEBUG_PRINT(tl_size<typename result::data>::value)
		DEBUG_PRINT(tl_size<typename meta_row_op::tl_result>::value)
		print_matrix_data<typename meta_row_op::tl_result>::print();
	}
};


template<int COL, int ROW_SUB, int ARG,class T>
struct meta_solve_equate_rows;

template<int COL, int ROW_SUB, int ARG, int N, int M, class TL>
struct meta_solve_equate_rows<COL,ROW_SUB,ARG,meta_matrix<N,M,TL> >
{
};

// front end to solve columns
template<int C, class M>
struct meta_solve_columns;

template<int C, int R, class M>
struct meta_solve_columns_2;


template<int C, int R, int N, class MTL>
struct meta_solve_columns_2<C,R,meta_matrix<N,N+1,MTL> >
{
	typedef meta_matrix<N,N+1,MTL> matrix_param;
	typedef typename meta_solve_equate_rows_addition<C,R,C,matrix_param>::result result;
	static void debug()
	{
		DEBUG_PRINT(C)
		DEBUG_PRINT(R)
		DEBUG_PRINT(N)
		std::cout << "result::print()" << std::endl;
		result::print();
	}
};


// just to speciaze where at end of last row
template<int C, int R, int NMONE, class M>
struct meta_solve_columns_1
{
	typedef typename meta_solve_columns_2<C,R,M>::result meta_result;

	typedef typename meta_solve_columns_1<C,R+1,NMONE,meta_result>::result result;
	//typedef meta_result result;

	static void debug()
	{
		DEBUG_PRINT(C)
		DEBUG_PRINT(R)
		DEBUG_PRINT(NMONE)
		meta_solve_columns_2<C,R,M>::debug();

		std::cout << "meta_solve_columns_1<" << C << "," << R+1 << "," << NMONE << ",meta_result>" << std::endl;
		meta_solve_columns_1<C,R+1,NMONE,meta_result>::debug();
	}

};

template<int C, int R_NMONE, class M>
struct meta_solve_columns_1<C,R_NMONE,R_NMONE,M>
{
	typedef typename meta_solve_columns_2<C,R_NMONE,M>::result meta_result;
	typedef meta_result result;

	static void debug()
	{
		std::cout << "in struct meta_solve_columns_1<" << C << "," << R_NMONE << "," << R_NMONE<< ",M>" << std::endl;
	}
};


// this is to get the value of N
template<int C, int N, class MTL>
struct meta_solve_columns<C,meta_matrix<N,N+1,MTL> >
{
	typedef meta_matrix<N,N+1,MTL> matrix_param;
	typedef meta_solve_columns_1<C,C+1,N-1,matrix_param> meta_struct;
	typedef typename meta_struct::result result; // N-1 cos can't have template<int N>struct foo<N-1>{...};

	static void debug()
	{
		DEBUG_PRINT(C)
		DEBUG_PRINT(N)
		meta_struct::debug();

	}
};


template<int ITER, int END, class M>
struct meta_solve_2
{
	typedef typename meta_solve_columns<ITER,M>::result meta_result;

	typedef meta_solve_2<ITER+1,END,meta_result> meta_struct;
	typedef typename meta_struct::result result;

	static void debug()
	{
		DEBUG_PRINT(ITER)
		DEBUG_PRINT(END)
		meta_struct::debug();
	}

};

template<int ITEREND, class M>
struct meta_solve_2<ITEREND,ITEREND,M>
{
	typedef typename meta_solve_columns<ITEREND,M>::result result;
	//typedef M result;

	static void debug()
	{
		DEBUG_PRINT(ITEREND)
	}
};



template<class T>
struct meta_solve;

template<int N, class TL>
struct meta_solve<meta_matrix<N,N+1,TL> >
{
	static const int M = N+1;
	typedef meta_matrix<N,M,TL> param;

	typedef meta_solve_2<0,N-2,param> meta_struct;
	typedef typename meta_struct::result result;

	static void debug()
	{
		meta_struct::debug();
	}



};



template<int ITER, int MN, class LPTL, class RPTL>
struct meta_matrix_mul_n_x_1_x_1_x_m_
{
	typedef meta_matrix<MN,1,LPTL> left_param;
	typedef meta_matrix<1,MN,RPTL> right_param;

	typedef scalar_operations<typename left_param::template get_element<ITER-1,0>::result> scalar_ops;
	typedef typename scalar_ops::template multiplication<typename left_param::template get_element<ITER-1,0>::result,
		typename right_param::template get_element<0,ITER-1>::result>::result meta_result;
	typedef meta_matrix_mul_n_x_1_x_1_x_m_<ITER+1,MN,LPTL,RPTL> impl;
	typedef typename scalar_ops::template addition<meta_result,typename impl::meta_resultt>::result meta_resultt;
	typedef meta_matrix<1,1,type_list<meta_resultt,null_type> > result;

	static void debug()
	{
		left_param::print();
		right_param::print();
		DEBUG_PRINT(get_value<meta_result>::value)
		result::print();
		std::cout << "---" << std::endl;
		impl::debug();
	}
};
template<int ITERMN, class LPTL, class RPTL>
struct meta_matrix_mul_n_x_1_x_1_x_m_<ITERMN,ITERMN,LPTL,RPTL>
{
	static const int ITER = ITERMN;
	static const int MN = ITERMN;
	typedef meta_matrix<MN,1,LPTL> left_param;
	typedef meta_matrix<1,MN,RPTL> right_param;
	typedef scalar_operations<typename left_param::template get_element<ITER-1,0>::result> scalar_ops;
	typedef typename scalar_ops::template multiplication<typename left_param::template get_element<ITER-1,0>::result,
		typename right_param::template get_element<0,ITER-1>::result>::result meta_resultt;
	typedef meta_matrix<1,1,type_list<meta_resultt,null_type> > result;

	static void debug()
	{
		DEBUG_PRINT(get_value<meta_resultt>::value)
		result::print();
	}
};

template<class LP, class RP>
struct meta_matrix_mul_n_x_1_x_1_x_m_front_end;
template<int MN, class LPTL, class RPTL>
struct meta_matrix_mul_n_x_1_x_1_x_m_front_end<meta_matrix<MN,1,LPTL>,meta_matrix<1,MN,RPTL> >
	: public meta_matrix_mul_n_x_1_x_1_x_m_<1,MN,LPTL,RPTL>
{
};

template<class M>
struct read_solution;


template<int N, class TL, bool DUMMY>
struct read_solution_1
{
	typedef meta_matrix<N,N+1,TL> matrix_param;
	typedef scalar_operations<typename matrix_param::template get_element<0,0>::result> scalar_ops;
	typedef typename matrix_param::template get_row<0>::result matrix_row;
	typedef typename matrix_param::template sub_matrix<1,1,N-1,N>::result sub_matrix;
	typedef read_solution<sub_matrix> impl;
	typedef typename matrix_row::template m_offset<1,N-1>::result lp;
	typedef typename matrix_row::template get_element<0,N>::result rp;

	typedef typename read_solution<sub_matrix>::solution meta_sub_sol;
	typedef typename meta_sub_sol::transpose::result sub_sol;

	typedef typename meta_matrix_mul_n_x_1_x_1_x_m_front_end<sub_sol,lp>::result meta_value;
	typedef typename scalar_ops::template subtraction<rp,typename meta_value::template get_element<0,0>::result>::result meta_valuee;
	typedef typename scalar_ops::template division<meta_valuee,typename matrix_row::template get_element<0,0>::result>::result meta_valueee;
#if 0		
	typedef typename matrix_param::get_row<0>::result matrix_row;
	typedef typename scalar_ops::subtraction<typename matrix_row::get_element<N-1>::result,meta_value>::result meta_valuee;
	typedef typename type_list<meta_valuee,typename impl::raw_solution> raw_solution;
	typedef meta_matrix<tl_size<raw_solution>::value,1,raw_solution> solution;
#endif
	typedef type_list<meta_valueee,typename impl::raw_solution> raw_solution;
	typedef meta_matrix<1,tl_size<raw_solution>::value,raw_solution> solution;
	


	static void debug()
	{
		matrix_param::print();
		std::cout << std::endl;
		lp::print();
		std::cout << std::endl;
		sub_matrix::print();
		std::cout << std::endl;
		matrix_row::print();
		meta_value::print();
		DEBUG_PRINT(get_value<rp>::value)

		DEBUG_PRINT(get_value<meta_valuee>::evaluate())
		DEBUG_PRINT(get_value<meta_valueee>::evaluate())
		solution::print();
		std::cout << "--------" << std::endl;
		impl::debug();
	}
};

template<int N, class TL>
struct read_solution_1<N,TL,true>
{
	typedef meta_matrix<N,N+1,TL> matrix_param;
	typedef scalar_operations<typename matrix_param::template get_element<0,0>::result> scalar_ops;

	typedef typename scalar_ops::template division<typename matrix_param::template get_element<0,1>::result,
		typename matrix_param::template get_element<0,0>::result>::result meta_result;

	typedef type_list<meta_result,null_type> raw_solution;

	typedef meta_matrix<1,1,raw_solution > solution;

	static void debug()
	{
		std::cout << "in read_solution_1<meta_matrix<" << N << "," << N+1 << ",TL>,true>" << std::endl;
		matrix_param::print();
		std::cout << get_value<meta_result>::value << std::endl;
		solution::print();
	};
};

template<int N, class TL>
struct read_solution<meta_matrix<N,N+1,TL> >
	: public read_solution_1<N,TL,N==1> 
{
};

template<class T>
struct solve
{
	typedef typename meta_solve<T>::result meta_solved;
	typedef typename read_solution<meta_solved>::solution result;
};

#endif
