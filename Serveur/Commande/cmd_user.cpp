#include "../serveur.hpp"

void Serveur::cmd_user(std::vector<std::string> input_split, Client *client)
{
    if(input_split.size() != 2)
        throw std::runtime_error("ERROR: Format is USER user\n");  
    else if(!client->getPassworded() || !client->getNicknamed())
        throw std::runtime_error("ERROR: First valide password and nickname\n"); 
    else
    {
        client->setUsernamed(true);
        std::string confirmation = "username validated: " + input_split[1] + "\n";
        send(client->client_pollfd.fd, confirmation.c_str(), confirmation.length(), 0);
        client->setUsername(input_split[1]);
    }
}