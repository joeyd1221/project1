#include <iostream>
using std::cout; using std::cin; using std::endl; using std::min;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <fstream>
using std::ifstream;
#include <map>
using std::map;
#include <algorithm>
using std::sort;

int shorter_word(const string &word, const string &comp_word) {
  int word_leng = static_cast<int>(word.size());
  int comp_leng = static_cast<int>(comp_word.size());
  return min(word_leng, comp_leng);
}

int main() {
  string pass;
  cout << "Give me a password:" << endl;
  cin >> pass;
  string com_pass;
//  this map will congtain the difference count as a key and
//  a vector of passwords at the value
  map<int,vector<string>> diff_pass;
  
  // im using an input file stream to get each password in the common passwords file and comparing the size to the user password, creating a map of integers and a vector of strings. the integers represent the number of characters different from the user password and the words with the same differences go in the same vector
  ifstream input("common_passwords.txt");
  while(getline(input, com_pass)) {
    int short_word = shorter_word(pass, com_pass);
    int diff_count = 0;
    const int leng_diff = abs(static_cast<int>(pass.size()) - static_cast<int>(com_pass.size()));
    for(int i = 0; i < short_word; ++i) {
      if(pass[i] != com_pass[i]) {
        ++diff_count;
      }
    }
    diff_count += leng_diff;
    diff_pass[diff_count].push_back(com_pass);
  }
  // the pair with most similar passwords is going to be the first accuring pair because maps are sorted by keys and going in increasing order 
  vector<string> words = diff_pass.begin()->second;
  int chars_off = diff_pass.begin()->first;
  
  // alphabetical order is required for the mimir style hence the sorting
  sort(words.begin(),words.end());
  string sim_words;
  for (auto x : words) {
    sim_words += x;
    sim_words += ", ";
  }
  cout << "You provided a password of " << pass << endl;
  cout << "The most similar passwords to " << pass << " are:"
       << endl;
  
  cout << sim_words << endl;
  cout << "All of which are " << chars_off << " character(s) different." << endl;
}
