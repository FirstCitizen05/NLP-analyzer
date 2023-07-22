#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>

class TextProcessor {
public:
    static std::string preprocessText(std::string text) {
        
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);
        text.erase(std::remove_if(text.begin(), text.end(), ::ispunct), text.end());
        return text;
    }
};

class WordFrequencyAnalyzer {
private:
    std::map<std::string, int> wordFrequency;

public:
    void analyzeWordFrequency(const std::string& text) {
        std::string processedText = TextProcessor::preprocessText(text);
        std::string word;
        std::istringstream iss(processedText);
        while (iss >> word) {
            wordFrequency[word]++;
        }
    }

    void displayWordFrequency() const {
        std::cout << "Word Frequency Analysis:\n";
        for (const auto& pair : wordFrequency) {
            std::cout << pair.first << ": " << pair.second << " occurrences\n";
        }
    }

    std::vector<std::pair<std::string, int>> getTopMostFrequentWords(int count) const {
        std::vector<std::pair<std::string, int>> mostFrequent;
        for (const auto& pair : wordFrequency) {
            mostFrequent.push_back(pair);
        }
        std::sort(mostFrequent.begin(), mostFrequent.end(),
                  [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                      return a.second > b.second;
                  });

        return std::vector<std::pair<std::string, int>>(mostFrequent.begin(), mostFrequent.begin() + count);
    }
};

class SentenceAnalyzer {
public:
    int countSentences(const std::string& text) const {
        int sentenceCount = 0;
        for (char c : text) {
            if (c == '.' || c == '?' || c == '!') {
                sentenceCount++;
            }
        }
        return sentenceCount;
    }

    double calculateAverageSentenceLength(const std::string& text) const {
        int sentenceCount = countSentences(text);
        int wordCount = std::count_if(text.begin(), text.end(), ::isspace) + 1;
        return static_cast<double>(wordCount) / sentenceCount;
    }
};

class KeywordSearch {
public:
    bool searchKeyword(const std::string& text, const std::string& keyword) const {
        std::string processedText = TextProcessor::preprocessText(text);
        return processedText.find(keyword) != std::string::npos;
    }
};

int main() {
    std::string text;
    std::cout << "Enter the text to analyze:\n";
    std::getline(std::cin, text);

    WordFrequencyAnalyzer wordAnalyzer;
    wordAnalyzer.analyzeWordFrequency(text);

    SentenceAnalyzer sentenceAnalyzer;
    int sentenceCount = sentenceAnalyzer.countSentences(text);
    double avgSentenceLength = sentenceAnalyzer.calculateAverageSentenceLength(text);

    int topN;
    std::cout << "\nEnter the value of N for the top N most frequent words: ";
    std::cin >> topN;

    std::vector<std::pair<std::string, int>> topWords = wordAnalyzer.getTopMostFrequentWords(topN);

    std::cout << "\nSentence Analysis:\n";
    std::cout << "Number of sentences: " << sentenceCount << '\n';
    std::cout << "Average sentence length: " << avgSentenceLength << " words per sentence\n";

    std::cout << "\nTop " << topN << " Most Frequent Words:\n";
    for (const auto& pair : topWords) {
        std::cout << pair.first << ": " << pair.second << " occurrences\n";
    }

    KeywordSearch keywordSearch;
    std::string keyword;
    std::cout << "\nEnter a keyword to search: ";
    std::cin.ignore();
    std::getline(std::cin, keyword);
    bool found = keywordSearch.searchKeyword(text, keyword);
    std::cout << "Keyword '" << keyword << "' " << (found ? "is found" : "is not found") << " in the text.\n";

    return 0;
}