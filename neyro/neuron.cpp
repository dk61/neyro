#include "neuron.h"



int neuron::clear()
{
	//полный сброс всех значений, всех X и всех W
	for (int i = 0; i < pic_dim; i++)
	{
		for (int j = 0; j < pic_size; j++)
		{
			x[i][j] = false;
		}
		x[i][0] = true;
	}
	int arr_dim[5] = { 13, 12, 12, 14, 12 };
	int arr[64] = { 1, 5, 6, 9, 10, 11, 13, 15, 16, 17, 20, 21, 25,
		3, 4, 5, 7, 10, 12, 15, 17, 20, 21, 22, 25,
		1, 6, 11, 12, 13, 14, 16, 20, 21, 22, 23, 24,
		2, 3, 4, 5, 6, 10, 12, 13, 14, 15, 17, 20, 21, 25,
		3, 7, 9, 12, 14, 16, 17, 18, 19, 20, 21, 25 };
	for (int i = 0; i < 64; i++)
	{
		if (i < 13)
		{
			x[0][arr[i]] = true;
		}
		if (i >= 13 && i < 13 + 12)
		{
			x[1][arr[i]] = true;
		}
		if (i >= 13 + 12 && i < 13 + 12 + 12)
		{
			x[2][arr[i]] = true;
		}
		if (i >= 13 + 12 + 12 && i < 13 + 12 + 12 + 14)
		{
			x[3][arr[i]] = true;
		}
		if (i >= 13 + 12 + 12 + 14 && i < 13 + 12 + 12 + 12 + 14)
		{
			x[4][arr[i]] = true;
		}
	}
	clear_w();
	return 0;
}

int neuron::clear_pic()
{
	//сброс значений на картинке
	for (int i = 0; i < pic_size - 1; i++)
	{
		SendMessage(hWndCheckBoxes[i], BM_SETCHECK, BST_UNCHECKED, 0);
	}
	return 0;
}

int neuron::remember(int num)
{
	//запись значений из чекбоксов в массив X
	num--;
	for (int i = 1; i < pic_size; i++)
	{
		LRESULT chkState = SendMessage(hWndCheckBoxes[i - 1], BM_GETCHECK, 0, 0);
		if (chkState == BST_CHECKED)
			x[num][i] = true;
		else
			x[num][i] = false;
	}
	return 0;
}

int neuron::malloc()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	//выделение памяти под массивы
	x = new bool*[pic_dim];
	for (int i = 0; i < pic_dim; i++)
	{
		x[i] = new bool[pic_size];
		for (int j = 0; j < pic_size; j++)
		{
			x[i][j] = false;
		}
	}
	

	w = new double*[pic_dim - 1];
	for (int i = 0; i < pic_dim - 1; i++)
	{
		w[i] = new double[pic_size];
	}
	fi_a = new double[size_a_neuron];
	fi_ae1 = new double[size_ae1_neuron];
	fi_ae2 = new double[size_ae2_neuron];
	fi_r = new double*[size_r_neuron];
	for (int i = 0; i < size_r_neuron; i++)
	{
		fi_r[i] = new double[2];
	}
	fi = new double*[pic_dim - 1];
	for (int i = 0; i < pic_dim - 1; i++)
		fi[i] = new double[4];
	clear();
	methods = new char*[num_methods];
	degree_of_similarity = new char*[5];

	methods[0] = "Hebbs method bipolar";
	methods[1] = "Hebbs method binary";
	methods[2] = "K-binary activation";
	methods[3] = "K-bipolar activation";
	methods[4] = "Delta rule";
	methods[5] = "Perceptron";
	methods[6] = "Back error";
	methods[7] = "Hemming";
	methods[8] = "Kohonin";

	degree_of_similarity[0] = "nothing like";
	degree_of_similarity[1] = "does not like";
	degree_of_similarity[2] = "neutral";
	degree_of_similarity[3] = "a bit like";
	degree_of_similarity[4] = "looks like";

	w_a = new double*[size_a_neuron]; //A нейронов на каждое изображение будет по 3
	w_r = new double*[size_r_neuron];
	w_ae1 = new double*[size_ae1_neuron];
	w_ae2 = new double*[size_ae2_neuron];
	w_re = new double*[size_r_neuron];
	for (int i = 0; i < size_a_neuron; i++)
	{
		w_a[i] = new double[pic_size - 1];
	}

	for (int i = 0; i < size_ae1_neuron; i++)
	{
		w_ae1[i] = new double[pic_size];
	}
	
	for (int i = 0; i < size_ae2_neuron; i++)
	{
		w_ae2[i] = new double[size_ae1_neuron];
	}

	for (int i = 0; i < size_r_neuron; i++)
	{
		w_re[i] = new double[size_ae2_neuron];
	}

	for (int i = 0; i < size_r_neuron; i++)
	{
		w_r[i] = new double[size_a_neuron];
	}

	w_z = new double*[pic_dim - 1];
	for (int i = 0; i < pic_dim - 1; i++)
	{
		w_z[i] = new double[pic_size];
	}
	b_z = new double[pic_dim - 1];
	w_k = new double*[3];
	for (int i = 0; i < 3; i++)
	{
		w_k[i] = new double[pic_size - 1];
	}
	return 0;
}

int neuron::compare_check_boxes(HWND * hWnd)
{
	hWndCheckBoxes = hWnd;
	return 0;
}

int neuron::compare_radio_buttons(HWND * hWnd)
{
	hWndMethodRadioButtons = hWnd;
	return 0;
}

int neuron::compare_check_boxes_result(HWND * hWnd)
{
	hWndCheckBoxesResult = hWnd;
	return 0;
}

int neuron::compare_label_result(HWND * hWnd)
{
	hWndLabelResult = hWnd;
	return 0;
}

int neuron::free()
{
	//освобождение памяти
	for (int i = 0; i < pic_dim; i++)
		delete[] x[i];
	delete[] x;
	delete[] w;
	delete[] b_z;
	for (int i = 0; i < pic_dim - 1; i++)
	{
		delete[] fi[i];
	}
	for (int i = 0; i < size_a_neuron; i++)
	{
		delete[] w_a[i];
	}
	for (int i = 0; i < size_r_neuron; i++)
	{
		delete[] w_r[i];
		delete[] w_re[i];
	}
	delete[] w_re;
	delete[] w_a;
	delete[] w_r;
	delete[] fi_a;
	for (int i = 0; i < size_r_neuron; i++)
	{
		delete[] fi_r[i];
	}
	for (int i = 0; i < size_ae1_neuron; i++)
	{
		delete[] w_ae1[i];
	}
	for (int i = 0; i < size_ae2_neuron; i++)
	{
		delete[] w_ae2[i];
	}
	for (int i = 0; i < pic_dim - 1; i++)
	{
		delete[] w_z[i];
	}
	delete[] w_z;
	for (int i = 0; i < 3; i++)
	{
		delete[] w_k[i];
	}
	delete[] w_k;
	delete[] w_ae1;
	delete[] w_ae2;
	delete[] fi_r;
	delete[] fi;
	delete[] degree_of_similarity;
	delete[] methods;
	FreeConsole();
	return 0;
}

