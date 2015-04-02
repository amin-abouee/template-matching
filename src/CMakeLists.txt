# relase binary folder
set(CMAKE_RELEASE_DIR "../bin/release")
# debug binary folder
set(CMAKE_DEBUG_DIR "../bin/debug")

find_package( OpenCV REQUIRED )
find_package( Qt4 REQUIRED )

set(template_matching_SOURCES
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/templatematchingui.cpp
	${PROJECT_SOURCE_DIR}/src/templatematchingopencv.cpp)

set(template_matching_HEADERS 
	${PROJECT_SOURCE_DIR}/src/templatematchingui.h 
	${PROJECT_SOURCE_DIR}/src/templatematchingopencv.h)

set(template_matching_FORMS 
	${PROJECT_SOURCE_DIR}/ui/templatematchingui.ui)

QT4_WRAP_CPP(template_matching_HEADERS_MOC ${template_matching_HEADERS})
QT4_WRAP_UI(template_matching_FORMS_HEADERS ${template_matching_FORMS})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

set (HEADERS_BINARY_DIR ${PROJECT_BINARY_DIR}/src)
include_directories("${HEADERS_BINARY_DIR}")

add_executable (template_matching 
	${template_matching_SOURCES} 
	${template_matching_HEADERS_MOC} 
	${template_matching_FORMS_HEADERS})

target_link_libraries (template_matching 
	${OpenCV_LIBS} 
	${QT_LIBRARIES})

if(CMAKE_BUILD_TYPE STREQUAL Debug)
	set_target_properties(template_matching PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_DEBUG_DIR})
	set_target_properties(template_matching PROPERTIES OUTPUT_NAME template_matching${BUILD_PREFIX})
else()
	set_target_properties(template_matching PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RELEASE_DIR})
endif()