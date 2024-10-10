function Run-HinaMSVC {
  try {
    cmake -S . -B ./build -G "Visual Studio 17 2022"
    cmake --build ./build
    ./build/Debug/hina
  } catch {
    clear

    if(Test-Path -Path build) {
      Remove-Item build -Recurse -Force
    }

    cmake -S . -B ./build -G "Visual Studio 17 2022"
    cmake --build ./build
    ./build/Debug/hina
  }
}

Run-HinaMSVC
