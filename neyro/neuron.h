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
	int clear();//�������� �������
	int clear_pic();//�������� ��������
	int remember(int num);//��������� ����������� ��������
	int compare_check_boxes(HWND * hWnd);//����������� ��������� �� ��� �����
	int compare_radio_buttons(HWND * hWnd);//����������� ��������� �� ������������ �������
	int compare_check_boxes_result(HWND * hWnd);//������������ ��������� �� ������������ ����������
	int compare_label_result(HWND * hWnd);
	int size_a_neuron;
	int size_r_neuron;
	int size_ae1_neuron;
	int size_ae2_neuron;
	int malloc();//�������� ������
	int free();//�������� ������
	int show_pic(int num);//�������� ��������
	int learn();//�������
	int recognize();//����������
	int pic_size;//������ �������� � ��������
	int pic_dim;//���������� ��������
	int num_methods;//����� ���������� �������
	char ** methods;//�������� �������

private:
	int method_hebba_bipolar();//���� ����������
	int method_hebba_binary();//���� ��������
	int method_hebba_k_binary_activation();//�������� �� ����� � �������� ������� ���������
	int method_hebba_k_bipolar_activation();//�������� �� ����� � ���������� ������� ���������
	int method_delta_rule();//�������� �� ������ �������
	int method_perceptron();//�������� �� �����
	int method_back_error();//�������� �������� ��������������� ������
	int method_hemming();//�������
	int method_kohonin();//�������
	int calc_neuron(int n); //��������� �������� ������� ����� �������
	int choose_method;//����� ���������� ������
	int clear_w();//�������� w
	int clear_label(); //�������� label
	double max_in_array(double *arr, int size);
	double min_in_array(double *arr, int size);
	template <typename T>
	int bubble_sort(T *a, int size);
	bool **x;//��������
	HWND * hWndCheckBoxes;
	HWND * hWndMethodRadioButtons;
	HWND * hWndCheckBoxesResult;
	HWND * hWndLabelResult;
	double alpha;
	double epsilon;
	double u_exit;
	double u_entrance;

	double **w;//�������� �����
	double **fi;//�� ��� � ������� ������� ���������
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
	char **degree_of_similarity; //������� ���������
	double S;//S 
	double y;//y
protected:
	double fun(double r_want, double r_res);
	double g_activation(double x);
	double sigma_g_activation(double x);
	double g_z_activation(double x);
	double g_a_activation(double x);
};

