// project headers
#include "../include/camera.hpp"

// Camera createCamera(vec3f position)
// {
//     Camera* camera = malloc(sizeof(Camera));
//     vec3_assign(camera->position, position);
//     camera->yaw = -90;
//     camera->pitch = 0;
//     updateVectors(camera);
//     return camera;
// }

// void updateVectors(Camera& camera)
// {
//     vec3(camera.forwards,
//         cos(MRADIANS(camera->yaw)) * cos(MRADIANS(camera->pitch)),
//         sin(MRADIANS(camera->pitch)),
//         sin(MRADIANS(camera->yaw)) * cos(MRADIANS(camera->pitch)));

//     vec3_normalize(camera->forwards, camera->forwards);
//     vec3_cross(camera->right, camera->forwards, (mfloat_t[])GLOBAL_UP);
//     vec3_normalize(camera->right, camera->right);
//     vec3_cross(camera->up, camera->right, camera->forwards);
//     vec3_normalize(camera->up, camera->up);
// }

// mfloat_t* createViewMatrix(mfloat_t* viewMatrix, Camera* camera)
// {
//     updateVectors(camera);
//     mfloat_t target[VEC3_SIZE];
//     vec3_add(target, camera->position, camera->forwards);
//     mat4_look_at(viewMatrix, camera->position, target, camera->up);
//     return viewMatrix;
// }