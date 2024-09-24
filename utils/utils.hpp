#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include "../Client/client.hpp"
#include "../Serveur/serveur.hpp"

std::vector<std::string> split(const std::string &str);
std::string trim(const std::string &str);
Channel* find_channel_by_name(const std::string& name, std::vector<Channel*> channels);
Client* find_client_in_vector(const std::string& name, std::vector<Client*> clients);

#endif