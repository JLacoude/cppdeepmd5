#include "hashfile.hpp"

std::string unsignedchar_to_hexastring(const unsigned char * input, std::size_t input_size);
void _get_directory_md5(boost::filesystem::path path, std::string prefix, std::map<std::string, std::string> * file_list);

using namespace std;
namespace fs = boost::filesystem;

/**
 * @inheritdoc
 */
map<string, string> get_directory_md5(const string path){
    map<string, string> result;
    fs::path current_path = path;
    string prefix;
    _get_directory_md5(path, prefix, &result);
    return result;
}

void _get_directory_md5(fs::path path, string prefix, map<string, string> * file_list){
    try{
        if(fs::exists(path)){
            if(fs::is_directory(path)){
                fs::directory_iterator end_iter;
                if(path.filename().string() != "." && path.filename().string() != ".."){
                    prefix.append(path.filename().string()).append("/");
                }
                for(fs::directory_iterator dir_iter(path); dir_iter != end_iter; ++dir_iter){
                    _get_directory_md5(dir_iter->path(), prefix, file_list);
                }
            }
            else if(fs::is_regular_file(path)){
                string md5 = get_file_md5(path.string());
                file_list->insert(pair<string, string>(prefix.append(path.filename().string()), md5));
            }
        }
    }
    catch(const fs::filesystem_error& ex){
        cerr << ex.what() << endl;
    }
}

/**
 * @inheritdoc
 */
string get_file_md5(const string path){
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5_CTX mdContext;
    size_t buffer_size = 1 * 1024 * 1024;
    size_t byte_read;
    char * buffer = new char[buffer_size];
    string result;

    ifstream input_file(path.c_str(), ios::binary);

    if(input_file.is_open()){
        MD5_Init(&mdContext);
        while(!input_file.eof()){
            input_file.read(buffer, buffer_size);
            byte_read = input_file.gcount();
            MD5_Update (&mdContext, buffer, byte_read);
        }
        MD5_Final(digest, &mdContext);
        input_file.close();
        result = unsignedchar_to_hexastring(digest, MD5_DIGEST_LENGTH);
    }
    return result;
}

/**
 * Converts an unsigned char array to a string containing its hexadecimal representation
 * @param const unsigned char * input Array to convert
 * @param std::size_t input_size Number of elements in the array
 * @return std::string
 */
string unsignedchar_to_hexastring(const unsigned char * input, size_t input_size){
    ostringstream stream;
    stream << hex << setfill('0');
    for(size_t i = 0; i != input_size; i++){
        stream << setw(2) << (int)input[i];
    }
    return stream.str();
}
