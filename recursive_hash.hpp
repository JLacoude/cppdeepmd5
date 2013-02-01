#ifndef RECURSIVE_HASH_H_INCLUDED
#define RECURSIVE_HASH_H_INCLUDED

#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include "hashfile.hpp"

/**
 * Saves a file or directory's md5 in a text file
 * @param std::string path Path of the file or directory for which to get md5
 * @param std::string output_path Path of the text file to save the md5 hashes in
 */
void save_recursive_md5(const std::string path, const std::string output_path);

#endif // RECURSIVE_HASH_H_INCLUDED
