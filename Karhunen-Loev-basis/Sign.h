#pragma once
#include <vector>
#include <time.h>
#include <algorithm>
#include "Drawer.h"
#include "Matrix.h"
#define Pi 3.1415926535
using namespace std;

class Signal {
public:
	vector<double>
		X,			
		keys;

	Matrix 
		*AKM,
		U,
		V,
		Singular;

	Drawer
		* GRU,
		* GRV,
		* GRSigma,
		* GRSignal;
	
	double
		N,
		fd,		
		A1,
		A2,
		A3,
		G1,
		G2,
		G3,
		niu1,
		niu2,
		niu3,
		p;
private:

	
	
public:
	//Деструктор
	~Signal();

	//заполнение сигнала
	void FillSignal(double n, double Fd,  double A1, double A2, double A3,
		double G1, double G2, double G3, double niu1, double niu2, double niu3, double p,
		Drawer* GRU, Drawer* GRV, Drawer* GRSignal, Drawer* GRSigma);

	//отчистка сигнала
	void ClearSignal();	

	//Создание сигнала
	void Create();

	//Нахождение Автокорреляционной матрицы и СВД
	void FindAKM_SVD();

	//Отрисовывает сигнал
	void DrawSign();

	//Отрисовывает сингулярные числа
	void DrawSingular();

	//Отрисовывает вектор из базиса U
	void DrawU(int id);

	//Отрисовывает вектор из базиса V
	void DrawV(int id);
};
