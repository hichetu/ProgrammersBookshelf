/*

276 Pow(x, n)
Problem:
Implement pow(x, n).
This is a great example to illustrate how to solve a problem during a technical
interview.The first and second solution exceeds time limit; the third and fourth are
accepted.

276.1 Recursive Method
Naturally, we next may think how to do it in O(logn).We have a relation that xˆn =
xˆ(n / 2) * xˆ(n / 2) * xˆ(n
	public static double pow(double x, int n) {
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	int half = n / 2;
	int remainder = n % 2;
	if (n % 2 == 1 && x < 0 && n < 0)
		return -1 / (pow(-x, half) * pow(-x, half) * pow(-x, remainder));
	else if (n < 0)
		return 1 / (pow(x, -half) * pow(x, -half) * pow(x, -remainder));
	else
		return (pow(x, half) * pow(x, half) * pow(x, remainder));
}

276.2 Accepted Solution
The accepted solution is also recursive, but does division first.Time complexity is
O(nlog(n)).The key part of solving this problem is the while loop.
public double pow(double x, int n) {
	if (n == 0)
		return 1;
	if (n == 1)
		return x;
	int pn = n > 0 ? n : -n;// positive n
	int pn2 = pn;
	double px = x > 0 ? x : -x;// positive x
	double result = px;
	int k = 1;
	//the key part of solving this problem
	while (pn / 2 > 0) {
		result = result * result;
		pn = pn / 2;
		k = k * 2;
	}
	result = result * pow(px, pn2 - k);
	// handle negative result
	if (x < 0 && n % 2 == 1)
		result = -result;
	// handle negative power
	if (n < 0)
		result = 1 / result;
	return result;
}

276.3 Best Solution
The most understandable solution I have found so far.
public double power(double x, int n) {
	if (n == 0)
		return 1;
	double v = power(x, n / 2);
	if (n % 2 == 0) {
		return v * v;
	}
	else {
		return v * v * x;
	}
}
public double pow(double x, int n) {
	if (n < 0) {
		return 1 / power(x, -n);
	}
	else {
		return power(x, n);
	}
}

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

using namespace std;

class Pow {
public:
	static double pow(double x, int n) {
		if (n < 0) return 1.0 / power(x, n);

		return power(x, n);
	}

	static double power(double x, int n) {

		if (n == 0) return 1;

		double v = power(x, n / 2);

		if (n % 2 == 0)
			return v * v;

		return v * v * x;
	}

private:
	int test() {

		double ans = Pow::pow(4, 4);
		assert(ans == 256.0);

		return 0;
	}

};