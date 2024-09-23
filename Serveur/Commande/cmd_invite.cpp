#include "../serveur.hpp"

void Serveur::cmd_invite(std::vector<std::string> input_split, Client *client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed()) 
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() != 3)
        throw std::runtime_error("ERROR: Format is /invite nick channel\n");

    const std::string& inviter = input_split[1];
    const std::string& channel_name = input_split[2];

    Channel* channel_find = find_channel_by_name(channel_name);
    Client* client_invite = find_client_in_vector(inviter, this->clients);
    if (!channel_find)
        throw std::runtime_error("ERROR: Channel does not exist.\n");
    else if (!client_invite)
        throw std::runtime_error("ERROR: User not found.\n");
    else if (channel_find->op != client)
        throw std::runtime_error("ERROR: You are not an operator of this channel.\n");
    else if(find_client_in_vector(inviter, channel_find->membre))
        throw std::runtime_error("ERROR: He is already in this channel.\n");
    else
    {
        std::string message = "User " + client->getNickname() + " invite you in " + channel_find->getName() + " channel.\n";
        send(client_invite->client_pollfd.fd, message.c_str(), message.size(), 0);
        channel_find->inviter.push_back(client_invite);
    }
}