int neuron::show_pic(int num)
{
	//отправка сообщений для отображения на чекбоксах
	num--;
	for (int i = 1; i < pic_size; i++)
	{
		if (x[num][i] == true)
		{
			SendMessage(hWndCheckBoxes[i - 1], BM_SETCHECK, BST_CHECKED, 0);
		}
		else
			SendMessage(hWndCheckBoxes[i - 1], BM_SETCHECK, BST_UNCHECKED, 0);
	}
	return 0;
}

int neuron::learn()
{
	//находим выбранный метод
	choose_method = -1;
	for (int i = 0; i < num_methods; i++)
	{
		LRESULT chkState = SendMessage(hWndMethodRadioButtons[i], BM_GETCHECK, 0, 0);
		if (chkState == BST_CHECKED)
		{
			choose_method = i;
			break;
		}
	}
	if (choose_method == -1)
	{
		return 1;
	}
	//есои нашли выбранный метод, то запускаем функцию обучения
	switch (choose_method)
	{
	case METHOD_HEBBA_BIPOLAR:
		method_hebba_bipolar();
		return 0;
	case METHOD_HEBBA_BINARY:
		method_hebba_binary();
		return 0;
	case METHOD_HEBBA_K_BINARY_ACTIVATION:
		method_hebba_k_binary_activation();
		return 0;
	case METHOD_HEBBA_K_BIPOLAR_ACTIVATION:
		method_hebba_k_bipolar_activation();
		return 0;
	case METHOD_DELTA_RULE:
		method_delta_rule();
		return 0;
	case METHOD_PERCEPTRON:
		method_perceptron();
		return 0;
	case METHOD_BACK_ERROR:
		method_back_error();
		return 0;
	case METHOD_HEMMING:
		method_hemming();
		return 0;
	case METHOD_KOHONIN:
		method_kohonin();
		return 0;
		
	}
	return 0;
}

int neuron::method_hebba_bipolar()
{
	clear_w();
	int tmpx;
	int tmpk;
	for (int i = 0; i < pic_dim - 1; i++)
	{
		for (int k = i; k < pic_dim - 1 + i; k++)
		{
			bool flag;
			if (k == i)
				continue;
			do
			{
				tmpk = k % (pic_dim - 1);
				flag = true;
				//y для картинки правильной 4 шаг
				y = 1;
				//5 шаг
				for (int j = 0; j < pic_size; j++)
				{
					if (x[i][j] == true)
						tmpx = 1;
					else
						tmpx = -1;
					w[i][j] += tmpx * y;
				}
				//шаг 4
				y = -1;
				//5 шаг для второго изображения в паре
				for (int j = 0; j < pic_size; j++)
				{
					if (x[tmpk][j] == true)
						tmpx = 1;
					else
						tmpx = -1;
					w[i][j] += tmpx * y;
				}
				S = w[i][0];
				for (int j = 1; j < pic_size; j++)
				{
					if (x[i][j] == true)
						tmpx = 1;
					else
						tmpx = -1;
					S += w[i][j] * tmpx;
				}
				//шаг 6 проверка условий останова для пары
				if (S <= 0)
					flag = false;
				S = w[i][0];
				for (int j = 1; j < pic_size; j++)
				{
					if (x[tmpk][j] == true)
						tmpx = 1;
					else
						tmpx = -1;
					S += w[i][j] * tmpx;
				}
				if (S > 0)
					flag = false;
			} while (!flag);
		}
	}
	return 0;
}


int neuron::method_hebba_binary()
{
	clear_w();
	int tmpx;
	int tmpk;
	int delta_w;
	for (int i = 0; i < pic_dim - 1; i++)
	{

		for (int k = i; k < pic_dim - 1 + i; k++)
		{
			bool flag;
			if (k == i)
				continue;
			do
			{
				tmpk = k % (pic_dim - 1);
				flag = true;
				//шаг 4 для определяемого изображения
				y = 1;
				//шаг 5 корректировка с delta w
				for (int j = 0; j < pic_size; j++)
				{
					if (x[i][j] == true)
						tmpx = 1;
					else
						tmpx = 0;
					if (tmpx == 1 && y == 1)
						delta_w = 1;
					else
						if (tmpx == 0)
							delta_w = 0;
						else
							if (tmpx != 0 && y == 0)
								delta_w = -1;
					w[i][j] += delta_w;
				}
				y = 0;
				for (int j = 0; j < pic_size; j++)
				{
					if (x[tmpk][j] == true)
						tmpx = 1;
					else
						tmpx = 0;
					if (tmpx == 1 && y == 1)
						delta_w = 1;
					else
						if (tmpx == 0)
							delta_w = 0;
						else
							if (tmpx != 0 && y == 0)
								delta_w = -1;
					w[i][j] += delta_w;
				}
				//шаг 6 проверка условий останова сначала при y = 1, потом для y = -1
				S = w[i][0];
				for (int j = 1; j < pic_size; j++)
				{
					if (x[i][j] == true)
						tmpx = 1;
					else
						tmpx = 0;
					S += tmpx * w[i][j];
				}
				if (S <= 0)
					flag = false;
				S = w[i][0];
				for (int j = 1; j < pic_size; j++)
				{
					if (x[tmpk][j] == true)
						tmpx = 1;
					else
						tmpx = 0;
					S += tmpx * w[i][j];
				}
				if (S > 0)
					flag = false;
			} while (!flag);
		}

	}
	return 0;
}

int neuron::method_hebba_k_binary_activation()
{
	//обучение нейронов по хеббу бинарному
	method_hebba_binary();
	//вычисление всех S для всех эталонов на каждом нейроне
	int tmpx;
	int **tmpS = new int*[pic_dim - 1];
	for (int n = 0; n < pic_dim - 1; n++)//n это счётчик нейрона
	{
		tmpS[n] = new int[pic_dim - 1];
		for (int i = 0; i < pic_dim - 1; i++)
		{
			tmpS[n][i] = w[n][0];
			for (int j = 1; j < pic_size; j++)
			{
				if (x[i][j] == true)
					tmpx = 1;
				else
					tmpx = 0;
				tmpS[n][i] += tmpx * w[n][j];
			}
		}
		//сортировка результатов
		bubble_sort(tmpS[n], pic_dim - 1);
	}
	//поиск fi
	for (int n = 0; n < pic_dim - 1; n++)
	{
		int fi_step = (tmpS[n][pic_dim - 2] - tmpS[n][pic_dim - 3]) / 5;
		fi[n][3] = tmpS[n][pic_dim - 2];
		for (int i = 2; i >= 0; i--)
		{
			fi[n][i] = fi[n][i + 1] - fi_step;
		}
	}
	return 0;
}

