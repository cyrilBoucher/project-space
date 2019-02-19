find_package(GLUT REQUIRED)

add_executable(project-space-app main.cpp)

target_link_libraries(project-space-app PUBLIC
	project-space
	GLUT::GLUT
)

target_include_directories(project-space-app PUBLIC
	${GLUT_INCLUDE_DIR}
)
