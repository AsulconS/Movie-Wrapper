#ifndef DOWNLOADER_HPP
#define DOWNLOADER_HPP

#include <curl/curl.h>

#include <gzip/decompress.hpp>

#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "core/common.hpp"

class Downloader
{
public:
    static bool download(const std::string& url);

private:
    explicit Downloader() {}

    inline static bool fileExists(const std::string& filename) { return std::ifstream(filename).good(); }
    static bool extract(const std::string& filename);

    static size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream);
};

#endif // DOWNLOADER_H
