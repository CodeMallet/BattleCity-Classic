#include "CBuilding.h"

CBuilding *CBuildingList::findBuilding(unsigned short id)
{
#ifndef _DEBUG
	try {
#endif
	CBuilding *bld = buildings;
	if (!bld)
		return 0;

	while (bld->prev)
		bld = bld->prev;

	while (bld)
	{
		if (bld->id == id)
			return bld;
		bld = bld->next;
	}
	return 0;

#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "findBuilding"); p->Engine->logerror("findBuilding");}
#endif
}

CBuilding *CBuildingList::findBuildingbyLocation(int X, int Y)
{
#ifndef _DEBUG
	try {
#endif
	CBuilding *bld = buildings;
	if (!bld)
		return 0;

	while (bld->prev)
		bld = bld->prev;

	while (bld)
	{
		if (bld->X == X && bld->Y == Y)
			return bld;
		bld = bld->next;
	}
	return 0;
#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "findBuildingbyLocation"); p->Engine->logerror("findBuildingbyLocation");}
#endif
}

CBuilding *CBuildingList::newBuilding(unsigned short X, unsigned short Y, unsigned char City, int Type, unsigned short id)
{
#ifndef _DEBUG
	try {
#endif
	CBuilding *bld = 0;

	if (id > 0)
	{
		bld = findBuilding(id);
		if (bld) return 0;
	}

	bld = buildings;

	if (!bld)
	{
		buildings = new CBuilding(X, Y, Type, City, id, p);
		return buildings;
	}
	else
	{
		while(bld->next)
			bld = bld->next;
		bld->next = new CBuilding(X, Y, Type, City, id, p);
		bld->next->prev = bld;
		return bld->next;
	}

	return 0;

#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "newBuilding"); p->Engine->logerror("newBuilding"); return 0;}
#endif
}

void CBuildingList::Cycle()
{
#ifndef _DEBUG
	try {
#endif
	int me = p->Winsock->MyIndex;

	CBuilding *bld = buildings;
	if (!bld)
		return;

	while (bld->prev)
		bld = bld->prev;

	while (bld)
	{
		if (p->Tick > bld->timeAnimation)
		{
			bld->Animation++; if (bld->Animation > 5) bld->Animation = 0;
			bld->timeAnimation = p->Tick + 500;
		}
		if (bld->Smoke > 0)
		{
			if (p->Tick > bld->timeSmoke)
			{
				bld->Smoke++; 
				if (bld->Smoke > 5) 
				{
					if (bld->ItemsLeft > 0) bld->Smoke = 1; else bld->Smoke = 0;
				}
				bld->timeSmoke = p->Tick + 500;
			}
		}
		else if (bld->ItemsLeft > 0) bld->Smoke = 1;
		bld = bld->next;
	}
#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "Building-Cycle"); p->Engine->logerror("Building-Cycle");}
#endif
}

CBuilding *CBuildingList::delBuilding(CBuilding *del)
{
#ifndef _DEBUG
	try {
#endif
	if (!buildings)
		return 0;
	if (del->prev)
		buildings = del->prev;
	else if (del->next)
		buildings = del->next;
	else
		buildings = 0;

	delete del;
	
	return buildings;
#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "delBuilding"); p->Engine->logerror("delBuilding");}
#endif
};

void CBuildingList::DestroyCity(char theCity)
{
#ifndef _DEBUG
	try {
#endif
	CBuilding *bld = this->buildings;
	if (!bld)
		return;

	while (bld->prev)
		bld = bld->prev;

	while (bld)
	{
		if (bld->City == theCity && bld->Type != 6)
		{
			delBuilding(bld);
			bld = this->buildings;
			if (!bld)
				return;
			while (bld->prev)
				bld = bld->prev;
		}
		bld = bld->next;
	}
#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "Building:DestroyCity"); p->Engine->logerror("Building-DestroyCity");}
#endif
}

int CBuildingList::inRange()
{
#ifndef _DEBUG
	try {
#endif
	if (p->Player[p->Winsock->MyIndex]->isAdmin == 2) return 1;

	CBuilding *bld = buildings;
	if (!bld)
		return 0;

	while (bld->prev)
		bld = bld->prev;

	while (bld)
	{
		if (bld->City == p->Player[p->Winsock->MyIndex]->City)
		{
			if ((abs((bld->X*48) - p->Player[p->Winsock->MyIndex]->X) < 500) && (abs((bld->Y*48) - p->Player[p->Winsock->MyIndex]->Y) < 500))
			{
				int cityX = (unsigned short)(512*48)-(32+(p->Player[p->Winsock->MyIndex]->City % 8*64)) * 48;
				int cityY = (unsigned short)(512*48)-(32+(p->Player[p->Winsock->MyIndex]->City / 8*64)) * 48; 

				if ((abs(cityX - p->Player[p->Winsock->MyIndex]->X) < 1440) && (abs(cityY - p->Player[p->Winsock->MyIndex]->Y) < 1440))
				{
					return 1;
				}
			}
		}
		bld = bld->next;
	}

	return 0;

#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "Building:inRange"); p->Engine->logerror("Building:inRange");}
#endif
}

int CBuildingList::itemInRange()
{
#ifndef _DEBUG
	try {
#endif
	if (p->Player[p->Winsock->MyIndex]->isAdmin == 2) return 1;

	CBuilding *bld = buildings;
	if (!bld)
		return 0;

	while (bld->prev)
		bld = bld->prev;

	while (bld)
	{
		if (bld->City == p->Player[p->Winsock->MyIndex]->City)
		{
			if ((abs((bld->X*48) - p->Player[p->Winsock->MyIndex]->X) < 500) && (abs((bld->Y*48) - p->Player[p->Winsock->MyIndex]->Y) < 500))
			{
				return 1;
			}
		}
		bld = bld->next;
	}

	return 0;

#ifndef _DEBUG
	}
	catch (...) {p->Winsock->SendData(cmCrash, "Building:inRange"); p->Engine->logerror("Building:inRange");}
#endif
}