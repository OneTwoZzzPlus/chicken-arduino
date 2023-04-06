void REQUEST() {
  REQ("/version", handleVersion)
  REQ("/led", handleLed)
  REQ("/resetMemory", handleResetMemory)
  REQ("/info", handleInfo)
  REQ("/moduleList", handleModuleList)
  REQ("/moduleInfo", handleModuleInfo)
  REQ("/moduleMode", handleModuleMode)
  REQ("/moduleEdit", handleModuleEdit)
}
