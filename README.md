# Sentiment Trader
Small test project in C++ checking the effectivness of the LLama2 llm model at predicting market changes from news snippets. Requires tweaks to the original model in order to predict percentage changes from a specific article. 

## Goals of the project
- Predict prices with a reasonable level of accuracy from a news article
- Reduce latency so we can respond to articles in milliseconds within recieving them
- Improve concurrency for news watching (e.g process different news types in parallel in order to watch multiple instruments)
- Develop a solid out strategy to cut trades at appropriate times

## Env
Requires a env file with the follwing parameters:

```
NEWS_API_KEY=<https://newsapi.org/docs/get-started> #Your key for newsAPI to update and get the latest news

MODEL_PATH=../llama.cpp/models/llama-2-7b.Q5_K_M.gguf #What model shoud we be using from huggingface as a base point?

UPDATE_FREQUENCY=3600 #How frequently should we be looking to check for articles (in seconds)

SAVE_ARTICLES=true #Should we save the articles to file or just discard them after we have checked signals/trained?

B_RUN_TRADES=false #Should we run trades if we get a strong signal? (i.e train only or trade?)
```
