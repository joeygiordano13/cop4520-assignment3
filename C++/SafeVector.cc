#include <mutex>
#include <vector>
#include <random>
#include <algorithm>

class SafeVector {
    private:
        std::mutex lock;
        std::vector<unsigned int> vec = std::vector<unsigned int>();
    public:
        SafeVector(unsigned int size) {
            // Create vector with tags 1->N
            for (int n = 0; n < size; n++) {
                vec.push_back(n);
            }
            // Don't perform these operations 
            // on empty vector
            if (size > 0) {
                // Create random number generator
                std::random_device rnd_device;
                std::mt19937 mersenne_engine(rnd_device());
                // Shuffle tags
                std::shuffle(begin(vec), end(vec), mersenne_engine);
            }
        }

        void push(unsigned int val) {
            lock.lock();
            vec.push_back(val);
            lock.unlock();
            return;
        }

        unsigned int pop() {
            lock.lock();
            unsigned int vecBack = vec.back();
            vec.pop_back();
            lock.unlock();
            return vecBack;
        }

        unsigned int size() {
            lock.lock();
            unsigned int size = vec.size();
            lock.unlock();
            return size;
        }
};