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

    // TODO: update/save previous
    void UpdateArticles(std::string checkName);

    // Load from a file
    void LoadArticles(std::string checkName);

    NewsManager(NewsManager const&) = delete;
    void operator=(NewsManager const&) = delete;

private:
    NewsManager();

    // Mapped by keyword
    std::unordered_map<std::string,std::vector<NewsArticle>> articles;

    void saveNewsToFile(std::string checkName,std::string responseData);

    static std::string getFileLoc(std::string checkName);
};