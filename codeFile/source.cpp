#include <iostream>
#include "../dettector.cpp"


int main()
{
    std::string VirusPath="";
    std::string filePAth="";

    std::cin>>VirusPath;
    std::cin>>filePAth;

    dettector dect("../scanFile/scan1","../scanFile");
    return 0;
}