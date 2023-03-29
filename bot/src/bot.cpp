#include "bot.hpp"
#include <netdb.h>

Bot::Bot(bool *sig, std::string addr, int port, std::string pass, std::string nick): sig(sig), addr(addr), pass(pass), nick(nick)
{
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("socket() failed");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	struct addrinfo hints, *servinfo;
	int rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	rv = getaddrinfo( addr.c_str() , 0 , &hints , &servinfo);

	serv_addr.sin_addr = ((struct sockaddr_in *) servinfo->ai_addr)->sin_addr;
	std::cout << "Connecting to " << addr << ":" << port << std::endl;
}

Bot::~Bot()
{
	send_msg("QUIT");
	close(sock);
}

void Bot::run()
{
	while (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "connect() failed" << std::endl;
		std::cout << "Retrying in 5 seconds..." << std::endl;
		sleep(5);
	}
	send_pass();
	sleep(1);
	send_msg("NICK BOT");
	std::cout << "Connected as " << nick << std::endl;
	sleep(1);
	send_msg("USER BOT");
	sleep(1);

	std::cout << "Bot is joining channel test " << addr << std::endl;
	send_msg("JOIN test");
	std::cout << "test channel joined" << std::endl;
	sleep(1);
	while (true)
	{
		if (messages.empty())
			recv_msg();
		std::string msg = messages[0];
		messages.erase(messages.begin());
		if (msg.empty())
			continue;
		std::cout << msg << std::endl;
		if (msg == "quit")
			break;
	}
}

void Bot::send_msg(std::string msg)
{
	std::vector<std::string> values = Utils::split(msg, " ");
	msg += "\r\n";
	if (send(sock, msg.c_str(), msg.size(), 0) < 0)
		throw std::runtime_error("send() failed");
}

void Bot::recv_msg()
{
	char buf[4096 + 1];
	struct pollfd pfd;

	pfd.fd = sock;
	pfd.events = POLLIN;
	if (poll(&pfd, 1, -1) == -1)
	{
		if (pfd.revents & POLLERR)
			throw std::runtime_error("poll() failed");
		messages.clear();
		messages.push_back("");
		return;
	}
	
	ssize_t len = recv(sock, &buf, 4096, 0);
	if (len < 0)
		throw std::runtime_error("recv() failed");
	if (len == 0)
		throw std::runtime_error("Connection closed");
	buf[len] = '\0';
	receive += buf;
	while (receive.find("\r\n") != std::string::npos)
	{
		std::string msg = receive.substr(0, receive.find("\r\n"));
		receive.erase(0, receive.find("\r\n") + 2);
		messages.push_back(msg);
	}
}

void Bot::send_pass()
{
	if (pass.empty())
		return;
	send_msg("PASS " + pass);
}


std::string Utils::currentTime()
{
	time_t t = std::time(0);
	struct tm *now = std::localtime(&t);
	std::string time(asctime(now));
	time.erase(--time.end());
	return time;
}

void Utils::error(std::string message, bool stop)
{
	std::cerr << "error: " << message << std::endl;
	if (stop)
		exit(EXIT_FAILURE);
}

std::vector<std::string> Utils::split(std::string str, std::string delimiter)
{
	std::vector<std::string> values = std::vector<std::string>();

	size_t position;
	while ((position = str.find(delimiter)) != std::string::npos)
	{
		values.push_back(str.substr(0, position));
		str.erase(0, position + delimiter.length());
	}
	values.push_back(str);

	return values;
}

bool Utils::isLetter(char c) { return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }
bool Utils::isSpecial(char c) { return (c >= '[' && c <= '`') || (c >= '{' && c <= '}'); }
bool Utils::isDigit(char c) { return (c >= '0' && c <= '9'); }

std::string Utils::toString(size_t var)
{
	std::stringstream stream;
	stream << var;
	return stream.str();
}

bool Utils::strmatch(std::string str, std::string pattern)
{
	size_t str_size = str.size();
	size_t pattern_size = pattern.size();

	if (str_size == 0 || pattern_size == 0)
		return false;
	std::vector<std::vector<bool> > lookup(str_size + 1, std::vector<bool>(pattern_size + 1, false));
 
	lookup[0][0] = true;
 
	for (size_t j = 1; j <= pattern_size; j++)
		if (pattern[j - 1] == '*')
			lookup[0][j] = lookup[0][j - 1];
 
	for (size_t i = 1; i <= str_size; i++) {
		for (size_t j = 1; j <= pattern_size; j++) {
			if (pattern[j - 1] == '*')
				lookup[i][j] = lookup[i][j - 1] || lookup[i - 1][j];
			else if (pattern[j - 1] == '?' || str[i - 1] == pattern[j - 1])
				lookup[i][j] = lookup[i - 1][j - 1];
			else
				lookup[i][j] = false;
		}
	}
 
	return lookup[str_size][pattern_size];
}