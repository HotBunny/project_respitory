// serverLogic.h
#ifndef SERVER_LOGIC_H
#define SERVER_LOGIC_H

#include <string>

struct User;
struct ChatRoom;

bool registerUser(const std::string& username, int clientSocket);
bool authenticateUser(const std::string& username, int clientSocket);
void disconnectUser(int clientSocket);
bool joinChatRoom(const std::string& username, const std::string& roomName);
bool leaveChatRoom(const std::string& username, const std::string& roomName);
void broadcastMessage(const std::string& sender, const std::string& roomName, const std::string& message);

#endif  // SERVER_LOGIC_H

