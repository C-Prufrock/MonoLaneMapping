/**
  ******************************************************************************
  * @file           : main.cpp
  * @author         : lxy
  * @brief          : None
  * @attention      : None
  * @date           : 24-1-3
  ******************************************************************************
  */
#include<iostream>
#include<Eigen/Core>

using namespace std;
using namespace Eigen;

int main() {
    MatrixXd::Index maxRow, maxCol;
    MatrixXd::Index minRow, minCol;
    MatrixXd mMat(4,4);
    mMat << 11, 10, 13, 15,
            3, 24, 56,	1,
            2, 12, 45,	0,
            8, 5,	6,	4;
    double min = mMat.minCoeff(&minRow,&minCol);
    double max = mMat.maxCoeff(&maxRow,&maxCol);
    cout << "Max = \n" << max << endl;
    cout << "Min = \n" << min << endl;
    cout << "minRow = " << minRow << "minCol = " <<minCol<<endl;
    cout << "maxRow = " << maxRow << "maxCol = " << maxCol << endl;

    std::cout<<" hello world" << std::endl;
    return 0;
}
