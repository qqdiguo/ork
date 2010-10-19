set(LIBNAME "ork")

# Sources
include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/libraries" "${PROJECT_SOURCE_DIR}/libraries/*")
file(GLOB SOURCE_FILES *.cpp */*.cpp)

# Libraries
set(LIBS GLEW glut pthread stb_image tinyxml)
if(UNIX)
	set(LIBS ${LIBS} rt)
endif(UNIX)

# Static or shared?
set(LIBTYPE STATIC)
if(BUILD_SHARED)
	set(LIBTYPE SHARED)
endif(BUILD_SHARED)

# Create a static library
add_library(${LIBNAME} ${LIBTYPE} ${SOURCE_FILES})
target_link_libraries(${LIBNAME} ${LIBS})

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

link_directories(${PROJECT_SOURCE_DIR}/lib)
