
// Karhunen-Loev-basisDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Karhunen-Loev-basis.h"
#include "Karhunen-Loev-basisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CKarhunenLoevbasisDlg



CKarhunenLoevbasisDlg::CKarhunenLoevbasisDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KARHUNENLOEVBASIS_DIALOG, pParent)
	, A1(1)
	, f1(2)
	, fi1(1)
	, A2(1)
	, f2(3)
	, fi2(4)
	, A3(1)
	, f3(4)
	, fi3(6)
	, N(1000)
	, fd(100)
	, p(100)
	, nU(1)
	, nV(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKarhunenLoevbasisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A1);
	DDX_Text(pDX, IDC_EDIT2, f1);
	DDX_Text(pDX, IDC_EDIT3, fi1);
	DDX_Text(pDX, IDC_EDIT4, A2);
	DDX_Text(pDX, IDC_EDIT5, f2);
	DDX_Text(pDX, IDC_EDIT6, fi2);
	DDX_Text(pDX, IDC_EDIT7, A3);
	DDX_Text(pDX, IDC_EDIT8, f3);
	DDX_Text(pDX, IDC_EDIT9, fi3);
	DDX_Text(pDX, IDC_EDIT10, N);
	DDX_Text(pDX, IDC_EDIT11, fd);
	DDX_Text(pDX, IDC_EDIT12, p);
	DDX_Text(pDX, IDC_EDIT13, nU);
	DDX_Text(pDX, IDC_EDIT14, nV);
}

BEGIN_MESSAGE_MAP(CKarhunenLoevbasisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CKarhunenLoevbasisDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CKarhunenLoevbasisDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CKarhunenLoevbasisDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDOK3, &CKarhunenLoevbasisDlg::OnBnClickedOk3)
END_MESSAGE_MAP()


// Обработчики сообщений CKarhunenLoevbasisDlg

BOOL CKarhunenLoevbasisDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	GR1.Create(GetDlgItem(IDC_GRAPH1)->GetSafeHwnd());
	GR2.Create(GetDlgItem(IDC_GRAPH2)->GetSafeHwnd());
	GR3.Create(GetDlgItem(IDC_GRAPH3)->GetSafeHwnd());
	GR4.Create(GetDlgItem(IDC_GRAPH4)->GetSafeHwnd());

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CKarhunenLoevbasisDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CKarhunenLoevbasisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CKarhunenLoevbasisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CKarhunenLoevbasisDlg::OnEnChangeEdit1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}

//Отрисовать
void CKarhunenLoevbasisDlg::OnBnClickedOk()
{
	UpdateData(true);

	curSignal.ClearSignal();
	curSignal.FillSignal(N, fd, A1, A2, A3, f1, f2, f3, fi1, fi2, fi3, p, &GR3, &GR2, &GR1, &GR4);

	//отрисовка сетки графиков
	GR1.DrawW();
	GR2.DrawW();
	GR3.DrawW();
	GR4.DrawW();

	curSignal.DrawSign();
	
}

//найти базис
void CKarhunenLoevbasisDlg::OnBnClickedOk2()
{
	curSignal.FindAKM_SVD();
	curSignal.DrawSingular();
}


void CKarhunenLoevbasisDlg::OnBnClickedOk3()
{
	UpdateData(true);
	curSignal.DrawU((int)nU);
	curSignal.DrawV((int)nV);
}
