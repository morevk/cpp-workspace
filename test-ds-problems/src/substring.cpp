#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function to generate all substrings of a given string
vector<string> generateAllSubstrings(const string& str) {
    vector<string> substrings;
    int n = str.length();
    
    // Outer loop for starting index
    for (int i = 0; i < n; i++) {
        // Inner loop for ending index
        for (int j = i; j < n; j++) {
            // Extract substring from index i to j
            substrings.push_back(str.substr(i, j - i + 1));
        }
    }
    
    return substrings;
}

// Alternative: Function that prints all substrings directly
void printAllSubstrings(const string& str) {
    int n = str.length();
    
    cout << "All substrings of \"" << str << "\":" << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            cout << str.substr(i, j - i + 1) << endl;
        }
    }
}

// Helper function for recursive approach
void generateSubstringsRecursive(const string& str, int start, int end, vector<string>& result) {
    // Base case: if start index exceeds string length
    if (start >= str.length()) {
        return;
    }
    
    // Base case: if end index exceeds string length
    if (end >= str.length()) {
        // Move to next starting position
        generateSubstringsRecursive(str, start + 1, start + 1, result);
        return;
    }
    
    // Add current substring to result
    result.push_back(str.substr(start, end - start + 1));
    
    // Recursively generate substrings by extending the end index
    generateSubstringsRecursive(str, start, end + 1, result);
}

// Main function to generate all substrings using recursion
vector<string> generateAllSubstringsRecursive(const string& str) {
    vector<string> result;
    if (str.empty()) {
        return result;
    }
    
    generateSubstringsRecursive(str, 0, 0, result);
    return result;
}

int substring_main() {
    string input = "abc";
    
    // Method 1: Get all substrings in a vector
    vector<string> substrings = generateAllSubstrings(input);
    
    cout << "Method 1 - Stored in vector:" << endl;
    for (const string& s : substrings) {
        cout << s << endl;
    }
    
    cout << "\nTotal substrings: " << substrings.size() << endl;
    
    cout << "\n-------------------\n" << endl;
    
    // Method 2: Print directly
    printAllSubstrings(input);
    
    // Method 3: Recursive approach with start and end indices
    cout << "Method 3 - Recursive (start, end):" << endl;
    vector<string> substrings1 = generateAllSubstringsRecursive(input);
    for (const string& s : substrings1) {
        cout << s << endl;
    }
    cout << "Total: " << substrings1.size() << endl;
    return 0;
}