int neuron::method_hebba_k_bipolar_activation()
{
	method_hebba_bipolar();
	method_hebba_binary();
	//вычисление всех S для всех эталонов на каждом нейроне
	int tmpx;
	int **tmpS = new int*[pic_dim - 1];
	for (int n = 0; n < pic_dim - 1; n++)//n это счётчик нейрона
	{
		tmpS[n] = new int[pic_dim - 1];
		for (int i = 0; i < pic_dim - 1; i++)
		{
			tmpS[n][i] = w[n][0];
			for (int j = 1; j < pic_size; j++)
			{
				if (x[i][j] == true)
					tmpx = 1;
				else
					tmpx = -1;
				tmpS[n][i] += tmpx * w[n][j];
			}
		}
		//сортировка результатов
		bubble_sort(tmpS[n], pic_dim - 1);
	}
	//поиск fi
	for (int n = 0; n < pic_dim - 1; n++)
	{
		int fi_step = (tmpS[n][pic_dim - 2] - tmpS[n][pic_dim - 3]) / 5;
		fi[n][3] = tmpS[n][pic_dim - 2];
		for (int i = 2; i >= 0; i--)
		{
			fi[n][i] = fi[n][i + 1] - fi_step;
		}
	}
	return 0;
}

int neuron::method_delta_rule()
{
	//создаём w предыдущей итерации
	double **w_old;
	w_old = new double*[pic_dim - 1];
	for (int i = 0; i < pic_dim - 1; i++)
	{
		w_old[i] = new double[pic_size];
	}
	//шаг первый
	srand(time(NULL));
	for (int i = 0; i < pic_dim - 1; i++)
	{
		for (int j = 0; j < pic_size; j++)
		{
			w[i][j] = ((rand() + rand() + rand() + rand()) % 100001 - 50000) / 100000.0;//генерируется число около 120к потом находим процент от 100к т.е. от 0 до 100к, после сдвигаем на 50 к и потом сдвигаем до 0 с запятой
		}
	}
	alpha = 0.1 / pic_size;
	epsilon = 0.00001;
	double E_check;
	int iter = 0;
	//шаг третий для каждой обучающей пары выполняются шаги 4-6
	do
	{
		//записываем данные до преобразований
		for (int i = 0; i < pic_dim - 1; i++)
		{
			for (int j = 0; j < pic_size; j++)
			{
				w_old[i][j] = w[i][j];
			}
		}

		for (int i = 0; i < pic_dim - 1; i++) //цикл считающий номер X
		{
			for (int j = 0; j < pic_dim - 1; j++) //цикл считающий номер нейрона
			{
				if (i == j)
					u_exit = 1;
				else
					u_exit = -1;
				//5 шаг расчёт входа
				u_entrance = w[i][0];
				for (int k = 1; k < pic_size; k++) //цикл для вычисления входного сигнала
				{
					int tmpx;
					if (x[j][k])
						tmpx = 1;
					else
						tmpx = 0;
					u_entrance += w[i][k] * tmpx;
				}
				//расчёт новых весов связей
				w[i][0] += alpha * (u_exit - u_entrance);
				for (int k = 1; k < pic_size; k++)
				{
					int tmpx;
					if (x[j][k])
						tmpx = 1;
					else
						tmpx = 0;
					w[i][k] += alpha * (u_exit - u_entrance) * tmpx;
				}
			}
		}
		//проверка условия останова
		E_check = 0;
		for (int i = 0; i < pic_dim - 1; i++)
		{
			for (int j = 0; j < pic_size; j++)
			{
				E_check += abs(w_old[i][j] - w[i][j]);
			}
		}
		iter++;
	} while (E_check > epsilon);
	for (int i = 0; i < pic_dim - 1; i++)
	{
		delete[] w_old[i];
	}
	delete[] w_old;
	char *msg = new char[100];
	_itoa(iter, msg, 10);
	MessageBox(NULL, msg, "Iterations", MB_OK);
	delete[] msg;
	return 0;
}

