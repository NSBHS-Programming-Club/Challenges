#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cstring>

using std::string;
using std::vector;


// leftPad function takes pointer and pads it by n spaces pre simple function
inline void rightPad(string *ptr, int padNum) {
  for (; padNum > 0; padNum--) {
    *ptr += " ";
  }
}

// Breaks a function into a vector of lines
vector<string> lineBreaker(string program) {
  vector<string> vec;
  std::stringstream ps(program);
  string line;
  while(std::getline(ps, line)) {
    vec.push_back(line);
  }
  return vec;
}

// Calulates the maximum line length given a single input pre simple function too
inline int maxLength(vector<string> vec) {
  int max = 0;
  for (string line: vec) {
    max = (line.length() > max ? line.length() : max);
  }
  return max;
}

inline bool containsSpecial(string line) {
  return (line.find("{") != string::npos) || (line.find("}") != string::npos) || (line.find(";") != string::npos);
}

// Cleans up the program and removes single closing braces
vector<string> cleanUp(vector<string> temp) {
  vector<string> vec = temp;
  for(int i = vec.size()-1; i > 0; i--) {
    bool isSingleBrace = true;
   
    
    // Determine if it is single brace or not
    for (int j = 0; j < vec[i].size(); j++) {
      if (!(vec[i][j] == ' ' || vec[i][j] == '\n' || vec[i][j] == '}')) {
        isSingleBrace = false;
      }
    }
    if (!isSingleBrace) {
      continue;
    }
    
    // Take this, append to top and continue
    vec[i-1].erase(std::remove(vec[i-1].begin(), vec[i-1].end(), '\n'), vec[i-1].end());
    vec[i-1].append(vec[i], (int) vec[i].find("}"), vec[i].length());
    vec.pop_back();
  }
  
  return vec;
}


// Main body of the algorithm
string evalString(string program) {
  string final = "";
  // Break the program into a vector first
  vector<string> vec = lineBreaker(program);
  vector<string> tempVec(0);
  // Get the amount to be padded
  int padAmt = maxLength(vec);
  // Iterate over vec and push element pack x spaces
  for (string line: vec) {
    // Determine if it contains one of the elements in the "special charachters" tuple
    if (!containsSpecial(line)) {
      continue;
    }
    
    // Perform rest of function
    // Get pos of first element that can be pushed to the edge
    size_t openBrace = line.find("{");
    size_t closeBrace = line.find("}");
    size_t semiColon = line.find(";");
    
    // Determine which one is first
    int first = std::min(std::min(openBrace, closeBrace), semiColon);
    string nonSpecial = line.substr(0, first);
    rightPad(&nonSpecial, padAmt - line.length());
    // Append it now boii
    string fin = nonSpecial + line.substr(first, line.length());
    tempVec.push_back(fin + "\n");
  }
  tempVec = cleanUp(tempVec);
  
  for (string line: tempVec) {
    final += line;
  }
  
  return final;
}

int main() {
  std::cout << evalString("public class Permuter {\nprivate static void permute(int n, char[] a) {\n  if (n == 0) {\n     System.out.println(String.valueOf(a));\n}\n}\n}");
  
  return 0;
}
