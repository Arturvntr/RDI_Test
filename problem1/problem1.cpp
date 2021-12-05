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
		tens = { "dez", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove" };
		cens = { "cem", "cento", "duzentos", "trezentos", "quatrocentos", "quinhetos", "seissentos", "setessentos", "oitossentos", "novessentos" };
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
							ret.push_back(unitsCreation(iValue, "e ", "", " mil", "mil"));
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
							ret.push_back(unitsCreation(iValue, "", " de", " milhoes", "um milhao"));
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
					if (steps == 5 || steps == 2) centoValue = 0;
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

private:
	string unitsCreation(int iValue, string preText, string endText, string unit, string initialValue) {
		string result = "";
		 result = preText + numbers[iValue - 1] + unit;
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
	bool stop = false;
	Convert conv = Convert();
	string temp, temp2="";

	while (!stop) {
		cin >> temp;
		cin >> temp2;

			string result = conv.convertAmount2Words(temp, temp2);

			cout << result + "\n";
		
	}
}
