#include "../serveur.hpp"

void Serveur::cmd_mode(std::vector<std::string> input_split, Client *client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed()) 
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() < 3 || input_split.size() > 4 || input_split[2].size() != 2)
        throw std::runtime_error("ERROR: Format is mode channel mode\n");

    const char signe = input_split[2][0];
    const char mode = input_split[2][1];
    Channel *channel_mode = find_channel_by_name(input_split[1], this->channels);
    if(!channel_mode)
        throw std::runtime_error("ERROR: Channel does not exist.\n");
    else if (!find_client_in_vector(client->getNickname(), channel_mode->oprator))
        throw std::runtime_error("ERROR: You are not an operator of this channel.\n");
    else
    {
        std::string message;
        if(input_split.size() > 3)
           message = channel_mode->setMode(signe, mode, input_split[3]);
        else
           message = channel_mode->setMode(signe, mode, "");
        send(client->client_pollfd.fd, message.c_str(), message.length(), 0);
    }
}
