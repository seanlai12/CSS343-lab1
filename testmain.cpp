//
//  testmain.cpp
//  lab01
//
//  Created by Sean on 4/7/14.
//  Copyright (c) 2014 Sean. All rights reserved.
//


#include "Poly.h"
#include <iostream>
using namespace std;

int main () {
    Poly A(1, 2);

//    Poly B(4);
//    Poly C(1);
    
    A.setCoeff(1, 4);
//    A.setCoeff(1, 3);
    A.setCoeff(1, 1);
    A.setCoeff(8, 0);
    
    Poly B(1);
    B.setCoeff(5, 2);
    B.setCoeff(-1, 6);
//    B.setCoeff(0, 1);
//    B.setCoeff(1, 0);
    
    Poly C(0);
    Poly D(5, 2);
    Poly E(-2, 3);
    
//    int a = A.getDegree();
//    cout << (A+B).getCoeff(5);
//    C = D * E;
    D*=E;
//    A-=B;
    cout << D + B + B;
    cout << endl << A.getCoeff(7) << " " << B.getCoeff(6) << " " << B.getCoeff(7);
//    if(A != B)
//    {
//        cout << "hey";
//    }
    
//    cout << C.getCoeff(0);
    
    
    
    cout << endl;
    return 0;
}