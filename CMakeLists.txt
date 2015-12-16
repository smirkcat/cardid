cmake_minimum_required(VERSION 2.8)
PROJECT (mser)
find_package(OpenCV REQUIRED)
set(OBJ_CARDID
    src/mser.cpp
	src/swt.cpp
	src/swtUtil.cpp
	src/GetCandidate.cpp
	src/LinkCandidate.cpp
	src/LinkCandidateUtil.cpp
	src/DealCorrect.cpp
)

set(OBJ_JAVA
	src/tojava.cpp
)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include )

#用$ENV{JAVA_HOME}获取 用于加载jni头文件
INCLUDE_DIRECTORIES($ENV{JAVA_HOME}/include)
if(WIN32)
	INCLUDE_DIRECTORIES($ENV{JAVA_HOME}/include/win32)
ELSE(WIN32) 
	INCLUDE_DIRECTORIES($ENV{JAVA_HOME}/include/linux)
endif(WIN32)


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# cardid静态库生成
ADD_LIBRARY(cardid STATIC ${OBJ_CARDID})
target_link_libraries(cardid ${OpenCV_LIBS} )

# Mser动态库生成
add_library(Mser SHARED ${OBJ_JAVA})
target_link_libraries(Mser cardid ${OpenCV_LIBS})

#设置位置无关码
set(GNU_FLAGS "-fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GNU_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GNU_FLAGS}")