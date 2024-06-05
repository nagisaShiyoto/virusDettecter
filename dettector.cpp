#include "dettector.h"
#include <exception>

#define READ_BINARY_MODE "rb"
#define ELF_FILE_SIZE 4


dettector::dettector(std::string VirusPath,std::string filePAth)
/*
get all the neccery data to start the test
input:virusPath-the path of the virus sig,
filePath-the path to the folder you want to scan
output:none
*/
{
    int start_place=0;
    FILE* virus=fopen(VirusPath.c_str(),READ_BINARY_MODE);
    this->file=opendir(filePAth.c_str());
    if(virus==NULL||this->file==NULL)
    {
        throw std::string("coudn't open on of the path you wrote, try a difrant ones:)\n");
    }
    if(this->isElfFile(virus))
    //in case the sig is a elf file
    {
        start_place=ELF_FILE_SIZE;
    }
    fseek(virus,start_place,SEEK_END);
    this->virusSize=ftell(virus);//get the size
    fseek(virus,start_place,SEEK_SET);
    this->virusInfo=this->getInfoFromFile(virus,this->virusSize);
    fclose(virus);
    this->filePath=filePAth;
    this->virusSize=this->virusInfo.size();
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

bool dettector::compareSig(std::vector<unsigned char> info1)
/*
compare chank of data to the virus sig
innput:info1-the chank of data to compare to
output:true-identical,false-diffrant
*/
{
    if(info1.size()==this->virusInfo.size())
    {
        for(int i=0;i<info1.size();i++)
        {
            if(this->virusInfo[i]!=info1[i])
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

std::string dettector::createFilePath(struct dirent* pb)
/*create the path to the file from the dir
input:pb-the data on every file
output:c_arr of the file path*/
{
    std::string path=this->filePath+"/"+pb->d_name;
    return path;
}

bool dettector::scanFile(FILE* file)
/*scan for virus sig in file(if the file is infacted)
input:file to check
output:true-infactes(has sig),false-not infacted*/
{
    std::vector<unsigned char> info=this->getInfoFromFile(file,this->virusSize);
    while(info.size()==this->virusSize)
    {
        if(this->compareSig(info))
        {
            return true;
        }
        info=this->getInfoFromFile(file,this->virusSize);
    }
    return false;
}

std::map<std::string,bool> dettector::scanFolder()
/*
run over on all the files in folder to check for infacted files
input:none
output:a map with file name and if it was infected
*/
{
    std::map<std::string,bool> res;
    struct dirent* dp=nullptr;
    FILE* currFile=nullptr;
    while((dp=readdir(this->file))!=nullptr)
    {
        if(dp->d_type!=DT_DIR&&dp->d_name[0]!='.')//aliminate the files in the dir
        {
            currFile=fopen(this->createFilePath(dp).c_str(),READ_BINARY_MODE);
            if(currFile!=NULL)
            {
                if(this->isElfFile(currFile))
                {
                    res[dp->d_name]=this->scanFile(currFile);
                    if(res[dp->d_name])
                    {
                        std::cout<<"File "<<this->createFilePath(dp)<<" is infected!"<<std::endl;
                    }
                }
                fclose(currFile);
            }
            else
            {
                std::cout<<"coudnt open file: "<<this->createFilePath(dp);
            }
        }
    }
    return res;
}

bool dettector::isElfFile(FILE* file)
/*
check if file is an elf file
input:file-to read the file
output:true-elf file,false-other file type
*/
{
    char elfSig[]={0x7f, 'E', 'L', 'F'};
    std::vector<unsigned char> info=this->getInfoFromFile(file,ELF_FILE_SIZE);
    fseek(file,ELF_FILE_SIZE,SEEK_SET);
    if(info.size()==ELF_FILE_SIZE&&info[0]==0x7f&&info[1]=='E'
    &&info[2]=='L'&&info[3]=='F')
    {
        return true;
    }
    return false;
}

dettector::~dettector()
{
    closedir(this->file);
}