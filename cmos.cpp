#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <dirent.h>
#include <sstream> 
#include <unordered_map>


const size_t SHINGLE_LENGTH = 3;  // Adjust this value as needed

std::vector<std::string> generateShingles(const std::string& line) {
    std::vector<std::string> shingles;
    for (size_t i = 0; i <= line.size() - SHINGLE_LENGTH; ++i) {
        shingles.push_back(line.substr(i, SHINGLE_LENGTH));
    }
    return shingles;
}

std::unordered_set<size_t> hashShingles(const std::vector<std::string>& shingles) {
    std::unordered_set<size_t> hashes;
    for (const auto& shingle : shingles) {
        size_t hashValue = std::hash<std::string>{}(shingle);
        hashes.insert(hashValue);
    }
    return hashes;
}

int main() {
    std::ifstream tokensFile("tokens.txt");
    std::vector<std::string> lines;
    std::string line;

    // Read lines from tokens.txt
    while (getline(tokensFile, line)) {
        lines.push_back(line);
    }

    // Winnowing algorithm
    for (size_t i = 0; i < lines.size(); ++i) {
        std::vector<std::string> shingles = generateShingles(lines[i]);
        std::unordered_set<size_t> fingerprints = hashShingles(shingles);

        std::cout << "Fingerprints for Line " << i + 1 << ": ";
        for (const auto& fingerprint : fingerprints) {
            std::cout << fingerprint << " ";
        }
        std::cout << std::endl;

        // Compare fingerprints with other lines
        for (size_t j = i + 1; j < lines.size(); ++j) {
            std::vector<std::string> otherShingles = generateShingles(lines[j]);
            std::unordered_set<size_t> otherFingerprints = hashShingles(otherShingles);

            // Find common fingerprints
            std::vector<size_t> intersection;
            for (const auto& fingerprint : fingerprints) {
                if (otherFingerprints.count(fingerprint) > 0) {
                    intersection.push_back(fingerprint);
                }
            }

            // Calculate and output the similarity percentage
            double similarityPercentage =
                (static_cast<double>(intersection.size()) / fingerprints.size()) * 100;

            std::cout << "Similarity Percentage between File " << i + 1 << " and File " << j + 1 << ": "
                      << similarityPercentage << "%" << std::endl;
        }
    }

    return 0;
}