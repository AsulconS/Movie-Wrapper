bool Downloader::download(const std::string& url)
{
    if(fileExists("dataCompressed.gz"))
    {
        std::cout << "The file already exists!\nDo you want to download it again? ";

        bool selected {};
        std::cin >> selected;

        if(!selected) return true;
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

    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "[Downloading], please wait . . ." << std::endl;
    result = curl_easy_perform(curl);

    if(result == CURLE_OK)
        std::cout << "- Downloaded Successfully! -\n" << std::endl;
    else
        std::cout << "[[ERROR]] : " << curl_easy_strerror(result) << std::endl;
    
    fclose(fp);

    curl_easy_cleanup(curl);

    return extract("dataCompressed.gz");
}

bool Downloader::extract(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios_base::binary);

    inFile.seekg(0, inFile.end);
    std::cout << "[ File Size is: " << inFile.tellg() << " bytes ]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    inFile.seekg(0, inFile.beg);

    std::string compressedData {};

    std::stringstream data;
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "[Creating Temp], please wait . . ." << std::endl;
    data << inFile.rdbuf();
    std::cout << "- Temp Created successfully! -\n" << std::endl;
    compressedData = data.str();

    std::cout << "[ Temp-File Size is: " << compressedData.size() << " bytes ]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "[Decompressing], please wait . . ." << std::endl;
    std::string decompressedData = gzip::decompress(compressedData.c_str(), compressedData.size());

    std::ofstream outFile;
    outFile.open("data.tsv");

    outFile << decompressedData;
    outFile.close();
    inFile.close();

    std::cout << "- Extracted Successfully! -\n" << std::endl;
    std::cout << "[ Final File Size is: " << decompressedData.size() << " bytes ]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    return true;
}

size_t Downloader::write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
