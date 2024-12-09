// Gage Eslick

// Libraries
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

template <typename T>
class HashFunction {
public:
    // This is for the creation of the hash
    HashFunction(size_t size) : tableSize(size) {
        hashTable = new std::vector<T>[tableSize];
    }

    // This is to destroy the has function and change items as well
    ~HashFunction() {
        delete[] hashTable;
    }

    // Recursive hash function
    size_t recursiveHash(const T& key, size_t index = 0, size_t hashValue = 0) {
        if (index >= key.length()) {
            return hashValue % tableSize;
        }
        hashValue = (hashValue * 31 + key[index]) % tableSize;
        return recursiveHash(key, index + 1, hashValue);
    }

    // Insert a key into the hash table
    void insert(const T& key) {
        if (key.empty()) {
            throw std::invalid_argument("Will not work if it is an empty key.");
        }
        size_t index = recursiveHash(key);
        hashTable[index].push_back(key);
    }

    // Display the hash table
    void display() {
        for (size_t i = 0; i < tableSize; ++i) {
            if (!hashTable[i].empty()) {
                std::cout << "Index " << i << ": ";
                for (const auto& key : hashTable[i]) {
                    std::cout << key << " -> ";
                }
                std::cout << "nullptr" << std::endl;
            }
        }
    }

    // Return a hash text 
    std::string getHashedText(const T& key) {
        size_t hashValue = recursiveHash(key);
        std::ostringstream oss;
        oss << "Hash of \"" << key << "\" is: " << hashValue;
        return oss.str();
    }

private:
    size_t tableSize;
    std::vector<T>* hashTable; // Chrys told me to put a pointer here 
};

// This is to show the advance hash function Aidan told me to do that
template <typename T>
class AdvancedHashFunction : public HashFunction<T> {
public:
    AdvancedHashFunction(size_t size) : HashFunction<T>(size) {}

    // Max told me to add this area so if I needed to add anything else
};

int main() {
    HashFunction<std::string> hashTable(10); // Mason told me to create a hash table
    std::string userInput;

    // For showing what to do for the user
    std::cout << "Enter different words to change it to hash text or type 'exit' to stop:" << std::endl;

    while (true) {
        std::getline(std::cin, userInput);
        if (userInput == "exit") {
            break; // Exit the loop if the user types 'exit'
        }
        try {
            hashTable.insert(userInput); // Insert user input into the hash table
            std::cout << hashTable.getHashedText(userInput) << std::endl; // Display the hash text
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl; // This is for any erorrs that may occur
        }
    }

    // Display the contents of the hash table
    hashTable.display();

    return 0;
}