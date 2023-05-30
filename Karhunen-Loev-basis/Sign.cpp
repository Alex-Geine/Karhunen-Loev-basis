//Signal.cpp - файл реализации Signal.h
#include "pch.h"
#include "Sign.h"
#include <fstream>


//Деструктор
Signal::~Signal() {
	X.~vector();
	
	keys.~vector();

}

//заполнение сигнала
void Signal::FillSignal(double n, double Fd, double A1, double A2, double A3,
	double G1, double G2, double G3, double niu1, double niu2, double niu3, double p,
	Drawer* GRU, Drawer* GRV, Drawer* GRSignal, Drawer* GRSigma) {
	this->N = n;
	this->fd = Fd;	
	this->A1 = A1;
	this->A2 = A2;
	this->A3 = A3;
	this->G1 = G1;
	this->G2 = G2;
	this->G3 = G3;
	this->niu1 = niu1;
	this->niu2 = niu2;
	this->niu3 = niu3;
	this->p = p;
	this->GRU = GRU;
	this->GRV = GRV;
	this->GRSignal = GRSignal;
	this->GRSigma = GRSigma;
		
	Create();
}

//отчистка сигнала
void Signal::ClearSignal() {
	X.clear();
	
	keys.clear();
}

//Создание сигнала
void Signal::Create() {
;

	for (int i = 0; i < N; i++) {
	
		keys.push_back(i / fd);
		X.push_back(
			A1 * sin(2 * Pi * G1 * (i / fd) + niu1) +
			A2 * sin(2 * Pi * G2 * (i / fd) + niu2) +
			A3 * sin(2 * Pi * G3 * (i / fd) + niu3)			
		);
	
	}


}

//Нахождение Автокорреляционной матрицы и СВД разложение
void Signal::FindAKM_SVD() {
	ofstream out("akp.txt");
	
	double** buf = new double*[p];
	buf[0] = new double[p];
	double R;

	for (int i = 0; i < p; i++) {
		R = 0;
		for (int k = 0; k < N - i; k++) 
			R += X[k] * X[k + i];
		buf[0][i] = R /N;
	}
	
	for (int i = 1; i < p; i++) {
		int m = i;
		bool flag = false;
		buf[i] = new double[p];

		for (int j = 0; j < p; j++) {			
			buf[i][j] = buf[0][m];
			
			if (i == j)
				flag = true;
			if (!flag)
				m--;
			else
				m++;
			
		}
		
	}
	
	for(int i = 0; i < p; i++){
		for (int j = 0; j < p; j++)
			out << buf[i][j] << " ";
		out << endl;
	}
	Matrix Buf(p, p, buf);
	AKM = &Buf;

	AKM->SVD(U, V, Singular);

	out.close();

}


//Отрисовывает сингулярные числа
void Signal::DrawSingular() {
	vector<double> 
		curSignal, 
		keys;

	for (int i = 0; i < p; i++) {
		keys.push_back(i);
		curSignal.push_back(Singular.getM()[i][i]);
	}

	GRSigma->DrawOnePoints(curSignal, *min_element(keys.begin(), keys.end()) , *max_element(keys.begin(), keys.end()) ,
		*min_element(curSignal.begin(), curSignal.end()), *max_element(curSignal.begin(), curSignal.end()), 't', 'A', keys);
	keys.~vector();
	curSignal.~vector();
}

//Отрисовывает вектор из базиса U
void Signal::DrawU(int id) {
	vector<double>
		curSignal,
		keys;
	for (int i = 0; i < p; i++) {
		keys.push_back(i);
		curSignal.push_back(U.getM()[i][id]);
	}
	GRU->DrawOne(curSignal, *min_element(keys.begin(), keys.end()), *max_element(keys.begin(), keys.end()),
		*min_element(curSignal.begin(), curSignal.end()), *max_element(curSignal.begin(), curSignal.end()), 't', 'A', keys);
	keys.~vector();
	curSignal.~vector();
}

//Отрисовывает вектор из базиса V
void Signal::DrawV(int id) {
	vector<double>
		curSignal,
		keys;
	for (int i = 0; i < p; i++) {
		keys.push_back(i);
		curSignal.push_back(V.getM()[i][id]);
	}
	GRV->DrawOne(curSignal, *min_element(keys.begin(), keys.end()), *max_element(keys.begin(), keys.end()),
		*min_element(curSignal.begin(), curSignal.end()), *max_element(curSignal.begin(), curSignal.end()), 't', 'A', keys);
	keys.~vector();
	curSignal.~vector();
}

//Отрисовывает сигнал
void Signal::DrawSign() {
	GRSignal->DrawOne(X, *min_element(keys.begin(), keys.end()), *max_element(keys.begin(), keys.end()),
		*min_element(X.begin(), X.end()), *max_element(X.begin(), X.end()), 't', 'A', keys);
}
