#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include "NewsArticle.h"

class NewsManager {
public:
    static NewsManager& getInstance() {
        static NewsManager instance;
        return instance;
    }

    std::vector<NewsArticle>* GetNewsArticles(std::string checkName);

    void UpdateArticles(std::string checkName);

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
    std::unordered_map<std::string,std::unordered_set<std::string>> priorTitles;

    void saveNewsToFile(std::string checkName,std::vector<NewsArticle> newArts);

    static std::string getFileLoc(std::string checkName);
};