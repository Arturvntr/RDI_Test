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
	vector<string> ret;

public:

	Convert() {
		dozens = { "dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa" };
		numbers = { "um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove" };
		tens = { "dez", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove" };
		cens = { "cem", "cento", "duzentos", "trezentos", "quatrocentos", "quinhetos", "seissentos", "setessentos", "oitossentos", "novessentos" };
		steps = 0;
		zeroValue = 0;
		dozensValue = 0;
	}


	// ---- FALTA RESOLVER O PROBLEMA DO QUARENTA MIL E QUATRO
	string convertAmount2Words(string value, string cents) {
		if (value.empty() && cents.empty()) return "";
		steps = 0;
		zeroValue = 0;
		dozensValue = 0;
		ret.clear();

		for (int i = value.length() - 1; i >= 0; i--) {
			int iValue = value[i] - '0';

			// 0 - 9
			if (steps == 0) {
				unitsCreation(iValue, "", "", "", "");
			}
			// 10 - 99
			else if (steps == 1) {
				dozensCreation(iValue, "", "");
			}
			// 100 - 999
			else if (steps == 2) {
				hundredsCreation(iValue, "", "");
			}
			// 1000 - 9999
			else if (steps == 3) {
				unitsCreation(iValue, " mil e", " mil e", " mil", " mil");
			}
			// 10000 - 99999
			else if (steps == 4) {
				dozensCreation(iValue, " mil", " mil");
			}
			// 100000 - 999999
			else if (steps == 5) {
				hundredsCreation(iValue, " mil", " mil");
			}
			// 1000000 - 9999999
			else if (steps == 6) {
				unitsCreation(iValue, " milhoes e", " milhoes e", " milhao de", " milhoes de");
			}
			// 10000000 - 99999999
			else if (steps == 7) {
				dozensCreation(iValue, " milhoes de", " milhoes de");
			}
			// 100000000 - 999999999
			else if (steps == 8) {
				hundredsCreation(iValue, " milhoes de", " milhoes de");
			}
			steps++;
		}
		string result = "";
		for (int i = 0; i < ret.size(); i++) {
			result = ret[i] + " " + result;
		}
		result = result + "reais";
		return result;
	}

private:
	 void unitsCreation(int iValue, string additional1, string additional2, string additional3, string additional4) {
		if (iValue > 0) {
			if (iValue > 1 && zeroValue > 0) ret.push_back(numbers[iValue - 1] + additional1);
			else if (zeroValue > 0) ret.push_back(additional2);
			else if (iValue == 1) ret.push_back(additional3);
			else ret.push_back(numbers[iValue - 1] + additional4);
			zeroValue = 1;
		}
		dozensValue = iValue;

	}
	void dozensCreation(int iValue, string additional1, string additional2) {
		if (iValue > 0) {
			if (iValue > 1 && zeroValue > 0) ret.push_back(dozens[iValue - 1] + " e");
			else if (iValue > 1) {
				ret.push_back(dozens[iValue - 1] + additional1);
			}
			else {
				if (dozensValue > 0) ret.pop_back();
				ret.push_back(tens[dozensValue] + additional2);
			}
			zeroValue = 1;
		}
	}
	void hundredsCreation(int iValue, string additional1, string additional2) {
		if (iValue > 0) {
			if (zeroValue > 0) ret.push_back(cens[iValue] + " e");
			else if (iValue == 1) ret.push_back(cens[0] + additional1);
			else ret.push_back(cens[iValue] + additional2);
			zeroValue = 1;
		}
	}
};


