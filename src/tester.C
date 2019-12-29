#include <iostream>
#include "tmat3.h"
#include "tmat4.h"

using namespace std;
//using namespace idwTest;
using namespace lwtv;

void
tvecTest()
{
  cout<<"*************** test tvec3 *********************"<<endl;
  cout<<"\nconstructors:"<<endl;
  tvec3<float> A;
  tvec3<float> B(.1,.2,.3);
  tvec3<float> C(.4);
  tvec3<float> D(B);
  cout <<A<<", "<<B<<", "<<C<<", "<<D<<endl;
 //-------------------------------------
   cout<<"\nAssignment operators:"<<endl;
  A = 1.2345;
  B = C;
  cout <<A<<", "<<B<<", "<<C<<endl;
  A = 1;
  B= .1;
  A += B;
  cout <<A<<", "<<B<<endl;
  A -= B;
  cout <<A<<", "<<B<<endl;
  A *= 2;
  B /= 2;
  C = 3;
  C[1] = .3;
  D.set(10,9,8);
  cout <<A<<", "<<B<<", "<<C<<", "<<D<<endl;
 //-------------------------------------
   cout<<"\nvector to vector operators:"<<endl;
  A = B = C = D = .25;
  A = B + C;
  B = A - D;
  C = A * B;
  D = A / B;
  tvec3<float> E;
  E = -D;
  cout <<A<<", "<<B<<", "<<C<<", "<<D<<", "<<E<<endl;
 //-------------------------------------
   cout<<"\nvector to digit operators:"<<endl;
  A = B = C = D = E =1.5;
  A = C + .1;
  B = .1 + C;
  C = A - -1;
  D = .1 - A;
  cout <<A<<", "<<B<<", "<<C<<", "<<D<<endl;
  A = B = C = D = E =1.5;
  A = C * 2;
  B = 2 * C;
  C = E / 2;
  D = 2 / E;
  cout <<A<<", "<<B<<", "<<C<<", "<<D<<endl;
  //-------------------------------------
  cout<<"\nequality:"<<endl;
  A = B = C = 1;
  D = E = 2;
  if(A==B)cout<<"a == b"<<endl;
  if(A==E)cout<<"SHOULD NOT PRINT"<<endl;
  if(A!=E)cout<<"a != e"<<endl;
  if(A!=B)cout<<"SHOULD NOT PRINT"<<endl;
  //-------------------------------------
  cout<<"\nutility functions:"<<endl;
  A = 1;
  B = A.normalized() * 2;
  cout<<A<<" "<< B.length2()<<" and "<<B.length()<<endl;
  A.normalize();
  cout<<A<<endl;
  A = 1;
  B = 1;
  B[1] = .5;
  C = A.cross(B);
  // dot should be 2.5, cross should be (.5,0,-.5)
  cout <<"dot: "<<A.dot(B)<<" cross:"<<C<<endl;
}

void
tmat3Test(){
  cout<<"\n\n*************** test tmat3 *********************"<<endl;
  tmat3<float> A;
  tmat3<float> B;
  tmat3<float> C;
  tmat3<float> D;
  //-------------------------------------
  cout<<"\nAssignment operators:"<<endl;
  A[7] = 3.141;
  A(1,2) = 2.718;
  tmat3<float> E(A);
  B = A;
  C -= A;
  D += A;
  cout <<A<<", \n"<<B<<", \n"<<C<<", \n"<<D<<", \n"<<E<<endl;
  A *= 2;
  B /= 2;
  cout <<"m/s:"<<A<<", \n"<<B<<endl;
  //-------------------------------------
  cout<<"\nmatrix3 scalar operators:"<<endl;
  B = A * .5;
  C = A / 2;
  cout <<A<<", \n"<<B<<", \n"<<C<<endl;
  //-------------------------------------
  cout<<"\nmatrix3 vector operators:"<<endl;
  A.identity();
  A(0,0)= .7071;
  A(0,2)=-.7071;
  A(2,0)= .7071;
  A(2,2)= .7071;
  tvec3<float> VA(1,0,0);
  tvec3<float> VB, VC;
  VB = A * VA;// A is a 45 degree turn around the Y axis
  cout <<A<<",\n"<<VA<<" "<<VB<<endl;
  //-------------------------------------
  cout<<"\nmatrix3 matrix3 operators:"<<endl;
  cout <<"starts off: "<<B<<C<<D<<endl;
  A = B + C;
  B = C + D;
  E = A * B;
  cout <<"results:\n"<<A<<", \n"<<B<<", \n"<<C<<", \n"<<D<<", \n"<<E<<endl;
  //-------------------------------------
  cout<<"\nequality functions:"<<endl;
  A.identity();
  B.identity();
  if(A==B)cout<<"good result"<<endl;
  if(A==C)cout<<"bad result"<<endl;
  if(A!=B)cout<<"bad result"<<endl;
  if(A!=C)cout<<"good result"<<endl;
  //-------------------------------------
  cout<<"\naccessor functions:"<<endl;
  VA.set(1,2,3);
  VB.set(4,5,6);
  VC.set(7,8,9);
  A.set(VA,VB,VC);
  B.setRow(1, VB);
  VA = A.getRow(2);
  cout <<"results:"<<A<<", \n"<<B<<",  "<<VA<<endl;
  //-------------------------------------
  cout<<"\nutility functions:"<<endl;
  B.identity();
  C.identity();
  tvec3<float> axis(0,1,0);
  C.rotate(axis, (45.0*M_PI/180.0));
  A.transpose();
  float det =  D.determinant();
  cout <<"results:\n"<<A<<", \n"<<B<<", \n"<<C<<", \n"<<D<<", \n"<<det<<endl;
}

