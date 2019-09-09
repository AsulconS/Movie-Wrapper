bool Downloader::download(const std::string& url)
{
    if(fileExists("dataCompressed.gz"))
    {
        std::cout << "The file is already downloaded!" << std::endl;
        return extract("dataCompressed.gz");
    }

    CURL* curl;
    FILE* fp;
    CURLcode result;

    fp = fopen("dataCompressed.gz", "wb");

    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Downloader::write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);

    result = curl_easy_perform(curl);

    if(result == CURLE_OK)
        std::cout << "Download Successful!" << std::endl;
    else
        std::cout << "ERROR: " << curl_easy_strerror(result) << std::endl;
    
    fclose(fp);

    curl_easy_cleanup(curl);

    return extract("dataCompressed.gz");
}

bool Downloader::extract(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios_base::binary);

    inFile.seekg(0, inFile.end);
    size_t totalSize = inFile.tellg();
    std::cout << totalSize << std::endl;
    inFile.seekg(0, inFile.beg);

    std::string compressedData {};

    std::stringstream data;
    data << inFile.rdbuf();
    compressedData = data.str();

    std::cout << compressedData.size() << std::endl;

    std::string decompressedData = gzip::decompress(compressedData.c_str(), compressedData.size());

    std::ofstream outFile;
    outFile.open("data.tsv");

    outFile << decompressedData;
    outFile.close();
    inFile.close();

    return true;
}

size_t Downloader::write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
