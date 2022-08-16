from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class HelloConan(ConanFile):
    name = "VkShared"
    version = "0.1"

    # Optional metadata
    license = "MIT"
    author = "<Paul Burgess> <paulburgess1357@gmail.com>"
    url = "https://github.com/paulburgess1357/VkShared"
    description = "Vulkan Shared"

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    exports_sources = "CMakeLists.txt", "VkShared/*"
    
    requires = "vulkan-loader/1.3.216.0"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["VkShared"]
