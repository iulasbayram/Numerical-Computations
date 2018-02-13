#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cmath>
#include <utility>
#include <string>
#include "Eigen/Dense" //This code works on my computer with "eigen3/Eigen/.." for eigen library.
#include "Eigen/Eigenvalues" 
#include "Eigen/QR"
using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using Eigen::EigenSolver;
using Eigen::HouseholderQR;
using Eigen::Vector3f;
using Eigen::Matrix3f;

int main(int argc, char const *argv[]){
	

	//Below that, there is an if-else condition to check data file is null or not.
	if(argc < 2){

		cout << "The first argument must be DATA file." << endl;
 	
 	}else{

  		/*"-------------------Beginning of data operations------------------------"*/

 		   string text = argv[1];

  		ifstream inFile(argv[1]);

  		//Below that, another if-else condition to check data file exists or not.
  		if (inFile.fail()) {
   			cerr << "This data file does not exist." << endl;
  			exit(1);
  		}

  		double nextToken;
  		int num = 0;
  		vector<double> vectorX;
  		vector<double> vectorY;
  	
  		while (inFile >> nextToken) {
  			if (num%2 == 0)
  		 	{
  		 		vectorX.push_back(nextToken);
  		 	}else{
  				vectorY.push_back(nextToken);
  		 	}
   			num++;
  		}

  		inFile.close();

  		ifstream lineNum(argv[1]);
	
  		int number_of_lines = 0;
 		string line;

		while (getline(lineNum, line))
  		++number_of_lines;

  		lineNum.close();

  		/*"-------------------End of data operations--------------------"*/

  		MatrixXd A(number_of_lines,3);
  		MatrixXd B(number_of_lines,1);
  		MatrixXd X(number_of_lines,1);

  		//Below that, A and B matrices is created with reference to data file.
  		for (int i = 0; i < number_of_lines; ++i)
  		{
  			double valueOfX = vectorX.at(i);
  			double valueOfY = vectorY.at(i);

  			A(i,0) = valueOfX * valueOfX;
  			A(i,1) = valueOfX;
  			A(i,2) = 1;

  			B(i,0) = valueOfY;
  		}
  
  		cout << " MatrixXd A is " << endl << A << endl << endl;
  		cout << " MatrixXd B is " << endl << B << endl;


  		//Below that, the part of solving linear equation with its solution method.
		if (number_of_lines<3)
  		{
  			cout << "This number is not valid to calculate coefficients";

 		}else if (number_of_lines==3)
 	 	{

 	   	cout << endl << "X was solved with LU decomposition." << endl; 
 	   	X = A.partialPivLu().solve(B); // X = A.lu().solve(B); -> it is also alternative method solving this equation with partial lu decomposition.

 	 	}else if (number_of_lines > 3)
  		{

    		if((argc < 3) || (strcmp(argv[2],"--qr") != 0))
    		{
    		  	cout << endl << "X was solved with LU decomposition." << endl; 
      			X = A.fullPivLu().solve(B); 
    		}

    		else if (strcmp(argv[2],"--qr") == 0)
    		{
    	
    		  cout << endl << "X was solved with QR decomposition." << endl;
    		  X = A.householderQr().solve(B);
    		}
		
		}

 		cout << endl << " MatrixXd X is " << endl << X << endl;

 		double a = X(0,0);
 		double b = X(1,0);
 		double c = X(2,0);

  		cout << endl << "Our coefficients are: " << endl << endl;
 		cout << "Value of a : " << a << endl << "Value of b : " << b << endl << "Value of c : " << c << endl;
 	
 		double backwardsSquareError = 0;

 		for (int i = 0; i < number_of_lines; ++i)
 		{
 			backwardsSquareError = backwardsSquareError + pow(( vectorY.at(i) - ((a * vectorX.at(i) * vectorX.at(i)) + (b * vectorX.at(i)) + c)),2.0);
 		}

    cout << endl << "Number of lines(N) in text file: " << number_of_lines << endl;

 		cout << endl << "Value of backwards square error : " << backwardsSquareError << endl << endl;

 		//Below that, this part is GNUPlot to show quadratic fitting using system method.
 		string gnuplot = "gnuplot -p -e \"";
 		 gnuplot += "a=" + to_string(a) +"; " + "b=" + to_string(b) +"; " + "c=" + to_string(c) +"; " +
  		"f(x)= a*x*x + b*x + c; plot '"+text+"', f(x)\"";
    
 	 	system((gnuplot).c_str());
 	}
 	 	
	return 0;
}