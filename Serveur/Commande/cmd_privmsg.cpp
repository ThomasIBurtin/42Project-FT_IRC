#include "../serveur.hpp"

void Serveur::cmd_privmsg(std::vector<std::string> input_split, Client *client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed())
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() < 3)
        throw std::runtime_error("ERROR: Format is PRIVMSG NICK message\n");

    const std::string& client_name = input_split[1];
    Client *client_find = find_client_in_vector(client_name, this->clients);
    if(client_find == NULL)
        throw std::runtime_error("ERROR: This User dont exsist\n");
    else
    {
        for(size_t i = 2; i < input_split.size(); i++)
        {
            send(client_find->client_pollfd.fd, input_split[i].c_str(), input_split[i].size(), 0);
            send(client_find->client_pollfd.fd, "\n", 1, 0), void();
        }
    }
}