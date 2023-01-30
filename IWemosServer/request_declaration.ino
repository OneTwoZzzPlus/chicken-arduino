// REQUEST COUNT
const int request_count = 10;

// COMMANDS
const String request_commands[] = {
  "/version",
  "/message",
  "/messageDelete",
  "/led",
  "/resetMemory",
  "/info",
  "/infoModules",
  "/infoTimer",
  "/editTimer",
  "/addTimer",
  "/deleteAllTimers"
};

// FUNCTIONS
void (*request_functions[])() = {
  handleGetVersion,
  handleGetMessage,
  handleDeleteMessage,
  handleLed,
  handleResetMemory,
  handleInfo,
  handleInfoModules,
  handleInfoTimer,
  handleEditTimer,
  handleAddTimer,
  handleDeleteAllTimers
};

// ERRORS NAME
const struct {
  String ERROR_FEW_ARGUMENTS = "100";
} ERRORS;
