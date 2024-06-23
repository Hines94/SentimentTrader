#include "NewsManager.h"
#include <curl/curl.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#include "Utils/Utils.h"
#include "Env/EnvManager.h"
#include <string>

using namespace std;

size_t writeCallback(char* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

vector<NewsArticle> NewsManager::GetNewsArticles(string checkName)
{
    return vector<NewsArticle>();
}

void NewsManager::UpdateArticles(string checkName)
{
    CURL* curl;
    CURLcode res;
    string response;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Construct the URL with required parameters
        std::string url = "https://newsapi.org/v2/everything";
        std::string reqOptions = "?q=" + checkName + "&from=2024-05-23&sortBy=popularity";

        // Append API key to the URL
        url += reqOptions + "&apiKey=" + EnvManager::getInstance().getParam("NEWS_API_KEY");

        // Set the URL for the request
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "SentimentTrader");

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    saveNewsToFile(checkName,response);

    //TODO: Load articles from response
}

NewsManager::NewsManager() 
{

}

void NewsManager::saveNewsToFile(std::string checkName,std::string responseData)
{   
    utils::CreateDirectory("News");
    const string fileName = "News/"+checkName+".txt";
    utils::saveDataToFile(fileName,responseData);
}
