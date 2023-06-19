#define REQ(x, y) server.on(F(x), y);
void REQUEST() {
  REQ("/", handleHello)
  REQ("/version", handleVersion)
  REQ("/request", handleRequest)
  REQ("/getWifi", handleGetWifi)
  REQ("/setWifi", handleSetWifi)
  
  /*REQ("/led", handleLed)
  REQ("/resetMemory", handleResetMemory)
  REQ("/info", handleInfo)
  REQ("/moduleList", handleModuleList)
  REQ("/moduleInfo", handleModuleInfo)
  REQ("/moduleMode", handleModuleMode)
  REQ("/moduleEdit", handleModuleEdit)*/
}
