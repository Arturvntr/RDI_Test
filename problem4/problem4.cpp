#include<string>
#include<iostream>
#include <vector>
#include <map>

using namespace std;


/* recursive function which will compute possibilies from each set of coins */
/*
* @Param: value - Integer value from 0 to 99
* @Param: coins - set of coins to be user for combination
*/
int countChange(int value, vector<int> coins) {
    if (value == 0) return 1;
    else if (coins.empty() || valeu < 0) return 0;
    else {
        int result = 0;
        result = countChange(valeu - coins.back(), coins);
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

	int temp = 5;

	int result = getNumberOfCombinations(temp);

	cout << "" + result;

}