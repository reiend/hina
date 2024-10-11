function Run-Debug {
  param (
    $BuildPathFolder = "$($PSScriptRoot)\..\..\build",
    $BuildPathFile = "$($PSScriptRoot)\..\..\build\Debug\hina",
    $CmakeRootPathFolder = "$($PSScriptRoot)\..\..\"
  )

  $GENERATOR = "Visual Studio 17 2022"
  $BUILD_TYPE = "Debug"

  try {
    cmake -S $CmakeRootPathFolder -B $BuildPathFolder -G $GENERATOR
    cmake --build $BuildPathFolder --config $BUILD_TYPE
    Start-Process $BuildPathFile -NoNewWindow -Wait
  } catch {
    clear

    if(Test-Path -Path $BuildPathFolder) {
      Remove-Item $BuildPathFolder -Recurse -Force
    }

    cmake -S $CmakeRootPathFolder -B $BuildPathFolder -G $GENERATOR
    cmake --build $BuildPathFolder --config $BUILD_TYPE
    Start-Process $BuildPathFile -NoNewWindow -Wait
  }
}

Run-Debug
