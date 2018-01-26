cmake_minimum_required(VERSION 3.6)

project(project-space
	LANGUAGES CXX
	VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

include(GenerateExportHeader)

set(_srcs
	project-space/Billboard.cpp
	project-space/Material.cpp
	project-space/ScreenPlane.cpp
	project-space/Texture2D.cpp
	project-space/Camera.cpp
	project-space/Object.cpp
	project-space/shaders.cpp
	project-space/TextureCubeMap.cpp
	project-space/Color.cpp
	project-space/Plane.cpp
	project-space/SingleObject.cpp
	project-space/trig.cpp
	project-space/CompositeObject.cpp
	project-space/Planet.cpp
	project-space/Skybox.cpp
	project-space/TwoPassRenderer.cpp
	project-space/Cube.cpp
	project-space/Point3.cpp
	project-space/Spaceship.cpp
	project-space/Vec3.cpp
	project-space/Light.cpp
	project-space/Program.cpp
	project-space/Sphere.cpp
	project-space/Renderer.cpp
	project-space/Sun.cpp
)

set(_hdrs
	project-space/Billboard.h
	project-space/Light.h
	project-space/Point3.h
	project-space/SingleObject.h
	project-space/Texture2D.h
	project-space/Camera.h
	project-space/Material.h
	project-space/Program.h
	project-space/Skybox.h
	project-space/TextureCubeMap.h
	project-space/Color.h
	project-space/Object.h
	project-space/Renderer.h
	project-space/Spaceship.h
	project-space/trig.h
	project-space/CompositeObject.h
	project-space/Plane.h
	project-space/ScreenPlane.h
	project-space/Sphere.h
	project-space/TwoPassRenderer.h
	project-space/Cube.h
	project-space/Planet.h
	project-space/shaders.h
	project-space/Sun.h
	project-space/Vec3.h
	${PROJECT_BINARY_DIR}/project-space/project-space-export.h
)

add_library(project-space SHARED ${_srcs} ${_hdrs})

target_link_libraries(project-space PUBLIC
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
)

set(_buildIncludeDir ${CMAKE_CURRENT_BINARY_DIR} 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIR})
target_include_directories(project-space PUBLIC
	"$<BUILD_INTERFACE:${_buildIncludeDir}>"
)

generate_export_header(project-space
	EXPORT_FILE_NAME ${PROJECT_BINARY_DIR}/project-space/project-space-export.h)
	
add_subdirectory(applications)