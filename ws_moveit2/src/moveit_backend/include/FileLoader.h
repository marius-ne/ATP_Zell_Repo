#ifndef FILELOADER_HPP
#define FILELOADER_HPP

#include <memory>
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "rcutils/filesystem.h"

// Structure to hold information about an object used to import meshes
struct Object {
    std::string name;
    std::string id;
    std::string path;
};


class FileLoader
{
    public:
        // Method for extracting the path of a mesh object specified by it's name in config csv file
        std::string get_object_path(const std::string& object_name, const std::string& configPath) {

        std::ifstream file(configPath);
        if (!file.is_open()) {
            std::cerr << "Error while trying to open the config file" << std::endl;
            return "0";
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Object object;

            if (std::getline(iss, object.name, ';') &&
                std::getline(iss, object.id, ';') &&
                std::getline(iss, object.path, ';')) {

                if (object.id == object_name || object.name == object_name) {
                    file.close();
                    return object.path;
                }
            }
        }

        file.close();
        std::cerr << "File not found" << std::endl;
        return "0";
    }

};

#endif