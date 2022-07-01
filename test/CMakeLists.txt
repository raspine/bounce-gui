Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.0.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(${PROJECT_NAME}_test)
target_sources(${PROJECT_NAME}_test
	PRIVATE
		test.cpp
)
target_link_libraries(${PROJECT_NAME}_test PRIVATE Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
enable_testing()
include(Catch)
catch_discover_tests(${PROJECT_NAME}_test)