string convertAmount2Words(string value, string cents) {
	
	if (value.empty() && cents.empty()) return "";

	vector<string> dozens({ "dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa" });
	vector<string> numbers({ "um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove" });
	vector<string> tens({ "dez", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove" });
	vector<string> cens({ "cem", "cento", "duzentos", "trezentos", "quatrocentos", "quinhetos", "seissentos", "setessentos", "oitossentos", "novessentos" });
	

	//Checking reais value

	vector<string> ret;
	string reaisResult = "";
	if (!value.empty() && stoi(value) != 0){
		if(stoi(value) == 1) reaisResult = "um real";
		else {
			int steps = 0;
			int zeroValue = 0;
			int dozensValue = 0;
			for (int i = value.length() - 1; i >= 0; i--) {
				int iValue = value[i] - '0';
				if (iValue > 0) {
					// 0 - 9
					if (steps == 0) {
						ret.push_back(numbers[iValue - 1]);
						zeroValue = 1;
						dozensValue = iValue;
					}
					// 10 - 99
					else if (steps == 1) {
						if (iValue > 1 && zeroValue > 0) ret.push_back(dozens[iValue - 1] + " e");
						else if (iValue > 1) {
							ret.push_back(dozens[iValue - 1]);
						}
						else {
							if (dozensValue > 0) ret.pop_back();
							ret.push_back(tens[dozensValue]);
						}
						zeroValue = 1;
					}
					// 100 - 999
					else if (steps == 2) {
						if (zeroValue > 0) ret.push_back(cens[iValue] + " e");
						else if (iValue == 1) ret.push_back(cens[0]);
						else ret.push_back(cens[iValue]);
						zeroValue = 1;
					}
					// 1000 - 9999 - mil
					else if (steps == 3) {
						if (iValue > 1 && zeroValue > 0) ret.push_back(numbers[iValue - 1] + " mil e");
						else if (zeroValue > 0) ret.push_back("mil e");
						else if (iValue == 1) ret.push_back("mil");
						else ret.push_back(numbers[iValue - 1] + " mil");
						zeroValue = 1;
						dozensValue = iValue;
					}
					// 10000 - 99999 - 10mil
					else if (steps == 4) {
						if (iValue > 1 && dozensValue > 0 && zeroValue > 0) ret.push_back(dozens[iValue - 1] + " e");
						else if (iValue > 1) {
							ret.push_back(dozens[iValue - 1] + " mil");
						}
						else {
							if (dozensValue > 0) ret.pop_back();
							ret.push_back(tens[dozensValue] + " mil");
						}
						zeroValue = 1;
					}
					// 100000 - 999999 - 100mil
					else if (steps == 5) {
						if (zeroValue > 0) ret.push_back(cens[iValue] + " e");
						else if (iValue == 1) ret.push_back(cens[0] + " mil");
						else ret.push_back(cens[iValue] + " mil");
						zeroValue = 1;
					}
					// 1000000 - 9999999 - 1milhao
					else if (steps == 6) {
						if (iValue > 1 && zeroValue > 0) ret.push_back(numbers[iValue - 1] + " milhoes e");
						else if (zeroValue > 0) ret.push_back("um milhao");
						else if (iValue == 1) ret.push_back("um milhao de");
						else ret.push_back(numbers[iValue - 1] + " milhoes de");
						zeroValue = 1;
						dozensValue = iValue;
					}
					// 10000000 - 99999999 - 10milhoes
					else if (steps == 7) {
						if (iValue > 1 && dozensValue > 0 && zeroValue > 0) ret.push_back(dozens[iValue - 1] + " e");
						else if (iValue > 1) {
							ret.push_back(dozens[iValue - 1] + " milhoes de");
						}
						else {
							if (dozensValue > 0) ret.pop_back();
							ret.push_back(tens[dozensValue] + " milhoes de");
						}
						zeroValue = 1;
					}
					// 100000000 - 999999999 - 100milhoes
					else if (steps == 8) {
						if (zeroValue > 0) ret.push_back(cens[iValue] + " e");
						else if (iValue == 1) ret.push_back(cens[0] + " milhoes de");
						else ret.push_back(cens[iValue] + " milhoes de");
						zeroValue = 1;
						
					}
				}
				steps++;
			}
			for (int i = 0; i < ret.size(); i++) {
				reaisResult = ret[i] + " " + reaisResult;
			}
			reaisResult = reaisResult + "reais";
		}
	}
	

	// checking cents
	vector<string> centsRet;
	string centsResult = "";
	if (!cents.empty() && stoi(cents) != 0) {
		if(stoi(cents) == 1) centsResult = "um centavo";
		else {
			int steps = 0;
			int zeroValue = 0;
			int dozensValue = 0;
			for (int i = cents.length() - 1; i >= 0; i--) {
				int iValue = cents[i] - '0';
				if (iValue > 0) {
					// 0 - 9
					if (steps == 0) {
						centsRet.push_back(numbers[iValue - 1]);
						zeroValue = 1;
						dozensValue = iValue;
					}
					// 10 - 99
					else if (steps == 1) {
						if (iValue > 1 && zeroValue > 0) centsRet.push_back(dozens[iValue - 1] + " e");
						else if (iValue > 1) {
							centsRet.push_back(dozens[iValue - 1]);
						}
						else {
							if (dozensValue > 0) centsRet.pop_back();
							centsRet.push_back(tens[dozensValue]);
						}
						zeroValue = 1;
					}
				}
				steps++;
			}
			for (int i = 0; i < centsRet.size(); i++) {
				centsResult = centsRet[i] + " " + centsResult;
			}
			centsResult = centsResult + "centavos";
		}
	}
	

	string result;
	if (reaisResult.empty()) result = centsResult;
	else if (centsResult.empty()) result = reaisResult;
	else result = reaisResult + " e " + centsResult;
	//remove(result.begin(), result.end(), ' ');
	result[0] = toupper(result[0]);
	return result;
}


int main(int argc, char* argv[]) {
	bool stop;
	//Convert conv = Convert();
	string temp, temp2="";

	while ("stop") {
		cin >> temp;
		cin >> temp2;

			//string result = conv.convertAmount2Words(temp, temp2);
			string result = convertAmount2Words(temp, temp2);

			cout << result + "\n";
		
	}
}
