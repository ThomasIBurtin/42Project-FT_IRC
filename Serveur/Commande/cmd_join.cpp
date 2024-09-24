#include "../serveur.hpp"

void Serveur::cmd_join(std::vector<std::string> input_split, Client* client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed())
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() < 2 || input_split.size() > 3 || input_split[1][0] != '#')
        throw std::runtime_error("ERROR: Format is /join #channel 'password'\n");

    Channel *channel_join = find_channel_by_name(input_split[1], this->channels);
    if(!channel_join)
    {
        Channel* new_channel = new Channel(input_split[1]);
        std::string message = "You created the " + new_channel->getName() + " channel.\n";
        send(client->client_pollfd.fd, message.c_str(), message.size(), 0);
        new_channel->oprator.push_back(client);
        new_channel->add_client(client);
        this->channels.push_back(new_channel);
    }
    else
    {
        if (client->channel == channel_join)
            throw std::runtime_error("ERROR: you already are in this channel\n");
        if (channel_join->getMode('L') && channel_join->membre.size() >= channel_join->getLimite())
            throw std::runtime_error("ERROR: The limit of the client is " + std::to_string(channel_join->getLimite()) + "\n");
        if(channel_join->getMode('I') && !(find_client_in_vector(client->getNickname(), channel_join->inviter)))
            throw std::runtime_error("ERROR: You are not invite\n");
        if (channel_join->getMode('K') &&
            !(find_client_in_vector(client->getNickname(), channel_join->membre)) &&
            !(find_client_in_vector(client->getNickname(), channel_join->inviter)) &&
            (input_split.size() < 3 || input_split[2] != channel_join->getPassword()))
            throw std::runtime_error("ERROR: Bad password\n");
        channel_join->add_client(client);
    }
}