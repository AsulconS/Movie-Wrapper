bool Downloader::download(const std::string& url)
{
    if(fileExists("dataCompressed.gz"))
    {
        std::cout << "The file already exists!" << std::endl;
        return true;
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
    {
        std::cerr << "[[ERROR]] : " << curl_easy_strerror(result) << std::endl;
        return false;
    }
    
    fclose(fp);

    curl_easy_cleanup(curl);

    return extract("dataCompressed.gz");
}

template <typename T>
bool Downloader::load(OrderedList<Movie>& movies, CriteriaOffset criteria, bool isCount, std::size_t count)
{
    if(isCount && !count) return true;

    if(!fileExists("data.tsv"))
    {
        std::cerr << "The file doesn't exist, please download ir first" << std::endl;
        return false;
    }

    std::size_t size;
    std::ifstream inFile("data.tsv", std::ios_base::binary | std::ios::ate);

    size = inFile.tellg();
    inFile.seekg(93, inFile.beg);

    char* buffer = new char[512];
    char* auxBuffer = new char[256];

    MovieData* currentMovieData = new MovieData;

    char val      {};
    int  index    {};
    int  subIndex {};
    int  stage    {};
    while(inFile.get(val))
    {
        if(val == '\t')
        {
            buffer[index] = '\0';
            switch(stage++)
            {
                case 0:
                    currentMovieData->id = atoi(buffer + 2);
                    break;

                case 1:
                    currentMovieData->type.assign(buffer);
                    break;

                case 2:
                    currentMovieData->primaryTitle.assign(buffer);
                    break;

                case 3:
                    currentMovieData->originalTitle.assign(buffer);
                    break;

                case 4:
                    currentMovieData->isAdult = buffer[index - 1];
                    break;

                case 5:
                    currentMovieData->startYear = atoi(buffer);
                    break;

                case 6:
                    currentMovieData->endYear = atoi(buffer);
                    break;

                case 7:
                    currentMovieData->runtimeMinutes = atoi(buffer);
                    break;

                default:
                    break;
            }

            index = 0;
            continue;
        }

        if(val == '\r' || val == '\n' || val == '\0')
        {
            if(stage == 8)
            {
                buffer[index] = '\0';
                subIndex = 0;
                for(int i = 0; i < index; ++i, ++subIndex)
                {
                    if(buffer[i] == ',')
                    {
                        auxBuffer[subIndex] = '\0';
                        currentMovieData->genders.emplace_back(auxBuffer);
                        subIndex = -1;
                        continue;
                    }
                    auxBuffer[subIndex] = buffer[i];
                }
                auxBuffer[subIndex] = '\0';
                currentMovieData->genders.emplace_back(auxBuffer);
                index = 0;

                Movie newMovie(currentMovieData);
                newMovie.setCriteria<T>(criteria);
                movies.insert(std::move(newMovie));

                if(isCount)
                {
                    --count;
                    if(!count)
                    {
                        delete[] buffer;
                        delete[] auxBuffer;

                        inFile.close();

                        return true;
                    }
                }

                currentMovieData = new MovieData;

                stage = 0;
                continue;
            }
            continue;
        }

        //std::this_thread::sleep_for(std::chrono::nanoseconds(10));
        //std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(10));

        buffer[index++] = val;
    }

    delete currentMovieData;
    delete[] buffer;
    delete[] auxBuffer;

    inFile.close();

    return true;
}

bool Downloader::extract(const std::string& filename)
{
    std::ifstream inFile(filename, std::ios::binary | std::ios::ate);

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
    std::cout << "[Extracting], please wait . . ." << std::endl;
    std::string decompressedData = gzip::decompress(compressedData.c_str(), compressedData.size());

    std::ofstream outFile;
    outFile.open("data.tsv");

    outFile << decompressedData;
    std::cout << "- Extracted Successfully! -\n" << std::endl;
    std::cout << "[ Final File Size is: " << decompressedData.size() << " bytes ]" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    outFile.close();
    inFile.close();

    return true;
}

size_t Downloader::write_data(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}
