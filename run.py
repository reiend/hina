import os
import shutil
import subprocess

# Specify the paths
source_dir = "."
build_dir = "build"
cache_dir = ".cache"
# build_system = "MinGW Makefiles"
build_system = "Ninja"

# Create the build directory if it doesn't exist
os.makedirs(build_dir, exist_ok=True)

def delete_build_files():
    is_path_exist = os.path.exists(build_dir)
    if(is_path_exist):
      shutil.rmtree(build_dir)

    is_path_exist = os.path.exists(cache_dir)
    if(is_path_exist):
      shutil.rmtree(cache_dir)

# Run CMake to generate the build files
def generate_build_files():
    cmake_command = ["cmake", "-Wno-dev", "-S", source_dir, "-B", build_dir, "-G", build_system]
    subprocess.run(cmake_command, shell=True)

# Build the C++ program using desired build tool
def build_with_make():
    make_command = ["ninja"]
    # make_command = ["make"]
    subprocess.run(make_command, cwd=build_dir, shell=True)

# Run the compiled C++ program (assuming main.exe)
def run_program(executable_name):
    cpp_program_path = os.path.join(build_dir, executable_name)
    subprocess.run([cpp_program_path], shell=True)

def clean_terminal():
    os.system("cls")

delete_build_files()
generate_build_files()
build_with_make()
# clean_terminal()
run_program("main.exe")

