#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void boyerMooreSearch(const std::string& text, const std::string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return;

    // Bad Character Heuristic Preprocessing
    std::vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[(unsigned char)pattern[i]] = i;
    }

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        // Check pattern from right to left
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        if (j < 0) {
            std::cout << "Pattern found at index: " << shift << std::endl;
            // Shift pattern to align next char in text
            shift += (shift + m < n) ? m - badChar[(unsigned char)text[shift + m]] : 1;
        } else {
            // Shift pattern based on bad character rule
            shift += std::max(1, j - badChar[(unsigned char)text[shift + j]]);
        }
    }
}

int main() {
    std::string text = "The quick brown fox jumped over the lazy dog";
    std::string pattern = "brown";
    boyerMooreSearch(text, pattern);
    return 0;
}
