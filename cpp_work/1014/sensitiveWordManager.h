#ifndef SENSITIVEWOEDMANAGER_H
#define SENSITIVEWOEDMANAGER_H

#include <nlohmann/json.hpp>
#include <string>
#include <tuple>
#include <unordered_set>
#include <mutex>

using json = nlohmann::json;

class SensitiveWordManager
{
private:
    SensitiveWordManager();

    ~SensitiveWordManager();

    std::mutex mutex_;

    std::unordered_set<std::string> sensitiveWords_;
public:
    static SensitiveWordManager& GetInstance();

    void AddSensitiveWord(const std::string& sensitive);

    void ModifySensitiveWord(const std::string& before, const std::string& after);

    void DeleteSensitiveWord(const std::string& word);

    std::tuple<bool, std::string> CheckSensitiveWord(const std::string& word) const;

    void LoadSensitiveWordsJson(const std::string& filePath);

    void SaveSensitiveWordsToJson(const std::string& filePath);

    SensitiveWordManager(const SensitiveWordManager &) = delete;

    SensitiveWordManager& operator=(const SensitiveWordManager &) = delete;
};

#endif // SENSITIVEWOEDMANAGER_H