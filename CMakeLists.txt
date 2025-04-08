cmake_minimum_required(VERSION 3.10)
project(OpenGLTutorial)

set(CMAKE_CXX_STANDARD 17)

# 헤더 파일 경로 추가
include_directories(${CMAKE_SOURCE_DIR}/include)

# 소스 파일 추가
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# 실행 파일 생성
add_executable(${PROJECT_NAME} ${SOURCES})

# GLFW 라이브러리 경로 추가
find_package(OpenGL REQUIRED)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Windows에서 필요한 설정
if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${CMAKE_SOURCE_DIR}/lib/libglfw3.a    # MinGW에서 정적 라이브러리 링크
        -static-libgcc
        -static-libstdc++
    )
    
    # DLL을 실행 파일과 같은 디렉토리에 복사 (필요한 경우)
    # file(COPY ${CMAKE_SOURCE_DIR}/lib/glfw3.dll DESTINATION ${CMAKE_BINARY_DIR})
else()
    target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        glfw
    )
endif()