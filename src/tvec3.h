
// Lightweight templated vector library
// Dec 2019
// Ivan DeWolf
//
// this was written with the goal of brevity and ease of use.
// all code is in this .h file
// there is no error checking, 
// this was not optimized for execution speed or mimimizing RAM usage.
// this was not written to handle every possible requirement.
// this is not documented, or written for ease of comprehension.

#ifndef __tvec3_h__
#define __tvec3_h__
#include <iostream>
#include <cmath>
namespace lwtv {
template <typename T>
class tvec3
{
 public:
  //constructors
  tvec3(){n[0]=n[1]=n[2]=0;}
  tvec3(const T x, const T y, const T z){n[0] = x; n[1] = y; n[2] = z;}
  tvec3(const T d){n[0]=n[1]=n[2]=d;}
  tvec3(const tvec3& b){n[0]=b.n[0];n[1]=b.n[1];n[2]=b.n[2];}
  // Assignment operators
  tvec3& operator = (const T d){n[0]=n[1]=n[2]=d; return *this; }
  tvec3& operator += (const tvec3& v){n[0]+=v.n[0]; n[1]+=v.n[1]; n[2]+=v.n[2]; return *this;}
  tvec3& operator -= (const tvec3& v){n[0]-=v.n[0]; n[1]-=v.n[1]; n[2]-=v.n[2]; return *this;}
  tvec3& operator *= ( const T d ){n[0]*=d; n[1]*=d; n[2]*=d; return *this;}
  tvec3& operator /= ( const T d ){double d_inv = 1.0/d; n[0]*=d_inv; n[1]*=d_inv; n[2]*=d_inv; return *this; }
  T& operator [] ( int i){return n[i];}
  void set(T Xin, T Yin, T Zin){n[0]=Xin; n[1]=Yin; n[2]=Zin;}

  // vector to vector operators
  tvec3 operator - (){return tvec3(-n[0],-n[1],-n[2]);}//unary
  tvec3 operator + (const tvec3& b){return tvec3(n[0] + b.n[0], n[1] + b.n[1], n[2] + b.n[2]);}
  tvec3 operator - (const tvec3& b){return tvec3(n[0] - b.n[0], n[1] - b.n[1], n[2] - b.n[2]);}
  tvec3 operator * (const tvec3& b){return tvec3(n[0] * b.n[0], n[1] * b.n[1], n[2] * b.n[2]);}
  tvec3 operator / (const tvec3& b){return tvec3(n[0] / b.n[0], n[1] / b.n[1], n[2] / b.n[2]);}

  // vector to digit operators
  tvec3 operator + (const T& d){return tvec3(n[0] + d, n[1] + d, n[2] + d);}
  friend tvec3 operator + (T d, tvec3 v){return v+d;}
  tvec3 operator - (const T& d){return tvec3(n[0] - d, n[1] - d, n[2] - d);}
  friend tvec3 operator - (T d, tvec3 v){return tvec3(d - v.n[0],d - v.n[1],d - v.n[2]);}
  tvec3 operator * (const T& d){return tvec3(n[0] * d, n[1] * d, n[2] * d);}
  friend tvec3 operator * (T d, tvec3 v){return v*d;}
  tvec3 operator / (const T& d){double d_inv = 1.0/d;return tvec3(n[0]*d_inv, n[1]*d_inv, n[2]*d_inv);}
  friend tvec3 operator / (T d, tvec3 v){return tvec3(d/v.n[0],d/v.n[1],d/v.n[2]);}

  // equality
  bool operator == (const tvec3& b){return (n[0]==b.n[0]) && (n[1]==b.n[1]) && (n[2]==b.n[2]);}
  bool operator != (const tvec3& b){return !(*this==b);}
  
  // utility functions
  friend std::ostream& operator << (std::ostream& s, const tvec3& v){return s<<"("<<v.n[0]<<", "<<v.n[1]<<", "<<v.n[2]<<")";}
  T length2(){return n[0]*n[0] + n[1]*n[1] + n[2]*n[2];}
  T length(){return sqrt(length2());}
  tvec3 normalize(){(*this) /= length();return tvec3(*this);}
  tvec3 normalized(){T L = length(); return tvec3(n[0]/L,n[1]/L,n[2]/L);}
  T dot(const tvec3& b){return (n[0]*b.n[0] + n[1]*b.n[1] + n[2]*b.n[2]);}
  tvec3 cross(const tvec3& b) {return tvec3(n[1]*b.n[2] - n[2]*b.n[1],n[2]*b.n[0] - n[0]*b.n[2],n[0]*b.n[1] - n[1]*b.n[0]);}
 private:
  T n[3];
};
} //end lwtv namespace
#endif

//Copyright 2019 Ivan DeWolf
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
