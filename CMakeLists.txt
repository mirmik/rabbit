cmake_minimum_required(VERSION 3.5.1)
project(rabbit)
set( CMAKE_VERBOSE_MAKEFILE on )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CC_STANDARD 11)

set (PLATFORM_SOURCES )

if (WIN32 OR WIN64)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
endif()

file(GLOB HEADERS 
	rabbit/*.h
	rabbit/**/*.h	
)

file(GLOB RABBIT_SOURCES
	rabbit/intersect.cpp
	rabbit/space/screw.cpp
)

set(RABBIT_SOURCES ${RABBIT_SOURCES} PARENT_SCOPE)

file(GLOB SOURCES_TEST 
	test/*.cpp
)


add_executable(rabbit_test ${SOURCES_TEST})
add_library(rabbit SHARED ${RABBIT_SOURCES})

target_include_directories(rabbit_test PRIVATE . test)
target_include_directories(rabbit PRIVATE .)
target_link_libraries(rabbit_test rabbit ralgo nos igris)

if (UNIX AND NOT APPLE)
	install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION /usr/lib
	)

	install(DIRECTORY ${PROJECT_NAME}
    	    DESTINATION /usr/local/include
    	    PATTERN "*HIDE*" EXCLUDE
   	)
endif()


if (APPLE)
	install(TARGETS ${PROJECT_NAME}
		LIBRARY DESTINATION /usr/local/lib
	)

	install(DIRECTORY ${PROJECT_NAME}
    	    DESTINATION /usr/local/include
    	    PATTERN "*HIDE*" EXCLUDE
   	)
endif()

enable_testing()
add_test(NAME rabbit_test COMMAND rabbit_test)