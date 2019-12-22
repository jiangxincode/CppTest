/*
 * test.cpp
 *
 *  Created on: 2016年9月9日
 *      Author: jiang
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int maintest() {
	std::vector<int> v = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	std::cout << accumulate(v.begin(), v.end(), 0.0) << std::endl;
	return 0;
}

