#ifndef __MSGS__
#define __MSGS__

enum ServerMessages {
	SMTCP,
	smLoginCorrect,
	smAppendNews,
	smChatEcho,
	smChatMessage,
	smPlayerData,
	smChatCommand,
	smAddRemCity,
	smStateGame,
	smMayorHire,
	smMayorInInterview,
	smInterviewCancel,
	smMayorDeclined,
	smMayorUpdate,
	smCanBuild,
	smNewBuilding,
	smPlaceBuilding,
	smError,
	smJoinData,
	smComms,
	smFired,
	smFinance,
	smItemCount,
	smAddItem,
	smRemItem,
	smUpdatePop,
	smDeath,
	smOrbed,
	smDestroyCity,
	smDemolish,
	smHP,
	smRemBuilding,
	smInterview,
	smPickedUp,
	smDropped,
	smTCPPong,
	smPointsUpdate,
	smMedKit,
	smExplosion,
	smWarp,
	smNextStep,
	smItemLife,
	smGlobal,
	smAdmin,
	smKicked,
	smUpdate,
	smShoot,
	smTurretLook,
	smTurretShoot,
	smSectorSent,
	smEditAccount,
	smInfoButton,
	smClearPlayer,
	smMayorChanged,
	smRightClickCity,
	smRespawn,
	smBan,
	smUnderAttack,
	smAdminEdit,
	smClickPlayer,
	smUpdateTank,
	smPrivateMessage,

	smCount
};

struct sSMUpdate
{
	unsigned char id;
	unsigned short x;
	unsigned short y;
	unsigned char turn;
	unsigned char move;
	unsigned char dir;
};

struct sSMItem
{
	unsigned short x;
	unsigned short y;
	unsigned char City;
	unsigned char type;
	unsigned char active;
	unsigned short id;
};

struct sSMFinance
{
	unsigned long Cash;
	unsigned long Income;
	unsigned long Research;
	unsigned long Items;
	unsigned long Hospital;
};

struct sSMItemCount
{
	unsigned short id;
	unsigned char count;
};

struct sSMBuild
{
	unsigned char City;
	unsigned short x;
	unsigned short y;
	unsigned char type;
	unsigned char count;
	unsigned short id;
	unsigned char pop;
};

struct sSMPop
{
	unsigned short id;
	unsigned char pop;
};

struct sSMUpdateTurret
{
	unsigned short id;
	unsigned short dir;
};

struct sSMOrbedCity
{
	unsigned char City;
	unsigned char OrberCity;
	unsigned int points;
	unsigned int OrberCityPoints;
};

struct sSMPoints
{
	unsigned char Index;
	unsigned int Points;
	unsigned int Deaths;
	unsigned int Orbs;
	unsigned int Assists;
	unsigned int MonthlyPoints;
};

struct sSMExplode
{
	unsigned char City;
	unsigned short x;
	unsigned short y;
};

struct sSMMayorUpdate
{
	unsigned char Index;
	unsigned char IsMayor;
};

struct sSMStateGame
{
	unsigned short x;
	unsigned short y;
	unsigned char City;
};

struct sSMJoinData
{
	unsigned char id;
	unsigned char Mayor;
	unsigned char City;
};

struct sSMItemLife
{
	unsigned short id;
	unsigned char life;
};

struct sSMAdmin
{
	unsigned short adminIndex;
	unsigned short id;
	unsigned char command;
};

struct sSMShot
{
	unsigned short id;
	unsigned short x;
	unsigned short y;
	unsigned char dir;
	unsigned char type;
};

struct sSMInfoButton
{
	unsigned char city;
};


struct sSMPlayer
{
	char Index;
	char Name[16];
	char Town[16];

	unsigned char isAdmin;
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Member;
	unsigned char Tank;
};

struct sSMRightClickCity
{
	char City;
	unsigned char BuildingCount;
	unsigned short OrbPoints;
};

struct sSMClickPlayer
{
	char Index;
	unsigned short Orbs;
	unsigned short Assists;
	unsigned short Deaths;
};

struct sSMBan
{
	char Account[16];
	char IPAddress[16];
	char Reason[31];
};

enum ClientMessages {
	CMTCP,
	cmVersion,
	cmLogin,
	cmNewAccount,
	cmChatMessage,
	cmSetState,
	cmJobApp,
	cmJobCancel,
	cmHireAccept,
	cmHireDecline,
	cmBuild,
	cmComms,
	cmFired,
	cmItemUp,
	cmItemDrop,
	cmDeath,
	cmDemolish,
	cmMedKit,
	cmHitObject,
	cmTCPPing,
	cmCrash,
	cmNextStep,
	cmSuccessor,
	cmGlobal,
	cmAdmin,
	cmBan,
	cmIsHiring,
	cmWalkie,
	cmUpdate,
	cmShoot,
	cmRequestSector,
	cmEditAccount,
	cmAccountUpdate,
	cmRecover,
	cmRequestInfo,
	cmRightClickCity,
	cmChangeNews,
	cmSetMayor,
	cmRefreshList,
	cmMiniMap,
	cmAdminEditRequest,
	cmAdminEdit,
	cmClickPlayer,
	cmCycleTank,
	cmPrivateMessage,

	cmCount
};

struct sCMBuild
{
	unsigned short x;
	unsigned short y;
	unsigned char type;
};

struct sCMUpdate
{
	unsigned short x;
	unsigned short y;
	unsigned char turn;
	unsigned char move;
	unsigned char dir; 
};

struct sCMItem
{
	unsigned short id;
	char active;
	unsigned char type;
};

struct sCMDemolish
{
	unsigned short id;
};

struct sCMAdmin
{
	unsigned short id;
	unsigned char command;
};

struct sCMVersion
{
	char UniqID[50];
	char Version[10];
};

struct sCMShot
{
	unsigned short x;
	unsigned short y;
	unsigned char dir;
	unsigned char type;
};

struct sCMSector
{
	unsigned char x;
	unsigned char y;
};

struct sCMLogin
{
	char User[15];
	char Pass[15];
};

struct sCMNewAccount
{
	char User[15];
	char Pass[15];
	char Email[50];
	char FullName[20];
	char Town[15];
	char State[15];
};

struct sCMAdminEditRequest
{
	char User[15];
};

struct sCMAdminEdit
{
	char User[15];
	char Pass[15];
	char Email[50];
	char FullName[20];
	char Town[15];
	char State[15];
	int Points;
	int MonthlyPoints;
	int Deaths;
	int Orbs;
	int Assists;
	unsigned char IsAdmin;
	unsigned char Member;
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	unsigned char Tank;
	unsigned char Tank2;
	unsigned char Tank3;
	unsigned char Tank4;
	unsigned char RentalCity;
};

#endif