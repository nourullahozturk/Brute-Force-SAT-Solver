#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <bitset>
#include <omp.h>
#include <climits>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

#include "hDef.h"
#include "hSeri.h"
#include "hParalel.h"
#include "hTest.h"

int main() {
	int cevap;
	do
	{
		printMenu(); // giris
		cin >> cevap;
		switch (cevap)
		{
		case 1:
			fileName(); // dosya adini kullanicidan alir. gFileName'e atar.
			readVarNum(); // dosya degisken sayisini gVarNum'e atar.
			setLimit(); // limit degeri gVarNum kullanarak üretir ve gBinaryLimit'e atar.
			fSeri();
			resetGlobals();
			break;
		case 2:
			fileName(); // dosya adini kullanicidan alir. gFileName'e atar.
			readVarNum(); // dosya degisken sayisini gVarNum'e atar.
			setLimit(); // limit degeri gVarNum kullanarak üretir ve gBinaryLimit'e atar.
			fParalel();
			resetGlobals();
			break;
		case 3:
			fileName(); // dosya adini kullanicidan alir. gFileName'e atar.
			readVarNum(); // dosya degisken sayisini gVarNum'e atar.
			setLimit(); // limit degeri gVarNum kullanarak üretir ve gBinaryLimit'e atar.
			fTest();
			resetGlobals();
			break;
		default:
			cout << "Bad choice! Please try again later.\n";
		}
	} while (cevap);

	return 0;
}
