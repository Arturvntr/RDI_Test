#include<string>
#include<iostream>
#include <vector>
#include <map>

using namespace std;


/* Function to check if a given string can be a palidrome permuting its letters
*  @param: text - String to be checked
*	string must contain lowcaser letters between a - z
*   Function check if there is more than one letters with odd amount. if there is this text cannot be a palindrome
*/
string isPalindromePermutation(string text) {
	vector<int> letters(27,0);

	for (int i = 0; i < text.length(); i++) {
		int iChar = text[i] - 'a';
		letters[iChar]++;
	}

	bool isPalindrome = true;
	int oddCount = 0;
	for (int i = 0; i < letters.size() && isPalindrome; i++) {
		if (letters[i] % 2 != 0) oddCount++;
		if (oddCount > 1) isPalindrome = false;
	}

	return (isPalindrome ? "YES" : "NO");

}


int main(int argc, char* argv[]) {

	string temp = "abcabcabcabczz";

	string result = isPalindromePermutation(temp);

	cout << result + "\n";

}
