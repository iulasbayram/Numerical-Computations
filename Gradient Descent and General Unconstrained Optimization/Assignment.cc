#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

void gradientDescentOptimization(vector<double> &vec, double &epsilon1, double &epsilon2, int &iter_max);
void printResults(int &k, double &x1, double &x2, double &y, double &grad_y_x1, double &grad_y_x2);

int main(int argc, char const *argv[]){
	
	if(argc < 4){

		cout << "There must be 3 argument to compile this program." << endl;
		cout << "First argument has to be epsilon1." << endl;
		cout << "Second argument has to be epsilon2." << endl;
		cout << "Third argument has to be iter_max." << endl;

	}else{

		double argv1 = atof(argv[1]);
		double argv2 = atof(argv[2]);
		double argv3 = atoi(argv[3]);

		cout << "For vector x0: " << endl << endl;

		vector<double> x0 = {1.2, 1.2};

		double epsilon1 = argv1;
		double epsilon2 = argv2;
		int iter_max = argv3;

		gradientDescentOptimization(x0, epsilon1, epsilon2, iter_max);

		cout << "For vector x1: " << endl << endl;;

		vector<double> x1 = {-1.2, 1.0};

		epsilon1 = argv1;
		epsilon2 = argv2;
		iter_max = argv3;

		gradientDescentOptimization(x1, epsilon1, epsilon2, iter_max);
	}

	return 0;
}

//This method does gradient descent optimization using datas.
void gradientDescentOptimization(vector<double> &vec, double &epsilon1, double &epsilon2, int &iter_max){

	double t = pow(10.0, -3);
	vector<double> x0 = vec;
	double x1 = x0.at(0);
	double x2 = x0.at(1);
	int k = 1;
	bool control = true;

	while(k < 10000 && control){
		double prev_y = 100 * pow((x2 - x1 * x1), 2.0) + pow((1 - x1), 2.0);

		double grad_y_x1 = 400 * pow(x1, 3.0) - 400 * x1 * x2 + 2 * x1 - 2;
		double grad_y_x2 = 200 * x2 - 200 * pow(x1,2.0);

		double prev_x1 = x1;
		double prev_x2 = x2;

		x1 = x1 - t * grad_y_x1;
		x2 = x2 - t * grad_y_x2;

		double y = 100 * pow((x2 - x1 * x1), 2.0) + pow((1 - x1), 2.0);

		if (k%100 == 0){

			printResults(k, x1, x2, y, grad_y_x1, grad_y_x2);
		}

		if (abs(y - prev_y) < epsilon1){
			cout << "Epsilon 1 stopped the iteration." << endl << endl;
			cout << "Final results are; " << endl;

			printResults(k, x1, x2, y, grad_y_x1, grad_y_x2);

			control = false;

		}else if(sqrt(grad_y_x1 * grad_y_x1 + grad_y_x2 * grad_y_x2) < epsilon2){

			cout << "Epsilon 2 stopped the iteration." << endl << endl;
			cout << "Final results are; " << endl;

			printResults(k, x1, x2, y, grad_y_x1, grad_y_x2);
			
			control = false;

		}else if(k == iter_max){

			cout << "The iteration reached maximum step." << endl << endl;
			cout << "Final results are; " << endl;

			printResults(k, x1, x2, y, grad_y_x1, grad_y_x2);
			
			control = false;
		}

		k = k + 1;

	}
}

//This method prints results.
void printResults(int &k, double &x1, double &x2, double &y, double &grad_y_x1, double &grad_y_x2){

	cout << "For step " << k << ", " << endl << endl;
	cout << "x1: " << x1 << endl;
	cout << "x2: " << x2 << endl << endl;

	cout << "f(x): " << y << endl << endl;

	cout << "Gradient for x1: " << grad_y_x1 << endl;
	cout << "Gradient for x2: " << grad_y_x2 << endl << endl;

}