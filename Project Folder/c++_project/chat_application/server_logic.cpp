// serverLogic.cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <thread>
#include <mutex>
#include "ServerLogic.h"  // Include the corresponding header file

// Define a structure to represent a user
struct User {
    std::string username;
    int socket;
    // Add more user-related data as needed
};

// Define a structure to represent a chat room
struct ChatRoom {
    std::string name;
    std::vector<User> members;
    // Add more chat room-related data as needed
};

// Mutex for thread safety
std::mutex mutex;

// Vector to store connected users
std::vector<User> connectedUsers;

// Vector to store active chat rooms
std::vector<ChatRoom> chatRooms;

// Function to handle user registration
bool registerUser(const std::string& username, int clientSocket) {
    std::lock_guard<std::mutex> lock(mutex);

    // Check if the username is already taken
    for (const User& user : connectedUsers) {
        if (user.username == username) {
            return false; // Username already taken
        }
    }

    // Register the new user
    User newUser;
    newUser.username = username;
    newUser.socket = clientSocket;
    connectedUsers.push_back(newUser);

    return true;
}

// Function to handle user authentication
bool authenticateUser(const std::string& username, int clientSocket) {
    std::lock_guard<std::mutex> lock(mutex);

    // Check if the username and socket match
    for (const User& user : connectedUsers) {
        if (user.username == username && user.socket == clientSocket) {
            return true; // Authentication successful
        }
    }

    return false; // Authentication failed
}

// Function to handle user disconnection
void disconnectUser(int clientSocket) {
    std::lock_guard<std::mutex> lock(mutex);

    // Remove the user from connected users
    connectedUsers.erase(
        std::remove_if(connectedUsers.begin(), connectedUsers.end(),
                       [clientSocket](const User& user) { return user.socket == clientSocket; }),
        connectedUsers.end());

    // Remove the user from all chat rooms
    for (ChatRoom& room : chatRooms) {
        room.members.erase(
            std::remove_if(room.members.begin(), room.members.end(),
                           [clientSocket](const User& user) { return user.socket == clientSocket; }),
            room.members.end());
    }
}

// Function to handle joining a chat room
bool joinChatRoom(const std::string& username, const std::string& roomName) {
    std::lock_guard<std::mutex> lock(mutex);

    // Find the user and the chat room
    auto userIt = std::find_if(connectedUsers.begin(), connectedUsers.end(),
                               [username](const User& user) { return user.username == username; });

    auto roomIt = std::find_if(chatRooms.begin(), chatRooms.end(),
                               [roomName](const ChatRoom& room) { return room.name == roomName; });

    // Check if the user and chat room exist
    if (userIt != connectedUsers.end() && roomIt != chatRooms.end()) {
        // Check if the user is not already in the chat room
        if (std::find(roomIt->members.begin(), roomIt->members.end(), *userIt) == roomIt->members.end()) {
            roomIt->members.push_back(*userIt);
            return true; // Successfully joined the chat room
        }
    }

    return false; // Joining failed
}

// Function to handle leaving a chat room
bool leaveChatRoom(const std::string& username, const std::string& roomName) {
    std::lock_guard<std::mutex> lock(mutex);

    // Find the user and the chat room
    auto userIt = std::find_if(connectedUsers.begin(), connectedUsers.end(),
                               [username](const User& user) { return user.username == username; });

    auto roomIt = std::find_if(chatRooms.begin(), chatRooms.end(),
                               [roomName](const ChatRoom& room) { return room.name == roomName; });

    // Check if the user and chat room exist
    if (userIt != connectedUsers.end() && roomIt != chatRooms.end()) {
        // Remove the user from the chat room
        roomIt->members.erase(
            std::remove(roomIt->members.begin(), roomIt->members.end(), *userIt),
            roomIt->members.end());
        return true; // Successfully left the chat room
    }

    return false; // Leaving failed
}

// Function to broadcast a message to all members of a chat room
void broadcastMessage(const std::string& sender, const std::string& roomName, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);

    // Find the chat room
    auto roomIt = std::find_if(chatRooms.begin(), chatRooms.end(),
                               [roomName](const ChatRoom& room) { return room.name == roomName; });

    // Check if the chat room exists
    if (roomIt != chatRooms.end()) {
        // Iterate over all members and send the message
        for (const User& member : roomIt->members) {
            // Assuming you have a function to send messages to specific clients
            // send(member.socket, message.c_str(), message.size(), 0);
        }
    }
}

