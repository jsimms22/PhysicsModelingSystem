// vendors
// project headers
#include "../Core/Application.hpp"
// std library
#include <memory>

int main(int argc, char** argv)
{
    std::unique_ptr<Application> app = std::make_unique<Application>();
    
    app->Run();

    return 0;
}