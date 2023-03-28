#pragma once

// include needed for header
class Server;
#include <string>

enum e_messages{
	E_PASS,
	E_NICK,
	E_USER,
	E_JOIN,
	E_NAMES,
	E_LIST,
	E_PRIVMSG,
	E_NOTICE,
	E_PING,
	E_OP,
	E_KICK,
	E_PART,
	E_BOT,
	E_FILE,
};

void	ign(Server &s, int fd, std::string n);

// Connection registration
void	pass(Server &s, int fd, std::string pwd);
void	nick(Server &s, int fd, std::string nick);
void	user(Server &s, int fd, std::string user);
	// Server message
	// Operator message
	// Quit message
	// Server Quit message

// Channel operations
void	join(Server &s, int fd, std::string channel);
void	part(Server &s, int fd, std::string channel);
	//Mode message
	//   Channel modes
	//   User modes
	// Topic messag
void	names(Server &s, int fd, std::string channel);
void	list(Server &s, int fd, std::string channel);
	// Invite message
void	kick(Server &s, int fd, std::string channelAndUser);
void	op(Server &s, int fd, std::string cmd);
void	bot(Server &s, int fd, std::string cmdBot);
void	dcc(Server &s, int fd, std::string filename);

//Sending messages
void	privmsg(Server &s, int fd, std::string targetAndText);
void	notice(Server &s, int fd, std::string targetAndText);

