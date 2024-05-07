cmake_minimum_required(VERSION 3.28)
project(edurithm_dijkstra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1)
FetchContent_MakeAvailable(SFML)

add_executable(edurithm_dijkstra main.cpp
        Application.cpp
        Application.h)
target_link_libraries(edurithm_dijkstra PRIVATE sfml-graphics)
target_compile_features(edurithm_dijkstra PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET edurithm_dijkstra
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
            VERBATIM)
endif()

install(TARGETS edurithm_dijkstra)