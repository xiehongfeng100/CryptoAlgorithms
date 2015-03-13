#define BOOST_TEST_MODULE IsPrime_Test_Module

#include "stdafx.h"
#include "../IsPrime/IsPrime.hpp"

struct IsPrime_Fixture
{
	IsPrime_Fixture()
	{
		testIsPrime = new IsPrime;
	}
	~IsPrime_Fixture()
	{
		delete testIsPrime;
	}

	IsPrime * testIsPrime;
};

BOOST_FIXTURE_TEST_SUITE(IsPrime_Test_Suite, IsPrime_Fixture)


BOOST_AUTO_TEST_CASE(test_retPrime_1)
{
	uint lbound, ubound;
	vector<uint> retPrime;
	uint comPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

     // 0 - 100
	lbound = 0;
	ubound = 100;
	retPrime = testIsPrime->retPrime_1(lbound, ubound);
	for (int i = 0; i < 25; i++)
	{
		BOOST_REQUIRE(retPrime[i] == comPrime[i]);
	}

}

BOOST_AUTO_TEST_CASE(test_retPrime_2)
{
	uint lbound, ubound;
	vector<uint> retPrime;
	uint comPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	// 0 - 100
	lbound = 0;
	ubound = 100;
	retPrime = testIsPrime->retPrime_2(lbound, ubound);
	for (int i = 0; i < 25; i++)
	{
		BOOST_REQUIRE(retPrime[i] == comPrime[i]);
	}

}

BOOST_AUTO_TEST_CASE(test_retPrime_3)
{
	uint lbound, ubound;
	vector<uint> retPrime;
	uint comPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	// 0 - 100
	lbound = 0;
	ubound = 100;
	retPrime = testIsPrime->retPrime_3(lbound, ubound);
	for (int i = 0; i < 25; i++)
	{
		BOOST_REQUIRE(retPrime[i] == comPrime[i]);
	}

}

BOOST_AUTO_TEST_CASE(test_retPrime_4)
{
	uint lbound, ubound;
	vector<uint> retPrime;
	uint comPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	// 0 - 100
	lbound = 0;
	ubound = 100;
	retPrime = testIsPrime->retPrime_4(lbound, ubound);
	for (int i = 0; i < 25; i++)
	{
		BOOST_REQUIRE(retPrime[i] == comPrime[i]);
	}

}

BOOST_AUTO_TEST_CASE(test_retPrime_5)
{
	uint lbound, ubound;
	vector<uint> retPrime;
	uint comPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	// 0 - 100
	lbound = 0;
	ubound = 100;
	retPrime = testIsPrime->retPrime_5(lbound, ubound);
	for (int i = 0; i < 25; i++)
	{
		BOOST_REQUIRE(retPrime[i] == comPrime[i]);
	}

}

BOOST_AUTO_TEST_CASE(test_retPrime_6)
{
	uint lbound, ubound;
	vector<uint> retPrime;
	uint comPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	// 0 - 100
	lbound = 0;
	ubound = 100;
	retPrime = testIsPrime->retPrime_6(lbound, ubound);
	for (int i = 0; i < 25; i++)
	{
		BOOST_REQUIRE(retPrime[i] == comPrime[i]);
	}

}

BOOST_AUTO_TEST_CASE(test_retPrime_7)
{
	uint lbound, ubound;
	vector<uint> retPrime;
	uint comPrime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

	// 0 - 100
	lbound = 0;
	ubound = 100;
	retPrime = testIsPrime->retPrime_7(lbound, ubound);
	for (int i = 0; i < 25; i++)
	{
		BOOST_REQUIRE(retPrime[i] == comPrime[i]);
	}

}

BOOST_AUTO_TEST_SUITE_END()