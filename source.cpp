#include <iostream>
#include "dettector.cpp"


int main(int argc, char** argv)
{
    std::string VirusPath="";
    std::string filePath="";
    if(argc==3)
    {
        VirusPath=argv[1];
        filePath=argv[2];
    }
    else
    {
        std::cin>>VirusPath;
        std::cin>>filePath;
    }
    dettector dect(VirusPath,filePath);
    std::cout<<"scanning started..."<<std::endl;
    std::map<std::string,bool> res=dect.scanFolder();
    return 0;
}