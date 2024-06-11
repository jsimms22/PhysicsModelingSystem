// project headers
#include "../include/graphics.hpp"

void drawMesh(Meshf mesh, unsigned int shaderID, GLenum mode, 
            vec4f position, vec4f rotation, float scale)
{
    vec3f scaling = { scale, scale, scale };

    struct {
        mat4x4f position;
        mat4x4f rotation;
        mat4x4f scaling;
        mat4x4f model;
    } matrices;

    /* Position */
    mat4x4_id(matrices.position);
    mat4x4_translation(matrices.position, matrices.position, position);

    /* Rotation */
    mat4x4_id(matrices.rotation);
    //mat4_from_eulers(matrices.rotation, rotation);

    /* Scaling */
    mat4x4_id(matrices.scaling);
    //mat4_scaling(matrices.scaling, matrices.scaling, scaling);

    /* Model matrix */
    mat4x4_mul(matrices.model, matrices.rotation, matrices.scaling);
    mat4x4_mul(matrices.model, matrices.position, matrices.model);

    glUseProgram(shaderID);

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"),
        1, GL_FALSE, matrices.model.data->data);

    vec4f projection;

    // mat4_perspective(projection, (M_PI /180)* 45.0, 1280.0 / 720.0, 0.1, 100.0);

    // glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"),
    //     1, GL_FALSE, projection.data);

    glBindVertexArray(mesh.VAO);

    glDrawArrays(mode, 0, mesh.numVertices);

    glUseProgram(0);

    glBindVertexArray(0);
}

void drawInstanced(Meshf mesh, unsigned int shaderID, GLenum mode, int num, float scale)
{
    glUseProgram(shaderID);

    vec4f projection{1,1,1,1};

    //mat4_perspective(projection, (M_PI /180)* 45.0, 1280.0 / 720.0, 0.1, 100.0);

    glUniformMatrix4fv(glGetUniformLocation(shaderID, "projection"),
        1, GL_FALSE, projection.data);

    glUniform1f(glGetUniformLocation(shaderID, "scale"), scale);

    glBindVertexArray(mesh.VAO);

    glDrawArraysInstanced(mode, 0, mesh.numVertices, num);

    glUseProgram(0);

    glBindVertexArray(0);
}