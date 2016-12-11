#ifndef ___PRINTE___VECTOR____H___
#define ___PRINTE___VECTOR____H___

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void print(const vector<T>& vec) {

	cout << " { ";

	if (vec.size()) {
		cout << vec[0];
	}

	for (size_t i = 1; i < vec.size(); ++i) {
		cout << ", " << vec[i];
	}

	cout << " } ";	
}

#endif // !___PRINTE___VECTOR____H___

