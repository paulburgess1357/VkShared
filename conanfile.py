from conans import ConanFile, CMake

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
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "VkShared/*"
    requires = "vulkan-loader/1.3.216.0"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["VkShared"]
