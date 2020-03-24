cmake_minimum_required(VERSION 3.13)
project(testApp)

include(ExternalProject)

set(CMAKE_CXX_STANDARD 11)

set(TARGET_NAME tester)

set(OFFLINE 0 CACHE BOOL "Skips the download step and uses local git repo
(https://github.com/kubaroth/tbb.git)
branch: termux (using tbb 2020)
cloned into top_level_cmake/tbb_src")
set(TBB_PATH "${PROJECT_SOURCE_DIR}/install_dir/lib" CACHE STRING "Path to already built tbb library - this implicitly assumes OFFLINE=ON")

# Specify location of TBB sources
if(OFFLINE EQUAL 0)
set (TBB_REPO GIT_REPOSITORY https://github.com/kubaroth/tbb.git)
else()
set (TBB_REPO URL ${PROJECT_SOURCE_DIR}/tbb_src) # Use local repo instead
endif()

# If provided search TBB path
find_library(TBB_LIB tbb PATHS ${TBB_PATH} PATH_SUFFIXES lib NO_DEFAULT_PATH) # skip LD_LIBRARY_PATH

# Sources
add_executable(${TARGET_NAME} tester.C)


# Set install dir,
# NOTE: if CMAKE_INSTALL_PREFIX is not provided we install into the repo instead to /usr/local

if (${CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT})
set (INSTALL_DIR ${PROJECT_SOURCE_DIR}/install_dir)
set (CMAKE_INSTALL_PREFIX ${INSTALL_DIR} CACHE PATH "Install to default location" FORCE)
else()
set (INSTALL_DIR ${CMAKE_INSTALL_PREFIX})
endif()

# Install TBB locally 
if (NOT TBB_LIB)
message (STATUS "TBB path not provided - installing TBB locally using: ${TBB_REPO}")

message (STATUS "Using TBB sources in: ${TBB_REPO}")
message (STATUS "Setting install dir to: ${INSTALL_DIR}")

# TBB currently uses in-source build.
# Out of the box it does not ship with 'install' target hence we are using 
# forked version from kubaroth which contains necessary changes.
ExternalProject_Add(
"TBB_PRJ"
PREFIX "external"
${TBB_REPO}
GIT_TAG "termux"
SOURCE_DIR ${CMAKE_BINARY_DIR}/tbb_src # Download location
UPDATE_COMMAND "" # Left empty for quicker updates
CONFIGURE_COMMAND "" # Still needed if CMake is not used in the build
BUILD_IN_SOURCE ON # TBB is build in source
# Already installed into desired final location.
BUILD_COMMAND tbb_install_prefix=${INSTALL_DIR} $(MAKE) install # One step build/install
)

# set library name
set(TBB_LIB tbb)
add_dependencies(${TARGET_NAME} TBB_PRJ)

endif() # end of local TBB install


target_link_directories(tester BEFORE PUBLIC ${INSTALL_DIR}/lib)
target_include_directories(tester BEFORE PUBLIC ${INSTALL_DIR}/include)
# if offline TBB_PATH provided
target_include_directories(tester BEFORE PUBLIC ${TBB_PATH}/include)
target_link_directories(tester BEFORE PUBLIC ${TBB_PATH}/lib)

# RPATH
set_target_properties(
     tester
    PROPERTIES INSTALL_RPATH
    "${INSTALL_DIR}/lib;${TBB_PATH}" # TODO: depending on TBB_PATH passed on command line this may be missing /lib subdirectory
    )


target_link_libraries(tester tbb)
install(TARGETS tester DESTINATION ${INSTALL_DIR}/bin)

