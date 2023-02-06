// REQUEST COUNT
const int request_count = 11;

// COMMANDS
const String request_commands[] = {
  "/version",
  "/message",
  "/messageDelete",
  "/led",
  "/resetMemory",
  "/info",
  "/moduleList",
  "/moduleInfo",
  "/moduleEdit"
};

// FUNCTIONS
void (*request_functions[])() = {
  handleGetVersion,
  handleGetMessage,
  handleDeleteMessage,
  handleLed,
  handleResetMemory,
  handleInfo,
  handleModuleList,
  handleModuleInfo,
  handleModuleEdit
};
