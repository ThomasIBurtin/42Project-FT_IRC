#include "../serveur.hpp"

void Serveur::cmd_join(std::vector<std::string> input_split, Client* client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed())
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() < 2 || input_split.size() > 3 || input_split[1][0] != '#')
        throw std::runtime_error("ERROR: Format is /join #channel 'password'\n");

    const std::string& channel_name = input_split[1];
    Channel *channel_find = find_channel_by_name(channel_name);
    if(!channel_find)
    {
        Channel* new_channel = new Channel(input_split[1]);
        std::string message = "You created the " + new_channel->getName() + " channel.\n";
        send(client->client_pollfd.fd, message.c_str(), message.size(), 0);
        new_channel->op = client;
        this->channels.push_back(new_channel);
        new_channel->add_client(client);
    }
    else
    {
        if (client->channel == channel_find)
            throw std::runtime_error("ERROR: you already are in this channel\n");
        if (channel_find->getMode('L') && channel_find->membre.size() >= channel_find->getLimite())
            throw std::runtime_error("ERROR: The limit of the client is " + std::to_string(channel_find->getLimite()));
        if(channel_find->getMode('I') && !(find_client_in_vector(client->getNickname(), channel_find->inviter)))
            throw std::runtime_error("ERROR: You are not invite");
        if (channel_find->getMode('K') &&
            !(find_client_in_vector(client->getNickname(), channel_find->membre)) &&
            !(find_client_in_vector(client->getNickname(), channel_find->inviter)) &&
            (input_split.size() < 3 || input_split[2] != channel_find->getPassword()))
            throw std::runtime_error("ERROR: Bad password");
        channel_find->add_client(client);
    }
}