// meta_matix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// meta_marix.cpp : Defines the entry point for the console application.
//

#define DEBUG_PRINT(NAME) \
	std::cout << #NAME + std::string(" = ") << NAME << std::endl;


#include <typeinfo>
#include <iostream>
#include <string>
#include "type_list.h"
#include "meta_structs.h"
#include "meta_solver.h"
#include "matrix_macros.h"
int main()
{
	typedef MAKE_MATRIX_3_X_4(1,3,1,8,1,5,4,19,2,10,10,44) matrix_eq;
	typedef MAKE_MATRIX_4_X_5(40,8,3,1,-113,0,-2,7,11,105,0,0,2,10,54,0,0,0,8,24) matrix_eq2;
	typedef meta_matrix<4,5,matrix_eq2> my_eq2;
	my_eq2::print();
	std::cout << "solution = ";
	solve<my_eq2>::result::print();
	std::cout << std::string(80,'-') << std::endl;
	typedef meta_matrix<3,4,matrix_eq> my_eq;
	my_eq::print();
	std::cout << "solution = ";
	solve<my_eq>::result::print();

	typedef MAKE_R_MATRIX_3_X_4(1,3,6,17,2,8,16,42,5,21,45,91) matrix_eq3;
	typedef meta_matrix<3,4,matrix_eq3> my_eq3;
	my_eq3::print();
	std::cout << "solution = ";
	solve<my_eq3>::result::print();

	typedef MAKE_R_MATRIX_3_X_4(5,-1,2,3,2,4,1,8,1,3,-3,2) matrix_eq4;
	typedef meta_matrix<3,4,matrix_eq4> my_eq4;
	my_eq4::print();
	std::cout << "solution = ";
	solve<my_eq4>::result::print();
	std::cin.get();
	return 0;
}
