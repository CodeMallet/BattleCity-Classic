#ifndef _CAdminEdit
#define _CAdminEdit

#include "CGame.h"
#include "NetMessages.h"

class CGame;

class CAdminEdit
{
public:
	CAdminEdit(CGame *game);
	~CAdminEdit();

	HWND hWnd;

	char IsOpen; 

	void ShowAdminEditDlg();

	char user[15];
	char pass[15];
	char email[50];
	char fullname[20];
	char town[15];
	char state[15];

	int points;
	int monthlypoints;
	int orbs;
	int deaths;
	int assists;
	char admin;
	char member;
	char tank;
	char tank2;
	char tank3;
	char tank4;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	char rentalcity;
private:
	CGame *p;
protected:

};

#endif