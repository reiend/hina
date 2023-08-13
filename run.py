import os
import subprocess

# Specify the paths
source_dir = "."
build_dir = "build"
build_system = "MinGW Makefiles"

# Create the build directory if it doesn't exist
os.makedirs(build_dir, exist_ok=True)

# Run CMake to generate the build files
def generate_build_files():
    cmake_command = ["cmake", "-S", source_dir, "-B", build_dir, "-G", build_system]
    subprocess.run(cmake_command)

# Build the C++ program using make
def build_with_make():
    make_command = ["make"]
    subprocess.run(make_command, cwd=build_dir)

# Run the compiled C++ program (assuming main.exe)
def run_program(executable_name):
    cpp_program_path = os.path.join(build_dir, executable_name)
    subprocess.run([cpp_program_path])

# Clean up (optional)
def make_clean_ups():
    subprocess.run(["make", "clean"], cwd=build_dir)

generate_build_files()
build_with_make()
run_program("main.exe")
make_clean_ups()

