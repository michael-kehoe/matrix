#include <iostream>
#include <cstdlib>
#include <time.h>

// Define a name for the unit tests
#define BOOST_TEST_MODULE Check_Matrix

// Include unit test files
#include <boost/test/unit_test.hpp>

#include "sparsematrix.h"

////////////////////////////////////////////
//*************************************/////
#define TIMING_LOOPS 1000	      /****/////
#define TIMING_ON true	          /****/////
//*************************************/////
////////////////////////////////////////////
//     The number of loops to perform when Running the timing tests. 
//     A higher number will provide higher accuracy, but will take longer to run.
//	   If your boost test is taking too long to run, reduce this number.
//	   RUN IN RELEASE MODE
//	   TIMING_LOOPS DOES NOT AFFECT DETERMINANT CALCULATION, IF IT IS RUNNING TOO LONG, COMMENT OUT THE LARGE DETERMINANT TEST (HIGHLIGHTED AT BOTTOM)
//     TO TURN OFF THE TIMING TEST, SET 'TIMING_ON' TO false

#pragma region Construct_tests
BOOST_AUTO_TEST_CASE(Basic_Constructor_1)
{
	SparseMatrix m;
	BOOST_CHECK_EQUAL(m.col_count,0);
	BOOST_CHECK_EQUAL(m.row_count,0);
	BOOST_CHECK_EQUAL(m.longest_column,0);
	BOOST_CHECK_EQUAL(m.num_elements,0);
	BOOST_CHECK_EQUAL(m.isSquare(),false);
	
	BOOST_CHECK_EQUAL(m.colCount(), 0);
	BOOST_CHECK_EQUAL(m.rowCount(), 0);
}

BOOST_AUTO_TEST_CASE(Basic_Constructor_2)
{
	SparseMatrix m(0,0);
	BOOST_CHECK_EQUAL(m.col_count,0);
	BOOST_CHECK_EQUAL(m.row_count,0);
	BOOST_CHECK_EQUAL(m.longest_column,0);
	BOOST_CHECK_EQUAL(m.isSquare(),false);
	BOOST_CHECK_EQUAL(m.num_elements,0);
	BOOST_CHECK_EQUAL(m.colCount(), 0);
	BOOST_CHECK_EQUAL(m.rowCount(), 0);
	
	SparseMatrix m2(1,1);
	BOOST_CHECK_EQUAL(m2.col_count,1);
	BOOST_CHECK_EQUAL(m2.row_count,1);
	BOOST_CHECK_EQUAL(m2.longest_column,1);
	BOOST_CHECK_EQUAL(m2.is_null,true);
	BOOST_CHECK_EQUAL(m2.isSquare(),true);
	BOOST_CHECK_EQUAL(m2.num_elements,0);
	BOOST_CHECK_EQUAL(m2.colCount(), 1);
	BOOST_CHECK_EQUAL(m2.rowCount(), 1);

	SparseMatrix m3(2,2);
	BOOST_CHECK_EQUAL(m3.col_count,2);
	BOOST_CHECK_EQUAL(m3.row_count,2);
	BOOST_CHECK_EQUAL(m3.longest_column,2);
	BOOST_CHECK_EQUAL(m3.is_null,true);
	BOOST_CHECK_EQUAL(m3.isSquare(),true);
	BOOST_CHECK_EQUAL(m3.num_elements,0);
	BOOST_CHECK_EQUAL(m3.colCount(), 2);
	BOOST_CHECK_EQUAL(m3.rowCount(), 2);

	SparseMatrix m4(3,2);
	BOOST_CHECK_EQUAL(m4.col_count,2);
	BOOST_CHECK_EQUAL(m4.row_count,3);
	BOOST_CHECK_EQUAL(m4.longest_column,2);
	BOOST_CHECK_EQUAL(m4.is_null,true);
	BOOST_CHECK_EQUAL(m4.isSquare(),false);
	BOOST_CHECK_EQUAL(m4.num_elements,0);
	BOOST_CHECK_EQUAL(m4.colCount(), 2);
	BOOST_CHECK_EQUAL(m4.rowCount(), 3);
}
BOOST_AUTO_TEST_CASE(Basic_Constructor_2_2)
{
	SparseMatrix m(1000000000,1000000000);
	BOOST_CHECK_EQUAL(m.colCount(), 1000000000);
	BOOST_CHECK_EQUAL(m.rowCount(), 1000000000);

	SparseMatrix m2(m);
	BOOST_CHECK_EQUAL(m2.colCount(), 1000000000);
	BOOST_CHECK_EQUAL(m2.rowCount(), 1000000000);

	SparseMatrix m5(0,0);
	BOOST_CHECK(m5.isNull());
}


