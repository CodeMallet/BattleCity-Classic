#ifndef _CPLAYER
#define _CPLAYER

#include "CServer.h"

class CServer;

class CPlayer
{
public:
	unsigned char id;

	float X;
	float Y;

	string Name;
	string Town;
	string UniqID;
	string IPAddress;

	int isAdmin;
	unsigned char Tank;
	unsigned char Tank1;
	unsigned char Tank2;
	unsigned char Tank3;
	unsigned char Tank4;
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Member;
	unsigned char RentalCity;

	int Points;
	int Orbs;
	int Assists;
	int Deaths;
	int MonthlyPoints;
	int City;
	int Mayor;
	int State;
	__int64 lastMove;
	__int64 lastShot;

	int Socket;
	char Buffer[2048];
	int BufferLength;

	void setMayor(int set);
	void JoinGame();
	void StartJoin();
	void LeaveGame(int showmessage);
	void LoggedIn(string User);
	void Death(int killer);
	void Clear();
	int FindApplyMayor();

	bool isDead;
	__int64 timeDeath;

	CPlayer(CServer *Server);
	~CPlayer();
private:
	CServer *p;
};

#endif
