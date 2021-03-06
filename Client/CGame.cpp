#include "CGame.h"
#include "NetMessages.h"

CGame::CGame()
{
	ResolutionX = 800;
	ResolutionY = 600;

	Login = new CLogin(this);
	NewAccount = new CNew(this);
	Personality = new CPersonality(this);
	Meeting = new CMeeting(this);
	InGame = new CInGame(this);
	Interview = new CInterview(this);
	Personnel = new CPersonnel(this);
	Options = new COptions(this);
	Manage = new CManage(this);
	Recover = new CRecover(this);
	Admin = new CAdmin(this);
	AdminEdit = new CAdminEdit(this);

	Dialog = new CDialog(this);
	Winsock = new CWinsock(this);
	Process = new CProcess(this);
	Engine = new CEngine(this);
	Send = new CSend(this);
	Map = new CMap(this);
	Collision = new CCollision(this);
	Build = new CBuildingList(this);
	Input = new CInput(this);
	Sound = new CSound(this);
	Item = new CItemList(this);
	Inventory = new CInventory(this);
	Bullet = new CBulletList(this);
	Explode = new CExplosionList(this);
	Draw = new CDrawing(this);
	DDraw = new CDDraw(this);

	Timer = new CTime();

	for (int i = 0; i < MaxPlayers; i++)
	{
		Player[i] = new CPlayer(this, i);
	}

	running = 1;

	Tick = 0;
	lastTick = 0;
}

CGame::~CGame()
{
	running = 0;

	delete Login;
	delete NewAccount;
	delete Personality;
	delete Meeting;
	delete InGame;
	delete Interview;
	delete Personnel;
	delete Options;
	delete Manage;
	delete Recover;
	delete Admin;
	delete AdminEdit;

	delete Dialog;
	delete Winsock;
	delete Process;
	delete Engine;
	delete Send;
	delete Map;
 	delete Collision;
	delete Build;
	delete Input;
	delete Sound;
	delete Item;
	delete Inventory;
	delete Bullet;
	delete Explode;
	delete Draw;
	delete DDraw;

	delete Timer;

	for (int i = 0; i < MaxPlayers; i++)
	{
		delete Player[i];
	}

	timeEndPeriod(1);
}

void CGame::Init(HWND hWnd, HINSTANCE hInst)
{
	this->hWnd = hWnd;
	this->hInst = hInst;

	int Exit = 0;
	if (CheckFile("imgArrows.bmp") == 0) Exit = 1;
	if (CheckFile("imgBCLogo.bmp") == 0) Exit = 1;
	if (CheckFile("imgBlackNumbers.bmp") == 0) Exit = 1;
	if (CheckFile("imgBtnStaff.bmp") == 0) Exit = 1;
	if (CheckFile("imgBuildIcons.bmp") == 0) Exit = 1;
	if (CheckFile("imgBuildings.bmp") == 0) Exit = 1;
	if (CheckFile("imgBullets.bmp") == 0) Exit = 1;
	if (CheckFile("imgCompany.bmp") == 0) Exit = 1;
	if (CheckFile("imgCursor.bmp") == 0) Exit = 1;
	if (CheckFile("imgDemolish.bmp") == 0) Exit = 1;
	if (CheckFile("imgGround.bmp") == 0) Exit = 1;
	if (CheckFile("imgHealth.bmp") == 0) Exit = 1;
	if (CheckFile("imgInterface.bmp") == 0) Exit = 1;
	if (CheckFile("imgInterfaceBottom.bmp") == 0) Exit = 1;
	if (CheckFile("imgInventorySelection.bmp") == 0) Exit = 1;
	if (CheckFile("imgItems.bmp") == 0) Exit = 1;
	if (CheckFile("imgLava.bmp") == 0) Exit = 1;
	if (CheckFile("imgLExplosion.bmp") == 0) Exit = 1;
	if (CheckFile("imgMiniMapColors.bmp") == 0) Exit = 1;
	if (CheckFile("imgMoneyBox.bmp") == 0) Exit = 1;
	if (CheckFile("imgMoneyDown.bmp") == 0) Exit = 1;
	if (CheckFile("imgMoneyUp.bmp") == 0) Exit = 1;
	if (CheckFile("imgMuzzleFlash.bmp") == 0) Exit = 1;
	if (CheckFile("imgPopulation.bmp") == 0) Exit = 1;
	if (CheckFile("imgRadarColors.bmp") == 0) Exit = 1;
	if (CheckFile("imgResearch.bmp") == 0) Exit = 1;
	if (CheckFile("imgResearchComplete.bmp") == 0) Exit = 1;
	if (CheckFile("imgRocks.bmp") == 0) Exit = 1;
	if (CheckFile("imgSExplosion.bmp") == 0) Exit = 1;
	if (CheckFile("imgSmoke.bmp") == 0) Exit = 1;
	if (CheckFile("imgStar.bmp") == 0) Exit = 1;
	if (CheckFile("imgTanks.bmp") == 0) Exit = 1;
	if (CheckFile("imgTurretBase.bmp") == 0) Exit = 1;
	if (CheckFile("imgTurretHead.bmp") == 0) Exit = 1;

	if (Exit == 1) { SendMessage(hWnd, WM_CLOSE, 0, 0); return; }

	Options->LoadOptions();

	Winsock->Init(SERVERIP);

	if (Options->fullscreen == 0)
		DDraw->InitWindowed(hWnd);
	else
		DDraw->InitFullscreen(hWnd);

	DDraw->Clear();
		DDraw->Draw(DDraw->imgCompany, 400, 60, 320, 240);
		DDraw->Draw(DDraw->imgCompany, 80, 300, 320, 240);
		DDraw->Draw(DDraw->imgBCLogo, 80, 60, 320, 240);
		DDraw->Draw(DDraw->imgBCLogo, 400, 300, 320, 240);
	DDraw->Flip();

	Dialog->Start();
	Map->LoadMap();
	Sound->Init();
	Input->StartDInput();

	Winsock->StartTCP();
	Engine->Init();

	//Did the user get kicked within 10 minutes ago?

	sKicked kicked;

	kicked.tick = 0;

	FILE *file;
	file = fopen("imgHealthy.bmp","r");

	if (file)
	{
		fread(&kicked, sizeof(kicked), 1, file);
		fclose(file);

		if (GetTickCount() < kicked.tick || GetTickCount() > kicked.tick + 600000)
		{
			remove("imgHealthy.bmp");
		}
		else
		{
			Winsock->Socket = 0;
			MessageBox(hWnd, "You have been kicked within 10 minutes ago.  You must wait before logging on again.", "BattleCity", 0);
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			return;
		}
	}

	CSHA1 test;
	test.HashFile("map.dat");
	test.Final();
	char szReport[96];
	memset(szReport, 0, sizeof(szReport));
	test.ReportHash(szReport, CSHA1::REPORT_HEX);
	if (strcmp(szReport, "74 2E 00 1A 48 05 AD A1 A8 8B E1 5E 1E 0F 75 1A 82 B6 E8 B7") != 0)
	{
		Winsock->Socket = 0;
		MessageBox(hWnd, "Your map.dat is corrupted.  Please redownload the client at www.battlecity.net!", "BattleCity", 0);
		SendMessage(hWnd, WM_CLOSE, 0, 0);
	}

	/////////////////////////////////////////////////
}

