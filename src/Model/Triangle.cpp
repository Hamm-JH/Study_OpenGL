#include "Triangle.h"

Triangle::Triangle(Shader* shaderProgram) {
    shader = shaderProgram;
    
    // 삼각형 버텍스 데이터 설정
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // 왼쪽 아래
         0.5f, -0.5f, 0.0f, // 오른쪽 아래
         0.0f,  0.5f, 0.0f  // 위쪽
    };

    // VAO, VBO 설정
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

    // VAO도 unbind합니다.
    glBindVertexArray(0); 
}

Triangle::~Triangle() {
    // 자원 해제
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Triangle::draw() {
    // 셰이더 사용
    shader->use();
    
    // VAO 바인딩
    glBindVertexArray(VAO);
    
    // 삼각형 그리기
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // 바인딩 해제 (선택사항)
    glBindVertexArray(0);
}