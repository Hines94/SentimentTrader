#include <string>

class LlamaModel {
public:
    static LlamaModel& getInstance() {
        static LlamaModel instance;
        return instance;
    }

    void InitLlama(const std::string& path);

    std::string runLLaMA(const std::string& input);

    LlamaModel(LlamaModel const&) = delete;
    void operator=(LlamaModel const&) = delete;

private:
    LlamaModel();
    ~LlamaModel();
    FILE* pipe;
};