string CGame::ReturnUniqID()
{
	char UniqID[50];
	memset(UniqID, 0, 50);
	GetPrivateProfileString("UniqID", "ID", "0", UniqID, 50, "froogle");

#ifndef _DEBUG
	if (strlen(UniqID) == 1) //We need to generate the ID
#endif
	{
		string NewID;
		char tmpBuffer[20];
		srand((unsigned int)GetTickCount());
		int rand1 = rand();
		memset(tmpBuffer, 0, 20);
		itoa(rand1, tmpBuffer, 10);
		NewID = tmpBuffer;
		NewID += "-";
		Sleep(10);
		srand((unsigned int)GetTickCount());
		int rand2 = rand();
		memset(tmpBuffer, 0, 20);
		itoa(rand2, tmpBuffer, 10);
		NewID += tmpBuffer;
		NewID += "-";
		Sleep(5);
		srand((unsigned int)Tick);
		int rand3 = rand();
		memset(tmpBuffer, 0, 20);
		itoa(rand3, tmpBuffer, 10);
		NewID += tmpBuffer;
		NewID += "-";
		int rand4 = (int)GetTickCount();
		itoa(rand4, tmpBuffer, 10);
		NewID += tmpBuffer;
		WritePrivateProfileString("UniqID", "ID", NewID.c_str(), "froogle");
		strcpy(UniqID, NewID.c_str());
	}

	string UniqIDStr;
	UniqIDStr = UniqID;

	return UniqIDStr;
}

int CGame::CheckFile(string file)
{
	int flag = 0;
	fstream fin;
	fin.open(file.c_str(),ios::in);
	if( fin.is_open() )
	{
		flag = 1;
	}
	fin.close();

	if (flag == 1) return 1;

	string ErrorString;
	ErrorString = "File " + file + " not found.  Please visit www.battlecity.net and download the latest client to fix this problem!";

	MessageBox(hWnd, ErrorString.c_str(), "Error", 0);
	return 0;
}

int CGame::SilentCheckFile(string file)
{
	int flag = 0;
	fstream fin;
	fin.open(file.c_str(),ios::in);
	if( fin.is_open() )
	{
		flag = 1;
	}
	fin.close();

	if (flag == 1) return 1;

	return 0;
}