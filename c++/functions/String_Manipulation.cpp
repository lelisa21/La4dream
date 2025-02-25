#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Function 1: Check if a string is a palindrome
bool isPalindrome(const string& str) {
    string cleanedStr;
    for (char ch : str) {
        if (isalnum(ch)) {
            cleanedStr += tolower(ch);
        }
    }
    string reversedStr = cleanedStr;
    reverse(reversedStr.begin(), reversedStr.end());
    return cleanedStr == reversedStr;
}

// Function 2: Count vowels in a string
int countVowels(const string& str) {
    int count = 0;
    for (char ch : str) {
        char lowerCh = tolower(ch);
        if (lowerCh == 'a' || lowerCh == 'e' || lowerCh == 'i' ||
            lowerCh == 'o' || lowerCh == 'u') {
            count++;
        }
    }
    return count;
}

// Function 3: Find a substring within a string
size_t findSubstring(const string& str, const string& substr) {
    return str.find(substr);
}

// Function 4: Reverse a string
string reverseString(const string& str) {
    string reversedStr = str;
    reverse(reversedStr.begin(), reversedStr.end());
    return reversedStr;
}

// Function 5: Check if two strings are anagrams
bool areAnagrams(const string& str1, const string& str2) {
    string sortedStr1 = str1;
    string sortedStr2 = str2;
    
    // Remove spaces and convert to lowercase
    sortedStr1.erase(remove_if(sortedStr1.begin(), sortedStr1.end(), ::isspace), sortedStr1.end());
    sortedStr2.erase(remove_if(sortedStr2.begin(), sortedStr2.end(), ::isspace), sortedStr2.end());
    
    transform(sortedStr1.begin(), sortedStr1.end(), sortedStr1.begin(), ::tolower);
    transform(sortedStr2.begin(), sortedStr2.end(), sortedStr2.begin(), ::tolower);
    
    sort(sortedStr1.begin(), sortedStr1.end());
    sort(sortedStr2.begin(), sortedStr2.end());
    
    return sortedStr1 == sortedStr2;
}

// Main function to demonstrate the string manipulation functions
int main() {
    string input;

    // Palindrome check
    cout << "Enter a string to check if it's a palindrome: ";
    getline(cin, input);
    cout << (isPalindrome(input) ? "The string is a palindrome." : "The string is not a palindrome.") << endl;

 
    cout << "Enter a string to count vowels: ";
    getline(cin, input);
    cout << "Number of vowels: " << countVowels(input) << endl;

 
    string substr;
    cout << "Enter a string to search in: ";
    getline(cin, input);
    cout << "Enter the substring to find: ";
    getline(cin, substr);
    size_t position = findSubstring(input, substr);
    if (position != string::npos) {
        cout << "Substring found at position: " << position << endl;
    } else {
        cout << "Substring not found." << endl;
    }
    cout << "Enter a string to reverse: ";
    getline(cin, input);
    cout << "Reversed string: " << reverseString(input) << endl;

    // Anagram check
    string str1, str2;
    cout << "Enter the first string for anagram check: ";
    getline(cin, str1);
    cout << "Enter the second string for anagram check: ";
    getline(cin, str2);
    cout << (areAnagrams(str1, str2) ? "The strings are anagrams." : "The strings are not anagrams.") << endl;

    return 0;
}
/*
Anagrams are words or phrases that are formed by rearranging the letters of another word or phrase, using all the original letters exactly once. 
For example, the words "listen" and "silent" are anagrams of each other.

*/
