#pragma once
enum class MainState 
{
	E_MAIN,
	E_FILETRANSITION,

#define MAIN		MainState::E_MAIN
#define FILETRANS	MainState::E_FILETRANSITION
};