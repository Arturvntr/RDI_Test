#include<string>
#include<iostream>
#include <vector>

using namespace std;

class Convert {

private:
	vector<string> dozens;
	vector<string> numbers;
	vector<string> tens;
	vector<string> cens;
	
	int steps;
	int zeroValue;
	int dozensValue;
	int centoValue;
	vector<string> ret;
	vector<string> centsRet;

public:

	Convert() {
		dozens = { "dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa" };
		numbers = { "um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove" };
		tens = { "dez", "onze", "doze", "treze", "catorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove" };
		cens = { "cem", "cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos" };
		steps = 0;
		zeroValue = 0;
		dozensValue = 0;
		centoValue = 0;
	}

	/*
	* Function which conver the number given in to portuguese text of number
	*  @Param: value - Reais value
	*          value must be from 0 to 10^9 - 1
	*  @Param: cents - Cents value
	*          cents must be from 0 to 99
	* Return a text string
	*/
	string convertAmount2Words(string value, string cents) {
		if (value.empty() && cents.empty()) return "";
		else if(value.compare("0") == 0 && cents.compare("0") == 0) return "Zero reais";
		//checking reais
		steps = 0;
		zeroValue = 0;
		dozensValue = 0;
		centoValue = 0;
		ret.clear();
		string reaisResult = "";
		if (!value.empty() && stoi(value) != 0) {
			if (stoi(value) == 1) reaisResult = "um real";
			else {
				for (int i = value.length() - 1; i >= 0; i--) {
					int iValue = value[i] - '0';
					if (iValue > 0) {
						// 0 - 9
						if (steps == 0) {
							ret.push_back(unitsCreation(iValue, "e ", "", "", "um"));
							// endText= ""
							// preText = "e"
							// unit = ""
							// initialValue = "um"
						}
						// 10 - 99
						else if (steps == 1) {
							ret.push_back(dozensCreation(iValue, "e ", "", "", true));
							// preText = "e "
							// endText = ""
							// unit = ""
						}
						// 100 - 999
						else if (steps == 2) {
							ret.push_back(hundredsCreation(iValue, "e ", "", ""));
							// preText = "e "
							// endText = ""
							// unit = ""
						}
						// 1000 - 9999
						else if (steps == 3) {
							ret.push_back(unitsCreation(iValue, "e ", "", " mil", "um mil"));
							// endText = "e"
							// preText = ""
							// unit = "mil"
							// initialValue = "mil"
						}
						// 10000 - 99999
						else if (steps == 4) {
							ret.push_back(dozensCreation(iValue, "e ", "", " mil", true));
							// preText = "e "
							// endText = ""
							// unit = "mii"
						}
						// 100000 - 999999
						else if (steps == 5) {
							ret.push_back(hundredsCreation(iValue, "e ", "", " mil"));
							// preText = "e "
							// endText = ""
							// unit = "mil"
						}
						// 1000000 - 9999999
						else if (steps == 6) {
							ret.push_back(unitsCreation(iValue, "e ", " de", " milhoes", "um milhao"));
							// endText = "de"
							// preText = ""
							// unit = "milhoes"
							// initialValue = "um milhao"
						}
						// 10000000 - 99999999
						else if (steps == 7) {
							ret.push_back(dozensCreation(iValue, "e ", " de", " milhoes", true));
							// preText = ""
							// endText = " de"
							// unit = "milhoes"
						}
						// 100000000 - 999999999
						else if (steps == 8) {
							ret.push_back(hundredsCreation(iValue, "e ", " de", " milhoes"));
							// preText = "e "
							// endText = " de"
							// unit = " milhoes"
						}
					}
					if (steps == 4 || steps == 1) dozensValue = 0;
					else if (steps == 5 || steps == 2) centoValue = 0;
					steps++;
				}
				for (int i = 0; i < ret.size(); i++) {
					reaisResult = ret[i] + " " + reaisResult;
				}
				reaisResult = reaisResult + "reais";
				//removing "e " from beginning
				if (reaisResult[0] == 'e') reaisResult = reaisResult.substr(2);
			}
		}
		
		//checking cents
		steps = 0;
		zeroValue = 0;
		dozensValue = 0;
		centsRet.clear();
		string centsResult = "";
		if (!cents.empty() && stoi(cents) != 0) {
			if (stoi(cents) == 1) centsResult = "um centavo";
			else {
				for (int i = cents.length() - 1; i >= 0; i--) {
					int iValue = cents[i] - '0';
					if (iValue > 0) {
						// 0 - 9
						if (steps == 0) {
							centsRet.push_back(unitsCreation(iValue, "e ", "", "", "um"));
							// endText= ""
							// preText = "e"
							// unit = ""
							// initialValue = "um"
						}
						// 10 - 99
						else if (steps == 1) {
							centsRet.push_back(dozensCreation(iValue, "e ", "", "", false));
							// preText = "e "
							// endText = ""
							// unit = ""
						}
					}
					steps++;
				}
				for (int i = 0; i < centsRet.size(); i++) {
					centsResult = centsRet[i] + " " + centsResult;
				}
				centsResult = centsResult + "centavos";
				//removing "e " from beginning
				if (centsResult[0] == 'e') centsResult = centsResult.substr(2);
			}
		}

		// join reais and cents string
		string result;
		if (reaisResult.empty()) result = centsResult;
		else if (centsResult.empty()) result = reaisResult;
		else result = reaisResult + " e " + centsResult;
		

		//for Mil reais removing "um"
		if(!value.empty() && 999 < stoi(value) && stoi(value) < 2000) result = result.substr(3);

		// converting first letter to upper case
		result[0] = toupper(result[0]);
		return result;
	}

