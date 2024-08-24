//#include "fstream"
//#include "string"
//#include "cstdlib"
//#include "cmath"
//#include "Debug.h"
//#include "../OPEN-GL/IndexBuffer.h"
//#include "../OPEN-GL/VertexArray.h"
//#include "../OPEN-GL/Shader.h"
//#include "../RENDERING/FPSCounter.h"
#include "iostream"
#include "glad/glad.h"  
#include "GLFW/glfw3.h"
#include "../OPEN-GL/Texture.h"
#include "../RENDERING/Renderer.h"
#include "../RENDERING/FPSCamera.h"
#include "../RENDERING/Timestep.h"
#include "../Vendor/glm/glm.hpp"
#include "../Vendor/glm/gtc/matrix_transform.hpp"
#include "../Vendor/imgui/imgui.h"
#include "../Vendor/imgui/imgui_impl_glfw.h"
#include "../Vendor/imgui/imgui_impl_opengl3.h"
#include "../Vendor/mipmap_generator/generator.h"

#define W_WIDTH 1920
#define W_HEIGHT 1080

using std::cout;
using std::endl;

bool wireframe = false;
bool vsync = true;

bool cursor = false;
bool cursor_lock = false;

Timespep dt;
float prevTime = 0.0f;

Mouse lastMouse( 0, 0 );
bool firstMouse = true;

FPSCamera camera(0.0f, 0.0f, -3.0f);
float step = 0.004317f;

float fov = 80;

void processInput(GLFWwindow* window, FPSCamera& camera)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        if (!cursor_lock)
        {
            cursor = !cursor;
            glfwSetInputMode(window, GLFW_CURSOR, !cursor ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            cursor_lock = true;
        }
    }
    else cursor_lock = false;

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        //step = 0.005612f;
        step = 0.01f;
    }
    else
    {
        step = 0.004317f;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move(0, 0, dt.deltaTime(step, DT_MS));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move(0, 0, -dt.deltaTime(step, DT_MS));
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move(-dt.deltaTime(step, DT_MS), 0, 0);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move(dt.deltaTime(step, DT_MS), 0, 0);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.move(0, -dt.deltaTime(step, DT_MS), 0);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.move(0, dt.deltaTime(step, DT_MS), 0);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        camera.set_tp();
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        camera.tp();

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Mouse m( xpos, ypos );
    if (firstMouse)
    {
        lastMouse = m;
        firstMouse = false;
    }

    if (!cursor) camera.set_look_direction(m - lastMouse);
    lastMouse = m;
}

