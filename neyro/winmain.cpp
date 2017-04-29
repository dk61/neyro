#include "winmain.h"


neuron network;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	

	network.pic_dim = 6;
	network.pic_size = 26;
	network.num_methods = 9;
	network.size_a_neuron = 15;
	network.size_ae1_neuron = 15;
	network.size_ae2_neuron = 10;
	network.size_r_neuron = 5;
	network.malloc();
	char ** button_captions = new char*[3];
	for (int i = 0; i < 3; i++)
	{
		button_captions[i] = new char[100];
	}
	button_captions[0] = "Clear";
	button_captions[1] = "Learn";
	button_captions[2] = "Recognize";
	

	LPCTSTR CLASS_NAME = "Neurons";
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX); //размер непосредственно самого класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	/*стиль окна, эти два параметра отвечают за перекраску окна,
	также можнно вырубить кнопку закрыть с помощью CS_NOCLOSE, из полезных фич, ещЄ дабл клик CS_DBLCLKS, на этом всЄ*/
	wc.lpfnWndProc = WndProc; //функци€ окна
	wc.cbClsExtra = 0;	//количество экстра байт идущих после структуры, не знаю зачем
	wc.cbWndExtra = 0;	//количество байт, выдел€емых после состо€ни€ окна, не особо пон€тно зачем нужно
	wc.hInstance = hInstance;	//состо€ние окна
	wc.hIcon = NULL;	//ссылка на ресурс иконку приложени€
	wc.hCursor = NULL;	//ссылка на икону мышки
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;	//как закрашивать окно, в DX ставить NULL
	wc.lpszMenuName = NULL;	//≈сли будет менюшка то параметру нужно название и проча€ шн€га, но тут меню нет поэтому NULL
	wc.lpszClassName = CLASS_NAME; //Ќазвание класса, об€зательно
	wc.hIconSm = NULL;	//ћаленька€ иконка в верхнем левом углу, тоже ссылка

	RegisterClassEx(&wc); //регистраци€ класса, похоже непосредственно в самой системе винды

	RECT desktop_rect = {};
	RECT hWndRect = {};
	GetWindowRect(GetDesktopWindow(), &desktop_rect);
	int nWidth = 530;
	int nHeight = 500;
	int x = desktop_rect.right / 2 - nWidth / 2;
	int y = desktop_rect.bottom / 2 - nHeight / 2;
	
	HWND hWnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW, //—тиль окна дл€ EX
		CLASS_NAME, //им€ класса
		"Neuron",	//»м€ окна
		WS_OVERLAPPEDWINDOW,	//—тиль окна обычный, более настраеваемый
		x,	//Ћева€ точка
		y,	//¬ерхн€€ точка
		nWidth,	//ширина окна
		nHeight,	//высота окна
		NULL,	//указатель на родитель окно
		NULL,	//указатель на меню
		hInstance,	//указатель на состо€ние
		lpCmdLine	//указатель на параметры командной строки
		);
	if (hWnd == NULL)
	{
		return 0;
	}
	//создание пол€ дл€ ввода символов
	HWND hWndGroupBoxSymbol = CreateWindowEx(
		NULL,
		"BUTTON",
		"Symbol",
		BS_GROUPBOX | WS_CHILD | WS_GROUP | WS_VISIBLE,
		10,
		10,
		90,
		120,
		hWnd,
		NULL,
		hInstance,
		NULL
		);
	OldWndProcGroupBoxSymbol = (WNDPROC)GetWindowLongPtr(hWndGroupBoxSymbol, GWLP_WNDPROC);
	SetWindowLongPtr(hWndGroupBoxSymbol, GWLP_WNDPROC, (LONG)WndProcGroupBoxSymbol);
	HWND * hWndCheckBoxes = new HWND[network.pic_size - 1];
	network.compare_check_boxes(hWndCheckBoxes);
	int startx = 10, starty = 20;

	for (int i = 0; i < network.pic_size - 1; i++)
	{
		if (!(i % 5))
		{
			if (i != 0)
			{
				startx = 10;
				starty += 15;
			}
		}
		hWndCheckBoxes[i] = CreateWindowEx(
			NULL,
			"BUTTON",
			NULL,
			BS_AUTOCHECKBOX | BS_CHECKBOX | WS_TABSTOP | WS_GROUP | WS_CHILD | BS_MULTILINE | WS_VISIBLE,
			startx,
			starty,
			10,
			10,
			hWndGroupBoxSymbol,
			NULL,
			(HINSTANCE)GetWindowLong(hWndGroupBoxSymbol, GWL_HINSTANCE),
			NULL);
		startx += 15;
	}
	startx = 5;
	starty += 15;
	HWND hWndClearCheckButton = CreateWindowEx(
		NULL,
		"BUTTON",
		"Clear Field",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		startx,
		starty,
		80,
		20,
		hWndGroupBoxSymbol,
		(HMENU)BTN_CLEAR_FIELD,
		(HINSTANCE)GetWindowLong(hWndGroupBoxSymbol, GWL_HINSTANCE),
		NULL);
	//—оздание кнопок соранени€
	WINDOWINFO wi;
	GetWindowInfo(hWndGroupBoxSymbol, &wi);
	startx = wi.rcClient.right - wi.rcClient.left + 15 ;
	starty = 10;

	HWND hWndGroupBoxSave = CreateWindowEx(
		NULL,
		"BUTTON",
		"Save",
		BS_GROUPBOX | WS_CHILD | WS_GROUP | WS_VISIBLE,
		startx,
		starty,
		90,
		20 + 20 * 6 + 5 * 5 + 5,
		hWnd,
		NULL,
		hInstance,
		NULL);

	OldWndProcGroupBoxSave = (WNDPROC)GetWindowLongPtr(hWndGroupBoxSave, GWL_WNDPROC);
	SetWindowLongPtr(hWndGroupBoxSave, GWL_WNDPROC, (LONG)WndProcGroupBoxSave);

	HWND * hWndSaveButtons = new HWND[network.pic_dim];
	HMENU men = {};
	
	char letter[7] = "Save A";
	startx = 5;
	starty = 20;
	for (int i = 0; i < network.pic_dim; i++)
	{
		hWndSaveButtons[i] = CreateWindowEx(
			NULL,
			"BUTTON",
			letter,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			startx,
			starty,
			80,
			20,
			hWndGroupBoxSave,
			(HMENU)(i + 1),
			(HINSTANCE)GetWindowLong(hWndGroupBoxSave, GWL_HINSTANCE),
			NULL
			);
		letter[5]++;
		starty += 25;
	}
	letter[5] -= 6;
