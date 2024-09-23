#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include "Client/client.hpp"

std::vector<std::string> split(const std::string &str);
std::string trim(const std::string &str);
Client* find_client_in_vector(const std::string& name, std::vector<Client*> clients);

#endif