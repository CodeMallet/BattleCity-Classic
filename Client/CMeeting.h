#ifndef _CMeeting
#define _CMeeting

#include "CGame.h"

class CGame;

struct Cities
{
	int RealCity;
	int Mayor;
	int Index;
};


class CMeeting
{
public:
	CMeeting(CGame *game);
	~CMeeting();

	HWND hWnd;
	HWND EditWnd;
	HWND ChatWnd;
	HWND CityWnd;
	HWND NewsWnd;
	string Chat;
	string News;

	void ShowMeetingDlg();
	void AppendData(string TheData);
	void AppendNews(string TheData);

	void ClearPlayer(int Index);
	void AddPlayer(int Index);
	void RedrawList();
	void ClearList();
	int FreePlayer();
	bool inUse(int Index);

	void AddCity(int City, int isMayor);
	int FreeCity();

	int lstPlayers[MaxPlayers];

	Cities City[30];
private:
	CGame *p;
protected:

};

#endif