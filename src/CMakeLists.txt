cmake_minimum_required(VERSION 3.6)
project(testApp)
set(LWTV_H 
	"tvec3.h"
	"tmat3.h"
	"tmat4.h"
)
add_executable(tester tester.C)
