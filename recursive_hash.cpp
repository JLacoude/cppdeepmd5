#include "recursive_hash.hpp"

void _get_directory_md5(boost::filesystem::path path, std::string prefix, std::ofstream * output_file);

using namespace std;
namespace fs = boost::filesystem;

/**
 * @inheritdoc
 */
void save_recursive_md5(const string path, const string output_path){
    ofstream output_file(output_path.c_str());
    if(!output_file.is_open()){
        cerr << "Could not create output file" << endl;
        return;
    }
    fs::path current_path = path;
    string prefix;
    _get_directory_md5(path, prefix, &output_file);
    output_file.close();
}

/**
 * Recursively stores the md5 and size of the files contained by a directory in a text file
 * @param boost::filesystem::path path Path of the file or directory
 * @param std::string prefix Prefix to add to file name (used to save file hierarchy)
 * @param std::ofstream * output_file Text file in which the files infos are stored
 */
void _get_directory_md5(fs::path path, string prefix, ofstream * output_file){
    try{
        if(fs::exists(path)){
            if(fs::is_directory(path)){
                fs::directory_iterator end_iter;
                if(path.filename().string() != "." && path.filename().string() != ".."){
                    prefix.append(path.filename().string()).append("/");
                }
                for(fs::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter){
                    _get_directory_md5(dir_iter->path(), prefix, output_file);
                }
            }
            else if(fs::is_regular_file(path)){
                string md5 = get_file_md5(path.string());
                (*output_file) << (prefix.append(path.filename().string())) << "\t" << md5 << "\t" << fs::file_size(path) << endl;
            }
        }
    }
    catch(const fs::filesystem_error& ex){
        cerr << ex.what() << endl;
    }
}
