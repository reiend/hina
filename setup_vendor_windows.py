import urllib.request
import zipfile
import shutil
import os
import platform
import subprocess

def check_system_windows():
  if platform.system() == "Windows":
    return

  raise OSError("setup vendor failed: make sure the system windows")

def download_vendor_windows():
  folder = None

  # download vendor glfw
  if not os.path.isdir("./vendor/glfw"):
    try:
      request = urllib.request.Request("https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.bin.WIN64.zip")
      response = urllib.request.urlopen(request)
      folder = open("./temp/glfw.zip", "wb")
      shutil.copyfileobj(response, folder)
    except:
      raise ConnectionError("vendor glfw download failed: make sure there is an internet connection")

    finally:
      if folder:
        folder.close()

    try:
      file = zipfile.ZipFile("./temp/glfw.zip", "r")
      file.extractall("./temp", "")
    except:
      raise RuntimeError("vendor glfw unzip failed: make sure vendor glfw was downloaded")

  # download vendor vulkan
  if not os.path.isdir("./vendor/glfw"):
    try:
      request = urllib.request.Request("https://sdk.lunarg.com/sdk/download/1.3.296.0/windows/VulkanSDK-1.3.296.0-Installer.exe")
      request.add_header('User-Agent', 'Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:106.0) Gecko/20100101 Firefox/106.0')

      response = urllib.request.urlopen(request)
      folder = open("./temp/vulkan/vulkan-sdk.exe", "wb")
      shutil.copyfileobj(response, folder)

    except:
      raise RuntimeError("vendor vulkan download failed: make sure there is an internet connection")

    finally:
      if folder:
        folder.close()

    if not os.path.isdir(os.environ["VULKAN_SDK"]):
      subprocess.run("powershell -Command Start-Process ./temp/vulkan/vulkan-sdk.exe -Wait")

def localize_vendor_windows():
  try:
    if not os.path.isdir("./vendor/glfw/include"):
       shutil.copytree('./temp/glfw-3.4.bin.WIN64/include', './vendor/glfw/include', dirs_exist_ok=True)

    if not os.path.isdir("./vendor/glfw/lib"):
       shutil.copytree('./temp/glfw-3.4.bin.WIN64/lib-vc2022', './vendor/glfw/lib', dirs_exist_ok=True)

    if not os.path.isdir("./vendor/vulkan/include"):
       shutil.copytree('%s/include' % os.environ["VULKAN_SDK"], './vendor/vulkan/include', dirs_exist_ok=True)
    
    if not os.path.isdir("./vendor/vulkan/include"):
       shutil.copytree('%s/include' % os.environ["VULKAN_SDK"], './vendor/vulkan/include', dirs_exist_ok=True)

    if not os.path.isdir("./vendor/vulkan/Lib"):
       shutil.copytree('%s/lib' % os.environ["VULKAN_SDK"], './vendor/vulkan/lib', dirs_exist_ok=True)

    if not os.path.isdir("./vendor/glm/include"):
       shutil.move('./vendor/vulkan/include/glm', './vendor/glm/include/glm')

  except:
    raise RuntimeError("vendor localization failed: make sure the vendors are successfully downloaded and installed")
  

check_system_windows()
download_vendor_windows()
localize_vendor_windows()
