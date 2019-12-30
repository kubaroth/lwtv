
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

#ifndef __tmat4_h__
#define __tmat4_h__
#include <iostream>
namespace lwtv {
template <typename T>
class tmat4
{
 public:
  tmat4(){this->identity();}
  tmat4(const T s){for(int i=0; i<16; ++i)n[i]=s;}
  tmat4(tmat4& m){for(int i=0; i<16; ++i)n[i]=m[i];}
  // Assignment operators
  tmat4& operator = (const T s){for(int i=0; i<16; ++i)n[i]=s;return *this;}
  tmat4& operator += (tmat4& m){for(int i=0; i<16; ++i)n[i]+=m[i];return *this;}
  tmat4& operator -= (tmat4& m){for(int i=0; i<16; ++i)n[i]-=m[i];return *this;}
  tmat4& operator *= (const T s){for(int i=0; i<16; ++i)n[i]*=s;return *this;}
  tmat4& operator /= (const T s){for(int i=0; i<16; ++i)n[i]/=s;return *this;}
  T& operator [] (const int i){return n[i];}
  T& operator () (const int r, const int c){return n[(r*4) + c];}
  T& val(const int r, const int c){return (n[(r*4) + c]);}
  // matrix4 scalar operators
  friend tmat4 operator * (tmat4 &m, const T &s){tmat4 out;for(int i=0; i<16; ++i)out[i]=m[i]*s;return out;}
  friend tmat4 operator / (tmat4 &m, const T &s){tmat4 out;for(int i=0; i<16; ++i)out[i]=m[i]/s;return out;}
  // matrix4 vector operators
  T rowVMult(const int index, tvec3<T> &v){T out = 0;for(int i=0;i<3;++i)out+=n[(index*4)+i]*v[i];return out+n[(index*4)+3];}
  friend tvec3<T> operator * (tmat4 &m, tvec3<T> &v){tvec3<T> out;for(int i=0;i<3;++i)out[i]=m.rowVMult(i,v);return out/m.rowVMult(3,v);} 
  // matrix4 matrix4 operators
  tmat4<T> operator + (tmat4<T>& m){tmat4<T> out;for(int i=0; i<16; ++i)out[i]=n[i]+m[i];return out;}
  tmat4<T> operator - (tmat4<T>& m){tmat4<T> out;for(int i=0; i<16; ++i)out[i]=n[i]-m[i];return out;}
  friend tmat4 operator * (tmat4 &mA, tmat4 &mB){tmat4 out;for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k)out(i,j)=mA(i,k)*mB(k,j);return out;}
  // equality functions
  bool operator == (tmat4<T>& m){for(int i=0; i<16; ++i)if(n[i]!=m[i])return false;return true;}
  bool operator != (tmat4<T>& m){return !(*this==m);}
  // accessor functions
  void set(tmat4 &m){for(int i=0; i<16; ++i){n[i]=m[i];}}
  // utility functions
  friend std::ostream& operator << (std::ostream& s, const tmat4 &m){
	s<<"\n("<<m.n[0]<<", "<<m.n[1]<<", "<<m.n[2]<<", "<<m.n[3]<<")";
	s<<"\n("<<m.n[4]<<", "<<m.n[5]<<", "<<m.n[6]<<", "<<m.n[7]<<")";
	s<<"\n("<<m.n[8]<<", "<<m.n[9]<<", "<<m.n[10]<<", "<<m.n[11]<<")";
	s<<"\n("<<m.n[12]<<", "<<m.n[13]<<", "<<m.n[14]<<", "<<m.n[15]<<")";
	return s;}
  void identity(){
	n[0]=1;n[1]=0;n[2]=0;n[3]=0;
	n[4]=0;n[5]=1;n[6]=0;n[7]=0;
	n[8]=0;n[9]=0;n[10]=1;n[11]=0;
	n[12]=0;n[13]=0;n[14]=0;n[15]=1;}
  void transpose(){
	tmat4<T> holder;
	for(int c=0;c<4;++c)
	  for(int r=0;r<4;++r)
		holder(c,r) = n[(r*4) + c];
	for(int i=0; i<16; ++i)
	  n[i] = holder[i];
	}
  T determinant2d(int a, int b, int c, int d){return n[a] * n[d] - n[c] * n[b];}
  T determinant(){
	T ab=determinant2d(8,12,9,13);
	T ac=determinant2d(8,12,10,14);
	T ad=determinant2d(8,12,11,15);
	T bc=determinant2d(9,13,10,14);
	T bd=determinant2d(9,13,11,15);
	T cd=determinant2d(10,14,11,15);
	T ABC=n[4]*bc-n[5]*ac+n[6]*ab;
	T ACD=n[4]*cd-n[6]*ad+n[7]*ac;
	T ABD=n[4]*bd-n[5]*ad+n[7]*ab;
	T BCD=n[5]*cd-n[6]*bd+n[7]*bc;
	T one=n[0]*BCD;T two=n[1]*ACD;T three=n[2]*ABD;T four=n[3]*ABC;
	return one-two+three-four;}
  void adjoint(tmat4& m){
	T abl = m.determinant2d( 8,12, 9,13);T abs = m.determinant2d(4,12,5,13);T abu = m.determinant2d(4,8,5,9 );
	T acl = m.determinant2d( 8,12,10,14);T acs = m.determinant2d(4,12,6,14);T acu = m.determinant2d(4,8,6,10);
	T adl = m.determinant2d( 8,12,11,15);T ads = m.determinant2d(4,12,7,15);T adu = m.determinant2d(4,8,7,11);
	T bcl = m.determinant2d( 9,13,10,14);T bcs = m.determinant2d(5,13,6,14);T bcu = m.determinant2d(5,9,6,10);
	T bdl = m.determinant2d( 9,13,11,15);T bds = m.determinant2d(5,13,7,15);T bdu = m.determinant2d(5,9,7,11);
	T cdl = m.determinant2d(10,14,11,15);T cds = m.determinant2d(6,14,7,15);T cdu = m.determinant2d(6,10,7,11);	
	T ABCll=m[4]*bcl-m[5]*acl+m[6]*abl;T ABCul=m[0]*bcl-m[1]*acl+m[2]*abl;T ABCus=m[0]*bcs-m[1]*acs+m[2]*abs;T ABCuu=m[0]*bcu-m[1]*acu+m[2]*abu;
	T ACDll=m[4]*cdl-m[6]*adl+m[7]*acl;T ACDul=m[0]*cdl-m[2]*adl+m[3]*acl;T ACDus=m[0]*cds-m[2]*ads+m[3]*acs;T ACDuu=m[0]*cdu-m[2]*adu+m[3]*acu;
	T ABDll=m[4]*bdl-m[5]*adl+m[7]*abl;T ABDul=m[0]*bdl-m[1]*adl+m[3]*abl;T ABDus=m[0]*bds-m[1]*ads+m[3]*abs;T ABDuu=m[0]*bdu-m[1]*adu+m[3]*abu;
	T BCDll=m[5]*cdl-m[6]*bdl+m[7]*bcl;T BCDul=m[1]*cdl-m[2]*bdl+m[3]*bcl;T BCDus=m[1]*cds-m[2]*bds+m[3]*bcs;T BCDuu=m[1]*cdu-m[2]*bdu+m[3]*bcu;
	n[0]=BCDll;n[1]=-ACDll;n[2]=ABDll;n[3]=-ABCll;
	n[4]=BCDul;n[5]=-ACDul;n[6]=ABDul;n[7]=-ABCul;
	n[8]=BCDus;n[9]=-ACDus;n[10]=ABDus;n[11]=-ABCus;
	n[12]=BCDuu;n[13]=-ACDuu;n[14]=ABDuu;n[15]=-ABCuu;
	transpose();}
  tmat4 inverse(){
	tmat4 adjointM4; adjointM4.adjoint(*this);
	adjointM4 *= (1.0/determinant());
	return adjointM4;
  }
  private:
  T n[16];
};
} //end lwtv namespace
#endif

// determinant hint:
//  1 | 2 | 3 | 4 
// ----------------
//  A | B | C | D
// ----------------
//  a | b | c | d   
// -|---|---|---|--
//  a | b | c | d 

//Copyright 2019 Ivan DeWolf
//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
