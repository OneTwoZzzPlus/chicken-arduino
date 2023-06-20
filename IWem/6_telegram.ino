FastBot bot(token);

void event(FB_msg& msg) {
  df("TG ") D(msg.toString());
  if (msg.text == "/start" || msg.text == "/help") {
    bot.sendMessage(F(R"(Вы в белом списке контроллера. Используйте ip, который он отправляет при запуске, чтобы зайти в панель настройки в локальной сети)"), msg.chatID);
    bot.sendMessage(F(R"(Приложение: https://github.com/OneTwoZzzPlus/chicken)"), msg.chatID);
    bot.sendMessage("IP: " + WiFi.localIP().toString(), msg.chatID);
  } else {
    bot.sendMessage("Я в разработке, " + msg.username, msg.chatID);
  }
}

void setup_tg() {
  bot.attach(event_r);
  bot.setToken(token);
  bot.setChatID(chatId);
  bot.sendMessage("Запущен " + WiFi.localIP().toString());
}

/*
   FB_msg:
  userID – ID пользователя
  username – имя пользователя (в API Telegram это first_name)
  chatID – ID чата
  messageID – ID сообщения в чате
  text - текст сообщения
*/
