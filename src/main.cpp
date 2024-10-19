// local
#include "cmake.h"
#include "log/log.h"

// vendor
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "vulkan/vulkan_core.h"

// std
#include <bit>
#include <cstdint>
#include <exception>
#include <iostream>

#define STANDARD_VULKAN "0"

class App {
 public:
  void run() {
    display_project_meta();
    init_window();
    init_vulkan();
    // main_loop();
    clean_up();
  }

 private:
  void init_window() {
    std::cout << "init window\n";
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    const uint32_t WIDTH = 1000;
    const uint32_t HEIGHT = 800;

    this->m_window =
        glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);
  }

  void main_loop() {
    while (!glfwWindowShouldClose(this->m_window)) {
      glfwPollEvents();
    }
  }

  void clean_up() {
    glfwDestroyWindow(this->m_window);
    glfwTerminate();
  }

  void init_vulkan() {
    std::cout << "init vulkan\n";
    createInstance();
  }

  void createInstance() {
    VkApplicationInfo app{};

    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName = PROJECT_NAME;
    app.applicationVersion =
        VK_MAKE_API_VERSION(std::bit_cast<uint64_t>(&STANDARD_VULKAN),
                            std::bit_cast<uint64_t>(&PROJECT_VERSION_MAJOR),
                            std::bit_cast<uint64_t>(&PROJECT_VERSION_MINOR),
                            std::bit_cast<uint64_t>(&PROJECT_VERSION_PATCH));
    app.pEngineName = PROJECT_NAME;
    app.engineVersion =
        VK_MAKE_API_VERSION(std::bit_cast<uint64_t>(&STANDARD_VULKAN),
                            std::bit_cast<uint64_t>(&PROJECT_VERSION_MAJOR),
                            std::bit_cast<uint64_t>(&PROJECT_VERSION_MINOR),
                            std::bit_cast<uint64_t>(&PROJECT_VERSION_PATCH));
    app.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pApplicationInfo = &app;

    uint32_t glfw_extension_count = 0;
    const char** glfw_extension =
        glfwGetRequiredInstanceExtensions(&glfw_extension_count);

    info.enabledExtensionCount = glfw_extension_count;
    info.ppEnabledExtensionNames = glfw_extension;

    info.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&info, nullptr, &this->m_vk_instance);

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan instance creation failed: make sure to supply "
          "pVKInstanceCreationInfo "
          "pVKAllocationCallbacks "
          "pVKInstance"
          "correctly when invoking vkCreateInstance");
    }

    std::cout << "vulkan instance creation success";
  }

  GLFWwindow* m_window;
  VkInstance m_vk_instance;
};

int run_app() {
  try {
    App app;
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int main() { return run_app(); }