// создание кнопок отрисовки
	GetWindowInfo(hWndGroupBoxSymbol, &wi);
	startx = wi.rcClient.right - wi.rcClient.left;
	GetWindowInfo(hWndGroupBoxSave, &wi);
	startx += wi.rcClient.right - wi.rcClient.left + 20;
	starty = 10;
	HWND hWndGroupBoxShow = CreateWindowEx(
		NULL,
		"BUTTON",
		"Show",
		BS_GROUPBOX | WS_CHILD | WS_GROUP | WS_VISIBLE,
		startx,
		starty,
		90,
		wi.rcClient.bottom - wi.rcClient.top,
		hWnd,
		NULL,
		hInstance,
		NULL);

	OldWndProcGroupBoxShow = (WNDPROC)GetWindowLongPtr(hWndGroupBoxShow, GWL_WNDPROC);
	SetWindowLongPtr(hWndGroupBoxShow, GWL_WNDPROC, (LONG)WndProcGroupBoxShow);

	HWND * hWndShowButtons = new HWND[network.pic_dim];

	letter[1] = 'h';
	letter[2] = 'o';
	letter[3] = 'w';

	startx = 5;
	starty = 20;
	for (int i = 0; i < network.pic_dim; i++)
	{
		hWndShowButtons[i] = CreateWindowEx(
			NULL,
			"BUTTON",
			letter,
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			startx,
			starty,
			80,
			20,
			hWndGroupBoxShow,
			(HMENU)(i + 6 + 1),
			(HINSTANCE)GetWindowLongPtr(hWndGroupBoxShow, GWL_HINSTANCE),
			NULL);
		letter[5]++;
		starty += 25;
	}

	// создание радиогруппы с методами
	GetWindowInfo(hWndGroupBoxSymbol, &wi);
	startx = wi.rcClient.right - wi.rcClient.left;
	GetWindowInfo(hWndGroupBoxSave, &wi);
	startx += wi.rcClient.right - wi.rcClient.left;
	GetWindowInfo(hWndGroupBoxShow, &wi);
	startx += wi.rcClient.right - wi.rcClient.left + 25;
	starty = 10;

	HWND hWndGroupBoxMethod = CreateWindowEx(
		NULL,
		"BUTTON",
		"Methods",
		BS_GROUPBOX | WS_CHILD | WS_GROUP | WS_VISIBLE,
		startx,
		starty,
		210,
		network.num_methods * 25 + 20,
		hWnd,
		NULL,
		hInstance,
		NULL);
	
	OldWndProcGroupBoxMethod = (WNDPROC)GetWindowLongPtr(hWndGroupBoxMethod, GWL_WNDPROC);
	SetWindowLongPtr(hWndGroupBoxMethod, GWL_WNDPROC, (LONG)WndProcGroupBoxMethod);

	HWND * hWndMethodRadioButtons = new HWND[network.num_methods];

	startx = 5;
	starty = 20;

	for (int i = 0; i < network.num_methods; i++)
	{
		hWndMethodRadioButtons[i] = CreateWindowEx(
			NULL,
			"BUTTON",
			network.methods[i],
			BS_AUTORADIOBUTTON | WS_CHILD | WS_TABSTOP | WS_VISIBLE,
			startx,
			starty,
			200,
			20,
			hWndGroupBoxMethod,
			NULL,
			(HINSTANCE)GetWindowLongPtr(hWndGroupBoxMethod, GWL_HINSTANCE),
			NULL);
		starty += 25;
	}
	network.compare_radio_buttons(hWndMethodRadioButtons);


	GetWindowInfo(hWndGroupBoxSymbol, &wi);
	startx = 10;
	starty = wi.rcClient.bottom - wi.rcClient.top + 15;
	HWND hWndGroupBoxManipulation = CreateWindowEx(
		NULL,
		"BUTTON",
		"Control",
		BS_GROUPBOX | WS_CHILD | WS_GROUP | WS_VISIBLE,
		startx,
		starty,
		90,
		25 * 3 + 20,
		hWnd,
		NULL,
		hInstance,
		NULL);
	OldWndProcGroupBoxManipulation = (WNDPROC)GetWindowLongPtr(hWndGroupBoxManipulation, GWL_WNDPROC);
	SetWindowLongPtr(hWndGroupBoxManipulation, GWL_WNDPROC, (LONG)WndProcGroupBoxManipulation);
	HWND * hWndManipulationButtons = new HWND[3];
	startx = 5;
	starty = 20;
	for (int i = 0; i < 3; i++)
	{
		hWndManipulationButtons[i] = CreateWindowEx(
			NULL,
			"BUTTON",
			button_captions[i],
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON ,
			startx,
			starty,
			80,
			20,
			hWndGroupBoxManipulation,
			(HMENU)(i + 200),
			(HINSTANCE)GetWindowLongPtr(hWndGroupBoxManipulation, GWL_HINSTANCE),
			NULL);
		starty += 25;
	}
	GetWindowInfo(hWndGroupBoxSymbol, &wi);
	startx = wi.rcClient.right - wi.rcClient.left;
	GetWindowInfo(hWndGroupBoxSave, &wi);
	startx += wi.rcClient.right - wi.rcClient.left;
	GetWindowInfo(hWndGroupBoxShow, &wi);
	startx += wi.rcClient.right - wi.rcClient.left + 25;
	GetWindowInfo(hWndGroupBoxMethod, &wi);
	starty =  wi.rcClient.bottom - wi.rcClient.top + 15;
	HWND hWndGroupBoxResult = CreateWindowEx(
		NULL,
		"BUTTON",
		"Result",
		BS_GROUPBOX | WS_CHILD | WS_GROUP | WS_VISIBLE,
		startx,
		starty,
		40 + 100 + 15,
		(network.pic_dim -1) * 25 + 20 ,
		hWnd,
		NULL,
		hInstance,
		NULL);

	HWND * hWndCheckBoxesResult = new HWND[network.pic_dim - 1];
	HWND * hWndLabelResult = new HWND[network.pic_dim - 1];
	char let[2] = "A";
	startx = 5;
	starty = 20;
	for (int i = 0; i < network.pic_dim - 1; i++)
	{
		hWndCheckBoxesResult[i] = CreateWindowEx(
			NULL,
			"BUTTON",
			let,
			BS_CHECKBOX | WS_TABSTOP | WS_GROUP | WS_CHILD | BS_MULTILINE | WS_VISIBLE | WS_DISABLED,
			startx,
			starty,
			40,
			20,
			hWndGroupBoxResult,
			NULL,
			(HINSTANCE)GetWindowLongPtr(hWndGroupBoxResult, GWLP_HINSTANCE),
			NULL);
		startx += 45;
		hWndLabelResult[i] = CreateWindowEx(
			NULL,
			"STATIC",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			startx,
			starty,
			100,
			20,
			hWndGroupBoxResult,
			NULL,
			(HINSTANCE)GetWindowLongPtr(hWndGroupBoxResult, GWLP_HINSTANCE),
			NULL);
		let[0]++;
		starty += 25;
		startx -= 45;
	}
	network.compare_check_boxes_result(hWndCheckBoxesResult);
	network.compare_label_result(hWndLabelResult);


	ShowWindow(hWnd, nCmdShow);
	

	MSG uMsg = {};
	while (GetMessage(&uMsg, NULL, 0, 0))
	{
		TranslateMessage(&uMsg);
		DispatchMessage(&uMsg);
	}
	delete[] hWndCheckBoxes;
	delete[] hWndSaveButtons;
	delete[] hWndShowButtons;
	network.free();
	return 0;
}

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
	)
{
	switch (uMsg)
	{
		case WM_COMMAND:
		{	
			switch (LOWORD(wParam))
			{

			case BTN_CLEAR_FIELD:
			{
				network.clear_pic();
				return 0;
			}
			case BTN_SAVE_A:
			{
				network.remember(A);
				return 0;
			}
			case BTN_SAVE_B:
			{
				network.remember(B);
				return 0;
			}
			case BTN_SAVE_C:
			{
				network.remember(C);
				return 0;
			}
			case BTN_SAVE_D:
			{
				network.remember(D);
				return 0;
			}
			case BTN_SAVE_E:
			{
				network.remember(E);
				return 0;
			}
			case BTN_SAVE_F:
			{
				network.remember(F);
				return 0;
			}
			case BTN_SHOW_A:
			{
				network.show_pic(A);
				return 0;
			}
			case BTN_SHOW_B:
			{
				network.show_pic(B);
				return 0;
			}
			case BTN_SHOW_C:
			{
				network.show_pic(C);
				return 0;
			}
			case BTN_SHOW_D:
			{
				network.show_pic(D);
				return 0;
			}
			case BTN_SHOW_E:
			{
				network.show_pic(E);
				return 0;
			}
			case BTN_SHOW_F:
			{
				network.show_pic(F);
				return 0;
			}
			case BTN_CLEAR:
			{
				network.clear();
				return 0;
			}
			case BTN_LEARN:
			{
				if (network.learn() == 1)
					MessageBox(hWnd, "You don't choose method", "Error", MB_OK);
				else
					MessageBox(hWnd, "Learn complete", "Congratulations", MB_OK);
				return 0;
			}
			case BTN_RECOGNIZE:
			{
				network.recognize();
				return 0;
			}
			return 0;
			}
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			OnSize(hWnd, (UINT)wParam, width, height);
			return 0;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOWFRAME));
			EndPaint(hWnd, &ps);
			return 0;
		}
		case WM_CLOSE:
		{
			if (MessageBox(hWnd, "Quit?", "Neyron", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hWnd);
			}
			return 0;
		}
		case WM_QUIT:
		{
			ExitProcess(wParam);
			return 0;
		}
		case WM_CREATE:
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		
	}
	
	return 0;
}

