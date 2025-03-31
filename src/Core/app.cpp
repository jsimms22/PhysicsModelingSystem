// vendors
// project headers
#include "../Core/Application.hpp"
// std library
#include <memory>

int main(int argc, char** argv)
{
    auto app = Application::GetApplication();
    
    app->Run();

    return 0;
}