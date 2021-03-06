#include "COptions.h"

void *COptionsPointer;

int CALLBACK OptionsDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	CGame *p = (CGame *)COptionsPointer;
    switch(Message)
    {
        case WM_INITDIALOG:
			p->Options->hWnd = hwnd;
			CheckDlgButton(hwnd, 1100, p->Options->sound);
			CheckDlgButton(hwnd, 1101, p->Options->tanksound);
			CheckDlgButton(hwnd, 1102, p->Options->music);
			CheckDlgButton(hwnd, 1103, p->Options->fullscreen);
			CheckDlgButton(hwnd, 1104, p->Options->newbietips);
			CheckDlgButton(hwnd, 1105, p->Options->fastwinsock);
			CheckDlgButton(hwnd, 1106, p->Options->debug);
			CheckDlgButton(hwnd, 1107, p->Options->names);
			CheckDlgButton(hwnd, 1108, p->Options->limitfps);
        return 1;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case 1:
					//Save Options
					p->Options->sound = IsDlgButtonChecked(hwnd, 1100);
					p->Options->tanksound = IsDlgButtonChecked(hwnd, 1101);
					p->Options->music = IsDlgButtonChecked(hwnd, 1102);
					p->Options->fullscreen = IsDlgButtonChecked(hwnd, 1103);
					p->Options->newbietips = IsDlgButtonChecked(hwnd, 1104);
					p->Options->fastwinsock = IsDlgButtonChecked(hwnd, 1105);
					p->Options->debug = IsDlgButtonChecked(hwnd, 1106);
					p->Options->names = IsDlgButtonChecked(hwnd, 1107);
					p->Options->limitfps = IsDlgButtonChecked(hwnd, 1108);
					if (p->Options->music == 0)
					{
						p->Sound->StopMID(1, 0);
					}
					p->Options->SaveOptions();
					p->Dialog->StartDialog = 0;
					EndDialog(hwnd, 1);
                break;
				case 2:
					p->Dialog->StartDialog = 0;
					EndDialog(hwnd, 2);
				break;
            }
        break;
        default:
            return 0;
    }
    return 1;
}

COptions::COptions(CGame *game)
{
	p = game;
	COptionsPointer = game;
}

COptions::~COptions()
{

}

void COptions::ShowOptionsDialog()
{
	p->Dialog->StartDialog = ID_OPTIONS;
	p->Dialog->DialogProcessor = &OptionsDlgProc;

}

void COptions::LoadOptions()
{
	char buffer[1024];

	GetCurrentDirectory(1024,buffer);
	strcat(buffer, "\\options.ini");

	int flag = 0;
	fstream fin;
	fin.open(buffer,ios::in);
	if( fin.is_open() )
	{
		flag = 1;
	}
	fin.close();

	if (flag == 1)
	{
		this->music = GetPrivateProfileInt("Options", "Music", 1, buffer);
		this->sound = GetPrivateProfileInt("Options", "Sound", 1, buffer);
		this->tanksound = GetPrivateProfileInt("Options", "TankSound", 1, buffer);
		this->fullscreen = GetPrivateProfileInt("Options", "Fullscreen", 1, buffer);
		this->newbietips = GetPrivateProfileInt("Options", "NewbieTips", 1, buffer);
		this->fastwinsock = GetPrivateProfileInt("Options", "FastWinsock", 1, buffer);
		this->debug = GetPrivateProfileInt("Options", "Debug", 0, buffer);
		this->names = GetPrivateProfileInt("Options", "Names", 1, buffer);
		this->limitfps = GetPrivateProfileInt("Options", "LimitFPS", 1, buffer);
	}
	else
	{
		this->music = 1;
		this->sound = 1;
		this->tanksound = 1;
		this->fullscreen = 1;
		this->newbietips = 1;
		this->fastwinsock = 1;
		this->debug = 0;
		this->names = 1;
		this->limitfps = 1;
		SaveOptions();
	}
}

void COptions::SaveOptions()
{
	char buffer[1024];

	GetCurrentDirectory(1024,buffer);
	strcat(buffer, "\\options.ini");

	char sdf[2];
	memset(sdf, 0, 2);
	itoa(this->music, sdf, 10);
	WritePrivateProfileString("Options", "Music", sdf, buffer);

	itoa(this->sound, sdf, 10);
	WritePrivateProfileString("Options", "Sound", sdf, buffer);

	itoa(this->tanksound, sdf, 10);
	WritePrivateProfileString("Options", "TankSound", sdf, buffer);

	itoa(this->fullscreen, sdf, 10);
	WritePrivateProfileString("Options", "Fullscreen", sdf, buffer);

	itoa(this->newbietips, sdf, 10);
	WritePrivateProfileString("Options", "NewbieTips", sdf, buffer);

	itoa(this->fastwinsock, sdf, 10);
	WritePrivateProfileString("Options", "FastWinsock", sdf, buffer);

	itoa(this->debug, sdf, 10);
	WritePrivateProfileString("Options", "Debug", sdf, buffer);

	itoa(this->names, sdf, 10);
	WritePrivateProfileString("Options", "Names", sdf, buffer);

	itoa(this->limitfps, sdf, 10);
	WritePrivateProfileString("Options", "LimitFPS", sdf, buffer);
}