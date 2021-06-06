/**
 * original source https://raymii.org/s/tutorials/Cpp_std_async_with_a_concurrency_limit.html
 */

#ifndef DEEP_TEXT_REPLACE_SEMPAHORE_HPP
#define DEEP_TEXT_REPLACE_SEMPAHORE_HPP
#include <condition_variable>
#include <cstddef>
#include <mutex>

class Semaphore {
 public:
    explicit Semaphore(size_t count) : count(count) {
    }

    [[nodiscard]] auto getCount() const -> size_t {
        return count;
    };

    void lock() {
        std::unique_lock<std::mutex> lock(mutex);
        condition_variable.wait(lock, [this] {
            if (count != 0) {
                return true;
            } else {
                return false;
            }
        });
        --count;
    }

    void unlock() {
        std::unique_lock<std::mutex> lock(mutex);
        ++count;
        condition_variable.notify_one();
    }

 private:
    std::mutex mutex;
    std::condition_variable condition_variable;
    size_t count;
};

#endif  // DEEP_TEXT_REPLACE_SEMPAHORE_HPP
