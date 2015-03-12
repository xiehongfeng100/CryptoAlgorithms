
// Blog: http://www.cnblogs.com/xiehongfeng100/p/4332998.html

#ifndef ISPRIME_H
#define ISPRIME_H

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

typedef unsigned int uint;

class IsPrime
{
public:
	// find prime numbers between [lower bound, upper bound)
	// method 1
	vector<uint> retPrime_1(uint lbound, uint ubound);
	bool isPrime_1(uint num);

	// method 2
	vector<uint> retPrime_2(uint lbound, uint ubound);
	bool isPrime_2(uint num);

	// method 3
	vector<uint> retPrime_3(uint lbound, uint ubound);	
	bool isPrime_3(uint num);

	// method 4
	vector<uint> retPrime_4(uint lbound, uint ubound);	
	bool isPrime_4(uint num);

	// method 5
	vector<uint> retPrime_5(uint lbound, uint ubound);	
	// bool isPrime_5(uint num);

};

//*********************************** method 1 ***********************************//
vector<uint> IsPrime::retPrime_1(uint lbound, uint ubound)
{
	assert(lbound >= 0);
	assert(ubound >= 0);
	assert(lbound <= ubound);

	vector<uint> ret;
	uint num = lbound - 1;
	uint round = ubound - lbound;
	for (uint i = 0; i < round; i++)
	{
		num++;
		if (num == 0 || num == 1)
			continue;
		else
		{
			if (isPrime_1(num))
				ret.push_back(num);
		}
	}

	return ret;
}

bool IsPrime::isPrime_1(uint num)
{
	bool ret = true;
	for (uint i = 2; i < num - 1; i++)
	{
		if (num % i == 0)
		{
			ret = false;
			break;
		}
	}

	return ret;
}

//*********************************** method 2 ***********************************//
vector<uint> IsPrime::retPrime_2(uint lbound, uint ubound)
{
	assert(lbound >= 0);
	assert(ubound >= 0);
	assert(lbound <= ubound);

	vector<uint> ret;
	uint num = lbound - 1;
	uint round = ubound - lbound;
	for (uint i = 0; i < round; i++)
	{
		num++;
		if (num == 0 || num == 1)
			continue;
		else
		{
			if (isPrime_2(num))
				ret.push_back(num);
		}
	}

	return ret;
}

bool IsPrime::isPrime_2(uint num)
{
	bool ret = true;
	uint ubound = num / 2 + 1;
	for (uint i = 2; i < ubound; i++)
	{
		if (num % i == 0)
		{
			ret = false;
			break;
		}
	}

	return ret;
}

//*********************************** method 3 ***********************************//
vector<uint> IsPrime::retPrime_3(uint lbound, uint ubound)
{
	assert(lbound >= 0);
	assert(ubound >= 0);
	assert(lbound <= ubound);

	vector<uint> ret;
	uint num = lbound - 1;
	uint round = ubound - lbound;
	for (uint i = 0; i < round; i++)
	{
		num++;
		if (num == 0 || num == 1)
			continue;
		else
		{
			if (isPrime_3(num))
				ret.push_back(num);
		}
	}

	return ret;
}

bool IsPrime::isPrime_3(uint num)
{
	bool ret = true;
	uint ubound = sqrt(num) + 1;
	for (uint i = 2; i < ubound; i++)
	{
		if (num % i == 0)
		{
			ret = false;
			break;
		}
	}

	return ret;
}

//*********************************** method 4 ***********************************//
vector<uint> IsPrime::retPrime_4(uint lbound, uint ubound)
{
	assert(lbound >= 0);
	assert(ubound >= 0);
	assert(lbound <= ubound);

	vector<uint> ret;
	uint num = lbound - 1;
	uint round = ubound - lbound;
	for (uint i = 0; i < round; i++)
	{
		num++;
		if (num == 0 || num == 1)
			continue;
		else
		{
			if (isPrime_4(num))
				ret.push_back(num);
		}
	}

	return ret;
}

bool IsPrime::isPrime_4(uint num)
{
	bool ret = true;
	if (num == 2)
		return ret;

	// it is no need to consider even numbers larger than 2
	if (num % 2 != 0)
	{
		uint ubound = sqrt(num) + 1;
		for (uint i = 2; i < ubound; i++)
		{
			if (num % i == 0)
			{
				ret = false;
				break;
			}
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

//*********************************** method 5 ***********************************//
vector<uint> IsPrime::retPrime_5(uint lbound, uint ubound)
{
	assert(lbound >= 0);
	assert(ubound >= 0);
	assert(lbound <= ubound);

	vector<bool> isprime;
	for (int i = 0; i < ubound; i++)
		isprime.push_back(true);

	for (int i = 2; i < ubound; i++)
	{
		for (int j = i + i; j < ubound; j += i)
		{
			isprime[j] = false;
		}
	}

	vector<uint> ret;
	for (int i = lbound; i < ubound; i++)
	{
		if (i != 0 && i != 1 && isprime[i])
			ret.push_back(i);
	}

	return ret;
}

//bool IsPrime::isPrime_5(uint num)
//{
//	bool ret = true;
//
//	return ret;
//}


#endif