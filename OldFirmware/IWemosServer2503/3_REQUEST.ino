void REQUEST() {
  R("/version", handleGetVersion)
  R("/message", handleGetMessage)
  R("/messageDelete", handleDeleteMessage)
  R("/led", handleLed)
  R("/resetMemory", handleResetMemory)
  R("/info", handleInfo)
  R("/moduleList", handleModuleList)
  R("/moduleInfo", handleModuleInfo)
  R("/moduleEdit", handleModuleEdit)
}
