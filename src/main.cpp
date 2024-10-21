// local
#include <map>
#include <utility>

#include "cmake.h"
#include "log/log.h"

// vendor
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vk_platform.h>
#include <vulkan/vulkan_core.h>

// std
#include <bit>
#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <stdexcept>
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

VkResult create_debug_utils_messenger_ext(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* p_info,
    const VkAllocationCallbacks* p_allocation_callback,
    VkDebugUtilsMessengerEXT* p_debug_messenger) {
  auto create = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkCreateDebugUtilsMessengerEXT");

  if (create == nullptr) return VK_ERROR_EXTENSION_NOT_PRESENT;

  return create(instance, p_info, p_allocation_callback, p_debug_messenger);
}

void destroy_debug_utils_messenger_ext(
    VkInstance instance, VkDebugUtilsMessengerEXT debug_messenger,
    const VkAllocationCallbacks* p_allocation_callback) {
  auto destroy = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");

  if (!enable_validation_layers) return;

  if (destroy == nullptr) return;

  destroy(instance, debug_messenger, p_allocation_callback);
}

class App {
 public:
  int run() {
    try {
      std::cout << "\n";
      this->display_supported_vulkan_extensions();
      this->display_supported_vulkan_validation_layers();
      display_project_meta();

      this->init_window();
      this->init_vulkan();
      this->main_loop();
      this->clean_up();
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

    this->window =
        glfwCreateWindow(WIDTH, HEIGHT, PROJECT_NAME, nullptr, nullptr);
  }

  void main_loop() {
    while (!glfwWindowShouldClose(this->window)) {
      glfwPollEvents();
    }
  }

  void clean_up() {
    destroy_debug_utils_messenger_ext(this->vk_instance,
                                      this->vk_debug_messenger, nullptr);
    vkDestroyInstance(this->vk_instance, nullptr);
    glfwDestroyWindow(this->window);
    glfwTerminate();
  }

  void init_vulkan() {
    std::cout << "init vulkan\n\n";
    create_instance();
    setup_debug_messenger();
    setup_physical_device();
  }

  void create_instance() {
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
    auto extensions = get_required_extensions();
    extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    info.pApplicationInfo = &app;
    info.enabledExtensionCount = extensions.size();
    info.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debug_info{};

    if (enable_validation_layers) {
      info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
      info.ppEnabledLayerNames = validation_layers.data();

      // added debug issues inside vkCreateIntance and vkDestroyed
      populate_debug_messenger_create_info(debug_info);
      info.pNext = &debug_info;
    } else {
      info.enabledLayerCount = 0;
      info.pNext = nullptr;
    }

    VkResult result = vkCreateInstance(&info, nullptr, &this->vk_instance);

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan instance creation failed: make sure to supply "
          "pVKInstanceCreationInfo "
          "pVKAllocationCallbacks "
          "pVKInstance "
          "correctly when invoking vkCreateInstance");
    }

    std::cout << "\nvulkan instance creation success\n\n";
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

  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debug_callback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                 VkDebugUtilsMessageTypeFlagsEXT messageType,
                 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                 void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  }

  void setup_debug_messenger() {
    if (!enable_validation_layers) return;

    VkDebugUtilsMessengerCreateInfoEXT info{};
    populate_debug_messenger_create_info(info);

    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    info.pfnUserCallback = debug_callback;
    info.pUserData = nullptr;
    info.pNext = nullptr;

    VkResult result = create_debug_utils_messenger_ext(
        this->vk_instance, &info, nullptr, &this->vk_debug_messenger);

    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan debug messenger creation failed:  make sure to supply "
          "VkInstance "
          "pVkDebugUtilsMessengerCreateInfoEXT "
          "pVkAllocationCallbacks "
          "pVkDebugUtilsMessengerEXT "
          "correctly when invoking create_debug_utils_messenger_ext");
    }
  }

  void populate_debug_messenger_create_info(
      VkDebugUtilsMessengerCreateInfoEXT& info) {
    info = {};

    info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    info.pfnUserCallback = debug_callback;
  }

  void setup_physical_device() {
    uint32_t device_count = 0;
    VkResult result =
        vkEnumeratePhysicalDevices(this->vk_instance, &device_count, nullptr);

    if ((result != VK_SUCCESS) || (device_count == 0)) {
      throw std::runtime_error(
          "vulkan get devices failed: no available device found");
    }

    std::vector<VkPhysicalDevice> devices(device_count);

    result = vkEnumeratePhysicalDevices(this->vk_instance, &device_count,
                                        devices.data());
    if (result != VK_SUCCESS) {
      throw std::runtime_error(
          "vulkan get devices failed: no available device found");
    }

    // rank physical device
    std::multimap<int, VkPhysicalDevice> candidates;
    for (const auto device : devices) {
      int score = this->rate_device_compatability(device);
      candidates.insert(std::make_pair(score, device));

      // default to discrete gpu
      // if (is_device_compatible(device)) {
      //   this->vk_device = device;
      //   break;
      // }
    }

    if ((this->vk_device == VK_NULL_HANDLE) && candidates.rbegin()->first > 0) {
      std::cout << "\nchosen device - " << candidates.rbegin()->first << "\n";
      this->vk_device = candidates.rbegin()->second;
    } else {
      throw std::runtime_error(
          "vulkan get devices failed: no available device found");
    }
  }

  bool is_device_compatible(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;

    vkGetPhysicalDeviceProperties(device, &device_properties);
    vkGetPhysicalDeviceFeatures(device, &device_features);

    if (!(device_properties.deviceType ==
              VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
          device_features.geometryShader)) {
      return false;
    }

    std::cout << device_properties.deviceType << "\n";
    std::cout << device_features.geometryShader << "\n";

    return true;
  }

  int rate_device_compatability(VkPhysicalDevice device) {
    VkPhysicalDeviceProperties device_properties;
    VkPhysicalDeviceFeatures device_features;

    vkGetPhysicalDeviceProperties(device, &device_properties);
    vkGetPhysicalDeviceFeatures(device, &device_features);

    int score = 0;

    if (device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
      score += 1000;
    }

    score += device_properties.limits.maxImageDimension2D;

    if (!device_features.geometryShader) {
      return 0;
    }

    std::cout << "\ndevices # \n";
    std::cout << "device name - " << device_properties.deviceName << "\n";
    std::cout << "device type - " << device_properties.deviceType << "\n";
    std::cout << "has geometery shader - " << device_features.geometryShader
              << "\n";
    std::cout << "score - " << score << "\n";

    return score;
  }

  GLFWwindow* window;
  VkInstance vk_instance;
  VkDebugUtilsMessengerEXT vk_debug_messenger;
  VkPhysicalDevice vk_device = VK_NULL_HANDLE;
};

int main() {
  App app;

  return app.run();
}
