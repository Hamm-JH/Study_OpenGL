#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include "../shader.h"

class Triangle {
private:
    unsigned int VAO, VBO;
    Shader* shader;
    
public:
    Triangle(Shader* shaderProgram);
    ~Triangle();
    
    void draw();
};

#endif