#include <iostream>
#include <limits>
#include <cmath>
#include <vector>

using namespace std;
float kahanSummation(vector<float> x);
float normalSum(vector<float> x);

int main(int argc, char const *argv[])
{
	vector<float> x = {10000.0,3.14159,2.71828};
	cout<< "Kahan's Algorithm = "<< kahanSummation(x) <<endl;
	cout<< "Direct Summation = " << normalSum(x) <<endl;
	return 0;
}

float normalSum(vector<float> x){
	float sum = 0.0;
	for (int i = 0; i < 10000; ++i)
	{
		for(float i : x){
		sum = sum + i;
		}
	}
	return sum;
}

float kahanSummation(vector<float> x){
	float c = 0.0;
	float s = 0.0;
	for (int i = 0; i < 10000; ++i)
	{
		for(float i : x){
		float v = i + c;
		float sNext = s + v;
		c = v - (sNext - s);
		s = sNext;
		}
	}
	return s;

}