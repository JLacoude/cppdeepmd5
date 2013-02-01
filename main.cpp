#include "recursive_hash.hpp"
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
        save_recursive_md5(dir_path, output_path);
    }
    return 0;
}