LRESULT CALLBACK WndProcGroupBoxSymbol(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		CallWindowProc(WndProc, GetParent(hWnd), uMsg, wParam, lParam);
		return 0;
	}
	return CallWindowProc(OldWndProcGroupBoxSymbol, hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcGroupBoxSave(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		CallWindowProc(WndProc, GetParent(hWnd), uMsg, wParam, lParam);
		return 0;
	}
	return CallWindowProc(OldWndProcGroupBoxSave, hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcGroupBoxShow(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	
	switch (uMsg)
	{

	case WM_COMMAND:
		CallWindowProc(WndProc, GetParent(hWnd), uMsg, wParam, lParam);
		return 0;
	}
	return CallWindowProc(OldWndProcGroupBoxShow, hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcGroupBoxMethod(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		CallWindowProc(WndProc, GetParent(hWnd), uMsg, wParam, lParam);
		return 0;
	}
	return CallWindowProc(OldWndProcGroupBoxMethod, hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcGroupBoxManipulation(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		CallWindowProc(WndProc, GetParent(hWnd), uMsg, wParam, lParam);
		return 0;
	}
	return CallWindowProc(OldWndProcGroupBoxManipulation, hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcGroupBoxResult(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		CallWindowProc(WndProc, GetParent(hWnd), uMsg, wParam, lParam);
		return 0;
	}
	return CallWindowProc(OldWndProcGroupBoxResult, hWnd, uMsg, wParam, lParam);
}

void OnSize(
	HWND hWnd,
	UINT flag,
	int width,
	int height)
{
	if (flag == 0)
	{
		
		RECT wnd_rect = {};
		GetWindowRect(hWnd, &wnd_rect);
		MoveWindow(
			hWnd,
			wnd_rect.left,
			wnd_rect.top,
			width + 20,
			height + 43,
			true
			);
	}
}