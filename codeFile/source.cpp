#include <iostream>
#include "../dettector.cpp"


int main()
{
    std::string VirusPath="";
    std::string filePAth="";
    std::vector<unsigned char> hi;
    hi.push_back('1');
    hi.push_back('2');
    hi.push_back('3');
    hi.push_back('2');
    //std::cin>>VirusPath;
    //std::cin>>filePAth;

    dettector dect("../scanFile/scan1","../scanFile");
    (dect.compareSig(hi)) ? std::cout<<"work":std::cout<<"not";
    return 0;
}