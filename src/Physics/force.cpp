// vendors
// project headers
#include "force.hpp"

#include "../fwd_math.hpp"

#include "../Scene/Model.hpp"

#include "../Types/vec3.hpp"
// std library

vec3d GRAVITY = { 0.0, -9.8, 0.0 };

bool IsColliding(std::shared_ptr<IModel>& model1, std::shared_ptr<IModel>& model2)
{
    if (!model1 || !model2) 
    { 
        return false; 
    }
    
    return true;
}

void ApplyCollisionForce(std::shared_ptr<IModel>& model1, std::shared_ptr<IModel>& model2)
{
    if (!model1 || !model2) 
    { 
        return; 
    }

    return;
}

void ApplyForces(std::vector<std::shared_ptr<IModel>>& container)
{
    for (std::shared_ptr<IModel>& i_model : container) 
    {
        if (!i_model->IsPhysicalized()) 
        { 
            continue; 
        }
    
        // Apply simple gravity to the balls
        vec3d result = vec3_add(GRAVITY, i_model->GetPosition());
        const double scale = static_cast<double>(i_model->GetScale());
        //vec3_scale(settings.GRAVITY, static_cast<float>(glfwGetTime()) - lastFrameTime ,settings.GRAVITY);
        
        
        // Only apply normal gravity vector if the model would not clip into the or be below the floor
        if (((i_model->GetPosition().data[1] - scale) > -12.0) && 
            (result.data[1] - scale) >= -12.0)
        {
            i_model->SetPosition(result);
        } 
        else 
        {
            // If model's bounds has fallen below the floor reset position to floor.y + .5*model height
            result.data[1] = -12.0 + scale;
            i_model->SetPosition(result);
        }
        
        // Apply simple collision to the balls
        for (std::shared_ptr<IModel>& j_model : container) 
        {
            if (i_model == j_model) 
            { 
                continue; 
            }

            // Check for collision
            if (IsColliding(i_model, j_model)) 
            {
                // Apply the collision force response
                ApplyCollisionForce(i_model, j_model);
    
                // Output new velocities after collision
                //std::cout << "Collision Detected!\n";
                //std::cout << "Sphere 1 velocity: (" << sphere1.velocity.x << ", " << sphere1.velocity.y << ", " << sphere1.velocity.z << ")\n";
                //std::cout << "Sphere 2 velocity: (" << sphere2.velocity.x << ", " << sphere2.velocity.y << ", " << sphere2.velocity.z << ")\n";
            }
    
            // Update positions based on velocities (simple simulation)
            //i_model.position = i_model.position + i_model.velocity;
            //j_model.position = j_model.position + j_model.velocity;
        }
    }
}