#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/freeglut.h>
#endif

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class GLUT_Stuff {

    // demo inferface elements
    ImVec4 clear_color;
    bool show_demo_window;
    float f = 0.0f;

    // my data
    int elementNum;
    int test;
    vector<int> elements;

    protected:
        GLUT_Stuff() :
            clear_color(ImVec4(0.45f, 0.55f, 0.60f, 1.00f)),
            show_demo_window(false),
            elementNum(0)
            { }

        static unique_ptr<GLUT_Stuff> theContext;

        void display_func() {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplGLUT_NewFrame();

            display();

            // Rendering
            ImGui::Render();
            ImGuiIO& io = ImGui::GetIO();
            glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
            glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound, but prefer using the GL3+ code.
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

            glutSwapBuffers();
            glutPostRedisplay();
        }

    public:

        static GLUT_Stuff & get() { return *theContext.get(); } // null reference exception is OK for the poor soul, who calls this prior to a call to Initialize()

        static void glut_display_func();

        ~GLUT_Stuff() {
            // Cleanup
            ImGui_ImplOpenGL2_Shutdown();
            ImGui_ImplGLUT_Shutdown();
            ImGui::DestroyContext();
        }

        void loop();

        static void Initialize(int argc, char * argv[]) {

            if (theContext.get() != nullptr)
                throw("double initialization - no, no, no!");

            theContext = unique_ptr<GLUT_Stuff>(new GLUT_Stuff());
            // Create GLUT window
            glutInit(&argc, argv);

#ifdef __FREEGLUT_EXT_H__
            glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif

            glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
            glutInitWindowSize(1280, 720);
            glutCreateWindow("Dear ImGui GLUT+OpenGL2 Example");

            // Setup GLUT display function
            // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
            // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
            glutDisplayFunc(glut_display_func);

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO(); (void)io;
            //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

            // Setup Dear ImGui style
            //ImGui::StyleColorsDark();
            ImGui::StyleColorsLight();

            // Setup Platform/Renderer backends
            ImGui_ImplGLUT_Init();
            ImGui_ImplGLUT_InstallFuncs();
            ImGui_ImplOpenGL2_Init();
        }

        void display_defaultHelloWorld() {
            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Quit!"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                exit(0);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        void display_HelloWorld() {
            ImGui::Begin("Numbers!");

            ImGui::Text("Elements: "); ImGui::SameLine();
            ImGui::InputInt("##elements", &elementNum);

            if (elementNum > 0) {
                if(elementNum != elements.size())
                    elements.resize(elementNum);
                for(int cur = 0; cur < elementNum; cur++) {
                    ImGui::PushID(cur);
                    ImGui::Text("Element %d: ", cur); ImGui::SameLine();
                    ImGui::InputInt("##inputElement", &elements[cur]);
                    ImGui::PopID();
                }
            } else {
                ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), "ERROR: Incorrect size: %d", elementNum);
            }

            if (ImGui::Button("Quit!"))
                exit(0);

            ImGui::End();
        }

        void display() {
            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
            //display_defaultHelloWorld();

            display_HelloWorld();
        }

};

unique_ptr<GLUT_Stuff> GLUT_Stuff::theContext;

void GLUT_Stuff::glut_display_func()
{
    theContext.get()->display_func();
}

void GLUT_Stuff::loop() {
    glutMainLoop();
}

int main(int argc, char * argv[]) {

    GLUT_Stuff::Initialize(argc, argv);

    GLUT_Stuff & GS = GLUT_Stuff::get();

    GS.loop();
/*
    int numberOfElements;

    cout << "Enter the number of elements: ";
    cin >> numberOfElements;
    cout << endl << "You will have " << numberOfElements
        << " elements in your queue. Now enter each element!";

    vector<int> elements(numberOfElements);
    for(size_t cur = 0; cur < numberOfElements; cur++) {
        cout << endl << "Enter element " << cur << ": ";
        cin >> elements[cur];
    }

    cout << endl << "You entered all elements. Here they are: ";
    for(auto cur : elements)
        cout << cur << " ";
    cout << endl;
*/
    return 0;
}
