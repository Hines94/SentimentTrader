#include "NewsManager.h"
#include <curl/curl.h>
#include <iostream>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

#include <chrono>
#include <iomanip>
#include <ctime>

#include "Utils/json.hpp"
#include "Utils/Utils.h"
#include "Env/EnvManager.h"
#include <string>

using namespace std;

size_t writeCallback(char* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append(ptr, size * nmemb);
    return size * nmemb;
}

std::string getDate30DaysAgo() {
    // Get current time as a time_point
    auto now = std::chrono::system_clock::now();
    
    // Subtract 30 days (30 * 24 * 60 * 60 seconds) from the current time
    auto thirty_days_ago = now - std::chrono::hours(24 * 30);
    
    // Convert the time_point to a time_t for formatting
    std::time_t thirty_days_ago_time_t = std::chrono::system_clock::to_time_t(thirty_days_ago);
    
    // Convert to tm struct for local time
    std::tm* tm_thirty_days_ago = std::localtime(&thirty_days_ago_time_t);
    
    // Create a string stream to format the date
    std::ostringstream oss;
    oss << std::put_time(tm_thirty_days_ago, "%Y-%m-%d"); // Format: YYYY-MM-DD

    return oss.str(); // Return the formatted date string
}

vector<NewsArticle>* NewsManager::GetNewsArticles(string checkName)
{
    auto it = articles.find(checkName);
    if (it != articles.end()) {
        return &it->second;
    }
    return nullptr;
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
        std::string reqOptions = "?q=" + checkName + "&from=" + getDate30DaysAgo() + "&sortBy=publishedAt";

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

    //TODO: Update our generated articles
}

void NewsManager::LoadArticles(std::string checkName)
{
    articles[checkName] = vector<NewsArticle>();

    nlohmann::json_abi_v3_11_3::json fileData = nlohmann::json_abi_v3_11_3::json::parse(utils::LoadDataFromFile(getFileLoc(checkName)));

    // Check if the "articles" field exists
    if (fileData.contains("articles")) {
        auto jsonArticles = fileData["articles"];

        // Iterate through the array of articles
        for (const auto& article : jsonArticles) {

            NewsArticle na;
            
            // Extract the desired fields
            na.source = article["source"]["name"].get<std::string>();
            na.title = article["title"].get<std::string>();
            na.description = article["description"].get<std::string>();
            na.URL = article["url"].get<std::string>();
            na.publishedAt = article["publishedAt"].get<std::string>();

            articles[checkName].push_back(na);
        }
    } else {
        std::cout << "No articles found in the JSON data." << std::endl;
    }
}

NewsManager::NewsManager() 
{

}

void NewsManager::saveNewsToFile(std::string checkName,std::string responseData)
{   
    utils::CreateDirectory("News");
    utils::SaveDataToFile(getFileLoc(checkName),responseData);
}

std::string NewsManager::getFileLoc(std::string checkName)
{
    return "News/"+checkName+".txt";
}
