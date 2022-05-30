#pragma once
void fParalel() {

	omp_set_num_threads(tNums);
	setTLimit();
	double itime, ftime, exec_time;
	itime = omp_get_wtime();
	std::cout << "hesapliyor..." << std::endl;
	#pragma omp parallel private(gBinary, gBinaryLimit, isFinished)
	{
		isFinished = false;
		ifstream pr(gFileName);
		string line, field;
		bool sonuc = 1;
		int i = 1, c, k;
		bool a[3] = { 0 }, b; // eger bir elemani tanimli ise diger elemanlarin "||" islemini etkilememesi icin diger elemanlar default olarak 0 tanimlidir.
		unsigned long long counter = omp_get_thread_num() * thLimit; //tnum * thLimit
		unsigned long long limit = (omp_get_thread_num()+1) * thLimit;
		int flag = 0;
		string limitforThread = bitset<1000>(limit).to_string();

		while (!isSatisfiable && !isFinished) {

			sonuc = 1; // her deger dizisi icin baslangicta 1 olmali. sonuc islemini hesaplarken gerekli
			// cok buyuk bir binary dizisine counter degerini(binary olarak) atiyoruz
			gBinary = bitset<1000>(counter).to_string();
			// bu buyuk dizinin bizi ilgilendiren kismini(gVarNum=20 ise son 20 basamagi) ekrana yazdir
			//cout << "deger dizisi: " << gBinary.substr(gBinary.length() - gVarNum, gVarNum) << endl;

			while (getline(pr, line))
			{
				stringstream stream(line);
				// her satir icin cumle dizisi sifirlanmali
				for (int i = 0; i < 3; i++) {
					a[i] = 0;
				}
				c = 0; // a dizisinin indisi. her satir icin 0'dan basliyor
				flag = 0;
				// mevcut satirdaki bosluga kadar olan bir kelimeyi field'a yaz. 
				while (getline(stream, field, ' ')) {
					// satirin ilk karakteri c veya p ise sonraki satira atla
					if (field == "c") {
						//std::cout << "(yorum satiri)" << endl;
						flag = 1;
						break;
					}
					if (field == "p") {
						//std::cout << "(p cnf satiri)" << endl;
						flag = 1;
						break;
					}

					if (field != "0") {
						// dosyadan string olarak okunan degeri tamsayiya cevirir
						k = stold(field);
						//cout << field << endl;
						if (k < 0) {
							k = k * (-1); //pozitife cevir. orn: -6 --> 6
							if (gBinary[gBinary.length() - gVarNum - 1 + k] == '1') {
								a[c] = 0;
							}
							else {
								a[c] = 1;
							}
						}
						else {
							if (gBinary[gBinary.length() - gVarNum - 1 + k] == '1') {
								a[c] = 1;
							}
							else {
								a[c] = 0;
							}
						}
					}
					if (field == "0") {
						break;
					}
					c++;
					//cout << flag << endl;
				}

				// eger c veya p satiri ise hemen sonraki satira gec (counteri arttirmamis oluyoruz)
				if (flag == 1) {
					continue;
				}
				//cout << a[0] << " " << a[1] << " " << a[2] << endl;

				// tek degiskenli 2 degiskenli ve 3 degiskenli cumleler icin sonuc hesaplamalari
				if (c == 0) {
					break;
				}
				else if (c == 1) {
					sonuc = sonuc && a[0];
					//cout << a[0] << " " << endl;
				}
				else if (c == 2) {
					sonuc = sonuc && (a[0] || a[1]);
					//cout << a[0] << " " << a[1] << " " << endl;
				}
				else if (c == 3) {
					sonuc = sonuc && (a[0] || a[1] || a[2]);
					//cout << a[0] << " " << a[1] << " " << a[2] << endl;
				}
				// sonuc 0 ise digerlerine bakmaya gerek olmadigi icin bir sonraki degerler dizine geciyoruz
				if (sonuc == 0) { break; }


			}

			// sonuc 1 ise sonlandir
			if (sonuc == 1) {
				isSatisfiable = true;
				std::cout << "Problem is SAT." << endl;
				std::cout << "Solution: " << gBinary.substr(gBinary.length() - gVarNum, gVarNum) << endl;
			}
			// sonuc 0, ancak butun degerler denendiyse
			if (limitforThread == gBinary.substr(gBinary.length() - gVarNum, gVarNum)) {
				std::cout << "Binary limit reached (" << gBinaryLimit << ")" << endl;
				std::cout << "Problem is UNSAT." << endl;
				isFinished = true;
			}
			if (counter == ULLONG_MAX) {
				isFinished = true;
				std::cout << "Counter limit reached! (" << counter << ")" << endl;
			}

			counter++;
			//cout << "counter " << counter << endl;
			//std::cout << sonuc << endl;
			// dosyanin basina konumlan
			pr.clear();                 // clear fail and eof bits
			pr.seekg(0, std::ios::beg);
		}

	}
	ftime = omp_get_wtime();
	exec_time = ftime - itime;
	std::cout << "\ngecen sure " << exec_time << endl;
}