	string testFunction(string testNumber, string compareString, string value1, string value2) {
		string test = "";
		string result = convertAmount2Words(value1, value2);

		if (result.compare(compareString) == 0) test = testNumber + " Pass    -     " + result;
		else test = testNumber + " Fail    -     " + result;
		
		return test;
	}

private:
	string unitsCreation(int iValue, string preText, string endText, string unit, string initialValue) {
		string result = "";
		if(iValue > 1) result = preText + numbers[iValue - 1] + unit;
		else result = preText + initialValue;
		 if (zeroValue == 0) result = result + endText;
		 zeroValue = 1;
		 dozensValue = iValue;
		 centoValue = 1;
		 return result;
	}
	//this function is not covering the result for "11 milhoes "de" reais" - It is missing the "de"
	string dozensCreation(int iValue, string preText, string endText, string unit, bool reais) {
		string result = "";
		if (iValue > 1) {
			result = preText + dozens[iValue - 1];
			if (dozensValue == 0) result = result + unit;
		}
		else {
			if (dozensValue > 0) {
				if (reais) ret.pop_back();
				else centsRet.pop_back();
			}
			result = preText + tens[dozensValue] + unit;
		}
		if (zeroValue == 0) result = result + endText;
		zeroValue = 1;
		centoValue = 1;
		dozensValue = 0;
		return result;
	}
	string hundredsCreation(int iValue, string preText, string endText, string unit) {
		string result = "";
		if (centoValue > 0) result = cens[iValue];
		else {
			if (iValue == 1) result = preText + cens[0] + unit;
			else result = preText + cens[iValue] + unit;
		}
		if (zeroValue == 0) result = result + endText;

		zeroValue = 1;
		centoValue = 0;
		return result;
		
	}
};

