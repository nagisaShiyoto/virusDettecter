#include "dettector.h"
#define READ_BINARY_MODE "rb"
#include <exception>
dettector::dettector(std::string VirusPath,std::string filePAth)
/*
get all the neccery data to start the test
input:virusPath-the path of the virus sig,
filePath-the path to the folder you want to scan
output:none
*/
{
    FILE* virus=fopen(VirusPath.c_str(),READ_BINARY_MODE);
    this->file=opendir(filePAth.c_str());
    if(virus==NULL)
    {
        throw "coudn't open file";
    }
    fseek(virus,0,SEEK_END);
    this->virusSize=ftell(virus);//get the size
    fseek(virus,0,SEEK_SET);
    this->virusInfo=this->getInfoFromFile(virus,this->virusSize);
    fclose(virus);
}

std::vector<unsigned char> dettector::getInfoFromFile(FILE* file,int size)
/*
gets from file a chanck of info and returning to one byte after the start of the data collection
input:file-the file to take data,size-the amount of data
output: a chank of data from file
*/
{
    std::vector<unsigned char> infoFile;
    char curr=fgetc(file);
    auto currentPlace=ftell(file);
    for(int i=0;i<size&&(curr!=EOF);i++)
    {
        infoFile.push_back((unsigned char)curr);
        curr=fgetc(file);
    }
    fseek(file,currentPlace,SEEK_SET);//to move it to the next char
    return infoFile;
}





dettector::~dettector()
{
    closedir(this->file);
}