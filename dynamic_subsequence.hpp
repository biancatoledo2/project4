///////////////////////////////////////////////////////////////////////////////
// dynamic_subsequence.hpp
//
// Dynamic programming algorithms for the longest substring, and longest
// subsequence, problems.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include <cstring>
#include <algorithm>
std::string dynamic_longest_substring(const std::string& a,
                                      const std::string& b) {
	std::string temp_a = a;
	std::string temp_b = b;

	int a_len = temp_a.length();
	int b_len = temp_b.length();
	int lcs = 0;
	int row;

	//turn the words into char[]
	char word_a[temp_a.size() + 1];
	strcpy(word_a, temp_a.c_str());

	char word_b[temp_b.size() + 1];
	strcpy(word_b, temp_b.c_str());

	int substrings[a_len + 1][b_len + 1];

	for(int x = 0; x <= a_len; x++){
		for(int y = 0; y <= b_len; y++){
			//fills outer layer with 0's for lcs retrieval buffer
			if(x == 0|| y == 0)
				substrings[x][y] = 0;
			//check if letters match
			else if(word_a[x - 1] == word_b[y - 1]){
				substrings[x][y] = substrings[x-1][y-1] + 1;
				if(substrings[x][y] > lcs){
					lcs++;
					row = x;
				}
			}
			else substrings[x][y] = 0;
		}	
	}

	int getlcs = 1;
	std::string least_common_string;
	std::string tmp;
	//loop appends letters in reverse order
	while(lcs != 0){
		tmp = word_a[row - getlcs];
		least_common_string.append(tmp);
		lcs--;
		getlcs++;
	}

	//switch them back to regular
	std::reverse(least_common_string.begin(), least_common_string.end());
	return least_common_string;
}

std::string dynamic_longest_subsequence(const std::string& a,
                                        const std::string& b) {

	std::string temp_a = a;
	std::string temp_b = b;

	int a_len = temp_a.length();
	int b_len = temp_b.length();

	//turn string into char[]
	char word_a[temp_a.size() + 1];
	strcpy(word_a, temp_a.c_str());

	char word_b[temp_b.size() + 1];
	strcpy(word_b, temp_b.c_str());

	int substrings[a_len + 1][b_len + 1];

	for(int x = 0; x <= a_len; x++){
		for(int y = 0; y <= b_len; y++){
			//fills outer layer with 0's for lcs retrieval buffer
			if(x == 0|| y == 0)
				substrings[x][y] = 0;
			//check if letters match
			else if(word_a[x - 1] == word_b[y - 1]){
				substrings[x][y] = substrings[x-1][y-1] + 1;
			}
			else 
				substrings[x][y] = std::max(substrings[x - 1][y], substrings[x][y-1]);
		}	
	}

	//retrieve lcs
	int pos1 = a_len;
	int pos2 = b_len;	


	std::string least_common_string;
	std::string tmp;
	while(pos1 > 0 && pos2 > 0){

		if(word_a[pos1 - 1] == word_b[pos2 - 1]){
			//letters appended in reverse order
			tmp = word_a[pos1 - 1]; 
			least_common_string.append(tmp);
			pos1--; pos2--; 
		}
		else if(substrings[pos1 - 1][pos2] > substrings[pos1][pos2 - 1])
			pos1--;
		else
			pos2--;

	}
	//reverse back to regular order
	std::reverse(least_common_string.begin(),least_common_string.end());

  return least_common_string;
}
