$global:SOURCE_DIR = "$($PSScriptRoot)\..\..\.."

$global:GENERATOR = @{
  NINJA = "Ninja"
  VISUAL_STUDIO = "Visual Studio 17 2022"
}

$global:BUILD_TYPE = @{
  DEBUG = "Debug"
  RELEASE = "Release"
}

function Invoke-RunApp {
  param (
    $build_dir = "${global:SOURCE_DIR}\build",
    $binary_dir = "${global:SOURCE_DIR}\build\bin",
    $source_dir = "${global:SOURCE_DIR}",
    $generator = $global:GENERATOR.NINJA,
    $build_type = $global:BUILD_TYPE.DEBUG
  )

  switch($generator) {
    $global:GENERATOR.NINJA {
      $binary_path_file = "${binary_dir}\hina"

      try {
        cmake -S $source_dir -B $build_dir -G $generator -DCMAKE_BUILD_TYPE="${build_type}" *> $null

        if($LASTEXITCODE -ne 0) {
          throw "project generate failed"
        }

        ninja -C $build_dir
        & $binary_path_file
      } catch {
        cmake -S $source_dir -B $build_dir -G $generator -DCMAKE_BUILD_TYPE="${build_type}" --fresh

        if($LASTEXITCODE -ne 0) {
          return
        }

        ninja -C $build_dir
        & $binary_path_file
      }
    }

    $global:GENERATOR.VISUAL_STUDIO {
      $binary_path_file = "${binary_dir}\${build_type}\hina"

      try {
        cmake -S $source_dir -B $build_dir -G $GENERATOR *> $null

        if($LASTEXITCODE -ne 0) {
          throw "project generate failed"
        }

        cmake --build $build_dir --config "${build_type}"

        & $binary_path_file
      } catch {
        cmake -S $source_dir -B $build_dir -G $GENERATOR --fresh

        if($LASTEXITCODE -ne 0) {
          return
        }

        cmake --build $build_dir --config "${build_type}"
        & $binary_path_file
      }
    }
  }
}
