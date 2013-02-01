#ifndef HASHFILE_HPP_INCLUDED
#define HASHFILE_HPP_INCLUDED
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

/**
 * Returns a string representing the md5 hash of a file
 * @param std::string path The path of the file
 * @return std::string
 */
std::string get_file_md5(const std::string path);

#endif // HASHFILE_HPP_INCLUDED
