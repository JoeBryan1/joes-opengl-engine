cmake_minimum_required (VERSION 3.21)
project (MyEngine)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(Freetype REQUIRED)

# Compile external dependencies
add_subdirectory (external)

include_directories(
		external/glfw-3.1.2/include
		external/glm-0.9.7.1
		external/glew-1.13.0/include
		external/freetype-2.10.0/include
		external/imgui-1.90.6
		.
)

add_definitions(
		-DTW_STATIC
		-DTW_NO_LIB_PRAGMA
		-DTW_NO_DIRECT3D
		-DGLEW_STATIC
		-D_CRT_SECURE_NO_WARNINGS
)

set(ALL_LIBS
		${OPENGL_LIBRARY}
		${FREETYPE_LIBRARIES}
		glfw
		GLEW_1130
)

add_executable(Circle
		src/circle/main.cpp
        common/shader.hpp
		src/shaders/circle.frag
		src/shaders/circle.vert
)

target_link_libraries(Circle
	${ALL_LIBS}
)

add_executable(TextRenderer
		src/textrenderer/main.cpp
)

target_link_libraries(TextRenderer
		${ALL_LIBS}
)

add_executable(Cube
		src/cube/main.cpp
		common/shader.hpp
)

target_link_libraries(Cube
		${ALL_LIBS}
)