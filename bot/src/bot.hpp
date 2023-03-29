#ifndef BOT_HPP
# define BOT_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <cerrno>
# include <cstdio>
# include <cstdlib>
# include <cstring>
# include <iostream>
# include <unistd.h>
# include <poll.h>
# include <vector>
# include <fstream>
# include <algorithm>
# include "color.hpp"
# include <ctime>
# include <sstream>
# include <string>

#define DEBUG false

namespace Utils
{
	std::string currentTime();

	void error(std::string message, bool stop);

	std::vector<std::string> split(std::string str, std::string delimiter);

	bool isLetter(char c);
	bool isSpecial(char c);
	bool isDigit(char c);

	std::string toString(size_t var);

	bool strmatch(std::string str, std::string pattern);
}

class Bot
{
	private:
		bool *sig;
		std::string addr;
		int sock;
		struct sockaddr_in serv_addr;

		std::string pass;
		std::string nick;
		bool connected;

		std::string receive;
		std::vector<std::string> messages;

		void send_msg(std::string msg);
		void recv_msg();
		void send_pass();
		void send_nick();

		std::vector<std::string> split(std::string str, std::string delim);
	public:
		Bot(bool *sig, std::string addr, int port = 6667, std::string pass = std::string(), std::string nick = "bot");
		~Bot();

		void run();
};


#endif