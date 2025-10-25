cmake -DGLFW_BUILD_DOCS=off -DPLATFORM_IMPL_OS=Windows -DPLATFORM_IMPL_RENDER=OpenGL -G "Unix Makefiles" -S . -B bin/build

make -C bin/build