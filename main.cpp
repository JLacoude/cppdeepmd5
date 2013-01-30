#include "hashfile.hpp"
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char ** argv){
    string dir_path, output_path;
    if(argc < 3){
        cout << "usage: hashcalc [path of directory to scan] [path of file to save to]";
        return 1;
    }
    else{
        dir_path = argv[1];
        output_path = argv[2];
        ofstream output_file(argv[2]);
        if(!output_file.is_open()){
            cout << "Could not create output file" << endl;
            return 1;
        }
        map<string, string> md5s = get_directory_md5(dir_path);

        for(map<string, string>::const_iterator i = md5s.begin(); i != md5s.end(); ++i){
            output_file << i->first << "\t" << i->second << endl;
        }
        output_file.close();
    }
    return 0;
}
