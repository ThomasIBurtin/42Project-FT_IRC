#include "../serveur.hpp"

void Serveur::cmd_privmsg(std::vector<std::string> input_split, Client *client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed())
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() < 3)
        throw std::runtime_error("ERROR: Format is PRIVMSG NICK message\n");

    Client *client_to_send = find_client_in_vector(input_split[1], this->clients);
    if(!client_to_send)
        throw std::runtime_error("ERROR: This User dont exsist\n");
    else
    {
        for(size_t i = 2; i < input_split.size(); i++)
        {
            send(client_to_send->client_pollfd.fd, input_split[i].c_str(), input_split[i].size(), 0);
            send(client_to_send->client_pollfd.fd, "\n", 1, 0), void();
        }
    }
}