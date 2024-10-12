. "$($PSScriptRoot)\..\common\common.ps1"

function Invoke-RunAppRelease {
  Invoke-RunApp `
    -build_dir "${global:SOURCE_DIR}\build" `
    -binary_dir "${global:SOURCE_DIR}\build\bin" `
    -source_dir "${global:SOURCE_DIR}" `
    -generator $global:GENERATOR.VISUAL_STUDIO  `
    -build_type $global:BUILD_TYPE.RELEASE
}


Invoke-RunAppRelease
