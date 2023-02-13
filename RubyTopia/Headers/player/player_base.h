#pragma once

struct ItemSharedUID {
	int actual_uid = 1;
	int shared_uid = 1;
};

struct InventoryItem {
	__int16 itemID;
	__int8 itemCount;
};

struct PlayerInventory {
	vector<InventoryItem> items;
	int inventorySize = 100;
};

#define cloth0 cloth_hair
#define cloth1 cloth_shirt
#define cloth2 cloth_pants
#define cloth3 cloth_feet
#define cloth4 cloth_face
#define cloth5 cloth_hand
#define cloth6 cloth_back
#define cloth7 cloth_mask
#define cloth8 cloth_necklace
#define STR16(x, y) (*(uint16_t*)(&(x)[(y)]))
#define STRINT(x, y) (*(int*)(&(x)[(y)]))
#define cloth9 cloth_ances

struct PlayerInfo {
	bool isCheck = false;
	bool isIn = false;
	int netID;
	int level = 1;
	int xp = 0;
	int adminLevel = 0;
	int premwl = 0;
	int buygems = 0;
	int buygacha = 0;
	bool haveGrowId = false;
	int characterState = 0;
	vector<string>friendinfo;
	vector<string>createfriendtable;
	int punchX;
	int punchY;
	int wrenchx;
	bool legend = false;
	int wrenchy;
	int droppeditemcount = 0;
	int wrenchsession = 0;
	string wrenchedplayer = "";
	int lasttrashitem = 0;
	int lasttrashitemcount = 0;
	int lastunt = 0;
	int lastuntc = 0;
	string wrenchdisplay = "";
	string lastInfo = "";
	string tankIDName = "";
	string tankIDPass = "";
	string requestedName = "";
	string rawName = "";
	long long int quest = 0;
	string displayName = "";
	string country = "";
	string currentWorld = "START";
	string lastInfoname = "";
	string lastgm = "";
	short currentInventorySize = 200;
	string lastgmname = "";
	string lastgmworld = "";
	string guildlast = "";
	vector<string>worldsowned;
	vector<string>createworldsowned;
	bool timedilation = false;
	bool DailyMaths = false;
	bool isinvited = false;
	int guildranklevel = 0;
	int guildBg = 0;
	int userID;
	int guildFg = 0;
	int petlevel = 0;
	string guildStatement = "";
	string guildLeader = "";
	vector <string> guildmatelist;
	vector<string>guildMembers;
	vector<string>guildGE;
	vector<string>guildGC;
	int guildlevel = 0;
	int guildexp = 0;
	string createGuildName = "";
	string createGuildStatement = "";
	string createGuildFlagBg = "";
	string createGuildFlagFg = "";
	string guild = "";
	bool joinguild = false;
	bool radio = true;
	int x;
	int y;
	int lastPunchX;
	int lastPunchY;
	int posX;
	int posY;
	string lastfriend = "";
	int x1;
	int y1;
	bool isRotatedLeft = false;
	string charIP = "";
	int peffect = 8421376;
	bool isUpdating = false;
	bool joinClothesUpdated = false;
	bool hasLogon = false;
	bool taped = false;

	int cloth_hair = 0;
	int cloth_shirt = 0;
	int cloth_pants = 0;
	int cloth_feet = 0;
	int cloth_face = 0;
	int cloth_hand = 0;
	int cloth_back = 0;
	int cloth_mask = 0;
	int cloth_necklace = 0;
	int cloth_ances = 0;

	bool canWalkInBlocks = false;
	bool canDoubleJump = false;
	bool isInvisible = false;
	bool noHands = false;
	bool noEyes = false;
	bool noBody = false;
	bool devilHorns = false;
	bool goldenHalo = false;
	bool isFrozen = false;
	bool isCursed = false;
	bool isDuctaped = false;
	bool haveCigar = false;
	int Ultrasound = 0;
	bool PatientHeartStopped = false;
	long long int SurgeryTime = 0;
	bool SurgeryCooldown = false;
	float PatientTemperatureRise = 0;
	bool FixIt = false;
	bool UnlockedAntibiotic = false;
	bool PerformingSurgery = false;
	int SurgerySkill = 0;
	bool RequestedSurgery = false;
	string TempColor = "";
	bool HardToSee = false;
	bool PatientLosingBlood = false;
	int SurgItem1 = 4320;
	int SurgItem2 = 4320;
	int SurgItem3 = 4320;
	int SurgItem4 = 4320;
	int SurgItem5 = 4320;
	int SurgItem6 = 4320;
	int SurgItem7 = 4320;
	int SurgItem8 = 4320;
	int SurgItem9 = 4320;
	int SurgItem10 = 4320;
	int SurgItem11 = 4320;
	int SurgItem12 = 4320;
	int SurgItem13 = 4320;
	string PatientDiagnosis = "";
	string PatientPulse = "";
	string PatientStatus = "";
	float PatientTemperature = 0;
	string OperationSite = "";
	string IncisionsColor = "";
	int PatientIncisions = 0;
	string PatientRealDiagnosis = "";
	bool isShining = false;
	bool isZombie = false;
	bool isHitByLava = false;
	bool haveHauntedShadows = false;
	bool haveGeigerRadiation = false;
	bool haveReflector = false;
	bool isEgged = false;
	bool havePineappleFloag = false;
	bool haveFlyingPineapple = false;
	bool haveSuperSupporterName = false;
	bool haveSupperPineapple = false;
	bool isGhost = false;
	int wrenchedBlockLocation = -1;
	int skinColor = 0x8295C3FF;
	PlayerInventory inventory;
	long long int lastSB = 0;
	vector<ItemSharedUID> item_uids;
	int last_uid = 1;
};

class PlayerDB {
public:
	static string getProperName(string name);
	static string fixColors(string text);
	static int playerLogin(ENetPeer* peer, string username, string password);
	static int playerRegister(ENetPeer* peer, string username, string password, string passwordverify, string email, string discord);
	static void showWrong(ENetPeer* peer, string itemFind, string listFull);
	static void OnTextOverlay(ENetPeer* peer, string text);
	static void OnSetCurrentWeather(ENetPeer* peer, int weather);
	static void PlayAudio(ENetPeer* peer, string audioFile, int delayMS);
	static void OnAddNotification(ENetPeer* peer, string text, string audiosound, string interfaceimage);
	static int guildRegister(ENetPeer* peer, string guildName, string guildStatement, string guildFlagfg, string guildFlagbg);
	static void OnTalkBubble(ENetPeer* peer, int netID, string message, bool stay) {
		if (message.length() == 0 || message.length() > 100) return;
		GamePacket p2;
		if (stay)
			p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), message), 0), 1));
		else
			p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), message), 0));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
};

struct PlayerMoving {
	int packetType;
	int netID;
	float x;
	float y;
	int characterState;
	int plantingTree;
	float XSpeed;
	float YSpeed;
	int punchX;
	int punchY;

};

enum ClothTypes {
	HAIR,
	SHIRT,
	PANTS,
	FEET,
	FACE,
	HAND,
	BACK,
	MASK,
	NECKLACE,
	ANCES,
	NONE
};