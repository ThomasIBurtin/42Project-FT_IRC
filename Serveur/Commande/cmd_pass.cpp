#include "../serveur.hpp"

void Serveur::cmd_pass(std::vector<std::string> input_split, Client *client)
{
    if(input_split[1] == this->_password && input_split.size() == 2)
    {
        client->setPassworded(true);
        send(client->client_pollfd.fd, "Password good\n", 14, 0);
    }
    else
        throw std::runtime_error("ERROR: Bad password\n");
}