int neuron::method_perceptron()
{
	int iter = 0;
	bool right_work = false;
	double **Nak = new double*[pic_dim - 1];
	double **Nagr = new double*[pic_dim - 1];
	for (int i = 0; i < pic_dim - 1; i++)
	{
		Nak[i] = new double[2];
		Nagr[i] = new double[2];
	}
	srand(time(NULL));
	
	while (!right_work)
	{
		right_work = true;
		//инициализация рандома и генерация 0..1 чисел для нейронов w[i][j]
		if (iter == 0)
		{
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
				{
					w_r[r_neuron][a_neuron] = (rand() % 99 + 1) / 100.0;//генерируем веса для R нейронов генерация верная
				}
			}
			for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
			{
				double max_entrance = 0.0, min_entrance = 30.0;
				for (int pixel = 0; pixel < pic_size - 1; pixel++)
				{
					w_a[a_neuron][pixel] = (rand() % 99 + 1) / 100.0;//генерируем веса между X и A, полностью рандомные связи генерация верная

				}
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					u_entrance = 0;
					double tmpx;
					for (int pixel = 0; pixel < pic_size - 1; pixel++)
					{
						if (x[pic][pixel + 1])
							tmpx = 1.0;
						else
							tmpx = 0.0;
						u_entrance += w_a[a_neuron][pixel] * tmpx;
					}
					if (u_entrance > max_entrance)
						max_entrance = u_entrance;
					if (u_entrance < min_entrance)
						min_entrance = u_entrance;
				}
					
				fi_a[a_neuron] = (max_entrance + min_entrance) / 2.0;//выставляем пороги для A
				
			}
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				double max_entrance = 0.0, min_entrance = 30.0;
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					u_entrance = 0;
					double u_entrance_a;
					for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
					{
						double tmpx;
						u_entrance_a = 0;
						for (int pixel = 0; pixel < pic_size - 1; pixel++)
						{
							if (x[pic][pixel + 1])
								tmpx = 1.0;
							else
								tmpx = 0.0;
							u_entrance_a += w_a[a_neuron][pixel] * tmpx;
						}
						if (u_entrance_a >= fi_a[a_neuron])
							u_exit = 1;
						else
							u_exit = 0;
						u_entrance += u_exit * w_r[r_neuron][a_neuron];
					}
					if (u_entrance > max_entrance)
						max_entrance = u_entrance;
					if (u_entrance < min_entrance)
						min_entrance = u_entrance;
				}
				fi_r[r_neuron][0] = (max_entrance + min_entrance) / 2.0;//Выставляем пороги для R
				//std::cout << "fi_r[" << r_neuron << "] = " << fi_r[r_neuron][0] << std::endl;
			}
			std::cout << "generation w is complete" << std::endl;
		}

		for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
		{
			double delta_w;
			double n;
			bool res[5] = { 1, 1, 1, 1, 1 };
			for (int pic = 0; pic < pic_dim - 1; pic++)
			{
				double u_entrance_a;
				double N = size_a_neuron;
				double Ngr = 0;
				Nak[r_neuron][0] = 0;
				Nak[r_neuron][1] = 0;
				Nagr[r_neuron][0] = 0;
				Nagr[r_neuron][1] = 0;
				u_entrance = 0;
				//вычисляем выходы для A для каждой картинки и нейрону R
				for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
				{
					double tmpx;
					u_entrance_a = 0;
					for (int pixel = 0; pixel < pic_size - 1; pixel++)
					{
						if (x[pic][pixel + 1])
							tmpx = 1.0;
						else
							tmpx = 0.0;
						u_entrance_a += w_a[a_neuron][pixel] * tmpx;
					}
					if (u_entrance_a >= fi_a[a_neuron])
					{
						u_exit = 1;
						Nak[r_neuron][1]++;
						if (w_r[r_neuron][a_neuron] == 1 || w_r[r_neuron][a_neuron] == 0)
						{
							if (w_r[r_neuron][a_neuron] == 1)
								Nagr[r_neuron][1]++;
							else
								Nagr[r_neuron][0]++;
							Ngr++;
						}
					}
					else
					{
						u_exit = 0;
						Nak[r_neuron][0]++;
					}
					//std::cout << "r neuron = " << r_neuron << " nagr 1 = " << Nagr[r_neuron][1] << " nagr 0 = " << Nagr[r_neuron][0] << std::endl;
					//if (r_neuron == 0)
						//std::cout << w_r[r_neuron][a_neuron] << std::endl;
					u_entrance += u_exit * w_r[r_neuron][a_neuron]; //вычисляем вход нейрона R
				}
				//if (iter == 0 || iter == 100 || iter == 1000 || iter == 4999)
					//std::cout << "u_entrance[" << r_neuron << "][" << pic << "]= " << u_entrance << " iter = " << iter << std::endl;
				
				if (u_entrance >= fi_r[r_neuron][0])
					u_exit = 1.0;
				else
					u_exit = -1.0;
				double u_exit_r;
				if (r_neuron == pic)
					u_exit_r = 1.0;
				else
					u_exit_r = -1.0;
				if (r_neuron == pic)
				{
					if (u_exit != u_exit_r)
						right_work = false;
				}
				if (u_exit == u_exit_r)
				{
					res[pic] = true;
				}
				if (u_exit != u_exit_r)
				{
					
					res[pic] = false;
				}
				n = fun(u_exit_r, u_exit);
				N = size_a_neuron;
				
				double tmpn = 0.0;
				double delta_tmp;
				for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
				{
					tmpn = 0.0;
					double tmpx;
					u_entrance_a = 0;
					for (int pixel = 0; pixel < pic_size - 1; pixel++)
					{
						if (x[pic][pixel + 1])
							tmpx = 1.0;
						else
							tmpx = 0.0;
						u_entrance_a += w_a[a_neuron][pixel] * tmpx;
					}
					if (u_entrance_a >= fi_a[a_neuron])
						u_exit = 1;
					else
						u_exit = 0;
					if (u_exit == 1)
						delta_w = n - (Nak[r_neuron][1] - Nagr[r_neuron][1]) * n / (N - Ngr);
					else
						delta_w = -(Nak[r_neuron][1] - Nagr[r_neuron][1]) * n / (N - Ngr);
					if (w_r[r_neuron][a_neuron] + delta_w > 1 || w_r[r_neuron][a_neuron] + delta_w < 0)
					{
						delta_tmp = delta_w - abs(1 - w_r[r_neuron][a_neuron]);
						if (w_r[r_neuron][a_neuron] - delta_w > 1)
							tmpn += delta_tmp / (N - 1 - Ngr);
						else
							tmpn -= delta_tmp / (N - 1 - Ngr);
						if (w_r[r_neuron][a_neuron] + delta_w > 1)
							w_r[r_neuron][a_neuron] = 1.0;
						if (w_r[r_neuron][a_neuron] + delta_w < 0)
							w_r[r_neuron][a_neuron] = 0.0;
					}
					else
					{
						if (w_r[r_neuron][a_neuron] < 1 && w_r[r_neuron][a_neuron] > 0)
						{
							if (r_neuron == pic)
								w_r[r_neuron][a_neuron] += delta_w;
							else
								w_r[r_neuron][a_neuron] -= delta_w;
						}
					}


					
				}
				if (tmpn != 0)
				{
					for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
					{
						if (w_r[r_neuron][a_neuron] > 0 && w_r[r_neuron][a_neuron] < 1)
							w_r[r_neuron][a_neuron] += tmpn;
					}
				}
			}
			/*bool flag = true;
			for (int pic = 0; pic < pic_dim - 1; pic++)
			{
				if (!res[pic])
					flag = false;
			}
			if (flag)
			{
				std::cout << "r_neuron = " << r_neuron << " succesful" << std::endl;
			}*/
		}
		iter++;
		if (iter == 5000 && right_work != true)
		{
			
			iter = 0;
			std::cout << "re rand" << std::endl;
		}
		if (right_work == true)
		{
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					u_entrance = 0;
					double u_entrance_a;
					//вычисляем выходы для A для каждой картинки и нейрону R
					for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
					{
						double tmpx;
						u_entrance_a = 0;
						for (int pixel = 0; pixel < pic_size - 1; pixel++)
						{
							if (x[pic][pixel + 1])
								tmpx = 1.0;
							else
								tmpx = 0.0;
							u_entrance_a += w_a[a_neuron][pixel] * tmpx;
						}
						if (u_entrance_a >= fi_a[a_neuron])
						{
							u_exit = 1;
						}
						else
						{
							u_exit = 0;
						}
						u_entrance += u_exit * w_r[r_neuron][a_neuron]; //вычисляем вход нейрона R
					}
					if (pic == r_neuron)
						fi_r[r_neuron][0] = u_entrance;
				}
			}
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				fi_r[r_neuron][1] = 140.0;
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{

					u_entrance = 0;
					double u_entrance_a;
					//вычисляем выходы для A для каждой картинки и нейрону R
					for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
					{
						double tmpx;
						u_entrance_a = 0;
						for (int pixel = 0; pixel < pic_size - 1; pixel++)
						{
							if (x[pic][pixel + 1])
								tmpx = 1.0;
							else
								tmpx = 0.0;
							u_entrance_a += w_a[a_neuron][pixel] * tmpx;
						}
						if (u_entrance_a >= fi_a[a_neuron])
						{
							u_exit = 1;
						}
						else
						{
							u_exit = 0;
						}
						u_entrance += u_exit * w_r[r_neuron][a_neuron]; //вычисляем вход нейрона R
					}
					//std::cout << "u_entrance[" << r_neuron << "][" << pic << "]= " << u_entrance << " iter = " << iter << std::endl;
					bool chalange;
					if (fi_r[r_neuron][0] < u_entrance)
						if ((chalange = u_entrance < fi_r[r_neuron][1]))
						{
							fi_r[r_neuron][1] = u_entrance;
							//std::cout << "fi_r[" << r_neuron << "][" << 1 << "] = " << fi_r[r_neuron][1] << std::endl;
						}
				}
			}

		}
	}
	char *msg = new char[100];
	_itoa(iter, msg, 10);
	MessageBox(NULL, msg, "Iterations", MB_OK);
	delete[] msg;
	for (int i = 0; i < pic_dim - 1; i++)
	{
		delete[] Nak[i];
		delete[] Nagr[i];
	}
	delete[] Nak;
	delete[] Nagr;
	return 0;
}

