#define tNums 4

using namespace std;

int gVarNum = 0;
int thLimit = 0;
string gBinary = bitset<1000>(0).to_string();
string gFileName = "";
bool isSatisfiable = false;
bool isFinished = false;
string gBinaryLimit = "";

void resetGlobals() {
	gVarNum = 0;
	thLimit = 0;
	gBinary = bitset<1000>(0).to_string();
	gFileName = "";
	isSatisfiable = false;
	isFinished = false;
	gBinaryLimit = "";
}


void printVars() {
	cout << "gVarNum: " << gVarNum << "\ngBinary: " << gBinary
		<< "\ngFileName: " << gFileName << "\ngBinaryLimit: "
		<< gBinaryLimit << endl;
}

void readVarNum() {
	ifstream pr(gFileName);
	string input;
	int degisken;
	while (pr >> input) {
		if (input == "cnf") {
			pr >> input;
			break;
		}
	}
	stringstream ss(input);
	ss >> degisken;
	gVarNum = degisken;
}

void printMenu() {
	std::cout << "MENU (sayi giriniz 1,2) " << endl;
	std::cout << "1 - Kaba kuvvet (Seri) SAT cozucu " << endl;
	std::cout << "2 - Kaba kuvvet (Paralel) SAT cozucu " << endl;
	std::cout << "3 - Sonucu test et! " << endl;
	std::cout << "0 - Cikis " << endl;
}

void fileName() {
	string fName;
	// input kontrolu yapilacak...
	cout << "Dosya adini giriniz" << endl;
	cin >> fName;
	gFileName = fName;
}


void setLimit() {
	string limit;
	for (int i = 0; i < gVarNum; i++) {
		limit += "1";
	}
	gBinaryLimit = limit;
}

void setTLimit() {
	thLimit = pow(2, gVarNum);
	thLimit = thLimit / tNums;
}