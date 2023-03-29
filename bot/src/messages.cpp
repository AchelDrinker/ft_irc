#include "../../inc/irc.hpp"

static int trimFirstSpace(int fd, std::string &s);

std::string	plFouiny(int pl)
{
	std::string		fouiny;

	switch(pl)
	{
		case 0:
			fouiny = "On a serré ta sœur, ton petit frère est mon neveu.";
			break;
		case 1:
			fouiny = "Ta meuf s’en fout des Beatles, elle aime les bites tout court.";
			break;
		case 2:
			fouiny = "J’parle dans ton dos, hmm, j’aime trop la levrette.";
			break;
		case 3:
			fouiny = "J’parle pas aux keufs, seuls les micros, les chiennes connaissent mon haleine.";
			break;
		case 4:
			fouiny = "Rebeu, personne regarde ta meuf elle est comme France 2.";
			break;
		case 5:
			fouiny = "Le rap c’est comme le McDo, t’as pas l’choix, j’suis le Filet.";
			break;
		case 6:
			fouiny = "Non l’amour rend pas aveugle, on t’a juste baisé dans l’noir.";
			break;
		case 7:
			fouiny = "Je suis dans mon jacuzzi, t’es dans ta jalousie.";
			break;
		case 8:
			fouiny = "Les mecs sont tous les mêmes, bah fallait pas tous les essayer.";
			break;
		case 9:
			fouiny = "Laisse pas traîner ta fille ou son fils aura ma tête.";
			break;
	}
	return (fouiny);
}

void bot(Server &s, int fd, std::string cmdBot)
{
	std::string target = "BOT";
	std::string chan = "test";
	std::string msg;
	std::string intro;
	Client *c;
	std::list<Client *> *cl;

	c = s.getClients(target);
	cl = s.getNames(target);
	if (trimFirstSpace(fd, cmdBot))
		return;
	if (c || cl){
		if (cl && !c){
			if (!s.clientOnChan(s.getClients(c->getClientSocket())->getUsername(), target)){
				return;
			}
		}
		if (chan.empty()){
			return;
		}
		if (cmdBot == "flip"){
			intro = "Flipping a coin...";
			intro += "\r\n";
			send(c->getClientSocket(), intro.c_str(), intro.length(), 0);
			msg = "Result: ";
			msg += (rand() % 2 == 0 ? "heads" : "tails");
			msg += "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
		else if (cmdBot == "fouiny"){
			intro = "Searching best punchline...";
			intro += "\r\n";
			send(c->getClientSocket(), intro.c_str(), intro.length(), 0);
			msg = "Result: ";
			int pl = rand() % 10;
			msg += plFouiny(pl);
			msg += "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
		else if (cmdBot == "help"){
			msg = "Available commands: flip, fouiny, quit";
			msg += "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
		else if (cmdBot == "quit"){
			msg = "quit\r\n";
			send(c->getClientSocket(), msg.c_str(), msg.length(), 0);
		}
		else{
			msg = "Unknown command: ! ";
			msg += cmdBot;
			msg += "\r\n";
			send(fd, msg.c_str(), msg.length(), 0);
		}
	}
	
}

static int trimFirstSpace(int fd, std::string &s){
	try{
		s = s.substr(1);
	}catch (std::exception const &e){
		send(fd, ERR_NEEDMOREPARAMS, sizeof(ERR_NEEDMOREPARAMS), 0);
		return 1;
	}
	if (s.empty()){
		send(fd, ERR_NEEDMOREPARAMS, sizeof(ERR_NEEDMOREPARAMS), 0);
		return 1;
	}
	return 0;
}