BOOST_AUTO_TEST_CASE(Basic_Constructor_3)
{
	SparseMatrix m(0,0);
	SparseMatrix m5(m);
	BOOST_CHECK_EQUAL(m5.col_count,0);
	BOOST_CHECK_EQUAL(m5.row_count,0);
	BOOST_CHECK_EQUAL(m5.longest_column,0);
	BOOST_CHECK_EQUAL(m5.isSquare(),false);
	BOOST_CHECK_EQUAL(m5.num_elements,0);
	BOOST_CHECK_EQUAL(m5.colCount(), 0);
	BOOST_CHECK_EQUAL(m5.rowCount(), 0);

	
	SparseMatrix m2(1,1);
	SparseMatrix m6(m2);
	BOOST_CHECK_EQUAL(m6.col_count,1);
	BOOST_CHECK_EQUAL(m6.row_count,1);
	BOOST_CHECK_EQUAL(m6.longest_column,1);
	BOOST_CHECK_EQUAL(m6.isSquare(),true);
	BOOST_CHECK_EQUAL(m6.num_elements,0);
	BOOST_CHECK_EQUAL(m6.colCount(), 1);
	BOOST_CHECK_EQUAL(m6.rowCount(), 1);

	SparseMatrix m3(2,2);
	SparseMatrix m7(m3);
	BOOST_CHECK_EQUAL(m7.col_count,2);
	BOOST_CHECK_EQUAL(m7.row_count,2);
	BOOST_CHECK_EQUAL(m7.longest_column,2);
	BOOST_CHECK_EQUAL(m7.isSquare(),true);
	BOOST_CHECK_EQUAL(m7.num_elements,0);
	BOOST_CHECK_EQUAL(m7.colCount(), 2);
	BOOST_CHECK_EQUAL(m7.rowCount(), 2);

	SparseMatrix m4(3,2);
	SparseMatrix m8(m4);
	BOOST_CHECK_EQUAL(m8.col_count,2);
	BOOST_CHECK_EQUAL(m8.row_count,3);
	BOOST_CHECK_EQUAL(m8.longest_column,2);
	BOOST_CHECK_EQUAL(m8.isSquare(),false);
	BOOST_CHECK_EQUAL(m8.num_elements,0);
	BOOST_CHECK_EQUAL(m8.colCount(), 2);
	BOOST_CHECK_EQUAL(m8.rowCount(), 3);
}


