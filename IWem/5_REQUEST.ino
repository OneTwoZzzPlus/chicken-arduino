#define REQ(x, y) server.on(F(x), y);
void REQUEST() {
  REQ("/", handleHello)
  REQ("/v", handleVersion)
  REQ("/request", handleRequest)
  REQ("/getWifi", handleGetWifi)
  REQ("/setWifi", handleSetWifi)
  REQ("/getAccessTg", handleGetAccessTg)
  REQ("/setAccessTg", handleSetAccessTg)
  REQ("/getToken", handleGetToken)
  REQ("/setToken", handleSetToken)
}