int neuron::method_back_error()
{
	method_perceptron();
	/*int iter = 0;
	bool right_work = false;
	double alpha = 0.05;
	srand(time(NULL));
	int last_iter = 20 + rand() % 10;
	double **delta_wr = new double*[size_r_neuron];
	double **delta_wa2 = new double*[size_ae2_neuron];
	double **delta_wa1 = new double*[size_ae1_neuron];
	for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
	{
		delta_wa2[ae2_neuron] = new double[size_ae1_neuron];
	}
	for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
	{
		delta_wr[r_neuron] = new double[size_ae2_neuron];
	}
	for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
	{
		delta_wa1[ae1_neuron] = new double[size_ae1_neuron];
	}
	double *Error = new double[pic_dim - 1];
	double *sigma = new double[pic_dim - 1];
	double *sigma_a2 = new double[size_ae2_neuron];
	double *sigma_a1 = new double[size_ae1_neuron];
	while (!right_work)
	{
		right_work = true;
		//инициализация рандома и генерация 0..1 чисел для нейронов w[i][j]
		if (iter == 0)
		{
			//шаг 1
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				w_re[r_neuron][0] = 1;
				for (int ae2_neuron = 1; ae2_neuron < size_ae2_neuron; ae2_neuron++)
				{
					if (r_neuron == 0)
						w_re[r_neuron][ae2_neuron] = 1;
					else
						w_re[r_neuron][ae2_neuron] = (rand() % 99 + 1) / 100.0;//генерируем веса для R нейронов генерация верная
				}
			}
			for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
			{
				w_ae2[ae2_neuron][0] = 1;
				for (int ae1_neuron = 1; ae1_neuron < size_ae1_neuron; ae1_neuron++)
				{
					if (ae2_neuron == 0)
						w_ae2[ae2_neuron][ae1_neuron] = 1;
					else
						w_ae2[ae2_neuron][ae1_neuron] = (rand() % 99 + 1) / 100.0;//генерируем веса для R нейронов генерация верная
				}
			}
			for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
			{
				w_ae1[ae1_neuron][0] = 1;
				for (int pixel = 1; pixel < pic_size; pixel++)
				{
					if (ae1_neuron == 0)
						w_ae1[ae1_neuron][pixel] = 1;
					else
						w_ae1[ae1_neuron][pixel] = (rand() % 99 + 1) / 100.0;//генерируем веса для R нейронов генерация верная
				}
			}
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				double max = 0, min = 1500;
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					double sum_pic = 0.0;
					for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
					{
						double sum_second = 0.0;
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							double sum = 0.0;
							for (int pixel = 0; pixel < pic_size; pixel++)
							{
								double tmpx;
								if (x[pic][pixel])
									tmpx = 1.0;
								else
									tmpx = 0.0;
								sum += tmpx * w_ae1[ae1_neuron][pixel];
							}
							sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
						}
						sum_pic += g_activation(sum_second) * w_re[r_neuron][ae2_neuron];
					}
					if (sum_pic > max)
						max = sum_pic;
					if (sum_pic < min)
						min = sum_pic;
				}
				fi_r[r_neuron][0] = (max + min) / 2;
			}
			std::cout << "generation w is complete" << std::endl;
		}

		for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
		{
			double max = 0, min = 1500;
			for (int pic = 0; pic < pic_dim - 1; pic++)
			{
				double sum_pic = 0.0;
				for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
				{
					double sum_second = 0.0;
					for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
					{
						double sum = 0.0;
						for (int pixel = 0; pixel < pic_size; pixel++)
						{
							double tmpx;
							if (x[pic][pixel])
								tmpx = 1.0;
							else
								tmpx = 0.0;
							sum += tmpx * w_ae1[ae1_neuron][pixel];
						}
						sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
					}
					sum_pic += g_activation(sum_second) * w_re[r_neuron][ae2_neuron];
				}
				if (r_neuron == pic)
				{
					if (sum_pic < fi_r[r_neuron][0])
					{
						right_work = false;
					}
				}
			}
		}
		if (right_work != true)
		{
			
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					double sum_pic = 0.0;
					for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
					{
						double sum_second = 0.0;
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							double sum = 0.0;
							for (int pixel = 0; pixel < pic_size; pixel++)
							{
								double tmpx;
								if (x[pic][pixel])
									tmpx = 1.0;
								else
									tmpx = 0.0;
								sum += tmpx * w_ae1[ae1_neuron][pixel];
							}
							sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
						}
						sum_pic += g_activation(sum_second) * w_re[r_neuron][ae2_neuron];
					}
					if (r_neuron == pic)
					{
						Error[pic] = 1 / 2 * (1 - g_activation(sum_pic));
						sigma[pic] = (1 - g_activation(sum_pic)) * sigma_g_activation(sum_pic);
					}
					else
					{
						Error[pic] = 1 / 2 * (0 - g_activation(sum_pic));
						sigma[pic] = (0 - g_activation(sum_pic)) * sigma_g_activation(sum_pic);
					}
				}
				
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
					{
						double sum_second = 0.0;
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							double sum = 0.0;
							for (int pixel = 0; pixel < pic_size; pixel++)
							{
								double tmpx;
								if (x[pic][pixel])
									tmpx = 1.0;
								else
									tmpx = 0.0;
								sum += tmpx * w_ae1[ae1_neuron][pixel];
							}
							sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
						}
						if (ae2_neuron == 0)
							delta_wr[r_neuron][ae2_neuron] = alpha * sigma[pic];
						else
							delta_wr[r_neuron][ae2_neuron] = alpha * sigma[pic] * g_activation(sum_second);
						//шаг 8
						double sigma_sum = 0.0;
						sum_second = 0.0;
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							double sum = 0.0;
							for (int pixel = 0; pixel < pic_size; pixel++)
							{
								double tmpx;
								if (x[pic][pixel])
									tmpx = 1.0;
								else
									tmpx = 0.0;
								sum += tmpx * w_ae1[ae1_neuron][pixel];
							}

							sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
							sigma_sum += sigma[r_neuron] * w_ae2[ae2_neuron][ae1_neuron];
						}
						sigma_a2[pic] = sigma_sum;
						sigma_a2[pic] = sigma_a2[pic] * sigma_g_activation(sum_second);
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							if (ae1_neuron == 0)
								delta_wa2[ae2_neuron][ae1_neuron] = alpha * sigma_a2[pic];
							else
								delta_wa2[ae2_neuron][ae1_neuron] = sigma_a2[pic] * alpha * w_ae2[ae2_neuron][ae1_neuron];
						}
					}
					for (int pic = 0; pic < pic_dim - 1; pic++)
					{
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							double sum = 0.0;
							double sigma_sum;
							for (int pixel = 0; pixel < pic_size; pixel++)
							{
								double tmpx;
								if (x[pic][pixel])
									tmpx = 1.0;
								else
									tmpx = 0.0;
								sum += tmpx * w_ae1[ae1_neuron][pixel];
								sigma_sum += sigma_a2[pic] * sigma;
							}
							
						}
					}

				}

				//шаг 9
				for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
				{
					w_re[r_neuron][ae2_neuron] += delta_wr[r_neuron][ae2_neuron];
					for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
					{
						w_ae2[ae2_neuron][ae1_neuron] += delta_wa2[ae2_neuron][ae1_neuron];
					}
				}
				
			}
			
		}

		iter++;
		if (iter == 1000 && right_work != true)
		{

			iter = 0;
			std::cout << "re rand" << std::endl;
		}
		
		if (right_work)
		{
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				int pic = r_neuron;

				double sum_pic = 0.0;
				for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
				{
					double sum_second = 0.0;
					for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
					{
						double sum = 0.0;
						for (int pixel = 0; pixel < pic_size; pixel++)
						{
							double tmpx;
							if (x[pic][pixel])
								tmpx = 1.0;
							else
								tmpx = 0.0;
							sum += tmpx * w_ae1[ae1_neuron][pixel];
						}
						sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
					}
					sum_pic += g_activation(sum_second) * w_re[r_neuron][ae2_neuron];
				}
				fi_r[r_neuron][0] = sum_pic;

			}
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				fi_r[r_neuron][1] = 1500.0;
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					double sum_pic = 0.0;
					for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
					{
						double sum_second = 0.0;
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							double sum = 0.0;
							for (int pixel = 0; pixel < pic_size; pixel++)
							{
								double tmpx;
								if (x[pic][pixel])
									tmpx = 1.0;
								else
									tmpx = 0.0;
								sum += tmpx * w_ae1[ae1_neuron][pixel];
							}
							sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
						}
						sum_pic += g_activation(sum_second) * w_re[r_neuron][ae2_neuron];
					}
					
					if (fi_r[r_neuron][0] <= sum_pic)
						if (sum_pic < fi_r[r_neuron][1])
						{
							fi_r[r_neuron][1] = sum_pic;
							//std::cout << "fi_r[" << r_neuron << "][" << 1 << "] = " << fi_r[r_neuron][1] << std::endl;
						}
				}
				
			}
			for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
			{
				for (int pic = 0; pic < pic_dim - 1; pic++)
				{
					double sum_pic = 0.0;
					for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
					{
						double sum_second = 0.0;
						for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
						{
							double sum = 0.0;
							for (int pixel = 0; pixel < pic_size; pixel++)
							{
								double tmpx;
								if (x[pic][pixel])
									tmpx = 1.0;
								else
									tmpx = 0.0;
								sum += tmpx * w_ae1[ae1_neuron][pixel];
							}
							sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
						}
						sum_pic += g_activation(sum_second) * w_re[r_neuron][ae2_neuron];
					}
					if ((fi_r[r_neuron][0] <= sum_pic && sum_pic < fi_r[r_neuron][1]) || (fi_r[r_neuron][0] == sum_pic && fi_r[r_neuron][0] == fi_r[r_neuron][1]))
					{
						if (r_neuron != pic)
							right_work = false;
					}
					else
					{
						if (r_neuron == pic)
							right_work = false;
					}
				}
			}
			if (right_work == false)
				iter = 0;
		}
	}
	delete[] sigma_a2;
	delete[] sigma_a1;
	delete[] sigma;
	delete[] Error;
	for (int r_neuron = 0; r_neuron < size_r_neuron; r_neuron++)
	{
		delete[] delta_wr[r_neuron];
	}
	delete[] delta_wr;
	for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
	{
		delete[] delta_wa2[ae2_neuron];
	}
	delete[] delta_wa2;
	for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
	{
		delete[] delta_wa1[ae1_neuron];
	}
	delete[] delta_wa1;
	
	char *msg = new char[100];
	_itoa(iter, msg, 10);
	MessageBox(NULL, msg, "Iterations", MB_OK);
	delete[] msg;*/

	return 0;
}

