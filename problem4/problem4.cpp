#include<string>
#include<iostream>
#include <vector>
#include <map>

using namespace std;


/* recursive function which will compute possibilies from each set of coins */
/*
* @Param: value - Integer value from 1 to 99
* @Param: coins - set of coins to be user for combination
*/
int countChange(int value, vector<int> coins) {
    if (value == 0) return 1;
    else if (coins.empty() || value < 0) return 0;
    else {
        int result = 0;
        result = countChange(value - coins.back(), coins);
        coins.pop_back();
        result = result + countChange(value, coins);
        return result;
    }
}


int getNumberOfCombinations(int value) {

    //Possible coins
    vector<int> coins({ 1, 5, 10, 20, 25, 50 });

    return countChange(value, coins);
}

/*
* Assuming values between 0 - 99 cents
* Input Values are integer
*/

int main(int argc, char* argv[]) {
    int value, result, compare;
    string testNumber;


    // test 1
    testNumber = "Test 1";
	value = 5;
    compare = 2;
    result = getNumberOfCombinations(value);
    if (result == compare) cout << testNumber << " Pass     -     " << result << "\n";
    else cout << testNumber << " Fail     -     " << result << "\n";

    // test 2
    testNumber = "Test 2";
    value = 10;
    compare = 4;
    result = getNumberOfCombinations(value);
    if (result == compare) cout << testNumber << " Pass     -     " << result << "\n";
    else cout << testNumber << " Fail     -     " << result << "\n";

    // test 3
    testNumber = "Test 3";
    value = 17;
    compare = 6;
    result = getNumberOfCombinations(value);
    if (result == compare) cout << testNumber << " Pass     -     " << result << "\n";
    else cout << testNumber << " Fail     -     " << result << "\n";

    // test 4
    testNumber = "Test 4";
    value = 20;
    compare = 10;
    result = getNumberOfCombinations(value);
    if (result == compare) cout << testNumber << " Pass     -     " << result << "\n";
    else cout << testNumber << " Fail     -     " << result << "\n";

    // test 5
    testNumber = "Test 5";
    value = 22;
    compare = 10;
    result = getNumberOfCombinations(value);
    if (result == compare) cout << testNumber << " Pass     -     " << result << "\n";
    else cout << testNumber << " Fail     -     " << result << "\n";

    

}