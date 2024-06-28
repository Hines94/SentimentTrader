#include <string>
#include <unordered_map>
#include <vector>
#include "NewsArticle.h"

class NewsManager {
public:
    static NewsManager& getInstance() {
        static NewsManager instance;
        return instance;
    }

    std::vector<NewsArticle>* GetNewsArticles(std::string checkName);

    void UpdateArticles(std::string checkName, bool SaveToFile);

    // Load from a file
    void LoadArticlesFromFile(std::string checkName);

    NewsManager(NewsManager const&) = delete;
    void operator=(NewsManager const&) = delete;

private:
    void LoadArticles(std::string checkName,std::string rawInput);
    // Will simply remove any duplicates
    void performDeduplication(std::string checkName,std::vector<NewsArticle> oldArticles);

    NewsManager();

    // Mapped by keyword
    std::unordered_map<std::string,std::vector<NewsArticle>> articles;

    void saveNewsToFile(std::string checkName,std::string responseData);

    static std::string getFileLoc(std::string checkName);
};