int neuron::method_hemming()
{
	//расчёт матрицы весов Z вгоняем туда эталоны

	for (int z_neuron = 0; z_neuron < pic_dim - 1; z_neuron++)
	{
		double tmpx;
		for (int pixel = 1; pixel < pic_size; pixel++)
		{
			if (x[z_neuron][pixel])
				tmpx = 1.0;
			else
				tmpx = -1.0;
			w_z[z_neuron][pixel - 1] = tmpx / 2.0;
		}
		b_z[z_neuron] = 25 / 2;
	}
	k_z = 0.04;
	Un_z = 1.0 / k_z;
	epsilon = 1.0 / (pic_dim - 1);

	
	return 0;
}

int neuron::method_kohonin()
{
	srand(time(NULL));
	double radius = 0;
	alpha = 0.6;
	double k = 0.5;
	epsilon = 0.0005;
	double **w_k_old = new double*[3];
	double *Vector_A = new double[3];
	bool right_work = false;
	for (int a_neuron = 0; a_neuron < 3; a_neuron++)
	{
		w_k_old[a_neuron] = new double[pic_size - 1];
	}
	
	//шаг 1 инициализация весов
	
	int iter = 0;
	while (!right_work)
	{
		right_work = true;
		if (iter == 0)
		{
			for (int a_neuron = 0; a_neuron < 3; a_neuron++)
			{
				for (int pixel = 1; pixel < pic_size; pixel++)
				{
					w_k_old[a_neuron][pixel - 1] = rand() % 11 / 10.0;;
				}
			}
		}
		double tmpx;
		int winner = 0;
		for (int pic = 0; pic < pic_dim - 1; pic++)
		{
			//расчитываем расстояния шаг 4
			for (int a_neuron = 0; a_neuron < 3; a_neuron++)
			{
				Vector_A[a_neuron] = 0.0;
				for (int pixel = 1; pixel < pic_size; pixel++)
				{
					if (x[pic][pixel])
						tmpx = 1.0;
					else
						tmpx = 0.0;
					Vector_A[a_neuron] += (w_k_old[a_neuron][pixel - 1] - tmpx) *(w_k_old[a_neuron][pixel - 1] - tmpx);
				}
			}
			//шаг 5 ищем победителя
			for (int a_neuron = 1; a_neuron < 3; a_neuron++)
			{
				if (Vector_A[winner] > Vector_A[a_neuron])
					winner = a_neuron;
			}
			//шаг 6 победителю меняем веса
			for (int pixel = 1; pixel < pic_size; pixel++)
			{
				if (x[pic][pixel])
					tmpx = 1.0;
				else
					tmpx = 0.0;
				w_k[winner][pixel - 1] = w_k_old[winner][pixel - 1] + alpha * (tmpx - w_k_old[winner][pixel - 1]);
			}
		}
		//шаг 7 модифицируем альфу
		alpha = 0.5 * alpha;
		//шаг 9 проверка условий останова
		for (int a_neuron = 0; a_neuron < 3; a_neuron++)
		{
			for (int pixel = 0; pixel < pic_size - 1; pixel++)
			{
				if (abs(w_k[a_neuron][pixel] - w_k_old[a_neuron][pixel]) > epsilon)
				{
					right_work = false;
				}
				w_k_old[a_neuron][pixel] = w_k[a_neuron][pixel];
			}
		}
		iter++;
		if (iter == 5000 && right_work == false)
		{
			iter = 0;
			std::cout << "re rand" << std::endl;
		}
	}

	char *msg = new char[100];
	_itoa(iter, msg, 10);
	MessageBox(NULL, msg, "Iterations", MB_OK);
	delete[] msg;
	
	delete[] Vector_A;
	for (int a_neuron = 0; a_neuron < 3; a_neuron++)
	{
		delete[] w_k_old[a_neuron];
	}
	delete[] w_k_old;
	return 0;
}

