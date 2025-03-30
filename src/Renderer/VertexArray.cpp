// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/glew.h"
#include "../../vendor/GLFW/include/glfw3.h"
// project headers
#include "../Renderer/VertexArray.hpp"
// std library

void VertexArray::LinkAttribute(VertexBuffer& VBO, 
                                uint32_t order, 
                                int layout, 
                                uint32_t type, 
                                int stride, 
                                void* offset)
{
    VBO.Bind();
    glVertexAttribPointer(order, layout, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(order);
    VBO.Unbind();
}