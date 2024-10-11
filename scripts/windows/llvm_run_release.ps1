function Run-Release {
  param (
    $BuildPathFolder = "$($PSScriptRoot)\..\..\build",
    $BuildPathFile = "$($PSScriptRoot)\..\..\build\hina",
    $CmakeRootPathFolder = "$($PSScriptRoot)\..\..\"
  )

  $GENERATOR = "Ninja"
  $BUILD_TYPE = "Release"

  try {
    cmake -S $CmakeRootPathFolder -B $BuildPathFolder -G $GENERATOR -DCMAKE_BUILD_TYPE="$($BUILD_TYPE)"
    ninja -C $BuildPathFolder
    Start-Process $BuildPathFile -NoNewWindow -Wait
  } catch {
    clear

    if(Test-Path -Path $BuildPathFolder) {
      Remove-Item $BuildPathFolder -Recurse -Force
    }

    cmake -S $CmakeRootPathFolder -B $BuildPathFolder -G $GENERATOR -DCMAKE_BUILD_TYPE="$($BUILD_TYPE)"
    ninja -C $BuildPathFolder
    Start-Process $BuildPathFile -NoNewWindow -Wait
  }
}

Run-Release
