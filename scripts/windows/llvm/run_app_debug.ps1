. "$($PSScriptRoot)\..\common\common.ps1"

function Invoke-RunAppDebug {
  Invoke-RunApp `
    -build_dir "${global:SOURCE_DIR}\build" `
    -binary_dir "${global:SOURCE_DIR}\build\bin" `
    -source_dir "${global:SOURCE_DIR}" `
    -generator $global:GENERATOR.NINJA  `
    -build_type $global:BUILD_TYPE.DEBUG
}

Invoke-RunAppDebug
