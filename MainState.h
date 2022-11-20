#pragma once
enum class MainState 
{
	E_MAIN,
	E_FILETRANSITION,
	E_DISCONNECTED,

#define MAIN		MainState::E_MAIN
#define FILETRANS	MainState::E_FILETRANSITION
#define DISCON		MainState::E_DISCONNECTED
};