#include <fmt/core.h>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "format"
#include "../include/AppState.h"
#include "../include/MainWindow.h"
#include "../include/LogWindow.h"
#include "../include/AboutWindow.h"
#include "../include/HelpWindow.h"
#include <png.h>


void SetWindowIcon(GLFWwindow* window, const char* iconPath) {
    FILE* fp = nullptr;
#ifdef _WIN32
    errno_t err = fopen_s(&fp, iconPath, "rb");
    if (err != 0 || fp == nullptr) {
        std::cerr << "Failed to open icon file: " << iconPath << std::endl;
        return;
    }
#else
    fp = fopen(iconPath, "rb");
    if (!fp) {
        std::cerr << "Failed to open icon file: " << iconPath << std::endl;
        return;
    }
#endif

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        std::cerr << "Failed to create png read struct" << std::endl;
        fclose(fp);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        std::cerr << "Failed to create png info struct" << std::endl;
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        std::cerr << "Error during png creation" << std::endl;
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        return;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    png_byte color_type = png_get_color_type(png, info);
    png_byte bit_depth = png_get_bit_depth(png, info);

    // Read any color_type into 8bit depth, RGBA format.
    // See http://www.libpng.org/pub/png/libpng-manual.txt

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    // PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    // These color_type don't have an alpha channel then fill it with 0xff.
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    png_bytep* row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    // Convert row pointers to a single buffer
    unsigned char* pixels = new unsigned char[width * height * 4];
    for (int y = 0; y < height; y++) {
        memcpy(pixels + (y * width * 4), row_pointers[y], width * 4);
        free(row_pointers[y]);
    }
    free(row_pointers);

    png_destroy_read_struct(&png, &info, NULL);

    // Set GLFWimage
    GLFWimage icon;
    icon.width = width;
    icon.height = height;
    icon.pixels = pixels;

    // Apply icon
    glfwSetWindowIcon(window, 1, &icon);

    // Cleanup
    delete[] pixels;
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1300, 500, "Bison Audio Converter", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    SetWindowIcon(window, "resources/icon.png");

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // App State and Windows
    AppState state;
    MainWindow mainWindow;
    LogWindow anotherWindow;
    SingleFileConverterWindow singleFileConverterWindow;

    // Set rounded corners for windows
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 5.0f;
    style.WindowBorderSize = 1.0f;
    style.FrameRounding = 3.0f;
    style.FrameBorderSize = 1.0f;
    style.ScrollbarRounding = 5.0f;

    ImVec4* colors = style.Colors;

// Backgrounds
    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.1f, 1.0f);   // Main Background
    colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.2f, 1.0f);   // Dim Background
    colors[ImGuiCol_PopupBg] = ImVec4(0.1f, 0.1f, 0.15f, 1.0f);    // Popup Background

// Headers
    colors[ImGuiCol_Header] = ImVec4(0.0f, 0.45f, 0.75f, 1.0f);    // Header
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.55f, 0.85f, 1.0f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.35f, 0.65f, 1.0f);

// Footer
    colors[ImGuiCol_Border] = ImVec4(0.0f, 0.6f, 0.6f, 1.0f);      // Footer

// Buttons
    colors[ImGuiCol_Button] = ImVec4(0.8f, 0.4f, 0.0f, 1.0f);      // Button Normal
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.9f, 0.55f, 0.1f, 1.0f); // Button Hover
    colors[ImGuiCol_ButtonActive] = ImVec4(0.7f, 0.35f, 0.0f, 1.0f);  // Button Active

// Text
    colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);        // Text
    colors[ImGuiCol_TextDisabled] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f); // Dimmed Text

// Highlights
    colors[ImGuiCol_SliderGrab] = ImVec4(0.6f, 0.3f, 0.8f, 1.0f);  // Highlight
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5f, 0.2f, 0.7f, 1.0f);

// Frame and Borders
    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.2f, 1.0f);   // Frame Background
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.2f, 0.25f, 1.0f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.3f, 1.0f);
    colors[ImGuiCol_Border] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);      // Borders

    // Title Colors
    colors[ImGuiCol_TitleBg] = ImVec4(0.0f, 0.45f, 0.75f, 1.0f);         // Active Title
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.0f, 0.55f, 0.85f, 1.0f);   // Title Background Active
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.3f, 0.35f, 0.4f, 1.0f); // Dimmed Title

    //set button size
    style.FramePadding = ImVec2(10.0f, 10.0f);
    style.ItemSpacing = ImVec2(10.0f, 10.0f);
    style.ItemInnerSpacing = ImVec2(10.0f, 10.0f);

    //set window size
    style.WindowPadding = ImVec2(10.0f, 10.0f);
    style.WindowMinSize = ImVec2(300.0f, 300.0f);
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

    //set slider size
    style.GrabMinSize = 20.0f;



    // Main loop
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();




        ImGui::NewFrame();

        if (state.show_demo_window) ImGui::ShowDemoWindow(&state.show_demo_window);



        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New", "Ctrl+N")) {
                    state.input_directory.clear();
                    state.output_directory.clear();
                    state.log.clear();
                }
                if (ImGui::MenuItem("Exit", "Ctrl+Q")) {
                    glfwSetWindowShouldClose(window, true);
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Main Window", nullptr, state.show_main_window)) {
                    state.show_main_window = !state.show_main_window;
                }
                if (ImGui::MenuItem("Log Window", nullptr, state.show_log_window)) {
                    state.show_log_window = !state.show_log_window;
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help")) {
                if (ImGui::MenuItem("About")) {
                    state.show_about_window = !state.show_about_window;
                }
                if (ImGui::MenuItem("Help")) {
                    state.show_help_window = !state.show_help_window;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        if (state.show_main_window) {
            MainWindow::Render(state);
        }
        if (state.show_log_window) {
            anotherWindow.Render(state);
        }
        if (state.show_about_window) {
            AboutWindow::Render(state);
        }

        if (state.show_help_window) {
            HelpWindow::Render(state);
        }
        singleFileConverterWindow.Render(state);
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + viewport->Size.y - 30));
        ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, 30));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f)); // Dark background
        ImGui::Begin("Footer", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::PopStyleColor();
        ImGui::Text("Bison Audio Converter © 2024 - All Rights Reserved Developed by: Rambod Ghashghai");
        ImGui::End();



// Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(state.clear_color.x, state.clear_color.y, state.clear_color.z, state.clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
