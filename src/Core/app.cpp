// vendors
// project headers
#include "../Core/Application.hpp"
// std library
#include <memory>

int main(int argc, char** argv)
{
    auto app = Application::Create();

    std::cout << "Current App reference count: " << app.use_count() << std::endl;
    
    app->Run();

    return 0;
}