int main(void)
{
    {
        generator g;
        g.generate("../res/atlas.png", 4);
    }

    {
        GLFWwindow* window;

        if (!glfwInit())
            return -1;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        glfwMakeContextCurrent(window);
        glfwSwapInterval(vsync ? 1 : 0);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // if (glewInit() != GLEW_OK)
        //     cout << "[GLEW Error!] --> couldn't initalize GLEW" << endl;

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            cout << "Failed to initialize GLAD" << endl;
            return -1;
        }

        cout << "Version : " << glGetString(GL_VERSION) << endl;

        std::vector<float> positions {
            1, 0, 0, 2, 15, 0, //napred
            0, 0, 0, 2, 15, 1,
            1, 1, 0, 2, 15, 2,
            0, 1, 0, 2, 15, 3,
                  
            1, 0, 1, 2, 15, 0, //levo
            1, 0, 0, 2, 15, 1,
            1, 1, 1, 2, 15, 2,
            1, 1, 0, 2, 15, 3,
             
            0, 0, 0, 2, 15, 0, //desno
            0, 0, 1, 2, 15, 1,
            0, 1, 0, 2, 15, 2,
            0, 1, 1, 2, 15, 3,
       
            0, 0, 1, 2, 15, 0, //iza
            1, 0, 1, 2, 15, 1,
            0, 1, 1, 2, 15, 2,
            1, 1, 1, 2, 15, 3,
      
            1, 1, 0, 2, 15, 0,
            0, 1, 0, 2, 15, 1, //gore
            1, 1, 1, 2, 15, 2,
            0, 1, 1, 2, 15, 3,
                    
            0, 0, 0, 2, 15, 0, //dole
            1, 0, 0, 2, 15, 1,
            0, 0, 1, 2, 15, 2,
            1, 0, 1, 2, 15, 3,
        };

        std::vector<unsigned int> indicesV {
            0 + 0 * 4, 3 + 0 * 4, 1 + 0 * 4, 0 + 0 * 4, 2 + 0 * 4, 3 + 0 * 4,
            0 + 1 * 4, 3 + 1 * 4, 1 + 1 * 4, 0 + 1 * 4, 2 + 1 * 4, 3 + 1 * 4,
            0 + 2 * 4, 3 + 2 * 4, 1 + 2 * 4, 0 + 2 * 4, 2 + 2 * 4, 3 + 2 * 4,
            0 + 3 * 4, 3 + 3 * 4, 1 + 3 * 4, 0 + 3 * 4, 2 + 3 * 4, 3 + 3 * 4,
            0 + 4 * 4, 3 + 4 * 4, 1 + 4 * 4, 0 + 4 * 4, 2 + 4 * 4, 3 + 4 * 4,
            0 + 5 * 4, 3 + 5 * 4, 1 + 5 * 4, 0 + 5 * 4, 2 + 5 * 4, 3 + 5 * 4,
        };

        int n = 500;
        for (int i = 1; i < n * n; i++)
        {
            glm::vec3 off(i % n, 0, i / n);
            for (int j = 0; j < 6; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    positions.push_back(positions[j * 24 + k * 6 + 0] + off.x);
                    positions.push_back(positions[j * 24 + k * 6 + 1] + off.z);
                    positions.push_back(positions[j * 24 + k * 6 + 2]);
                    positions.push_back(positions[j * 24 + k * 6 + 3]);
                    positions.push_back(positions[j * 24 + k * 6 + 4]);
                    positions.push_back(positions[j * 24 + k * 6 + 5]);
                }
                indicesV.push_back(0 + ( j + i * 6) * 4);
                indicesV.push_back(3 + ( j + i * 6) * 4);
                indicesV.push_back(1 + ( j + i * 6) * 4);
                indicesV.push_back(0 + ( j + i * 6) * 4);
                indicesV.push_back(2 + ( j + i * 6) * 4);
                indicesV.push_back(3 + ( j + i * 6) * 4);
            }
        }


        VertexArray va;
        VertexBuffer vb((void*)&positions[0], positions.size() * sizeof(float));   
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        va.add_buffer(vb, layout);

        IndexBuffer ib(&indicesV[0], indicesV.size());

        Shader shader("../GLSL/basic.shader", true);
        shader.bind();

        va.unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        Texture texture("../res/atlas.png");
        texture.bind(1);

        float x = 0;
        float y = 0;
        float z = -3;

        shader.set_uniform1i("u_Texture", 1);

        shader.unbind();

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
        glm::vec3 color(0.5f, 0.6f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

        std::vector<float> frames(0);
        for (int i = 0; i < 100; i++) frames.push_back(0);
        int n_frames = 0;

        while (!glfwWindowShouldClose(window))
        {
            float time = (float)glfwGetTime();
            dt = time - prevTime;
            prevTime = time;

            float fps = ImGui::GetIO().Framerate;
            // float fps = 60;
            n_frames++;

            processInput(window, camera);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            glClearColor(color.x, color.y, color.z, 1.0f);
            renderer.clear();

            shader.bind();

            if (n_frames % 10 == 0)
            {
                for (size_t i = 1; i < frames.size(); i++) frames[i - 1] = frames[i];
                frames[frames.size() - 1] = fps;
            }

            {
                ImGui::Begin("Hello, world!");

                ImGui::Text("Render time :  %.2f ms/frame (%.1f FPS)", 1000.0f / fps, fps);
                ImGui::PlotHistogram("FPS", &frames[0], frames.size(), 0, NULL, 0.0f, 240.0f, ImVec2(300, 100));
                ImGui::Text(camera.log_pos_string().c_str());
                ImGui::Text(camera.log_dir_string().c_str());
                for (int i = 0; i < 5; i++) ImGui::Spacing();

                ImGui::PushItemWidth(46);
                ImGui::InputFloat(":X", &camera.tpPos.x, 0, 0, "%.1f", 0);
                ImGui::SameLine();
                ImGui::InputFloat(":Y", &camera.tpPos.y, 0, 0, "%.1f", 0);
                ImGui::SameLine();
                ImGui::InputFloat(":Z", &camera.tpPos.z, 0, 0, "%.1f", 0);
                ImGui::SameLine();
                if (ImGui::Button("TP")) camera.tp();

                ImGui::PushItemWidth(0);

                if ( ImGui::Checkbox("Wireframe", &wireframe) )
                    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
                if (ImGui::Checkbox("V-Sync", &vsync))
                    glfwSwapInterval(vsync ? 1 : 0);

                ImGui::SliderFloat("FOV", &fov, 30.0f, 130.0f, "%.2f", ImGuiSliderFlags_AlwaysClamp);
                ImGui::ColorEdit3("Sky color", (float*)&color);
                ImGui::End();

            }
            glm::mat4 proj = glm::perspective(glm::radians(fov), (float)W_WIDTH / (float)W_HEIGHT, 0.01f, 1000.0f);
            //glm::mat4 test = glm::scale(2.0f, 2.0f, 2.0f);
            glm::mat4 temp = proj * camera.get_matrix();
            //temp = glm::scale(temp, glm::vec3(0.1f, 0.1f, 0.1f));

           
            shader.set_uniformMat4("proj", temp);
            renderer.draw(va, ib, shader);

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            GLCall(glfwSwapBuffers(window));
            GLCall(glfwPollEvents());
        }
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}