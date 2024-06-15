// project headers
#include "../include/graphics.hpp"

void drawMesh(Mesh& mesh, unsigned int shaderID, unsigned int mode, 
            vec3f& position, vec3f& rotation, float scale)
{
    vec3f scaling{ scale, scale, scale };

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
    mat4_eulerAngles(matrices.rotation, rotation);

    /* Scaling */
    mat4x4_id(matrices.scaling);
    mat4x4_buildScaler(matrices.scaling, matrices.scaling, scaling);

    /* Model matrix */
    mat4x4_mul(matrices.model, matrices.rotation, matrices.scaling);
    mat4x4_mul(matrices.model, matrices.position, matrices.model);

    glUseProgram(shaderID);
    glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"), 1, GL_FALSE, matrices.model.data->data);

    glBindVertexArray(mesh.VAO);
    glDrawArrays(mode, 0, mesh.vertices.size());
    glUseProgram(0);
    glBindVertexArray(0);
}

void drawInstanced(Mesh& mesh, unsigned int shaderID, unsigned int mode, int num, float scale)
{
    glUseProgram(shaderID);
    glUniform1f(glGetUniformLocation(shaderID, "scale"), scale);

    glBindVertexArray(mesh.VAO);
    glDrawArraysInstanced(mode, 0, mesh.vertices.size(), num);
    glUseProgram(0);
    glBindVertexArray(0);
}