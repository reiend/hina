. "$($PSScriptRoot)\..\common\common.ps1"

function Invoke-RunAppDebug {
  Invoke-RunApp `
    -build_dir "${global:SOURCE_DIR}\build" `
    -source_dir "${global:SOURCE_DIR}" `
    -generator $global:GENERATOR.VISUAL_STUDIO  `
    -build_type $global:BUILD_TYPE.DEBUG
}

Invoke-RunAppDebug
