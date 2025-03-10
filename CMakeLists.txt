cmake_minimum_required(VERSION 3.15)
project(Engine)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 빌드 타입 기본 설정(Visual Studio 사용시 무시됨)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 실행 파일(.exe) 빌드 경로
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build/Release/bin)

# 소스 코드 자동 탐색 (Recursive)
file(GLOB_RECURSE SOURCES
    "Source/Engine/*.cpp"
)

file(GLOB_RECURSE HEADERS
    "Source/Engine/*.h"
)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 포함 디렉토리 설정 (include path)
target_include_directories(${PROJECT_NAME} PRIVATE
    "Source/Engine"
    "Source/Engine/IO"
    "Source/Engine/Render"
    "Source/Engine/Camera"
)

# 라이브러리
# -------------------------------------- GLFW --------------------------------------
add_library(glfw3 STATIC IMPORTED)

set_target_properties(glfw3 PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/GLFW/lib/glfw3.lib"
)

target_include_directories(glfw3 INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/ThirdParty/GLFW/include"
)
# ------------------------------------------------------------------------------------
#
# -------------------------------------- GLAD --------------------------------------
add_library(glad STATIC
    "Source/ThirdParty/GLAD/src/glad.c"
)

target_include_directories(glad PUBLIC
    "Source/ThirdParty/GLAD/include"
)
# ------------------------------------------------------------------------------------
#
# --------------------------------------- GLM --------------------------------------
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
    "Source/ThirdParty/GLM"
)
# ------------------------------------------------------------------------------------
#
# ----------------------------------- STB_IMAGE -----------------------------------
add_library(stb_image STATIC
    "Source/ThirdParty/STB_IMAGE/src/stb_image.cpp"
)
target_include_directories(stb_image PUBLIC
    "Source/ThirdParty/STB_IMAGE/include"
)
# ------------------------------------------------------------------------------------
# 라이브러리 링크
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glad
    glfw3
    glm
    stb_image
)