#include "../serveur.hpp"

void Serveur::cmd_invite(std::vector<std::string> input_split, Client *client)
{
    if (!client->getPassworded() || !client->getNicknamed() || !client->getUsernamed()) 
        throw std::runtime_error("ERROR: You are not identified.\n");
    if (input_split.size() != 3)
        throw std::runtime_error("ERROR: Format is /invite nick channel\n");

    const std::string& client_inviter_name = input_split[1];
    Channel* channel_invite = find_channel_by_name(input_split[2], this->channels);
    Client* client_inviter = find_client_in_vector(client_inviter_name, this->clients);
    if (!channel_invite)
        throw std::runtime_error("ERROR: Channel does not exist.\n");
    else if (!client_inviter)
        throw std::runtime_error("ERROR: User not found.\n");
    else if (!find_client_in_vector(client->getNickname(), channel_invite->oprator))
        throw std::runtime_error("ERROR: You are not an operator of this channel.\n");
    else if(find_client_in_vector(client_inviter_name, channel_invite->membre))
        throw std::runtime_error("ERROR: He is already in this channel.\n");
    else
    {
        std::string message = "User " + client->getNickname() + " invite you in " + channel_invite->getName() + " channel.\n";
        send(client_inviter->client_pollfd.fd, message.c_str(), message.size(), 0);
        channel_invite->inviter.push_back(client_inviter);
    }
}
