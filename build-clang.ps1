function Run-HinaClang {
  try {
    cmake -S . -B ./build -G Ninja
    ninja -C ./build
    ./build/hina
  } catch {
    clear

    if(Test-Path -Path build) {
      Remove-Item build -Recurse -Force
    }

    cmake -S . -B ./build -G Ninja
    ninja -C ./build
    ./build/hina
  }
}

Run-HinaClang
