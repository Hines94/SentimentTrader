#include <iostream>
#include <chrono>
#include <thread>

#include "News/NewsManager.h"
#include "Llama/LlamaModel.h"
#include "Env/EnvManager.h"
#include "Utils/Utils.h"

int main() {
    while(true) {
        // Get the start time
        auto start = std::chrono::steady_clock::now();

        std:: cout << "Running update cycle" << std::endl;

        // Get new articles / prices
        NewsManager::getInstance().UpdateArticles("Tesla",false);

        // If trade mode enabled then first check for strong signals
        if(EnvManager::getInstance().getBoolParam("B_RUN_TRADES")) {
            std::cout << "TODO run trades if strong enough signals" << std::endl;
        }
        
        // TODO: Look at https://huggingface.co/ProsusAI/finbert
        // Update LLM with new articles
        // LlamaModel::getInstance().InitLlama(EnvManager::getInstance().getParam("MODEL_PATH"));
        std::cout << "TODO: Update Llama" << std::endl;

        // Await for next cycle of articles
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::chrono::duration<double> sleep_duration = std::chrono::seconds(EnvManager::getInstance().getIntParam("UPDATE_FREQUENCY")) - elapsed;
        if (sleep_duration.count() > 0) {
            std::this_thread::sleep_for(sleep_duration);
        }

    }

    return 0;
}
