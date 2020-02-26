
// Lightweight templated matrix3 library
// Dec 2019
// Ivan DeWolf
//
// this was written with the goal of brevity and ease of use.
// all code is in this .h file
// there is no error checking, 
// this was not optimized for execution speed or mimimizing RAM usage.
// this was not written to handle every possible requirement.
// this is not documented, or written for ease of comprehension.

#ifndef __tmat3_h__
#define __tmat3_h__
#include <iostream>
#include <cmath>
#include "tvec3.h"
namespace lwtv {
template <typename T>
class tmat3
{
 public:
  tmat3(){this->identity();}
  tmat3(tmat3& m){for(int i=0; i<9; ++i)n[i]=m[i];}
  // Assignment operators
  tmat3& operator += (const tmat3& m){for(int i=0; i<9; ++i)n[i]+=m.get(i);return *this;}
  tmat3& operator -= (const tmat3& m){for(int i=0; i<9; ++i)n[i]-=m.get(i);return *this;}
  tmat3& operator *= (const T& s){for(int i=0; i<9; ++i)n[i]*=s;return *this;}
  tmat3& operator /= (const T& s){for(int i=0; i<9; ++i)n[i]/=s;return *this;}
  T& operator [] (const int i){return n[i];}
  T& operator() (const int r, const int c){return n[(r*3) + c];}
  // matrix3 scalar operators
  friend tmat3 operator * (const tmat3& m, const T& s){tmat3 out;for(int i=0; i<9; ++i)out[i]=m.get(i)*s;return out;}
  friend tmat3 operator / (const tmat3& m, const T& s){tmat3 out;for(int i=0; i<9; ++i)out[i]=m.get(i)/s;return out;}
  // matrix3 vector operators
  tvec3<T> operator * (tvec3<T>& v){
    tvec3<T> rowX = getRow(0) * v[0]; tvec3<T> rowY = getRow(1) * v[1]; tvec3<T> rowZ = getRow(2) * v[2];
    return rowX + rowY + rowZ;}
  // matrix3 matrix3 operators
  tmat3 operator + (const tmat3& m){tmat3 out;for(int i=0; i<9; ++i)out[i]=n[i]+m.get(i);return out;}
  tmat3 operator - (const tmat3& m){tmat3 out;for(int i=0; i<9; ++i)out[i]=n[i]-m.get(i);return out;}
  friend tmat3 operator * (const tmat3& mA, const tmat3& mB){
    tmat3 out;for(int i=0;i<3;++i)for(int j=0;j<3;++j)for(int k=0;k<3;++k)out(i,j)=mA.get(i,k)*mB.get(k,j);return out;}
  // equality functions
  bool operator == (const tmat3& m){for(int i=0; i<9; ++i)if(n[i]!=m.get(i))return false;return true;}
  bool operator != (const tmat3& m){return !(*this==m);}
  // accessor functions
  T get(const int i)const{return n[i];}// get() is const
  T get(const int r, const int c)const{return n[(r*3) + c];}// get() is const
  void set(const tvec3<T> a, const tvec3<T> b, const tvec3<T> c){
    n[0]=a.get(0); n[1]=a.get(1); n[2]=a.get(2);
    n[3]=b.get(0); n[4]=b.get(1); n[5]=b.get(2);
    n[6]=c.get(0); n[7]=c.get(1); n[8]=c.get(2);}
  void setRow(const int i,const tvec3<T> v){n[(3*i)+0]=v.get(0); n[(3*i)+1]=v.get(1); n[(3*i)+2]=v.get(2);}
  tvec3<T> getRow(const int i){return tvec3<T>(n[(3*i)+0], n[(3*i)+1], n[(3*i)+2]);}
  // utility functions
  friend std::ostream& operator << (std::ostream& s, const tmat3<T>& m){
    s<<"\n("<<m.n[0]<<", "<<m.n[1]<<", "<<m.n[2]<<")";
    s<<"\n("<<m.n[3]<<", "<<m.n[4]<<", "<<m.n[5]<<")";
    s<<"\n("<<m.n[6]<<", "<<m.n[7]<<", "<<m.n[8]<<")";
    return s;}
  void identity(){
    n[0]=1;n[1]=0;n[2]=0;
    n[3]=0;n[4]=1;n[5]=0;
    n[6]=0;n[7]=0;n[8]=1;}
  void rotate(const tvec3<T>& Axis, const T angle) { // assumes your axis is normalized
    T c = cos(angle); T s = sin(angle); T t = 1.0 - c; tvec3<T> A,B,C;
    A.set(t*Axis.get(0)*Axis.get(0) + c, t*Axis.get(0)*Axis.get(1) + s*Axis.get(2), t*Axis.get(0)*Axis.get(2) - s*Axis.get(1));
    B.set(t*Axis.get(0)*Axis.get(1) - s*Axis.get(2), t*Axis.get(1)*Axis.get(1) + c, t*Axis.get(1)*Axis.get(2) + s*Axis.get(0));
    C.set(t*Axis.get(0)*Axis.get(2) + s*Axis.get(1), t*Axis.get(1)*Axis.get(2) - s*Axis.get(0), t*Axis.get(2)*Axis.get(2) + c);
    set(A,B,C);}
  void transpose(){
    tvec3<T> A, B, C;
    A.set(n[0],n[3],n[6]);
    B.set(n[1],n[4],n[7]);
    C.set(n[2],n[5],n[8]);
    set(A,B,C);}
  T determinant2d(const int& a, const int& b, const int& c, const int& d){return n[a] * n[d] - n[c] * n[b];}
  T determinant(){
    T ab = determinant2d(3,6,4,7);
    T ac = determinant2d(3,6,5,8);
    T bc = determinant2d(4,7,5,8);
    T a = n[0] * bc;
    T b = n[1] * ac;
    T c = n[2] * ab;
    return a - b + c;}
private:
  T n[9];
};
} //end lwtv namespace
#endif

//Copyright 2019 Ivan DeWolf
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
