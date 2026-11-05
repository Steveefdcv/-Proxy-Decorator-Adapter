#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class VeryHeavyDatabase {
public:
    virtual ~VeryHeavyDatabase() = default;
    virtual std::string GetData(const std::string& key) const noexcept {
        return "value";
    }
};

class OneShotDB : public VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1)
        : real_object_(real_object), shots_(shots) {
    }

    std::string GetData(const std::string& key) const noexcept override {
        if (shots_ > 0) {
            --shots_;
            return real_object_->GetData(key);
        }
        return "error";
    }

private:
    VeryHeavyDatabase* real_object_;
    mutable size_t shots_;
};

int main() {
    auto real_db = VeryHeavyDatabase();
    auto limit_db = OneShotDB(std::addressof(real_db), 2);
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    return 0;
}