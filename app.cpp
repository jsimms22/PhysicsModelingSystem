// vendors
// project headers
#include "src/Core/Application.hpp"
// std library
#include <memory>

int main(int argc, char** argv)
{
    std::shared_ptr<Application> spApp = Application::Create();
    
    spApp->Run();

    return 0;
}