int main(int argc, char* argv[]) {
	Convert conv = Convert();
	string value1, value2, testNumber, assert, result;


	// Test 1
	testNumber = "Test 1";
	value1 = "1";
	value2 = "0";
	assert = "Um real";
	result = conv.testFunction(testNumber, assert, value1, value2);
	
	cout << result << "\n";

	// Test 2
	testNumber = "Test 2";
	value1 = "2";
	value2 = "0";
	assert = "Dois reais";
	result = conv.testFunction(testNumber, assert, value1, value2);
	
	cout << result << "\n";

	// Test 3
	testNumber = "Test 3";
	value1 = "10";
	value2 = "0";
	assert = "Dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 4
	testNumber = "Test 4";
	value1 = "11";
	value2 = "0";
	assert = "Onze reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";


	// Test 5
	testNumber = "Test 5";
	value1 = "20";
	value2 = "0";
	assert = "Vinte reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 6
	testNumber = "Test 6";
	value1 = "25";
	value2 = "0";
	assert = "Vinte e cinco reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";
	
	// Test 7
	testNumber = "Test 7";
	value1 = "100";
	value2 = "0";
	assert = "Cem reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 8
	testNumber = "Test 8";
	value1 = "101";
	value2 = "0";
	assert = "Cento e um reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 9
	testNumber = "Test 9";
	value1 = "110";
	value2 = "0";
	assert = "Cento e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 10
	testNumber = "Test 10";
	value1 = "111";
	value2 = "0";
	assert = "Cento e onze reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 11
	testNumber = "Test 11";
	value1 = "200";
	value2 = "0";
	assert = "Duzentos reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 12
	testNumber = "Test 12";
	value1 = "210";
	value2 = "0";
	assert = "Duzentos e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 13
	testNumber = "Test 13";
	value1 = "1000";
	value2 = "0";
	assert = "Mil reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 14
	testNumber = "Test 14";
	value1 = "1100";
	value2 = "0";
	assert = "Mil e cem reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 15
	testNumber = "Test 15";
	value1 = "1110";
	value2 = "0";
	assert = "Mil cento e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";


	// Test 16
	testNumber = "Test 16";
	value1 = "2110";
	value2 = "0";
	assert = "Dois mil cento e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 17
	testNumber = "Test 17";
	value1 = "10110";
	value2 = "0";
	assert = "Dez mil cento e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 18
	testNumber = "Test 18";
	value1 = "11110";
	value2 = "0";
	assert = "Onze mil cento e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 19
	testNumber = "Test 19";
	value1 = "31110";
	value2 = "0";
	assert = "Trinta e um mil cento e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 20
	testNumber = "Test 20";
	value1 = "30010";
	value2 = "0";
	assert = "Trinta mil e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 21
	testNumber = "Test 21";
	value1 = "30001";
	value2 = "0";
	assert = "Trinta mil e um reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 22
	testNumber = "Test 22";
	value1 = "100100";
	value2 = "0";
	assert = "Cem mil e cem reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 23
	testNumber = "Test 23";
	value1 = "200100";
	value2 = "0";
	assert = "Duzentos mil e cem reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 24
	testNumber = "Test 24";
	value1 = "200110";
	value2 = "0";
	assert = "Duzentos mil cento e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 25
	testNumber = "Test 25";
	value1 = "210101";
	value2 = "0";
	assert = "Duzentos e dez mil cento e um reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 26
	testNumber = "Test 26";
	value1 = "1210101";
	value2 = "0";
	assert = "Um milhao duzentos e dez mil cento e um reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 27
	testNumber = "Test 27";
	value1 = "1000000";
	value2 = "0";
	assert = "Um milhao de reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";
	// Test 28
	testNumber = "Test 28";
	value1 = "1100200";
	value2 = "0";
	assert = "Um milhao e cem mil e duzentos reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";
	// Test 29
	testNumber = "Test 29";
	value1 = "1110200";
	value2 = "0";
	assert = "Um milhao e cento e dez mil e duzentos reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";
	// Test 30
	testNumber = "Test 30";
	value1 = "1100210";
	value2 = "0";
	assert = "Um milhao cem mil duzentos e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 31
	testNumber = "Test 31";
	value1 = "1110210";
	value2 = "0";
	assert = "Um milhao cento e dez mil duzentos e dez reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 32
	testNumber = "Test 32";
	value1 = "1110001";
	value2 = "0";
	assert = "Um milhao cento e dez mil e um reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 33
	testNumber = "Test 33";
	value1 = "11000000";
	value2 = "0";
	assert = "Onze milhoes de reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 34
	testNumber = "Test 34";
	value1 = "45000000";
	value2 = "0";
	assert = "Quarenta e cinco milhoes de reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 35
	testNumber = "Test 35";
	value1 = "945000000";
	value2 = "0";
	assert = "Novecentos e quarenta e cinco milhoes de reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 36
	testNumber = "Test 36";
	value1 = "0";
	value2 = "1";
	assert = "Um centavo";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 37
	testNumber = "Test 37";
	value1 = "100";
	value2 = "45";
	assert = "Cem reais e quarenta e cinco centavos";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 38
	testNumber = "Test 38";
	value1 = "10";
	value2 = "15";
	assert = "Dez reais e quinze centavos";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

	// Test 39
	testNumber = "Test 39";
	value1 = "0";
	value2 = "0";
	assert = "Zero reais";
	result = conv.testFunction(testNumber, assert, value1, value2);

	cout << result << "\n";

}
