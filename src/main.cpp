#include <iostream>

#include "News/NewsManager.h"
#include "Llama/LlamaModel.h"

int main() {

    NewsManager::getInstance().UpdateArticles("Apple");
    NewsManager::getInstance().LoadArticles("Apple");
    const auto articles = NewsManager::getInstance().GetNewsArticles("Apple");
    const auto a = articles->at(0);
    
    std::cout << LlamaModel::getInstance().runLLaMA("How likely from -10 to 10 is this news to increase the Apple share price? " + a.title) << std::endl;

    return 0;
}
