#include <string>

class LlamaModel {
public:
    static LlamaModel& getInstance() {
        static LlamaModel instance;
        return instance;
    }

    std::string runLLaMA(const std::string& input);

    LlamaModel(LlamaModel const&) = delete;
    void operator=(LlamaModel const&) = delete;

private:
    LlamaModel();
};