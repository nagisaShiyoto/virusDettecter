#ifndef DETTECTOR_H
#define DETTECTOR_H

#pragma once
#include <iostream>
#include<string>
#include <vector>
#include <dirent.h>
#include <map>

class dettector
{
public:
    dettector(std::string VirusPath,std::string filePAth);
    std::map<std::string,bool> scanFolder();
    ~dettector();
    bool isElfFile(FILE* file);
private:
    std::vector<unsigned char> virusInfo;
    DIR* file;
    int virusSize;
    std::string filePath;


    bool scanFile(FILE* file);
    std::vector<unsigned char> getInfoFromFile(FILE* file,int size);
    std::string createFilePath(struct dirent* pb);
    
    bool compareSig(std::vector<unsigned char> info1);
};

#endif