double neuron::fun(double r_want, double r_res)
{
	if (r_want - r_res == 0)
		return 0;
	return 0.01;
}

double neuron::g_activation(double x)
{
	return 1.0 / (1.0 + exp(- x));
}

double neuron::sigma_g_activation(double x)
{
	return g_activation(x) * (1 - g_activation(x));
}

double neuron::g_z_activation(double x)
{
	if (x <= 0)
	{
		return 0.0;
	}
	if (0 <= x <= Un_z)
	{
		return k_z * x;
	}
	return Un_z;
}

double neuron::g_a_activation(double x)
{
	if (x > 0)
		return x;
	return 0.0;
}

int neuron::clear_w()
{
	for (int i = 0; i < pic_dim - 1; i++)
		for (int j = 0; j < pic_size; j++)
			w[i][j] = 0;
	return 0;
}

int neuron::clear_label()
{
	for (int i = 0; i < pic_dim - 1; i++)
	{
		SetWindowText(hWndLabelResult[i], NULL);
	}
	return 0;
}

double neuron::max_in_array(double * arr, int size)
{
	double maximum = arr[0];
	for (int i = 1; i < size; i++)
	{
		maximum = max(arr[i], maximum);
	}
	return maximum;
}

double neuron::min_in_array(double * arr, int size)
{
	double minimum = arr[0];
	for (int i = 1; i < size; i++)
	{
		minimum = min(arr[i], minimum);
	}
	return minimum;
}


template <typename T>
int neuron::bubble_sort(T *a, int size)
{
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				T b = a[j];
				a[j] = a[j + 1];
				a[j + 1] = b;
			}
		}
	}
	return 0;
}

int neuron::recognize()
{
	clear_label();
	if (choose_method != METHOD_HEMMING && choose_method != METHOD_KOHONIN)
		for (int i = 0; i < pic_dim - 1; i++)
		{
			calc_neuron(i);
		}
	else
	{
		if (choose_method == METHOD_KOHONIN)
		{
			double VectorA[3];
			for (int a_neuron = 0; a_neuron < 3; a_neuron++)
			{
				VectorA[a_neuron] = 0.0;
				double tmpx;
				for (int pixel = 1; pixel < pic_size; pixel++)
				{
					if (x[pic_dim - 1][pixel])
						tmpx = 1.0;
					else
						tmpx = 0.0;
					VectorA[a_neuron] += w_k[a_neuron][pixel - 1] * tmpx;
				}
			}
			int winner = 0;
			for (int a_neuron = 1; a_neuron < 3; a_neuron++)
			{
				if (VectorA[winner] < VectorA[a_neuron])
				{
					winner = a_neuron;
				}
			}
			for (int i = 0; i < pic_dim - 1; i++)
			{
				if (i == winner)
					SendMessage(hWndCheckBoxesResult[i], BM_SETCHECK, BST_CHECKED, 0);
				else
					SendMessage(hWndCheckBoxesResult[i], BM_SETCHECK, BST_UNCHECKED, 0);
			}
		}
		else
		{
			double *u_z_entrance = new double[pic_dim - 1];
			double *u_z_exit = new double[pic_dim - 1];

			for (int z_neuron = 0; z_neuron < pic_dim - 1; z_neuron++)
			{
				double tmpx;
				u_z_entrance[z_neuron] = b_z[z_neuron];
				for (int pixel = 1; pixel < pic_size; pixel++)
				{
					if (x[5][pixel])
						tmpx = 1.0;
					else
						tmpx = -1.0;
					u_z_entrance[z_neuron] += w_z[z_neuron][pixel - 1] * tmpx;
				}
				u_z_exit[z_neuron] = k_z * u_z_entrance[z_neuron];
			}

			double * u_a_exit = new double[pic_dim - 1];
			double * u_a_exit_old = new double[pic_dim - 1];
			for (int i = 0; i < pic_dim - 1; i++)
			{
				u_a_exit_old[i] = u_z_exit[i];
				std::cout << "u_z_exit[" << i << "] = " << u_z_exit[i] << std::endl;
			}
			bool changes = false;
			int iter = 0;
			while (!changes)
			{
				changes = true;
				for (int i = 0; i < pic_dim - 1; i++)
				{
					u_a_exit[i] = 0;
					for (int k = 0; k < pic_dim - 1; k++)
					{
						if (k != i)
							u_a_exit[i] += u_a_exit_old[k];
					}
					u_a_exit[i] = u_a_exit_old[i] - epsilon * u_a_exit[i];
					u_a_exit[i] = g_a_activation(u_a_exit[i]);
					//std::cout << "u_a_exit[" << i << "] = " << u_a_exit[i] << std::endl;
				}
				for (int i = 0; i < pic_dim - 1; i++)
				{
					if (u_a_exit[i] != u_a_exit_old[i])
						changes = false;
					u_a_exit_old[i] = u_a_exit[i];
				}
				iter++;
			}
			std::cout << "iter = " << iter << std::endl;
			for (int i = 0; i < pic_dim - 1; i++)
			{
				std::cout << "u_a_exit[" << i << "] = " << u_a_exit[i] << std::endl;
				if (u_a_exit[i] > 0)
					SendMessage(hWndCheckBoxesResult[i], BM_SETCHECK, BST_CHECKED, 0);
				else
					SendMessage(hWndCheckBoxesResult[i], BM_SETCHECK, BST_UNCHECKED, 0);
			}

			delete[] u_a_exit_old;
			delete[] u_a_exit;
			delete[] u_z_entrance;
			delete[] u_z_exit;
		}
		
	}
	return 0;
}

