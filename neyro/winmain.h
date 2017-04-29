#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>

#include "neuron.h"

#define BTN_CLEAR_FIELD 13
//кнопки сохранения
#define BTN_SAVE_A A
#define BTN_SAVE_B B
#define BTN_SAVE_C C
#define BTN_SAVE_D D
#define BTN_SAVE_E E
#define BTN_SAVE_F F
//кнопки показа кнопок
#define BTN_SHOW_A A + 6
#define BTN_SHOW_B B + 6
#define BTN_SHOW_C C + 6
#define BTN_SHOW_D D + 6
#define BTN_SHOW_E E + 6
#define BTN_SHOW_F F + 6

//кнопки управления
#define BTN_CLEAR 200
#define BTN_LEARN 201
#define BTN_RECOGNIZE 202

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow);

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

WNDPROC OldWndProcGroupBoxSymbol;
LRESULT CALLBACK WndProcGroupBoxSymbol(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

WNDPROC OldWndProcGroupBoxSave;
LRESULT CALLBACK WndProcGroupBoxSave(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

WNDPROC OldWndProcGroupBoxShow;
LRESULT CALLBACK WndProcGroupBoxShow(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

WNDPROC OldWndProcGroupBoxMethod;
LRESULT CALLBACK WndProcGroupBoxMethod(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

WNDPROC OldWndProcGroupBoxManipulation;
LRESULT CALLBACK WndProcGroupBoxManipulation(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

WNDPROC OldWndProcGroupBoxResult;
LRESULT CALLBACK WndProcGroupBoxResult(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);

void OnSize(
	HWND hwnd, 
	UINT flag, 
	int width,
	int height);