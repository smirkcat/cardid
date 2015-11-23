cmake_minimum_required(VERSION 2.8)
PROJECT (mser)
find_package(OpenCV REQUIRED )
set( NAME_SRC
    src/mser.cpp
	src/swt.cpp
	src/swtUtil.cpp
	src/GetCandidate.cpp
	src/LinkCandidate.cpp
	src/LinkCandidateUtil.cpp
	src/DealCorrect.cpp
	src/tojava.cpp
	test.cpp
)

set( NAME_HEADERS
     include/Candidate.h
	 include/swt.h
	 include/swtUtil.h
	 include/headline.h
	 include/GetCandidate.h
	 include/LinkCandidate.h
	 include/LinkCandidateUtil.h
	 include/DealCorrect.h
	 include/mser.h
	 include/tojava.h
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
#用$ENV{JAVA_HOME}  获取
INCLUDE_DIRECTORIES($ENV{JAVA_HOME}/include)
INCLUDE_DIRECTORIES($ENV{JAVA_HOME}/include/linux)
link_directories( ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#MODULE 动态库生成
ADD_LIBRARY( mser MODULE ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( mser ${OpenCV_LIBS} )