BOOST_AUTO_TEST_CASE(String_Constructor_1)
{
	//simple
	SparseMatrix m11("2 3 ; 4 5");
	BOOST_CHECK_EQUAL(m11(0,0), 2);
	BOOST_CHECK_EQUAL(m11(0,1), 3);
	BOOST_CHECK_EQUAL(m11(1,0), 4);
	BOOST_CHECK_EQUAL( m11(1,1), 5);
	BOOST_CHECK_EQUAL( m11.colCount(), 2);
	BOOST_CHECK_EQUAL( m11.rowCount(), 2);
	BOOST_CHECK_EQUAL( m11.longest_column, 2);
	BOOST_CHECK_EQUAL( m11.is_null, false);
	BOOST_CHECK_EQUAL( m11.isSquare(), true);
	BOOST_CHECK_EQUAL(m11.str(),"2 3 ; 4 5");


	SparseMatrix m12("0 3 ; 4 0");
	BOOST_CHECK_EQUAL( m12(0,0), 0);
	BOOST_CHECK_EQUAL( m12(0,1), 3);
	BOOST_CHECK_EQUAL( m12(1,0), 4);
	BOOST_CHECK_EQUAL( m12(1,1), 0);
	BOOST_CHECK_EQUAL( m12.colCount(), 2);
	BOOST_CHECK_EQUAL( m12.rowCount(), 2);
	BOOST_CHECK_EQUAL( m12.longest_column, 2);

	BOOST_CHECK_EQUAL( m12.isSquare(), true);
	BOOST_CHECK_EQUAL(m12.str(),"0 3 ; 4 0");

	SparseMatrix m13("0 ; 4 0");
	BOOST_CHECK_EQUAL( m13(0,0), 0);
	BOOST_CHECK_EQUAL( m13(0,1), 0);
	BOOST_CHECK_EQUAL( m13(1,0), 4);
	BOOST_CHECK_EQUAL( m13(1,1), 0);
	BOOST_CHECK_EQUAL( m13.colCount(), 2);
	BOOST_CHECK_EQUAL( m13.rowCount(), 2);
	BOOST_CHECK_EQUAL( m13.longest_column, 2);
	BOOST_CHECK_EQUAL( m13.is_null, false);
	BOOST_CHECK_EQUAL( m13.isNull(), false);
	BOOST_CHECK_EQUAL( m13.isSquare(), true);
	BOOST_CHECK_EQUAL(m13.str(),"0 0 ; 4 0");

}
BOOST_AUTO_TEST_CASE(String_Constructor_2)
{
	//negative numbers
	SparseMatrix m("; 1 0 0 0 0 0 11 ; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK_EQUAL(m.colCount(), 8);
	BOOST_CHECK_EQUAL(m.rowCount(), 9);
	BOOST_CHECK_EQUAL(m.longest_column, 8);
	BOOST_CHECK_EQUAL(m(2,1),-1);
	BOOST_CHECK_EQUAL( m.isSquare(), false);

	//No space between 11 and ;
	SparseMatrix m3("; 1 0 0 0 0 0 11; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK(m3.isNull());

	////invalid character
	SparseMatrix m5("; 1 0 0 0 0 0 11 ; 0 -1 0 0 0 A 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK(m5.isNull());	

	// Space at start
	SparseMatrix m8(" ; 1 0 0 0  0 0 11 ; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK(m8.isNull());

	// Space at end
	SparseMatrix m9("1 0 0 0 0 0 11 ; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1 ");
	BOOST_CHECK(m9.isNull());

	// No Values
	SparseMatrix m10("; ; ; ; ;");
	BOOST_CHECK(m10.isNull());
}
BOOST_AUTO_TEST_CASE(str_output0)
{
	SparseMatrix m("1 0 3 ; 0 1 0 0 0 ; 5 2 ; ; 5");
	BOOST_CHECK_EQUAL(m.str(), "1 0 3 0 0 ; 0 1 0 0 0 ; 5 2 0 0 0 ; 0 0 0 0 0 ; 5 0 0 0 0");
	m.set(2,4,-3);
	m.set(4,3,2);
	BOOST_CHECK_EQUAL(m.str(), "1 0 3 0 0 ; 0 1 0 0 0 ; 5 2 0 0 -3 ; 0 0 0 0 0 ; 5 0 0 2 0");
}
#pragma endregion Construct_tests

#pragma region set_tests
BOOST_AUTO_TEST_CASE(Set)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	m.set(0,0,0);
	BOOST_CHECK_EQUAL(m(0,0),0);

	m.set(1,1,55);
	BOOST_CHECK_EQUAL(m(1,1),55);
	
	m.set(2,2,-123);
	BOOST_CHECK_EQUAL(m(2,2),-123);
	
	m.set(0,2,0);
	BOOST_CHECK_EQUAL(m(0,2),0);
	
	SparseMatrix m2("0 2 ; 5 55 6 ; 7 6 -123");
	BOOST_CHECK_EQUAL(m2.str(), "0 2 0 ; 5 55 6 ; 7 6 -123");
	
	m2.set(0,1,0);
	BOOST_CHECK_EQUAL(m2(0,1),0);
	
	m2.set(1,0,0);
	BOOST_CHECK_EQUAL(m2(1,0),0);
	
	m2.set(1,1,0);
	BOOST_CHECK_EQUAL(m2(1,1),0);
	
	m2.set(1,2,0);
	BOOST_CHECK_EQUAL(m2(1,2),0);
	
	m2.set(2,0,0);
	BOOST_CHECK_EQUAL(m2(2,0),0);
	
	m2.set(2,1,0);
	BOOST_CHECK_EQUAL(m2(2,1),0);
	
	m2.set(2,2,0);
	BOOST_CHECK_EQUAL(m2(2,2),0);
	
	SparseMatrix m3(3,3);
	BOOST_CHECK_THROW(m3.set(2,5,9), InvalidMatrixSize);
}
#pragma endregion set_tests

#pragma region Assignment
BOOST_AUTO_TEST_CASE(Assigning)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	SparseMatrix m3(5,2);
	m3 = m;
	BOOST_CHECK_EQUAL(m3.str(), m.str());
}
#pragma endregion Assignment

#pragma region ==Operator
BOOST_AUTO_TEST_CASE(equals)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	SparseMatrix m3(5,2);
	m3 = m;
	BOOST_CHECK(m3 == m);
}
#pragma endregion ==Operator

BOOST_AUTO_TEST_CASE(CoreTest)
{
	SparseMatrix m(100, 100);
	m.set(0,8, 10.1);
	m.set(99,99, 110.1);
	SparseMatrix m2(100, 100);
	m2.set(8,0, 10.1);
	m2.set(99,99, 110.1);
	SparseMatrix m3 = m + m2;
	SparseMatrix m4(100, 100);
	m4.set(0,8, 10.1);
	m4.set(8,0,10.1);
	m4.set(99,99,220.2);
	BOOST_CHECK(m4 == m3);

	m3 = m - m2;

	m4.set(8,0,-10.1);
	m4.set(99,99,0);
	BOOST_CHECK(m4 == m3);
	BOOST_CHECK_EQUAL(m4(99,99), 0);
	SparseMatrix m5 = m * m2;
	SparseMatrix m6 = m * 3;
	double detofm = m.determinant();
	BOOST_CHECK_EQUAL(detofm,0);
	SparseMatrix m7(m);
	m7.transpose();
	SparseMatrix m8(1000000, 2000000);
	m8.set(999999,999999, -17);
	SparseMatrix m9("1 0 ; 0 1");
	BOOST_CHECK_EQUAL(m9.isNull(), false);
	BOOST_CHECK_EQUAL(m9(0,0), 1);
	BOOST_CHECK_EQUAL(m9.rowCount(), 2);
	BOOST_CHECK_EQUAL(m9.colCount(), 2);
	BOOST_CHECK(m9.isSquare());
	SparseMatrix m10(m9);
	m10.transpose();
	BOOST_CHECK(m9 == m10);
	BOOST_CHECK_EQUAL(m10.str(),"1 0 ; 0 1");
}

BOOST_AUTO_TEST_CASE(constructor_1)
{
	SparseMatrix m;
	BOOST_CHECK(m.isNull());
	BOOST_CHECK_EQUAL(m.colCount(), 0);
	BOOST_CHECK_EQUAL(m.rowCount(), 0);
}

BOOST_AUTO_TEST_CASE(constructor_2_3)
{
	SparseMatrix m(1000000000,1000000000);
	BOOST_CHECK_EQUAL(m.colCount(), 1000000000);
	BOOST_CHECK_EQUAL(m.rowCount(), 1000000000);

	SparseMatrix m2(m);
	BOOST_CHECK_EQUAL(m2.colCount(), 1000000000);
	BOOST_CHECK_EQUAL(m2.rowCount(), 1000000000);

	BOOST_CHECK(m == m2);

	SparseMatrix m3(5,0);
	BOOST_CHECK(m3.isNull());

	SparseMatrix m4(0,5);
	BOOST_CHECK(m4.isNull());

	SparseMatrix m5(0,0);
	BOOST_CHECK(m5.isNull());

}

BOOST_AUTO_TEST_CASE(constructor_4)
{
	//simple
	SparseMatrix m11("2 3 ; 4 5");
	BOOST_CHECK_EQUAL( m11(0,0), 2);
	BOOST_CHECK_EQUAL( m11(0,1), 3);
	BOOST_CHECK_EQUAL( m11(1,0), 4);
	BOOST_CHECK_EQUAL( m11(1,1), 5);
	BOOST_CHECK_EQUAL( m11.colCount(), 2);
	BOOST_CHECK_EQUAL( m11.rowCount(), 2);
	
	//negative numbers
	SparseMatrix m("; 1 0 0 0 0 0 11 ; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK_EQUAL(m.colCount(), 8);
	BOOST_CHECK_EQUAL(m.rowCount(), 9);
	BOOST_CHECK_EQUAL(m(2,1),-1);

	//No space between 11 and ;
	SparseMatrix m3("; 1 0 0 0 0 0 11; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK(m3.isNull());

	//invalid character
	SparseMatrix m5("; 1 0 0 0 0 0 11 ; 0 -1 0 0 0 A 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK(m5.isNull());	

	// Space at start
	SparseMatrix m8(" ; 1 0 0 0  0 0 11 ; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1");
	BOOST_CHECK(m8.isNull());

	// Space at end
	SparseMatrix m9("1 0 0 0 0 0 11 ; 0 -1 0 0 0 0 20 ; 0 1 ; 0 0 0 5 ; 0 -0 0 3 45 ; 6 0 0 0 0 2 ; ; 0 0 10 0 0 0 0 1 ");
	BOOST_CHECK(m9.isNull());

	// No Values
	SparseMatrix m10("; ; ; ; ;");
	BOOST_CHECK(m10.isNull());
}



BOOST_AUTO_TEST_CASE(is_square)
{
	SparseMatrix m(2,2);
	BOOST_CHECK(m.isSquare());

	SparseMatrix m2(2,5);
	BOOST_CHECK_EQUAL(m2.isSquare(), false);

	//not 100% about this, is a null matrix square? I say not.
	SparseMatrix m3;
	BOOST_CHECK(!m3.isSquare());
}

BOOST_AUTO_TEST_CASE(transpose)
{
	SparseMatrix m("1 0 3 ; 0 1 0 0 0 0 0 0 0 0 0 ; -5 2 ; ; 5");	
	SparseMatrix m2(m.transpose());


	BOOST_CHECK_EQUAL(m2(1,1), 1);
	BOOST_CHECK_EQUAL(m2(0,2), -5);
	BOOST_CHECK_EQUAL(m2.rowCount(), 11);
	BOOST_CHECK_EQUAL(m2.colCount(), 5);

	SparseMatrix m3= (m2.transpose());

	SparseMatrix m4("1 2 3 ; 4 5 6");	
	SparseMatrix m5(m4.transpose());
	SparseMatrix m6= (m5.transpose());
	BOOST_CHECK(m == m3);

}

BOOST_AUTO_TEST_CASE(Addition)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	SparseMatrix m2("1 8 1 ; 3 0 6 ; 0 6 0");
	SparseMatrix m4("2 10 4 ; 8 -8 12 ; 7 12 -2");
	SparseMatrix m3(m+m2);
	BOOST_CHECK(m4 == m3);

	SparseMatrix m5("1 2 3 ; 3 4 5");
	BOOST_CHECK_THROW(m3+m5, InvalidMatrixSize);
}
BOOST_AUTO_TEST_CASE(subtraction)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	SparseMatrix m2("1 8 1 ; 3 0 -6 ; 0 6 -2");
	SparseMatrix m4("0 -6 2 ; 2 -8 12 ; 7 0 0");
	SparseMatrix m3(m-m2);
	BOOST_CHECK(m4 == m3);

	SparseMatrix m5("1 2 3 ; 3 4 5");
	BOOST_CHECK_THROW(m3-m5, InvalidMatrixSize);

	SparseMatrix m7(m-m);
	SparseMatrix m8(3,3);
	BOOST_CHECK(m7 == m8);
}
BOOST_AUTO_TEST_CASE(Matrix_Multiplication_result)
{
	SparseMatrix m0("3 5 ; 2 7");
	SparseMatrix m00("4 9 ; 1 6");
	SparseMatrix r0("17 57 ; 15 60");
	
	BOOST_CHECK(r0 == (m0*m00));
	
	SparseMatrix m1("3 5 9 ; 2 7 -3 ; 0 0 0");
	SparseMatrix m2("4 9 0 ; 0 0 0 ; 1 9 2");
	SparseMatrix r1("21 108 18 ; 5 -9 -6 ; 0 0 0");
	BOOST_CHECK(r1 == (m1*m2));
	SparseMatrix r2("30 83 9 ; 0 0 0 ; 21 68 -18");
	BOOST_CHECK(r2 == (m2*m1));

	SparseMatrix m3("1 2 3 4");
	SparseMatrix r3("30");
	BOOST_CHECK(r3 == (m3*(m3.transpose())));
	SparseMatrix r4("1 2 3 4 ; 2 4 6 8 ; 3 6 9 12 ; 4 8 12 16");
	BOOST_CHECK(r4 == ((m3.transpose())*m3));
	BOOST_CHECK_THROW(m3*m3, InvalidMatrixSize);

	SparseMatrix I("1 0 0 ; 0 1 0 ; 0 0 1");
	SparseMatrix r5(m1*I);
	SparseMatrix r6(I*m1);
	BOOST_CHECK(m1 == r5);
	BOOST_CHECK(m1 == r6);

	SparseMatrix Z("0 0 0 ; 0 0 0 ; 0 0 0");
	SparseMatrix r7(3,3);
	BOOST_CHECK(m1*Z == Z && m1*Z == r7);
}

BOOST_AUTO_TEST_CASE(Scalar_Multiplication)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	SparseMatrix r1(3,3);
	SparseMatrix r2("2 4 6 ; 10 -16 12 ; 14 12 -4");
	SparseMatrix r3("-1 -2 -3 ; -5 8 -6 ; -7 -6 2");
	BOOST_CHECK(m*0 == r1);
	BOOST_CHECK(r2 == m*2);
	BOOST_CHECK(r3 == m*-1);
}

BOOST_AUTO_TEST_CASE(multiple_operations)
{
	SparseMatrix m(3,3);
	BOOST_CHECK(m+m+m-m == m);

	SparseMatrix m2("1 2 3 ; 4 5 6 ; 7 8 9");
	BOOST_CHECK( ((m2*2) - m2) == m2);

	BOOST_CHECK( (m2-m2) == m);

	BOOST_CHECK( (m2+m2-m)*m2.determinant() == m);

	SparseMatrix m3;
	BOOST_CHECK_THROW(m3.determinant(), InvalidMatrixSize);
}

BOOST_AUTO_TEST_CASE(Assigning5)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	SparseMatrix m3(5,2);
	m3 = m;
	BOOST_CHECK(m3 == m);
	m3 = m*2;
	m3 = m3*m;	
	m3 = m*(m3*(m+m));
	BOOST_CHECK_EQUAL( m3.str(), "5036 616 2628 ; -164 56792 -30528 ; 7268 -31096 23992");
}

