from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd
import os

class BulkRecipe(ConanFile):
	name = "bulk"
	version = "1.0.0"
    
	settings = "os", "compiler", "build_type", "arch"

	def requirements(self):
		self.requires("boost/1.83.0")
        
	def layout(self):
		cmake_layout(self)

	def generate(self):
		tc = CMakeToolchain(self)
		tc.generate()
        
		deps = CMakeDeps(self)
		deps.generate()
        
	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

	def packege(self):
		cmake = CMake(self)
		cmake.install()
	
