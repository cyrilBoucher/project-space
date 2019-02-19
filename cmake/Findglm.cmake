include(FindPackageHandleStandardArgs)

find_path(GLM_INCLUDE_DIR
	NAMES glm.hpp
	PATH_SUFFIXES glm
)

find_package_handle_standard_args(glm
	DEFAULT_MESSAGE
	GLM_INCLUDE_DIR
)
