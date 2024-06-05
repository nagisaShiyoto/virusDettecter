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
        std::cout<<"enter virus path:"<<std::endl;
        std::cin>>VirusPath;
        std::cout<<"enter diractory path:"<<std::endl;
        std::cin>>filePath;
    }


    try
    {
        dettector dect(VirusPath,filePath);
        std::cout<<"scanning started..."<<std::endl;
        std::map<std::string,bool> res=dect.scanFolder();
    }
    catch(std::string e)
    {
        std::cerr << e << '\n';
        return -1;
    }
    
    
    
    return 0;
}