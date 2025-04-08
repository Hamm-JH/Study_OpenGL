#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"

// 윈도우 크기 변경 시 호출되는 콜백 함수
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// 입력 처리 함수
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // GLFW 초기화
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 윈도우 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Tutorial", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD 초기화
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 뷰포트 설정
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 셰이더 컴파일
    Shader ourShader("D:/Project/OpenGL/shaders/basic.vert", "D:/Project/OpenGL/shaders/basic.frag");

    // 삼각형 버텍스 데이터 설정
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 왼쪽 아래
         0.5f, -0.5f, 0.0f, // 오른쪽 아래
         0.0f,  0.5f, 0.0f  // 위쪽
    };

    // VAO, VBO 설정
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // 먼저 VAO를 바인딩하고, 그 다음 VBO를 바인딩 및 설정하고, 마지막으로 버텍스 속성을 구성합니다.
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VBO 설정이 끝났으므로 unbind합니다.
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // VAO도 unbind합니다. (보통 이렇게 하지 않지만, 다른 VAO를 실수로 수정하지 않기 위해 unbind합니다.)
    glBindVertexArray(0); 

    // 와이어프레임 모드 활성화 (필요시)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 렌더링 루프
    while (!glfwWindowShouldClose(window)) {
        // 입력 처리
        processInput(window);

        // 렌더링 명령
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 셰이더 사용
        ourShader.use();
        
        // VAO 바인딩
        glBindVertexArray(VAO);
        
        // 삼각형 그리기
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 버퍼 교체 및 이벤트 처리
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 선택사항: 자원 해제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // GLFW 종료
    glfwTerminate();
    return 0;
}