BOOST_AUTO_TEST_CASE(Set3)
{
	SparseMatrix m("1 2 3 ; 5 -8 6 ; 7 6 -2");
	m.set(0,0,0);
	m.set(1,1,55);
	m.set(2,2,-123);
	m.set(0,2,0);
	SparseMatrix m2("0 2 ; 5 55 6 ; 7 6 -123");
	BOOST_CHECK(m==m2);
	m2.set(0,1,0);
	m2.set(1,0,0);
	m2.set(1,1,0);
	m2.set(1,2,0);
	m2.set(2,0,0);
	m2.set(2,1,0);
	m2.set(2,2,0);
	SparseMatrix m3(3,3);
	BOOST_CHECK(m2==m3);
	BOOST_CHECK_THROW(m3.set(2,5,9), InvalidMatrixSize);
}

BOOST_AUTO_TEST_CASE(str_output)
{
	SparseMatrix m("1 0 3 ; 0 1 0 0 0 ; 5 2 ; ; 5");
	BOOST_CHECK_EQUAL(m.str(), "1 0 3 0 0 ; 0 1 0 0 0 ; 5 2 0 0 0 ; 0 0 0 0 0 ; 5 0 0 0 0");
	m.set(2,4,-3);
	m.set(4,3,2);
	BOOST_CHECK_EQUAL(m.str(), "1 0 3 0 0 ; 0 1 0 0 0 ; 5 2 0 0 -3 ; 0 0 0 0 0 ; 5 0 0 2 0");
	BOOST_CHECK_EQUAL( m.transpose().str(), "1 0 5 0 5 ; 0 1 2 0 0 ; 3 0 0 0 0 ; 0 0 0 0 2 ; 0 0 -3 0 0");
}

