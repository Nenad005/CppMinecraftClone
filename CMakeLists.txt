cmake_minimum_required(VERSION 3.0.0)
project(MojKraft VERSION 0.1.0)

set(SOURCES 
    src/Application.cpp
    src/Debug.cpp
    src/Debug.h
    RENDERING/FPSCamera.cpp
    RENDERING/FPSCamera.h  
    RENDERING/FPSCounter.cpp    
    RENDERING/FPSCounter.h    
    RENDERING/Renderer.cpp   
    RENDERING/Renderer.h    
    RENDERING/Timestep.h
    OPEN-GL/IndexBuffer.cpp
    OPEN-GL/IndexBuffer.h
    OPEN-GL/Shader.cpp
    OPEN-GL/Shader.h
    OPEN-GL/Texture.cpp
    OPEN-GL/Texture.h
    OPEN-GL/VertexArray.cpp
    OPEN-GL/VertexArray.h
    OPEN-GL/VertexBuffer.cpp
    OPEN-GL/VertexBuffer.h
    OPEN-GL/VertexBufferLayout.cpp
    OPEN-GL/VertexBufferLayout.h
    Dependencies/GLAD/src/glad.c
    Vendor/stb_image/stb_image_write.cpp
    Vendor/stb_image/stb_image_write.h
    Vendor/stb_image/stb_image.cpp
    Vendor/stb_image/stb_image.h
    Vendor/imgui/imconfig.h
    Vendor/imgui/imgui.cpp
    Vendor/imgui/imgui.h
    Vendor/imgui/imgui_demo.cpp
    Vendor/imgui/imgui_draw.cpp
    Vendor/imgui/imgui_impl_glfw.cpp
    Vendor/imgui/imgui_impl_glfw.h
    Vendor/imgui/imgui_impl_opengl3.cpp
    Vendor/imgui/imgui_impl_opengl3.h
    Vendor/imgui/imgui_impl_opengl3_loader.h
    Vendor/imgui/imgui_internal.h
    Vendor/imgui/imgui_tables.cpp
    Vendor/imgui/imgui_widgets.cpp
    Vendor/imgui/imstb_rectpack.h
    Vendor/imgui/imstb_textedit.h
    Vendor/imgui/imstb_truetype.h
    )
add_executable(MojKraft ${SOURCES})

# GLFW BIBLIOTEKA
# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include)
# include_directories(${CMAKE_SOURCE_DIR}/Dependencies/GLFW/include)
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib/libglfw3.a)

# OPENGL BIBLIOTEKA
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

# GLEW BIBLIOTEKA
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Dependencies/GLAD/include)