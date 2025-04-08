#include "Rectangle.h"

Rectangle::Rectangle(Shader* shaderProgram) {
    shader = shaderProgram;
    
    // 사각형 버텍스 데이터 설정 (4개의 정점)
    float vertices[] = {
         0.5f,  0.5f, 0.0f,  // 우측 상단
         0.5f, -0.5f, 0.0f,  // 우측 하단
        -0.5f, -0.5f, 0.0f,  // 좌측 하단
        -0.5f,  0.5f, 0.0f   // 좌측 상단
    };
    
    // 인덱스 배열 - 삼각형 2개로 사각형 구성
    unsigned int indices[] = {
        0, 1, 3,  // 첫 번째 삼각형
        1, 2, 3   // 두 번째 삼각형
    };

    // VAO, VBO, EBO 설정
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // 먼저 VAO를 바인딩
    glBindVertexArray(VAO);

    // VBO를 바인딩하고 데이터 설정
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO를 바인딩하고 인덱스 데이터 설정
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 정점 속성 포인터 설정
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // VBO 바인딩 해제
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // VAO 바인딩 해제 (EBO는 VAO에 의해 기억되므로 VAO 이후에 바인딩 해제)
    glBindVertexArray(0); 
}

Rectangle::~Rectangle() {
    // 자원 해제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Rectangle::draw() {
    // 셰이더 사용
    shader->use();
    
    // VAO 바인딩
    glBindVertexArray(VAO);
    
    // EBO를 사용하여 사각형 그리기 (인덱스 버퍼 사용)
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    // 바인딩 해제 (선택사항)
    glBindVertexArray(0);
}