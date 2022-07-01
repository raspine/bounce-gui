Include(FetchContent)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG        v1.88
)
FetchContent_MakeAvailable(imgui)
include_directories(${imgui_SOURCE_DIR})
set(ImGuiSources
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
	)

FetchContent_Declare(
  implot
  GIT_REPOSITORY https://github.com/epezent/implot
  GIT_TAG        v0.13
)
FetchContent_MakeAvailable(implot)
include_directories(${implot_SOURCE_DIR})

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
  GIT_TAG        3.3.7
)
FetchContent_MakeAvailable(glfw)
include_directories(${glfw_SOURCE_DIR})

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME}
	PRIVATE
		${ImGuiSources}
		${GlfwSources}
		main.cpp
		Gui.hpp
		Gui.cpp
		MainWnd.hpp
		MainWnd.cpp
		ChildWnd.hpp
		ChildWnd.cpp
		AnimTimer.hpp
)
target_link_libraries(${PROJECT_NAME}
	glfw
	GL
)
