// vendors
#define GLFW_INCLUDE_NONE
#include "../../vendor/GL/include/GL/glew.h"
#include "../../vendor/GLFW/include/GLFW/glfw3.h"
// project headers
#include "../Renderer/VertexArray.hpp"
// std library

void VertexArray::LinkAttribute(VertexBuffer& VBO, 
                                std::uint32_t order, 
                                int layout, 
                                std::uint32_t type, 
                                int stride, 
                                void* offset)
{
    VBO.Bind();
    if (type == GL_DOUBLE) 
    {
        // must be used for attributes defined to be double precision
        glVertexAttribLPointer(order, layout, type, stride, offset);
    } 
    else 
    {
        // will implicitly convert to single precision float
        // GL_FALSE: do not normalize
        // GL_TRUE: normalize [-1,1] for integers, [0,1] for floats
        glVertexAttribPointer(order, layout, type, GL_FALSE, stride, offset);
    }
    
    glEnableVertexAttribArray(order);
    VBO.Unbind();
}