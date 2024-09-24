#include "../serveur.hpp"

void Serveur::cmd_nick(std::vector<std::string> input_split, Client *client)
{
    if (input_split.size() != 2)
        throw std::runtime_error("ERROR: Format is NICK nickname\n");
    if (!client->getPassworded())
        throw std::runtime_error("ERROR: First validate password\n");

    Client *client_find = find_client_in_vector(input_split[1], this->clients);
    if(client_find)
        throw std::runtime_error("ERROR: Nickname already use\n");
    else
    {
        client->setNicknamed(true);
        client->setNickname(input_split[1]);
        std::string confirmation = "nickname validated: " + input_split[1] + "\n";
        send(client->client_pollfd.fd, confirmation.c_str(), confirmation.length(), 0);
    }
}