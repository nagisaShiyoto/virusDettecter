# virusDettecter
backstory:
"crypty" is a new virus which his goal is to encrypt the entire hardDrive.
resarcher were able to find out two key caricaristics, first the virus has a uniqe signature
which means that every file with certain known set of bytes is enfacted by the virus
the virus can only infacts ELF binaries file which exist on linux
our goal is to create a software to recognise all the infacted files from a certain diractory

the softwere gets two parameters the path to the virus signature and a directory to check
the code will check file file if he is an ELF file and if he is he will check if in the file
there is the wanted signature(compare two files' info)

commands:
./find_sig(and than there you can inout the data)
./find_sig <virusSig> <dict>

example:
./find_sig scanFile/virusSig scanFile

./find_sig
scanFile/virusSig scanFile


