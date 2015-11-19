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
)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
link_directories( ${CMAKE_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
add_executable( mser ${NAME_SRC} ${NAME_HEADERS} )

target_link_libraries( mser lept tesseract ${OpenCV_LIBS} )