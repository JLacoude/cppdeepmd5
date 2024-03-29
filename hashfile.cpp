#include "hashfile.hpp"

std::string unsignedchar_to_hexastring(const unsigned char * input, std::size_t input_size);

using namespace std;

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
    delete buffer;
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
