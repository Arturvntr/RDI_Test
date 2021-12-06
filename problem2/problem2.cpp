#include<string>
#include<iostream>
#include <vector>
#include <map>

using namespace std;

/* Function to get the last loop executed by the robot
*  @Param: List of commands executed by robot
*    String with uppercase letters D, U, R, L
*  @return: commands executed during loop
* 
*    function goes command by command until find a possition which were visited before when it is find it goes backward until the first visite on that position
*/
string getLastLoop(string commands) {
	
	// Saving double of cell from command list (robot starts at the middle of the matrix
	int commandsSize = commands.size()*2;
	vector<vector<bool>> list(commandsSize + 1, vector<bool>(commandsSize + 1,0));
	int xValue = commandsSize / 2, yValue = commandsSize / 2;

	// visit for each cell according the commands received
	list[xValue][yValue] = true;
	bool cycle = false;
	int index = 0;
	while (index < commands.length() && !cycle ) {
		char command = commands[index];

		if (command == 'R') xValue++; // right command
		else if (command == 'L') xValue--; // left command
		else if (command == 'D') yValue--; // down command
		else if (command == 'U') yValue++; // up command
		
		//check if the cell was visited
		if (!list[xValue][yValue]) list[xValue][yValue] = true;
		else cycle = true;
		index++;
	}

	if (!cycle) return "";

	// going back from the point already visited until the begin of loop
	string commandsCycle = "";
	index--;
	int xFound = xValue;
	int yFound = yValue;
	bool cycleClosed = false;
	while (!cycleClosed) {
		char command = commands[index];

		if (command == 'R') xValue--; // right command
		else if (command == 'L') xValue++; // left command
		else if (command == 'D') yValue++; // down command
		else if (command == 'U') yValue--; // up command
	
		// check if return to position of loop started
		if (xValue == xFound && yValue == yFound) cycleClosed = true;
		index--;
		commandsCycle = command + commandsCycle;
	}
	
	return commandsCycle;
}

int main(int argc, char* argv[]) {
	//string temp = "RRRRDDDLLUUUUUUURRDDDDR";

	string temp = "RRRRRRRRUUUUUUUULLLLLLLLDDDDDDDD";
	
	string result = getLastLoop(temp);
	
	cout << result + "\n";

}
