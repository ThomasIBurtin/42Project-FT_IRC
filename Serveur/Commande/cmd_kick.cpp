#include "../serveur.hpp"

void Serveur::cmd_kick(const std::vector<std::string> input_split, Client* client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed()) 
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() != 3)
        throw std::runtime_error("ERROR: Invalid parameters. Usage: /kick #channel user\n");

    Channel* channel_kick = find_channel_by_name(input_split[1], this->channels);
    if (!channel_kick)
        throw std::runtime_error("ERROR: Channel does not exist.\n");
    Client *client_to_kick = find_client_in_vector(input_split[2], channel_kick->membre);
    if(!client_to_kick)
        throw std::runtime_error("ERROR: User not found.\n");
    else if (!find_client_in_vector(client->getNickname(), channel_kick->oprator))
        throw std::runtime_error("ERROR: You are not an operator of this channel.\n");
    else
    {
        channel_kick->remove_client(client_to_kick);
        send(client_to_kick->client_pollfd.fd, "You have been kicked from the channel.\n", 39, 0);
    }
}