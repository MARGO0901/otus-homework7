from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
from conan.tools.build import check_min_cppstd
import os

class BulkRecipe(ConanFile):
	name = "bulk"
	version = "1.0.0"
    
	settings = "os", "compiler", "build_type", "arch"
	exports_sources = "CMakeLists.txt", "src/*"  # ТОЛЬКО src, без tests

	def requirements(self):
		self.requires("boost/1.83.0")
        
	def layout(self):
		cmake_layout(self)

	def generate(self):
		tc = CMakeToolchain(self)
		tc.variables["BUILD_TESTING"] = False
		tc.generate()
        
		deps = CMakeDeps(self)
		deps.generate()
        
	def build(self):
		cmake = CMake(self)
		cmake.configure()
		cmake.build()

		# Собираем тесты сразу после основной сборки
		source_folder = self.folders.source_folder
		build_folder = self.build_folder
		
		print(f"Source folder: {source_folder}")
		print(f"Build folder: {build_folder}")
		
		compile_cmd = (
		    f"cd {build_folder} && "
		    f"g++ -std=c++17 -DBOOST_TEST_DYN_LINK "
		    f"-I{source_folder}/tests -I{source_folder}/src "
		    f"-I./conan/include "
		    f"{source_folder}/tests/tests.cpp "
		    f"-L./conan/lib "
		    f"-lboost_unit_test_framework -lboost_filesystem -lboost_system "
		    f"-o test_bulk"
		)
		
		self.run(compile_cmd)
	
