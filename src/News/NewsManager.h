#include <string>
#include <map>
#include <vector>
#include "NewsArticle.h"

class NewsManager {
public:
    static NewsManager& getInstance() {
        static NewsManager instance;
        return instance;
    }

    std::vector<NewsArticle> GetNewsArticles(std::string checkName);

    void UpdateArticles(std::string checkName);

    NewsManager(NewsManager const&) = delete;
    void operator=(NewsManager const&) = delete;

private:
    NewsManager();

    // Mapped by keyword
    std::map<std::string,std::vector<NewsArticle>> articles;

    void saveNewsToFile(std::string checkName,std::string responseData);
};