void handleNotFound() { server.send(200, "text/plain", F("\
Command not found!  \n\
Available commands: \n\  
  '/version'        \n\  
  '/message'        \n\  
  '/messageDelete'  \n\
  '/led'            \n\  
  '/resetMemory'    \n\  
  '/info'           \n\  
  '/infoModules'    \n\  
  '/infoTimer?n='   \n\
  '/editTimer?n=&channel=&pos=&val='  \n\
  '/addTimer?channel=&pos=&val='      \n\
  '/deleteAllTimers'                  \n\
")); }