int neuron::calc_neuron(int n)
{
	switch (choose_method)
	{
	case METHOD_HEBBA_BIPOLAR:
	{
		int tmpx;
		S = w[n][0];
		for (int j = 1; j < pic_size; j++)
		{
			if (x[5][j])
				tmpx = 1;
			else
				tmpx = -1;
			S += tmpx * w[n][j];
		}
		if (S > 0)
			y = 1;
		else
			y = -1;
		if (y == 1)
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
		else
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
		return 0;
	}
	case METHOD_HEBBA_BINARY:
	{
		int tmpx;
		S = w[n][0];
		for (int j = 1; j < pic_size; j++)
		{
			if (x[5][j])
				tmpx = 1;
			else
				tmpx = 0;
			S += tmpx * w[n][j];
		}
		if (S > 0)
			y = 1;
		else
			y = 0;
		if (y == 1)
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
		else
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
		return 0;
	}
	case METHOD_HEBBA_K_BINARY_ACTIVATION:
	{
		int tmpx;
		S = w[n][0];
		for (int j = 1; j < pic_size; j++)
		{
			if (x[5][j])
				tmpx = 1;
			else
				tmpx = 0;
			S += tmpx * w[n][j];
		}
		for (int i = 0; i < 5; i++)
		{
			switch (i)
			{
			case 0:
			{
				if (S < fi[n][i])
				{
					SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
					SetWindowText(hWndLabelResult[n], degree_of_similarity[i]);
				}
				break;
			}
			case 4:
			{
				if (S >= fi[n][i - 1])
				{
					SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
					SetWindowText(hWndLabelResult[n], degree_of_similarity[i]);
				}
				break;
			}
			default:
			{
				if (fi[n][i - 1] <= S && S < fi[n][i])
				{
					SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
					SetWindowText(hWndLabelResult[n], degree_of_similarity[i - 1]);
				}
			}
			}
		}
		return 0;
	}
	case METHOD_HEBBA_K_BIPOLAR_ACTIVATION:
	{
		int tmpx;
		S = w[n][0];
		for (int j = 1; j < pic_size; j++)
		{
			if (x[5][j])
				tmpx = 1;
			else
				tmpx = -1;
			S += tmpx * w[n][j];
		}
		for (int i = 0; i < 5; i++)
		{
			switch (i)
			{
			case 0:
			{
				if (S < fi[n][i])
				{
					SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
					SetWindowText(hWndLabelResult[n], degree_of_similarity[i]);
				}
				break;
			}
			case 4:
			{
				if (S >= fi[n][i - 1])
				{
					SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
					SetWindowText(hWndLabelResult[n], degree_of_similarity[i]);
				}
				break;
			}
			default:
			{
				if (fi[n][i - 1] <= S && S < fi[n][i])
				{
					SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
					SetWindowText(hWndLabelResult[n], degree_of_similarity[i - 1]);
				}
			}
			}
		}
		return 0;
	}
	case METHOD_DELTA_RULE:
	{
		u_exit = w[n][0];
		for (int i = 1; i < pic_size; i++)
		{
			int tmpx;
			if (x[5][i])
				tmpx = 1;
			else
				tmpx = 0;
			u_exit += tmpx * w[n][i];
		}
		//std::cout << "u_exit = " << u_exit << std::endl;
		if (u_exit >= 1 - alpha)
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
		else
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
		return 0;
	}
	case METHOD_PERCEPTRON:
	{
		int r_neuron = n;
		int pic = pic_dim - 1;
		double u_entrance_a;
		u_entrance = 0;
		//вычисляем выходы для A для каждой картинки и нейрону R
		for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
		{
			double tmpx;
			u_entrance_a = 0;
			for (int pixel = 0; pixel < pic_size - 1; pixel++)
			{
				if (x[pic][pixel + 1])
					tmpx = 1.0;
				else
					tmpx = 0.0;
				u_entrance_a += w_a[a_neuron][pixel] * tmpx;
			}
			if (u_entrance_a >= fi_a[a_neuron])
			{
				u_exit = 1;
			}
			else
			{
				u_exit = 0;
			}
			u_entrance += u_exit * w_r[r_neuron][a_neuron]; //вычисляем вход нейрона R
		}
		bool first = false, second = false;
		if ( (fi_r[r_neuron][0] <= u_entrance && u_entrance < fi_r[r_neuron][1]) || (fi_r[r_neuron][0] == u_entrance && fi_r[r_neuron][0] == fi_r[r_neuron][1]))
		{
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
		}
		else
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
		//std::cout << "first = " << fi_r[r_neuron][0] << "second = " << fi_r[r_neuron][1] << std::endl;
		return 0;
	}
	case METHOD_BACK_ERROR:
	{
		int r_neuron = n;
		int pic = pic_dim - 1;
		double u_entrance_a;
		u_entrance = 0;
		//вычисляем выходы для A для каждой картинки и нейрону R
		for (int a_neuron = 0; a_neuron < size_a_neuron; a_neuron++)
		{
			double tmpx;
			u_entrance_a = 0;
			for (int pixel = 0; pixel < pic_size - 1; pixel++)
			{
				if (x[pic][pixel + 1])
					tmpx = 1.0;
				else
					tmpx = 0.0;
				u_entrance_a += w_a[a_neuron][pixel] * tmpx;
			}
			if (u_entrance_a >= fi_a[a_neuron])
			{
				u_exit = 1;
			}
			else
			{
				u_exit = 0;
			}
			u_entrance += u_exit * w_r[r_neuron][a_neuron]; //вычисляем вход нейрона R
		}
		bool first = false, second = false;
		if ((fi_r[r_neuron][0] <= u_entrance && u_entrance < fi_r[r_neuron][1]) || (fi_r[r_neuron][0] == u_entrance && fi_r[r_neuron][0] == fi_r[r_neuron][1]))
		{
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
		}
		else
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
		/*int pic = 5;
		int r_neuron = n;
		double sum_pic = 0.0;
		for (int ae2_neuron = 0; ae2_neuron < size_ae2_neuron; ae2_neuron++)
		{
			double sum_second = 0.0;
			for (int ae1_neuron = 0; ae1_neuron < size_ae1_neuron; ae1_neuron++)
			{
				double sum = 0.0;
				for (int pixel = 0; pixel < pic_size; pixel++)
				{
					double tmpx;
					if (x[pic][pixel])
						tmpx = 1.0;
					else
						tmpx = 0.0;
					sum += tmpx * w_ae1[ae1_neuron][pixel];
				}
				sum_second += g_activation(sum) * w_ae2[ae2_neuron][ae1_neuron];
			}
			sum_pic += g_activation(sum_second) * w_re[r_neuron][ae2_neuron];
		}
		std::cout << sum_pic << " neuron=" << r_neuron << " fi_r1=" << fi_r[r_neuron][0] << " fi_r2=" << fi_r[r_neuron][1] << std::endl;
		if ((fi_r[r_neuron][0] <= sum_pic && sum_pic < fi_r[r_neuron][1]) || (fi_r[r_neuron][0] == sum_pic && fi_r[r_neuron][0] == fi_r[r_neuron][1]))
		{
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
		}
		else
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);*/
		return 0;
	}

	case METHOD_KOHONIN:
	{
		u_exit = w_k[n][0];
		for (int i = 1; i < pic_size; i++)
		{
			int tmpx;
			if (x[5][i])
				tmpx = 1;
			else
				tmpx = 0;
			u_exit += tmpx * w_k[n][i - 1];
		}
		//std::cout << "u_exit = " << u_exit << std::endl;
		if (u_exit > 0)
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_CHECKED, 0);
		else
			SendMessage(hWndCheckBoxesResult[n], BM_SETCHECK, BST_UNCHECKED, 0);
		return 0;
	}
	
	default:
	{
		return 1;
	}
	}

	return 0;
}