void
tmat4Test(){
  cout<<"\n\n*************** test tmat4 *********************"<<endl;
  tmat4<float> A;
  tmat4<float> B(3.14);
  tmat4<float> C(B);
  tmat4<float> D, E, F, G, H;
  //-------------------------------------
  cout<<"\nAssignment operators:"<<endl;
  A[3] = 3.141;
  A(1,3) = 2.718;
  D = A;
  E -= A;
  F += A;
  G *= 2;
  H /= 2;
  cout <<A<<", \n"<<B<<", \n"<<C<<", \n"<<D<<", \n"<<E<<", \n"<<F<<", \n"<<G<<", \n"<<H<<endl;
  //-------------------------------------
  cout<<"\nmatrix4 scalar operators:"<<endl;
  B = A * .5;
  C = A / 2;
  cout <<A<<", \n"<<B<<", \n"<<C<<endl;
  //-------------------------------------
  cout<<"\nmatrix4 vector operators:"<<endl;
  A.identity();
  A(0,0)= .7071;
  A(0,2)=-.7071;
  A(2,0)= .7071;
  A(2,2)= .7071;
  tvec3<float> VA(1,0,0);
  tvec3<float> VB, VC;
  VB = A * VA;// A is a 45 degree turn around the Y axis
  cout <<A<<",\n"<<VA<<" "<<VB<<endl;
  //-------------------------------------
  cout<<"\nmatrix4 matrix4 operators:"<<endl;
  cout <<"starts off: "<<B<<C<<D<<endl;
  A = B + C;
  B = C + D;
  E = A * B;
  cout <<"results:\n"<<A<<", \n"<<B<<", \n"<<C<<", \n"<<D<<", \n"<<E<<endl;
  //-------------------------------------
  cout<<"\nequality functions:"<<endl;
  A.identity();
  B.identity();
  if(A==B)cout<<"good result"<<endl;
  if(A==C)cout<<"bad result"<<endl;
  if(A!=B)cout<<"bad result"<<endl;
  if(A!=C)cout<<"good result"<<endl;
  //-------------------------------------
  cout<<"\naccessor functions:"<<endl;
  A.set(C);
  cout <<"results:\n"<<A<<endl;
  //-------------------------------------
  cout<<"\nutility functions:"<<endl;
  A.identity();
  //rotate
  B(0,2) = .12345;
  B.transpose();
  float det = C.determinant();
  D.identity();
  D(0,0)= .7071;
  D(0,2)=-.7071;
  D(2,0)= .7071;
  D(2,2)= .7071;
  E = D.inverse();// WAAA!!!! this looks broken. :'(
  cout <<"results:\n"<<A<<", \n"<<B<<", \n"<<det<<", \n"<<D<<", \n"<<E<<endl;

}

main()
{
  tvecTest();
  tmat3Test();
  tmat4Test();
}

//Copyright 2019 Ivan DeWolf
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
