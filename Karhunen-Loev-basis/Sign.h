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
	//����������
	~Signal();

	//���������� �������
	void FillSignal(double n, double Fd,  double A1, double A2, double A3,
		double G1, double G2, double G3, double niu1, double niu2, double niu3, double p,
		Drawer* GRU, Drawer* GRV, Drawer* GRSignal, Drawer* GRSigma);

	//�������� �������
	void ClearSignal();	

	//�������� �������
	void Create();

	//���������� ������������������ ������� � ���
	void FindAKM_SVD();

	//������������ ������
	void DrawSign();

	//������������ ����������� �����
	void DrawSingular();

	//������������ ������ �� ������ U
	void DrawU(int id);

	//������������ ������ �� ������ V
	void DrawV(int id);
};
