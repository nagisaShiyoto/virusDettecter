#ifndef DETTECTOR_H
#define DETTECTOR_H

#pragma once
#include <iostream>
#include<string>
#include <vector>
#include <dirent.h>


class dettector
{
public:
    dettector(std::string VirusPath,std::string filePAth);
    ~dettector();

private:
    std::vector<unsigned char> virusInfo;
    DIR* file;
    int virusSize;

    std::vector<unsigned char> getInfoFromFile(FILE* file,int size);
public:
    bool compareSig(std::vector<unsigned char> info1);
};

#endif