#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>
#include "../shader.h"

class Rectangle {
private:
    unsigned int VAO, VBO, EBO;
    Shader* shader;
    
public:
    Rectangle(Shader* shaderProgram);
    ~Rectangle();
    
    void draw();
};

#endif