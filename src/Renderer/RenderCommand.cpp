// vendors
// project headers
#include "../Renderer/RenderCommand.hpp"
// std library

std::unique_ptr<RenderAPI> RenderCommand::s_renderAPI = RenderAPI::Create();