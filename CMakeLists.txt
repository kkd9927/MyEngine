cmake_minimum_required(VERSION 3.15)
project(MyEngine)

# C++ 표준 설정
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 빌드 타입 기본 설정(Visual Studio 사용시 무시됨)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# UTF-8 인코딩 설정
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 실행 파일(.exe) 빌드 경로 설정
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/build/Release/bin)

# 소스 코드 자동 탐색 (Recursive)
file(GLOB_RECURSE SOURCES "source/*.cpp")
file(GLOB_RECURSE HEADERS "source/*.h")

# 내부 의존성
# -------------------------------------- Engine -------------------------------------
# Engine 라이브러리 정의
add_library(Engine STATIC ${SOURCES} ${HEADERS})

# 포함 디렉토리 설정 (include path)
target_include_directories(Engine PUBLIC "source")

# 실행 파일 생성
# set(GAME_SOURCES ${SOURCES} ${HEADERS} source/EntryPoint.cpp)
set(EDITOR_SOURCES ${SOURCES} ${HEADERS} source/EntryPoint.cpp)

# add_executable(Game WIN32 ${GAME_SOURCES})
add_executable(EDITOR WIN32 ${EDITOR_SOURCES})

# 실행 파일별 매크로 정의(현재 사용안함)
# target_compile_definitions(Game PRIVATE GameEntry)
# target_compile_definitions(EDITOR PRIVATE EditorEntry)

# Engine 라이브러리 링크
# target_link_libraries(Game PRIVATE Engine)
target_link_libraries(EDITOR PRIVATE Engine)

# 빌드 후 리소스 복사
add_custom_target(CopyResources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resource
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resource
)
add_dependencies(EDITOR CopyResources)
# ------------------------------------------------------------------------------------

# 외부 라이브러리
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
    "source/ThirdParty/GLAD/src/glad.c"
)

target_include_directories(glad PUBLIC
    "source/ThirdParty/GLAD/include"
)
# ------------------------------------------------------------------------------------
#
# --------------------------------------- GLM --------------------------------------
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE
    "source/ThirdParty/GLM"
)
# ------------------------------------------------------------------------------------
#
# ------------------------------------- SPDLOG ------------------------------------
add_library(spdlog INTERFACE)
target_include_directories(spdlog INTERFACE
    "source/ThirdParty/SPDLOG/include"
)
# ------------------------------------------------------------------------------------
#
# ----------------------------------- STB_IMAGE -----------------------------------
add_library(stb_image STATIC
    "source/ThirdParty/STB_IMAGE/src/stb_image.cpp"
)
target_include_directories(stb_image PUBLIC
    "source/ThirdParty/STB_IMAGE/include"
)
# ------------------------------------------------------------------------------------
# 라이브러리 링크
target_link_libraries(Engine PUBLIC 
    glad
    glfw3
    glm
    spdlog
    stb_image
)