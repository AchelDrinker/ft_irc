#include "../../inc/irc.hpp"
#include <memory>

static int trimFirstSpace(int fd, std::string &s);

void send_file(int fd, std::ifstream& file, size_t filesize) {
    // Allocate a buffer for the file data
    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, BUFFER_SIZE);
    // Send the file data in chunks
    size_t bytes_sent = 0;
    while (bytes_sent < filesize) {
        // Read a chunk of data from the file
        size_t bytes_to_read = std::min(filesize - bytes_sent, (size_t)BUFFER_SIZE);
        file.read(buffer, bytes_to_read);

        // Send the chunk of data to the socket
        int bytes_sent_now = send(fd, buffer, bytes_to_read, 0);
        if (bytes_sent_now < 0) {
            std::cerr << "ERROR writing to socket" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        // Update the total number of bytes sent
        bytes_sent += bytes_sent_now;
    }
}

std::auto_ptr<std::ifstream> open_file(const std::string& filename) {
    std::auto_ptr<std::ifstream> file(new std::ifstream(filename.c_str(), std::ios::binary));
    if (!(*file)) {
        return std::auto_ptr<std::ifstream>();
    }
    return file;
}


void filesent(std::string file){
    std::string msg2 = "cp " + file + " " + file + ".sent";
    system(msg2.c_str());
}

size_t get_size(std::ifstream& file){
    file.seekg(0, std::ios::end);
    std::streampos filesize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file contents into a buffer
    std::string buffer;
    buffer.reserve(filesize);
    buffer.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Print the file size and contents
    return static_cast<size_t>(filesize);
}

void close_file(std::unique_ptr<std::ifstream>& file) {
    file->close();
}

void dcc(Server &s, int fd, std::string filename){
    if (trimFirstSpace(fd, filename))
		return;
    size_t i = 0;
	size_t pos = 0;
	std::string data[2];

	// Split the command in 2 parts: the destinator, and the file
	while ((pos = filename.find(" ")) != std::string::npos){
		data[i] = filename.substr(0, pos);
		filename.erase(0, pos + 1);
		i++;
	}
	data[i] = filename.substr(0, pos);
    
    // Ouvrez le fichier à transférer
    std::unique_ptr<std::ifstream> file(open_file(data[1]));
    if (!file) {
        std::cout << "Error opening file: " << data[1] << std::endl;
        return;
    }
    size_t  filesize = get_size(*file);
    std::unique_ptr<std::ifstream> file2(open_file(data[1]));
    if(s.getClientsUser(data[0]) == NULL){
			send(fd, "Error : This user doesnt exists.\n", strlen("Error : This user doesnt exists.\n"), 0);
            return;
		}
    int ID = s.getClientsUser(data[0])->getClientSocket();
    std::string msg = "The user " + s.getClientsUser(data[0])->getNickname() + " sent you a file named " + data[1] + " with a size of " + std::to_string(filesize) + " bytes.\n\n";
    send(ID , msg.c_str(), msg.length(), 0);
    // Envoyez les données du fichier
    send_file(ID, *file2, filesize);
    filesent(data[1]);

    // Fermez le fichier
    close_file(file);
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