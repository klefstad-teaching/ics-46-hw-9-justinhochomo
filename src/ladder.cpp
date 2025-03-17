#include "ladder.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>

void error(string word1, string word2, string msg){
    cout << "Error" << word1 << "and" << word2 << msg  << endl;
}

void load_words(set<string> & word_list, const string& file_name){
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string> &ladder){
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }

    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        cout << ladder[i];
        if (i < ladder.size() - 1) {
            cout << " ";
        }
    }
    cout << endl;
}




bool is_adjacent(const string &word1, const string &word2) {
    if (word1 == word2) return true;
    int len1 = word1.length(), len2 = word2.length();
    if (abs(len1 - len2) > 1) return false;

    if (len1 == len2) {
        int diff_count = 0;
        for (int i = 0; i < len1; i++) {
            if (word1[i] != word2[i]) {
                diff_count++;
                if (diff_count > 1) return false;
            }
        }
        return (diff_count == 1);
    }

    const string &shorter = (len1 < len2) ? word1 : word2;
    const string &longer = (len1 < len2) ? word2 : word1;
    size_t i = 0, j = 0;
    while (i < shorter.length() && j < longer.length()) {
        if (shorter[i] != longer[j]) {
            return shorter.substr(i) == longer.substr(j + 1);
        }
        i++, j++;
    }
    return true;
}


bool edit_distance_within(const string &str1, const string &str2, int d) {
    int m = str1.size(), n = str2.size();
    if (abs(m - n) > d) return false;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }

    return dp[m][n] <= d;
}


vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> queue;
    queue.push({begin_word}); 
    
    set<string> visited;
    visited.insert(begin_word);
    
    while (!queue.empty()) {
        vector<string> ladder = queue.front();
        queue.pop();
        
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                
                if (word == end_word) {
                    return new_ladder;
                }
                
                visited.insert(word);
                queue.push(new_ladder);
            }
        }
    }
    
    return {};
}

#define my_assert(e) {cout << #e << ((e) ? " passed" : " failed") << endl;}
void verify_word_ladder(){
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}