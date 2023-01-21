// REQUEST COUNT
const int request_count = 5;

// COMMANDS
const String request_commands[] = {
  "/version",
  "/message",
  "/info",
  "/settings",
  "/led"
};

// FUNCTIONS
void (*request_functions[])() = {
  handleGetVersion,
  handleGetMessage,
  handleInfo,
  handleSetSettings,
  handleLed
};

// ERRORS NAME
const struct {
  String ERROR_FEW_ARGUMENTS = "100";
} ERRORS;
