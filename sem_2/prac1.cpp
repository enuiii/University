#include <iostream>
#include <string>
#include <vector>

class FibonacciCipher {
public:
    FibonacciCipher(const std::vector<int>& key) : key_(key) {}

    std::string Encode(const std::string& message) const {
        std::vector<std::string> words = SplitMessageIntoWords(message);
        std::vector<int> wordIndices(words.size());
        for (int i = 0; i < words.size(); i++) {
            wordIndices[i] = i + 1;
        }
        SortWordsByFibonacciSequence(wordIndices, words);
        return JoinWordsIntoMessage(words);
    }

    std::string Decode(const std::string& encodedMessage) const {
        std::vector<std::string> words = SplitMessageIntoWords(encodedMessage);
        std::vector<int> wordIndices(words.size());
        for (int i = 0; i < words.size(); i++) {
            wordIndices[i] = i + 1;
        }
        SortWordsByFibonacciSequence(wordIndices, words);
        std::vector<std::string> decodedWords(words.size());
        for (int i = 0; i < words.size(); i++) {
            decodedWords[wordIndices[i] - 1] = words[i];
        }
        return JoinWordsIntoMessage(decodedWords);
    }

    void SetKey(const std::vector<int>& key) {
        key_ = key;
    }

    const std::vector<int>& GetKey() const {
        return key_;
    }

private:
    std::vector<int> key_;

    std::vector<std::string> SplitMessageIntoWords(const std::string& message) const {
        std::vector<std::string> words;
        std::string word;
        for (char c : message) {
            if (std::isspace(c) || std::ispunct(c)) {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
            } else {
                word += c;
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }
        return words;
    }

    std::string JoinWordsIntoMessage(const std::vector<std::string>& words) const {
        std::string message;
        for (int i = 0; i < words.size(); i++) {
            message += words[i];
            if (i != words.size() - 1) {
                message += " ";
            }
        }
        return message;
    }

    void SortWordsByFibonacciSequence(std::vector<int>& wordIndices, std::vector<std::string>& words) const {
        int n = key_.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (key_[i] > key_[j]) {
                    std::swap(key_[i], key_[j]);
                    std::swap(wordIndices[i], wordIndices[j]);
                }
            }
        }
        int i = 0;
        int j = n - 1;
        while (i < j) {
            std::swap(wordIndices[i], wordIndices[j]);
            std::swap(words[i], words[j]);
            i++;
            j--;
        }
        for (int k = 2; k < n; k++) {
            int i = k;
            while (i > 1 && key_[i] < key_[i - 2]) {
                std::swap(key_[i], key_[i - 2]);
                std::swap(wordIndices[i], wordIndices[i - 2]);
                std::swap(words[i], words[i - 2]);
                i -= 2;
            }
        }
    }
};

int main() {
    FibonacciCipher cipher({2, 8, 5, 1, 3});
    std::string message = "Hello, my name is Ivan.";
    std::string encodedMessage = cipher.Encode(message);
    std::cout << "Encoded message: " << encodedMessage << std::endl;
    std::string decodedMessage = cipher.Decode(encodedMessage);
    std::cout << "Decoded message: " << decodedMessage << std::endl;
}
