// local
#include <cstring>
#include <stdexcept>

#include "cmake.h"
#include "log/log.h"

// vendor
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

// std
#include <bit>
#include <cstdint>
#include <exception>
#include <iostream>
#include <vector>

#define STANDARD_VULKAN "0"

const uint32_t WIDTH = 1000;
const uint32_t HEIGHT = 800;

const std::vector<const char*> validation_layers = {
    "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enable_validation_layers = false;
#else
const bool enable_validation_layers = true;
#endif

class App {
 public:
  int run() {
    try {
      display_project_meta();
      init_window();
      init_vulkan();
      main_loop();
      clean_up();

    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }

 private:
  void init_window() {
    std::cout << "init window\n";
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    this->m_window =
        glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);
  }

  void main_loop() {
    while (!glfwWindowShouldClose(this->m_window)) {
      glfwPollEvents();
    }
  }

  void clean_up() {
    vkDestroyInstance(this->m_vk_instance, nullptr);
    glfwDestroyWindow(this->m_window);
    glfwTerminate();
  }

  void init_vulkan() {
    std::cout << "init vulkan\n";
    createInstance();
    display_supported_vulkan_extensions();
    display_supported_vulkan_validation_layers();
  }

  void createInstance() {
    if (enable_validation_layers &&
        !check_supported_vulkan_validation_layers()) {
      throw std::runtime_error(
          "vulkan validation layer request failed: "
          "make sure vulkan validation layer is available");
    }

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

    if (enable_validation_layers) {
      info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
      info.ppEnabledLayerNames = validation_layers.data();
    } else {
      info.enabledLayerCount = 0;
    }

    auto extensions = get_required_extensions();
    extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    info.pApplicationInfo = &app;
    info.enabledExtensionCount = extensions.size();
    info.ppEnabledExtensionNames = extensions.data();

    VkResult result = vkCreateInstance(&info, nullptr, &this->m_vk_instance);

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan instance creation failed: make sure to supply "
          "pVKInstanceCreationInfo "
          "pVKAllocationCallbacks "
          "pVKInstance"
          "correctly when invoking vkCreateInstance");
    }

    std::cout << "vulkan instance creation success\n\n";
  }

  void display_supported_vulkan_extensions() {
    VkResult result;
    uint32_t extension_count = 0;

    result = vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
                                                    nullptr);

    if (result != VK_SUCCESS) {
      throw std::runtime_error("vulkan get supported extension count failed");
    }

    std::vector<VkExtensionProperties> extensions(extension_count);
    result = vkEnumerateInstanceExtensionProperties(nullptr, &extension_count,
                                                    extensions.data());

    if (result != VK_SUCCESS) {
      throw std::runtime_error("vulkan get supported extension names failed");
    }

    std::cout << "Supported Vulkan Extensions\n";

    for (const auto extension : extensions) {
      std::cout << extension.extensionName << " - " << extension.specVersion
                << "\n";
    }
    std::cout << "\n";
  }

  void display_supported_vulkan_validation_layers() {
    VkResult result;
    uint32_t layer_count = 0;

    result = vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan get supported validation layer count failed");
    }

    std::vector<VkLayerProperties> supported_validation_layers(layer_count);
    result = vkEnumerateInstanceLayerProperties(
        &layer_count, supported_validation_layers.data());

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan get supported validation layer name failed");
    }

    std::cout << "Supported Validation Layer\n";
    for (const auto layer : supported_validation_layers) {
      std::cout << layer.layerName << " - " << layer.description << "\n";
    }

    std::cout << "\n";
  }

  bool check_supported_vulkan_validation_layers() {
    VkResult result;
    uint32_t layer_count = 0;

    result = vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan get supported validation layer count failed");
    }

    std::vector<VkLayerProperties> supported_validation_layers(layer_count);
    result = vkEnumerateInstanceLayerProperties(
        &layer_count, supported_validation_layers.data());

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan get supported validation layer name failed");
    }

    bool layer_found = true;

    for (const auto validation_layer : validation_layers) {
      for (const auto supported_validation_layer :
           supported_validation_layers) {
        if (strcmp(validation_layer, supported_validation_layer.layerName) ==
            0) {
          layer_found = true;
        }
      }

      if (!layer_found) return false;
    }

    return layer_found;
  }

  std::vector<const char*> get_required_extensions() {
    uint32_t glfw_extensions_count = 0;
    const char** glfw_extensions =
        glfwGetRequiredInstanceExtensions(&glfw_extensions_count);

    std::vector<const char*> extensions(
        glfw_extensions, glfw_extensions + glfw_extensions_count);

    if (enable_validation_layers) {
      extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
  }

  GLFWwindow* m_window;
  VkInstance m_vk_instance;
};

int main() {
  App app;

  return app.run();
}
