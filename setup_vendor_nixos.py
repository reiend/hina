import platform
import os
import shutil
import subprocess

def download_vendor_nixos():
  try:
    os.environ["vendor_glfw"]
    os.environ["vendor_vulkan_header"]
    os.environ["vendor_vulkan_loader"]
    os.environ["vendor_glm"]
    os.environ["vendor_gl"]
  except:
    raise RuntimeError("vendor download failed: shell variables doesn't exist make sure to download vendors using nixpkgs and set the shell variables via nix-shell")

def localize_vendor_nixos():
  try:
    if platform.freedesktop_os_release()["NAME"] == "NixOS":
      if not os.path.isdir("./vendor/glfw/include"):
        shutil.copytree('%s/include' % os.environ["vendor_glfw"], './vendor/glfw/include', dirs_exist_ok=True)

      if not os.path.isdir("./vendor/glfw/lib"):
        shutil.copytree('%s/lib' % os.environ["vendor_glfw"], './vendor/glfw/lib', dirs_exist_ok=True)

      if not os.path.isdir("./vendor/vulkan/include"):
        shutil.copytree('%s/include' % os.environ["vendor_vulkan_header"], './vendor/vulkan/include', dirs_exist_ok=True)

      if not os.path.isdir("./vendor/vulkan/lib"):
        shutil.copytree('%s/lib' % os.environ["vendor_vulkan_loader"], './vendor/vulkan/lib', dirs_exist_ok=True)

      if not os.path.isdir("./vendor/glm/include"):
        shutil.copytree('%s/include' % os.environ["vendor_glm"], './vendor/glm/include', dirs_exist_ok=True)

      if not os.path.isdir("./vendor/gl/include"):
        shutil.copytree('%s/include' % os.environ["vendor_gl"], './vendor/gl/include', dirs_exist_ok=True)
  except:
    raise RuntimeError("vendor localization failed: shell variables doesn't exist make sure to download vendors using nixpkgs and set the shell variables via nix-shell")

download_vendor_nixos()
localize_vendor_nixos()
