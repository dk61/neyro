#pragma once
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A 1
#define B 2
#define C 3
#define D 4
#define E 5
#define F 6

#define METHOD_HEBBA_BIPOLAR 0
#define METHOD_HEBBA_BINARY 1
#define METHOD_HEBBA_K_BINARY_ACTIVATION 2
#define METHOD_HEBBA_K_BIPOLAR_ACTIVATION 3
#define METHOD_DELTA_RULE 4
#define METHOD_PERCEPTRON 5
#define METHOD_BACK_ERROR 6
#define METHOD_HEMMING 7
#define METHOD_KOHONIN 8


class neuron
{
public:
	int clear();//очистить нейроны
	int clear_pic();//очистить картинку
	int remember(int num);//запомнить опредлеЄнную картинку
	int compare_check_boxes(HWND * hWnd);//сопоставить указатели на чек боксы
	int compare_radio_buttons(HWND * hWnd);//сопоставить указатели на радиобаттоны методов
	int compare_check_boxes_result(HWND * hWnd);//сопопставить указатели на радиобаттоны результата
	int compare_label_result(HWND * hWnd);
	int size_a_neuron;
	int size_r_neuron;
	int size_ae1_neuron;
	int size_ae2_neuron;
	int malloc();//выделить пам€ть
	int free();//очистить пам€ть
	int show_pic(int num);//показать картинку
	int learn();//обучить
	int recognize();//распознать
	int pic_size;//размер картинки в пиксел€х
	int pic_dim;//количество картинок
	int num_methods;//номер количества методов
	char ** methods;//названи€ методов

private:
	int method_hebba_bipolar();//хебб бипол€рный
	int method_hebba_binary();//хебб бинарный
	int method_hebba_k_binary_activation();//обучение по хеббу к бинарна€ функци€ активации
	int method_hebba_k_bipolar_activation();//обучение по хеббу к бипол€рной функции активации
	int method_delta_rule();//обучение по дельта правилу
	int method_perceptron();//обучение по гамма
	int method_back_error();//обучение обратное распространение ошибки
	int method_hemming();//хемминг
	int method_kohonin();//кохонин
	int calc_neuron(int n); //посчитать значени€ нейрона номер нейрона
	int choose_method;//цифра выбранного метода
	int clear_w();//очистить w
	int clear_label(); //очистить label
	double max_in_array(double *arr, int size);
	double min_in_array(double *arr, int size);
	template <typename T>
	int bubble_sort(T *a, int size);
	bool **x;//картинки
	HWND * hWndCheckBoxes;
	HWND * hWndMethodRadioButtons;
	HWND * hWndCheckBoxesResult;
	HWND * hWndLabelResult;
	double alpha;
	double epsilon;
	double u_exit;
	double u_entrance;

	double **w;//значени€ весов
	double **fi;//фи дл€ к значной функции активации
	double **w_a;
	double **w_ae1;
	double **w_ae2;
	double **w_k;
	double **w_z;
	double *b_z;
	double **w_r;
	double **w_re;
	double *fi_a;
	double *fi_ae1;
	double *fi_ae2;
	double **fi_r;
	double k_z;
	double Un_z;
	char **degree_of_similarity; //степень похожести
	double S;//S 
	double y;//y
protected:
	double fun(double r_want, double r_res);
	double g_activation(double x);
	double sigma_g_activation(double x);
	double g_z_activation(double x);
	double g_a_activation(double x);
};