BOOST_AUTO_TEST_CASE(determinant)
{
	SparseMatrix m0("1 2 ; 4 1");
	BOOST_CHECK_EQUAL(m0.determinant(), -7);

	SparseMatrix m1("1 2 ; 4 1 0 2 ; ; 3");
	BOOST_CHECK_EQUAL(m1.determinant(), 0);

	SparseMatrix m8("1 2 3 ; 3 -4 5 ; 5 6 7");
	BOOST_CHECK_EQUAL(m8.determinant(), 64);

	SparseMatrix m9("5 3 4 5 1 ; 8 6 7 1 3 ; 6 7 5 6 4 ; 5 6 7 2 6 ; 1 2 4 4 6");
	double  d = m9.determinant();
	m9.minor(1,1);
	BOOST_CHECK_EQUAL(d, -554);

	//determinant of a null matrix?
	SparseMatrix m3(2,4);
	BOOST_CHECK_THROW(m3.determinant(), InvalidMatrixSize);

}

BOOST_AUTO_TEST_CASE(Matrix_Operations_Timed)
{
	if(TIMING_ON)
	{
		srand ( rand() );

		SparseMatrix m(100000000,100000000);
		SparseMatrix m2(100000000, 100000000);
		for(int i = 0; i < 100 ; i++)
		{
			m.set((long)rand(), (long)rand(), (double)rand());
		}
		for(int j = 0; j < 100 ; j++)
		{
			m2.set((long)rand()*3050, (long)rand()*3050, (double)rand());
		}
		clock_t t1, t2;

		t1 = clock();
		for(int i = 0; i < TIMING_LOOPS ; i++)
		{
			(m*m2);
		}
		t2 = clock();
		std::cout << "100,000,000 x 100,000,000 Matrix Multiplication with 100 values each: " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(1000/TIMING_LOOPS) << "ms" << std::endl;
	

		t1 = clock();
		for(int i = 0; i < TIMING_LOOPS; i++)
		{
			m.transpose();
		}
		t2 = clock();
		std::cout << "100,000,000 x 100,000,000 Transpose with 100 values: " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(1000/TIMING_LOOPS) << "ms" << std::endl;	

		for(int i = 0; i < 400 ; i++)
		{
			m.set((long)rand(), (long)rand(), (double)rand());
		}
		for(int j = 0; j < 400 ; j++)
		{
			m2.set((long)rand()*3050, (long)rand()*3050, (double)rand());
		}
		t1 = clock();
		for(int i = 0; i < TIMING_LOOPS; i++)
		{
			(m*m2);
		}
		t2 = clock();
		std::cout << "100,000,000 x 100,000,000 Matrix Multiplication with 500 values each: " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(1000/TIMING_LOOPS) << "ms" << std::endl;	
		for(int i = 0; i < 500 ; i++)
		{
			m.set((long)rand(), (long)rand(), (double)rand());
		}
		for(int j = 0; j < 500 ; j++)
		{
			m2.set((long)rand()*3050, (long)rand()*3050, (double)rand());
		}
		t1 = clock();
		for(int i = 0; i < TIMING_LOOPS; i++)
		{
			(m*m2);
		}
		t2 = clock();
		std::cout << "100,000,000 x 100,000,000 Matrix Multiplication with 1000 values each: " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(1000/TIMING_LOOPS) << "ms" << std::endl;		
	
		for(int i = 0; i < TIMING_LOOPS; i++)
		{
			m2.determinant();
		}
		t2 = clock();
		std::cout << "100,000,000 x 100,000,000 Sparse Determinant: " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(1000/TIMING_LOOPS) << "ms" << std::endl;

		t1 = clock();
		for(int i = 0; i < (TIMING_LOOPS/10); i++)
		{
			m.transpose();
		}
		t2 = clock();
		std::cout << "100,000,000 x 100,000,000 Transpose with 1000 values: " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(10000/TIMING_LOOPS) << "ms" << std::endl;	

		SparseMatrix m3("1 50 80 -9 1 0 11 8 73 ; 0 -1 0 9 0 2 20 -8 20 ; 0 1 -1 -1 -1 ; 0 10 0 5 ; 0 -0 0 3 -45 ; 6 0 0 16 0 2 ; 2 5 7 ; 1 0 10 0 2 0 0 1 7 22 ; 1 2 3 4 5 6 7 8 9 10 ; 1 2 3 4 5 6 7 8 9 9");
		t1=clock();
		double testdet = m3.determinant();
		t2=clock();
		std::cout << "10 x 10 Determinant (Some Zeroes): " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(1000) << "ms" << std::endl;
		BOOST_CHECK_EQUAL(testdet, -81840);

		///////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////
		std::cout << "Don't freak, the next test could take a while (~10 secs?)" << std::endl;
		SparseMatrix m4("1 2 3 4 5 6 7 8 9 10 ; 11 12 13 14 15 16 17 18 19 20 ; 21 22 23 24 25 26 27 28 29 30 ; 31 32 33 34 35 36 37 38 39 40 ; 41 42 43 44 45 46 47 48 49 50 ; 51 52 53 54 55 56 57 58 59 60 ; 61 62 63 64 65 66 67 68 69 70 ; 71 72 73 74 75 76 77 78 79 80 ; 81 82 83 84 85 86 87 88 89 90 ; 91 92 93 94 95 96 97 98 99 100");
		t1=clock();
		testdet = m4.determinant();
		t2=clock();
		std::cout << "10 x 10 Determinant (No Zeroes): " << ((float)(t2-t1)/((float)CLOCKS_PER_SEC))*(1000) << "ms" << std::endl;
		BOOST_CHECK_EQUAL(testdet, 0);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}

typedef SparseMatrix Matrix;

BOOST_AUTO_TEST_CASE(testConstructorsDestructors) {
	// check null constructor
	Matrix empty;
	BOOST_CHECK(empty.isNull());
	BOOST_CHECK(empty.rowCount() == 0);
	BOOST_CHECK(empty.colCount() == 0);

	Matrix *emptyPtr = new Matrix();
	BOOST_CHECK(emptyPtr->isNull());
	BOOST_CHECK(emptyPtr->rowCount() == 0);
	BOOST_CHECK(emptyPtr->colCount() == 0);
	delete emptyPtr;

	// check standard constructor
	Matrix m1(10,10);
	m1.set(0,0, 7.0);
	m1.set(1,1, 7.0);
	m1.set(2,2, -10000.0);

	BOOST_CHECK_EQUAL(m1.isNull(), false);
	BOOST_CHECK_EQUAL(m1.rowCount(), 10);
	BOOST_CHECK_EQUAL(m1.colCount(), 10);

	BOOST_CHECK_EQUAL(m1(0,0), 7);
	BOOST_CHECK_EQUAL(m1(0,1), 0);
	BOOST_CHECK_EQUAL(m1(1,1), 7);
	BOOST_CHECK_EQUAL(m1(2,2), -10000);
	BOOST_CHECK_EQUAL(m1(9,9), 0);


	// check copy constructor
	Matrix m1copy1(m1);
	Matrix m1copy2 = m1;

	BOOST_CHECK_EQUAL(m1copy1.isNull(), false);
	BOOST_CHECK_EQUAL(m1copy1.rowCount(), 10);
	BOOST_CHECK_EQUAL(m1copy1.colCount(), 10);
	
	BOOST_CHECK_EQUAL(m1copy2.isNull(), false);
	BOOST_CHECK_EQUAL(m1copy2.rowCount(), 10);
	BOOST_CHECK_EQUAL(m1copy2.colCount(), 10);
	
	// check string constructor

}

BOOST_AUTO_TEST_CASE(CheckExceptions) {
	Matrix m(10,10);

	// test set out of bounds
	BOOST_REQUIRE_THROW(m.set(10, 0, 5), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m.set(10, 10, 5), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m.set(0, 10, 5), InvalidMatrixSize);

	BOOST_REQUIRE_THROW(m.set(-1, 10, 5), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m.set(-1, 0, 5), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m.set(-1, -50, 5), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m.set(5, -1, 5), InvalidMatrixSize);

	// test () out of bounds
	BOOST_REQUIRE_THROW(m(10, 0), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m(10, 10), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m(0, 10), InvalidMatrixSize);

	BOOST_REQUIRE_THROW(m(-1, 10), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m(-1, 0), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m(-1, -50), InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m(5, -1), InvalidMatrixSize);

	// test determinant with non-square matrix
	Matrix m2(2,4);
	BOOST_REQUIRE_THROW(m2.determinant(), InvalidMatrixSize);

	// test +, - with non-similar matrices
	BOOST_REQUIRE_THROW(m + m2, InvalidMatrixSize);
	BOOST_REQUIRE_THROW(m - m2, InvalidMatrixSize);

	// test matrix mult with wrong sides
	// (remember: need to have (m x n) * (n * x))
	BOOST_REQUIRE_THROW(m * m2, InvalidMatrixSize);

}


BOOST_AUTO_TEST_CASE(testDeterminant) {

	// check a simple 2x2 matrix
	SparseMatrix m("1 2 ; 3 4");
	BOOST_CHECK_EQUAL(m.determinant(), 1*4-2*3);

	// test some 3x3 matrices
	SparseMatrix m2("1 2 3 ; 4 5 6 ; 7 8 9");
	BOOST_CHECK_EQUAL(m2.determinant(), 0);

	SparseMatrix m3("1 2 3 ; 4 5 6 ; 7 8 10");
	BOOST_CHECK_EQUAL(m3.determinant(), -3);

	SparseMatrix m4("0 0 2 ; 1 2 4 ; 9 9 8");
	BOOST_CHECK_EQUAL(m4.determinant(), -18);


	// test a huge matrix which is 0
	SparseMatrix ml1(100000, 100000);
	long sum = 0;
	for (long i = 0; i < 99999; ++i) {
		ml1.set(i, i, i+1);
	}

	BOOST_CHECK_EQUAL(ml1.determinant(), 0);
}

BOOST_AUTO_TEST_CASE(testMatrixMult) {
	// some timing variables
	clock_t t1, t2;
	int NUM_TESTS = 1000;
	
	// small matrix test
	SparseMatrix m("1 2 3 ; 4 5 6 ; 7 8 9");
	SparseMatrix m2(m);

	SparseMatrix m3 = m * m2;
	BOOST_CHECK_EQUAL(m3.str(),	"30 36 42 ; 66 81 96 ; 102 126 150");

	// large matrix test 1
	SparseMatrix ml(100000000, 100000000);
	SparseMatrix ml2(100000000, 100000000);
	for (long i = 0; i < 50; ++i) {
		ml.set(0, i, i+1);
		ml2.set(0, i, -1.5*(i+1));
		
		ml.set(1, i, 2*(i+1));
		ml2.set(1, i, -1.5*2*(i+1));
	}


	SparseMatrix mlr = ml * ml2;
	for (long i = 1; i <= 50; ++i) {
		// should be only getting nonzero elems here
		BOOST_CHECK_EQUAL(mlr(0,i-1), -1.5*i+2*-3*i);
		BOOST_CHECK_EQUAL(mlr(1,i-1), 2*(-1.5*i+2*-3*i));
		
		// check getting zeros elsewhere
		BOOST_CHECK_EQUAL(mlr(2,i-1), 0);
		BOOST_CHECK_EQUAL(mlr(99999999,i-1), 0);
	}

	// time for large matrix test 1
	t1 = clock();
	for (int i = 0; i < NUM_TESTS; ++i) {
		ml*ml2;
	}
	t2 = clock();

	std::cout << double(t2-t1) << "tics = " <<
		(double(t2-t1))/CLOCKS_PER_SEC << " secs = " <<
		1000*double(t2-t1)/(NUM_TESTS*CLOCKS_PER_SEC) <<
		"ms to complete large matrix test 1" << std::endl;

	// large matrix test 2
	SparseMatrix ml3(100000000, 100000000);
	SparseMatrix ml4(100000000, 100000000);
	for (long i = 0; i < 100; ++i) {
		ml3.set(0, i, i+1);

		ml4.set(i, 1, i+1);
		ml4.set(i, 2, 6554-0.5*(i+1));
	}

	SparseMatrix mlr2 = ml3 * ml4;

	BOOST_CHECK_EQUAL(mlr2(0, 1), 338350);
	BOOST_CHECK_EQUAL(mlr2(0, 2), 32928525);

	
	// time for large matrix test 1
	t1 = clock();
	for (int i = 0; i < NUM_TESTS; ++i) {
		mlr2 = ml3*ml4;
	}
	t2 = clock();

	std::cout << 1000*double(t2-t1)/(NUM_TESTS*CLOCKS_PER_SEC) <<
		"ms to complete large matrix test 2" << std::endl;
	
}
