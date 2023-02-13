#pragma once

namespace packet {
	void consolemessage(ENetPeer* peer, string message) {
		gamepacket_t p;
		p.Insert("OnConsoleMessage");
		p.Insert(message);
		p.CreatePacket(peer);
	}
	void OnAddNotification(ENetPeer* peer, string text, string audiosound, string interfaceimage) {
		auto p = packetEnd(appendInt(appendString(appendString(appendString(appendString(createPacket(), "OnAddNotification"),
			interfaceimage),
			text),
			audiosound),
			0));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	void OnNameChanged(ENetPeer* peer, int netID, string name) {
		gamepacket_t p;
		p.Insert("OnNameChanged");
		p.Insert(netID);
		p.Insert(name);
		p.CreatePacket(peer);
	}
	void dialog(ENetPeer* peer, string message) {
		gamepacket_t p;
		p.Insert("OnDialogRequest");
		p.Insert(message);
		p.CreatePacket(peer);
	}
	void onspawn(ENetPeer* peer, string message) {
		gamepacket_t p;
		p.Insert("OnSpawn");
		p.Insert(message);
		p.CreatePacket(peer);
	}
	void requestworldselectmenu(ENetPeer* peer, string message) {
		gamepacket_t p;
		p.Insert("OnRequestWorldSelectMenu");
		p.Insert(message);
		p.CreatePacket(peer);
	}
	void storerequest(ENetPeer* peer, string message) {
		gamepacket_t p;
		p.Insert("OnStoreRequest");
		p.Insert(message);
		p.CreatePacket(peer);
	}
	void storepurchaseresult(ENetPeer* peer, string message) {
		gamepacket_t p;
		p.Insert("OnStorePurchaseResult");
		p.Insert(message);
		p.CreatePacket(peer);
	}
	void SendTalkSelf(ENetPeer* peer, string text) {
		GamePacket p2 = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), ((PlayerInfo*)(peer->data))->netID), text), 0), 1));
		ENetPacket* packet2 = enet_packet_create(p2.data,
			p2.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet2);
		delete p2.data;
	}
	void OnTalkBubble(ENetPeer* peer, int netID, string text, int chatColor, bool isOverlay) {
		if (isOverlay == true) {
			GamePacket p = packetEnd(appendIntx(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"),
				((PlayerInfo*)(peer->data))->netID), text), chatColor), 1));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
		else {
			GamePacket p = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"),
				((PlayerInfo*)(peer->data))->netID), text), chatColor));
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete p.data;
		}
	}
	void OnTextOverlay(ENetPeer* peer, string text) {
		GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnTextOverlay"), text));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	void OnFailedToEnterWorld(ENetPeer* peer) {
		GamePacket p = packetEnd(appendIntx(appendString(createPacket(), "OnFailedToEnterWorld"), 1));
		ENetPacket* packet = enet_packet_create(p.data,
			p.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete p.data;
	}
	void PlayAudio(ENetPeer* peer, string audioFile, int delayMS) {
		string text = "action|play_sfx\nfile|" + audioFile + "\ndelayMS|" + to_string(delayMS) + "\n";
		BYTE* data = new BYTE[5 + text.length()];
		BYTE zero = 0;
		int type = 3;
		memcpy(data, &type, 4);
		memcpy(data + 4, text.c_str(), text.length());
		memcpy(data + 4 + text.length(), &zero, 1);
		ENetPacket* packet = enet_packet_create(data,
			5 + text.length(),
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete[] data;
	}
}

int getState(PlayerInfo* info) {
	int val = 0;
	val |= info->canWalkInBlocks << 0;
	val |= info->canDoubleJump << 1;
	val |= info->isInvisible << 2;
	val |= info->noHands << 3;
	val |= info->noEyes << 4;
	val |= info->noBody << 5;
	val |= info->devilHorns << 6;
	val |= info->goldenHalo << 7;
	val |= info->isFrozen << 11;
	val |= info->isCursed << 12;
	val |= info->isDuctaped << 13;
	val |= info->haveCigar << 14;
	val |= info->isShining << 15;
	val |= info->isZombie << 16;
	val |= info->isHitByLava << 17;
	val |= info->haveHauntedShadows << 18;
	val |= info->haveGeigerRadiation << 19;
	val |= info->haveReflector << 20;
	val |= info->isEgged << 21;
	val |= info->havePineappleFloag << 22;
	val |= info->haveFlyingPineapple << 23;
	val |= info->haveSuperSupporterName << 24;
	val |= info->haveSupperPineapple << 25;
	return val;
}

string PlayerDB::getProperName(string name) {
	string newS;
	for (char c : name) newS += (c >= 'A' && c <= 'Z') ? c - ('A' - 'a') : c;
	string ret;
	for (int i = 0; i < newS.length(); i++)
	{
		if (newS[i] == '`') i++; else ret += newS[i];
	}
	string ret2;
	for (char c : ret) if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) ret2 += c;

	string username = ret2;
	if (username == "prn" || username == "con" || username == "aux" || username == "nul" || username == "com1" || username == "com2" || username == "com3" || username == "com4" || username == "com5" || username == "com6" || username == "com7" || username == "com8" || username == "com9" || username == "lpt1" || username == "lpt2" || username == "lpt3" || username == "lpt4" || username == "lpt5" || username == "lpt6" || username == "lpt7" || username == "lpt8" || username == "lpt9") {
		return "";
	}

	return ret2;
}

string PlayerDB::fixColors(string text) {
	string ret = "";
	int colorLevel = 0;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '`')
		{
			ret += text[i];
			if (i + 1 < text.length())
				ret += text[i + 1];


			if (i + 1 < text.length() && text[i + 1] == '`')
			{
				colorLevel--;
			}
			else {
				colorLevel++;
			}
			i++;
		}
		else {
			ret += text[i];
		}
	}
	for (int i = 0; i < colorLevel; i++) {
		ret += "``";
	}
	for (int i = 0; i > colorLevel; i--) {
		ret += "`w";
	}
	return ret;
}

struct Admin {
	string username;
	string password;
	int level = 0;
	long long int lastSB = 0;
};

vector<Admin> admins;

int PlayerDB::playerLogin(ENetPeer* peer, string username, string password) {
	std::ifstream ifs("core/players/" + PlayerDB::getProperName(username) + ".json");
	if (ifs.is_open()) {
		json j;
		ifs >> j;
		string pss = j["password"];
		int adminLevel = j["adminLevel"];
		if (password == pss) {
			((PlayerInfo*)(peer->data))->hasLogon = true;
			bool found = false;
			for (int i = 0; i < admins.size(); i++) {
				if (admins[i].username == username) {
					found = true;
				}
			}
			if (!found) {
				if (adminLevel != 0) {
					Admin admin;
					admin.username = PlayerDB::getProperName(username);
					admin.password = pss;
					admin.level = adminLevel;
					admins.push_back(admin);
				}
			}
			ENetPeer* currentPeer;

			for (currentPeer = server->peers;
				currentPeer < &server->peers[server->peerCount];
				++currentPeer)
			{
				if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
					continue;
				if (currentPeer == peer)
					continue;
				if (((PlayerInfo*)(currentPeer->data))->rawName == PlayerDB::getProperName(username))
				{
					{
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("Someone else logged into this account!");
						p.CreatePacket(peer);
					}
					{
						gamepacket_t p;
						p.Insert("OnConsoleMessage");
						p.Insert("Someone else was logged into this account! He was kicked out now.");
						p.CreatePacket(peer);
					}
					enet_peer_disconnect_later(currentPeer, 0);
				}
			}
			return 1;
		}
		else {
			return -1;
		}
	}
	else {
		return -2;
	}
}

int PlayerDB::guildRegister(ENetPeer* peer, string guildName, string guildStatement, string guildFlagfg, string guildFlagbg) {
	if (guildName.find(" ") != string::npos || guildName.find(".") != string::npos || guildName.find(",") != string::npos || guildName.find("@") != string::npos || guildName.find("[") != string::npos || guildName.find("]") != string::npos || guildName.find("#") != string::npos || guildName.find("<") != string::npos || guildName.find(">") != string::npos || guildName.find(":") != string::npos || guildName.find("{") != string::npos || guildName.find("}") != string::npos || guildName.find("|") != string::npos || guildName.find("+") != string::npos || guildName.find("_") != string::npos || guildName.find("~") != string::npos || guildName.find("-") != string::npos || guildName.find("!") != string::npos || guildName.find("$") != string::npos || guildName.find("%") != string::npos || guildName.find("^") != string::npos || guildName.find("&") != string::npos || guildName.find("`") != string::npos || guildName.find("*") != string::npos || guildName.find("(") != string::npos || guildName.find(")") != string::npos || guildName.find("=") != string::npos || guildName.find("'") != string::npos || guildName.find(";") != string::npos || guildName.find("/") != string::npos) {
		return -1;
	}

	if (guildName.length() < 3) {
		return -2;
	}
	if (guildName.length() > 15) {
		return -3;
	}
	int fg;
	int bg;

	try {
		fg = stoi(guildFlagfg);
	}
	catch (std::invalid_argument& e) {
		return -6;
	}
	try {
		bg = stoi(guildFlagbg);
	}
	catch (std::invalid_argument& e) {
		return -5;
	}
	if (guildFlagbg.length() > 4) {
		return -7;
	}
	if (guildFlagfg.length() > 4) {
		return -8;
	}

	string fixedguildName = PlayerDB::getProperName(guildName);

	std::ifstream ifs("core/guilds/" + fixedguildName + ".json");
	if (ifs.is_open()) {
		return -4;
	}
	return 1;
}

int PlayerDB::playerRegister(ENetPeer* peer, string username, string password, string passwordverify, string email, string discord) {
	string name = username;
	if (name == "CON" || name == "PRN" || name == "AUX" || name == "NUL" || name == "COM1" || name == "COM2" || name == "COM3" || name == "COM4" || name == "COM5" || name == "COM6" || name == "COM7" || name == "COM8" || name == "COM9" || name == "LPT1" || name == "LPT2" || name == "LPT3" || name == "LPT4" || name == "LPT5" || name == "LPT6" || name == "LPT7" || name == "LPT8" || name == "LPT9") return -1;
	username = PlayerDB::getProperName(username);
	if (discord.find("#") == std::string::npos && discord.length() != 0) return -5;
	if (email.find("@") == std::string::npos && email.length() != 0) return -4;
	if (passwordverify != password) return -3;
	if (username.length() < 3) return -2;
	std::ifstream ifs("core/players/" + username + ".json");
	if (ifs.is_open()) {
		return -1;
	}

	std::ofstream o("core/players/" + username + ".json");
	if (!o.is_open()) {
		cout << GetLastError() << endl;
		_getch();
	}
	json j;
	j["username"] = username;
	j["password"] = password;
	j["email"] = email;
	j["discord"] = discord;
	j["adminLevel"] = 0;
	j["level"] = 1;
	j["xp"] = 0;
	j["ClothBack"] = 0;
	j["ClothHand"] = 0;
	j["ClothFace"] = 0;
	j["ClothShirt"] = 0;
	j["ClothPants"] = 0;
	j["ClothNeck"] = 0;
	j["ClothHair"] = 0;
	j["ClothFeet"] = 0;
	j["ClothMask"] = 0;
	j["ClothAnces"] = 0;
	j["guild"] = "";
	j["joinguild"] = false;
	j["premwl"] = 0;
	j["effect"] = 8421376;
	j["skinColor"] = 0x8295C3FF;
	j["worldsowned"] = ((PlayerInfo*)(peer->data))->createworldsowned;
	o << j << std::endl;
	std::ofstream oo("core/player/inventory/" + username + ".json");
	if (!oo.is_open()) {
		cout << GetLastError() << endl;
		_getch();
	}
	json items;
	json jjall = json::array();
	json jj;
	jj["aposition"] = 1;
	jj["itemid"] = 18;
	jj["quantity"] = 1;
	jjall.push_back(jj);
	jj["aposition"] = 2;
	jj["itemid"] = 32;
	jj["quantity"] = 1;
	jjall.push_back(jj);
	for (int i = 2; i < 200; i++)
	{
		jj["aposition"] = i + 1;
		jj["itemid"] = 0;
		jj["quantity"] = 0;
		jjall.push_back(jj);
	}
	items["items"] = jjall;
	oo << items << std::endl;

	return 1;
}

void savegem(ENetPeer* peer) {
	if (((PlayerInfo*)(peer->data))->haveGrowId == true) {
		PlayerInfo* p5 = ((PlayerInfo*)(peer->data));
		string username = PlayerDB::getProperName(p5->rawName);
		ifstream fg("core/players/gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		json j;
		fg >> j;
		fg.close();
		ofstream fs("core/players/gemdb/" + ((PlayerInfo*)(peer->data))->rawName + ".txt");
		fs << j;
		fs.close();
	}
}
void sendConsole(ENetPeer* x, string e) {
	GamePacket p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), e));
	ENetPacket* packet = enet_packet_create(p.data,
		p.len,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(x, 0, packet);
	delete p.data;
}

void savejson(ENetPeer* peer) {
	if (((PlayerInfo*)(peer->data))->haveGrowId == true) {
		PlayerInfo* p5 = ((PlayerInfo*)(peer->data));
		string username = PlayerDB::getProperName(p5->rawName);
		ifstream fg("core/players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		json j;
		fg >> j;
		fg.close();
		j["premwl"] = ((PlayerInfo*)(peer->data))->premwl;
		j["level"] = ((PlayerInfo*)(peer->data))->level;
		j["xp"] = ((PlayerInfo*)(peer->data))->xp;
		ofstream fs("core/players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		fs << j;
		fs.close();
	}
}

bool CheckItemMaxed(ENetPeer* peer, int fItemId, int fQuantityAdd) {
	bool isMaxed = false;
	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++) {
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemId && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount + fQuantityAdd > 200) {
			isMaxed = true;
			break;
		}
	}
	return isMaxed;
}

bool CheckItemExists(ENetPeer* peer, const int fItemId) {
	auto isExists = false;
	for (auto i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++) {
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemId) {
			isExists = true;
			break;
		}
	}
	return isExists;
}

void showWrong(ENetPeer* peer, string listFull, string itemFind) {
	packet::dialog(peer, "add_label_with_icon|big|`wFind item: " + itemFind + "``|left|3802|\nadd_spacer|small|\n" + listFull + "add_textbox|Enter a word below to find the item|\nadd_text_input|item|Item Name||30|\nend_dialog|findid|Cancel|Find the item!|\n");
}

void addAdmin(string username, string password, int level)
{
	Admin admin;
	admin.username = username;
	admin.password = password;
	admin.level = level;
	admins.push_back(admin);
}

int getAdminLevel(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password) {
			return admin.level;
		}
	}
	return 0;
}

int adminlevel(string name) {
	std::ifstream ifff("core/players/" + PlayerDB::getProperName(name) + ".json");
	json j;
	ifff >> j;

	int adminlevel;
	adminlevel = j["adminLevel"];

	ifff.close();
	if (adminlevel == 0) {
		return 0;
	}
	else {
		return adminlevel;
	}

}
int level(string name) {
	std::ifstream ifff("core/players/" + PlayerDB::getProperName(name) + ".json");
	json j;
	ifff >> j;

	int level;
	level = j["level"];

	ifff.close();
	return level;

}

string getRankText(string name) {
	int lvl = 0;
	lvl = adminlevel(name);
	if (lvl == 0) {
		return "`wPlayer";
	}
	if (lvl == 444) {
		return "`w[`1VIP`w]";
	}
	else if (lvl == 666) {
		return "`#Moderator";
	}
	else if (lvl == 777) {
		return "`4Administrator";
	}
	else if (lvl == 999) {
		return "`4CO-Creator";
	}
	else if (lvl == 1337) {
		return "`cServer-Creator";
	}
}
string getRankId(string name) {
	int lvl = 0;
	lvl = adminlevel(name);
	if (lvl == 0) {
		return "18";
	}
	if (lvl == 444) {
		return "274";
	}
	else if (lvl == 666) {
		return "278";
	}
	else if (lvl == 777) {
		return "276";
	}
	else if (lvl == 999) {
		return "1956";
	}
	else if (lvl == 1337) {
		return "2376";
	}
}
string getRankTexts(string name) {
	int lvl = 0;
	lvl = level(name);
	if (lvl <= 10) {
		return "`2Newbie";
	}
	if (lvl >= 11) {
		return "`1Advance";
	}
	if (lvl >= 50) {
		return "`cPro";
	}
	if (lvl >= 100) {
		return "`eMaster";
	}
	if (lvl >= 150) {
		return "`9Expert";
	}
	if (lvl >= 200) {
		return "`5A`4C`qE";
	}
}
string getRankIds(string name) {
	int lvl = 0;
	lvl = level(name);
	if (lvl <= 10) {
		return "3900";
	}
	if (lvl >= 11) {
		return "3192";
	}
	if (lvl >= 50) {
		return "7832";
	}
	if (lvl >= 100) {
		return "7586";
	}
	if (lvl >= 150) {
		return "6312";
	}
	if (lvl >= 200) {
		return "1956";
	}
}

bool canSB(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password && admin.level > 1) {
			using namespace std::chrono;
			if (admin.lastSB + 900000 < (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count() || admin.level == 999)
			{
				admins[i].lastSB = (duration_cast<milliseconds>(system_clock::now().time_since_epoch())).count();
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool canClear(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password) {
			return admin.level > 0;
		}
	}
	return false;
}

bool isSuperAdmin(string username, string password) {
	for (int i = 0; i < admins.size(); i++) {
		Admin admin = admins[i];
		if (admin.username == username && admin.password == password && admin.level == 999) {
			return true;
		}
	}
	return false;
}

bool isHere(ENetPeer* peer, ENetPeer* peer2)
{
	return ((PlayerInfo*)(peer->data))->currentWorld == ((PlayerInfo*)(peer2->data))->currentWorld;
}

void sendInventory(ENetPeer* peer, PlayerInventory inventory)
{
	string asdf2 = "0400000009A7379237BB2509E8E0EC04F8720B050000000000000000FBBB0000010000007D920100FDFDFDFD04000000040000000000000000000000000000000000";
	int inventoryLen = inventory.items.size();
	int packetLen = (asdf2.length() / 2) + (inventoryLen * 4) + 4;
	BYTE* data2 = new BYTE[packetLen];
	for (int i = 0; i < asdf2.length(); i += 2)
	{
		char x = ch2n(asdf2[i]);
		x = x << 4;
		x += ch2n(asdf2[i + 1]);
		memcpy(data2 + (i / 2), &x, 1);
	}
	int endianInvVal = _byteswap_ulong(inventoryLen);
	memcpy(data2 + (asdf2.length() / 2) - 4, &endianInvVal, 4);
	endianInvVal = _byteswap_ulong(((PlayerInfo*)(peer->data))->currentInventorySize);
	memcpy(data2 + (asdf2.length() / 2) - 8, &endianInvVal, 4);
	int val = 0;
	for (int i = 0; i < inventoryLen; i++)
	{
		val = 0;
		val |= inventory.items.at(i).itemID;
		val |= inventory.items.at(i).itemCount << 16;
		val &= 0x00FFFFFF;
		val |= 0x00 << 24;
		memcpy(data2 + (i * 4) + (asdf2.length() / 2), &val, 4);
	}
	ENetPacket* packet3 = enet_packet_create(data2,
		packetLen,
		ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet3);
	delete data2;
}

void sendGazette(ENetPeer* peer) {
	std::ifstream news("news.txt");
	std::stringstream buffer;
	buffer << news.rdbuf();
	std::string newsString(buffer.str());
	packet::dialog(peer, newsString);
}
bool SaveConvertedItem(int fItemid, int fQuantity, ENetPeer* peer)
{
	int invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;

	bool doesItemInInventryAlready = false;

	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items[i].itemID == fItemid)
		{
			doesItemInInventryAlready = true;
			if (((PlayerInfo*)(peer->data))->inventory.items[i].itemCount >= 101) return false;
			break;
		}
	}

	std::ifstream iffff("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");

	json jj;

	if (iffff.fail()) {
		iffff.close();
		cout << "SaveConvertedItem funkcijoje (ifstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;

	}
	if (iffff.is_open()) {


	}

	iffff >> jj; //load


	std::ofstream oo("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
	if (!oo.is_open()) {
		cout << GetLastError() << " SaveConvertedItem funkcijoje (ofstream dalyje) error: itemid - " << fItemid << ", kiekis - " << fQuantity << endl;
		_getch();
	}
	int howManyHasNow = 0;

	for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
	{
		int itemidFromJson = jj["items"][i]["itemid"];
		int quantityFromJson = jj["items"][i]["quantity"];;
		if (doesItemInInventryAlready)
		{
			if (itemidFromJson == fItemid)
			{
				howManyHasNow = jj["items"][i]["quantity"];
				howManyHasNow += fQuantity;
				jj["items"][i]["quantity"] = howManyHasNow;

				for (int k = 0; k < ((PlayerInfo*)(peer->data))->inventory.items.size(); k++)
				{
					if (((PlayerInfo*)(peer->data))->inventory.items[k].itemID == fItemid)
					{
						((PlayerInfo*)(peer->data))->inventory.items[k].itemCount += (byte)fQuantity;
						break;
					}
				}
				sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);

				break;
			}
		}
		else if (itemidFromJson == 0 && quantityFromJson == 0)
		{
			jj["items"][i]["quantity"] = fQuantity;
			jj["items"][i]["itemid"] = fItemid;

			InventoryItem item;
			item.itemID = fItemid;
			item.itemCount = fQuantity;
			((PlayerInfo*)(peer->data))->inventory.items.push_back(item);

			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);

			break;
		}
	}

	oo << jj << std::endl;
	return true;
}
void RemoveInventoryItem(int fItemid, int fQuantity, ENetPeer* peer)
{
	std::ifstream iffff("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");

	json jj;

	if (iffff.fail()) {
		iffff.close();

	}
	if (iffff.is_open()) {


	}

	iffff >> jj; //load


	std::ofstream oo("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
	if (!oo.is_open()) {
		cout << GetLastError() << " Gak bisa delete " << fItemid << " bruh" << fQuantity << endl;
		_getch();
	}


	for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
	{
		int itemid = jj["items"][i]["itemid"];
		int quantity = jj["items"][i]["quantity"];
		if (itemid == fItemid)
		{
			if (quantity - fQuantity == 0)
			{
				jj["items"][i]["itemid"] = 0;
				jj["items"][i]["quantity"] = 0;
			}
			else
			{
				jj["items"][i]["itemid"] = itemid;
				jj["items"][i]["quantity"] = quantity - fQuantity;
			}

			break;
		}

	}
	oo << jj << std::endl;

	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
		{
			if ((unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount > fQuantity && (unsigned int)((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount != fQuantity)
			{
				((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount -= fQuantity;
			}
			else
			{
				((PlayerInfo*)(peer->data))->inventory.items.erase(((PlayerInfo*)(peer->data))->inventory.items.begin() + i);
			}
			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
	}


}
void SearchInventoryItem(ENetPeer* peer, int fItemid, int fQuantity, bool& iscontains)
{
	iscontains = false;
	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{
		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount >= fQuantity) {

			iscontains = true;
			break;
		}
	}
}
void SaveFindsItem(int fItemid, int fQuantity, ENetPeer* peer)
{

	std::ifstream iffff("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");

	json jj;

	if (iffff.fail()) {
		iffff.close();


	}
	if (iffff.is_open()) {


	}

	iffff >> jj; //load


	std::ofstream oo("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
	if (!oo.is_open()) {
		cout << GetLastError() << endl;
		_getch();
	}

	//jj["items"][aposition]["aposition"] = aposition;

	for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
	{
		int itemid = jj["items"][i]["itemid"];
		int quantity = jj["items"][i]["quantity"];
		if (itemid == 0 && quantity == 0)
		{
			jj["items"][i]["itemid"] = fItemid;
			jj["items"][i]["quantity"] = fQuantity;
			break;
		}

	}
	oo << jj << std::endl;


	InventoryItem item;
	item.itemID = fItemid;
	item.itemCount = fQuantity;
	((PlayerInfo*)(peer->data))->inventory.items.push_back(item);

	sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
}
void SaveShopsItemMoreTimes(int fItemid, int fQuantity, ENetPeer* peer, bool& success)
{
	size_t invsizee = ((PlayerInfo*)(peer->data))->currentInventorySize;
	bool invfull = false;
	bool alreadyhave = false;


	if (((PlayerInfo*)(peer->data))->inventory.items.size() == invsizee) {

		GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1432|\nadd_spacer|small|\nadd_textbox|`oSorry! Your inventory is full! You can purchase an inventory upgrade in the shop.|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
		ENetPacket* packet = enet_packet_create(ps.data,
			ps.len,
			ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
		delete ps.data;


		alreadyhave = true;
	}

	bool isFullStock = false;
	bool isInInv = false;
	for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
	{

		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount >= 200) {


			GamePacket ps = packetEnd(appendString(appendString(createPacket(), "OnDialogRequest"), "add_label_with_icon|big|`4Whoops!|left|1432|\nadd_spacer|small|\nadd_textbox|`oSorry! You already have full stock of this item!|\nadd_spacer|small|\nadd_button|close|`5Close|0|0|"));
			ENetPacket* packet = enet_packet_create(ps.data,
				ps.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
			delete ps.data;


			isFullStock = true;
		}

		if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid && ((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount < 200)	isInInv = true;

	}

	if (isFullStock == true || alreadyhave == true)
	{
		success = false;
	}
	else
	{
		success = true;

		std::ifstream iffff("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");

		json jj;

		if (iffff.fail()) {
			iffff.close();


		}
		if (iffff.is_open()) {


		}

		iffff >> jj; //load


		std::ofstream oo("core/players/inventory/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
		if (!oo.is_open()) {
			cout << GetLastError() << endl;
			_getch();
		}
		if (isInInv == false)
		{

			for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
			{
				int itemid = jj["items"][i]["itemid"];
				int quantity = jj["items"][i]["quantity"];

				if (itemid == 0 && quantity == 0)
				{
					jj["items"][i]["itemid"] = fItemid;
					jj["items"][i]["quantity"] = fQuantity;
					break;
				}

			}
			oo << jj << std::endl;


			InventoryItem item;
			item.itemID = fItemid;
			item.itemCount = fQuantity;
			((PlayerInfo*)(peer->data))->inventory.items.push_back(item);

			sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
		}
		else
		{
			for (int i = 0; i < ((PlayerInfo*)(peer->data))->currentInventorySize; i++)
			{
				int itemid = jj["items"][i]["itemid"];
				int quantity = jj["items"][i]["quantity"];

				if (itemid == fItemid)
				{
					jj["items"][i]["quantity"] = quantity + fQuantity;
					break;
				}

			}
			oo << jj << std::endl;


			for (int i = 0; i < ((PlayerInfo*)(peer->data))->inventory.items.size(); i++)
			{
				if (((PlayerInfo*)(peer->data))->inventory.items.at(i).itemID == fItemid)
				{
					((PlayerInfo*)(peer->data))->inventory.items.at(i).itemCount += fQuantity;
					sendInventory(peer, ((PlayerInfo*)(peer->data))->inventory);
				}
			}

		}
	}
}

void removeAcc(ENetPeer* peer, string name) {
	string resetacc;
	std::ifstream ifff("core/players/" + PlayerDB::getProperName(name) + ".json");
	json j;
	ifff >> j;
}
void sendGrowmojis(ENetPeer* peer) {
	std::ifstream emoji("growmoji.txt");
	std::stringstream buffer;
	buffer << emoji.rdbuf();
	std::string newsString(buffer.str());
	packet::dialog(peer, newsString);
}

BYTE* packPlayerMoving(PlayerMoving* dataStruct)
{
	BYTE* data = new BYTE[56];
	for (int i = 0; i < 56; i++)
	{
		data[i] = 0;
	}
	memcpy(data, &dataStruct->packetType, 4);
	memcpy(data + 4, &dataStruct->netID, 4);
	memcpy(data + 12, &dataStruct->characterState, 4);
	memcpy(data + 20, &dataStruct->plantingTree, 4);
	memcpy(data + 24, &dataStruct->x, 4);
	memcpy(data + 28, &dataStruct->y, 4);
	memcpy(data + 32, &dataStruct->XSpeed, 4);
	memcpy(data + 36, &dataStruct->YSpeed, 4);
	memcpy(data + 44, &dataStruct->punchX, 4);
	memcpy(data + 48, &dataStruct->punchY, 4);
	return data;
}

PlayerMoving* unpackPlayerMoving(BYTE* data)
{
	PlayerMoving* dataStruct = new PlayerMoving;
	memcpy(&dataStruct->packetType, data, 4);
	memcpy(&dataStruct->netID, data + 4, 4);
	memcpy(&dataStruct->characterState, data + 12, 4);
	memcpy(&dataStruct->plantingTree, data + 20, 4);
	memcpy(&dataStruct->x, data + 24, 4);
	memcpy(&dataStruct->y, data + 28, 4);
	memcpy(&dataStruct->XSpeed, data + 32, 4);
	memcpy(&dataStruct->YSpeed, data + 36, 4);
	memcpy(&dataStruct->punchX, data + 44, 4);
	memcpy(&dataStruct->punchY, data + 48, 4);
	return dataStruct;
}

void sendState(ENetPeer* peer) {
	PlayerInfo* info = ((PlayerInfo*)(peer->data));
	int netID = info->netID;
	ENetPeer* currentPeer;
	int state = getState(info);
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = 0;
			data.x = 1000;
			data.y = 100;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 600;
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = info->peffect;
			memcpy(raw + 1, &var, 3);
			float waterspeed = 125.0f;
			memcpy(raw + 16, &waterspeed, 4);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}

void SendDropSingle(ENetPeer* peer, int netID, int x, int y, int item, int count, BYTE specialEffect)
{
	if (item >= maxItems) return;
	if (item < 0) return;

	PlayerMoving data;
	data.packetType = 14;
	data.x = x;
	data.y = y;
	data.netID = netID;
	data.plantingTree = item;
	float val = count;
	BYTE val2 = specialEffect;

	BYTE* raw = packPlayerMoving(&data);
	memcpy(raw + 16, &val, 4);
	memcpy(raw + 1, &val2, 1);

	SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}

void onPeerConnect(ENetPeer* peer)
{
	ENetPeer* currentPeer;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				string netIdS = std::to_string(((PlayerInfo*)(currentPeer->data))->netID);
				packet::onspawn(peer, "spawn|avatar\nnetID|" + netIdS + "\nuserID|" + netIdS + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(((PlayerInfo*)(currentPeer->data))->x) + "|" + std::to_string(((PlayerInfo*)(currentPeer->data))->y) + "\nname|``" + ((PlayerInfo*)(currentPeer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(currentPeer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\n"); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
				string netIdS2 = std::to_string(((PlayerInfo*)(peer->data))->netID);
				packet::onspawn(currentPeer, "spawn|avatar\nnetID|" + netIdS2 + "\nuserID|" + netIdS2 + "\ncolrect|0|0|20|30\nposXY|" + std::to_string(((PlayerInfo*)(peer->data))->x) + "|" + std::to_string(((PlayerInfo*)(peer->data))->y) + "\nname|``" + ((PlayerInfo*)(peer->data))->displayName + "``\ncountry|" + ((PlayerInfo*)(peer->data))->country + "\ninvis|0\nmstate|0\nsmstate|0\n"); // ((PlayerInfo*)(server->peers[i].data))->tankIDName
			}
		}
	}

}

void updateAllClothes(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			GamePacket p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants), ((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand), ((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace), ((PlayerInfo*)(peer->data))->skinColor), ((PlayerInfo*)(peer->data))->cloth_ances, 0.0f, 0.0f));
			memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4);
			ENetPacket* packet3 = enet_packet_create(p3.data,
				p3.len,
				ENET_PACKET_FLAG_RELIABLE);

			enet_peer_send(currentPeer, 0, packet3);
			delete p3.data;
			GamePacket p4 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(currentPeer->data))->cloth_hair, ((PlayerInfo*)(currentPeer->data))->cloth_shirt, ((PlayerInfo*)(currentPeer->data))->cloth_pants), ((PlayerInfo*)(currentPeer->data))->cloth_feet, ((PlayerInfo*)(currentPeer->data))->cloth_face, ((PlayerInfo*)(currentPeer->data))->cloth_hand), ((PlayerInfo*)(currentPeer->data))->cloth_back, ((PlayerInfo*)(currentPeer->data))->cloth_mask, ((PlayerInfo*)(currentPeer->data))->cloth_necklace), ((PlayerInfo*)(currentPeer->data))->skinColor), ((PlayerInfo*)(currentPeer->data))->cloth_ances, 0.0f, 0.0f));
			memcpy(p4.data + 8, &(((PlayerInfo*)(currentPeer->data))->netID), 4);
			ENetPacket* packet4 = enet_packet_create(p4.data,
				p4.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet4);
			delete p4.data;
		}
	}
}

void sendClothes(ENetPeer* peer) {
	GamePacket p3 = packetEnd(appendFloat(appendIntx(appendFloat(appendFloat(appendFloat(appendString(createPacket(), "OnSetClothing"), ((PlayerInfo*)(peer->data))->cloth_hair, ((PlayerInfo*)(peer->data))->cloth_shirt, ((PlayerInfo*)(peer->data))->cloth_pants), ((PlayerInfo*)(peer->data))->cloth_feet, ((PlayerInfo*)(peer->data))->cloth_face, ((PlayerInfo*)(peer->data))->cloth_hand), ((PlayerInfo*)(peer->data))->cloth_back, ((PlayerInfo*)(peer->data))->cloth_mask, ((PlayerInfo*)(peer->data))->cloth_necklace), ((PlayerInfo*)(peer->data))->skinColor), ((PlayerInfo*)(peer->data))->cloth_ances, 0.0f, 0.0f));
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			string text = "action|play_sfx\nfile|audio/change_clothes.wav\ndelayMS|0\n";
			BYTE* data = new BYTE[5 + text.length()];
			BYTE zero = 0;
			int type = 3;
			memcpy(data, &type, 4);
			memcpy(data + 4, text.c_str(), text.length());
			memcpy(data + 4 + text.length(), &zero, 1);
			ENetPacket* packet2 = enet_packet_create(data,
				5 + text.length(),
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
			delete[] data;
			memcpy(p3.data + 8, &(((PlayerInfo*)(peer->data))->netID), 4); // ffloor
			ENetPacket* packet3 = enet_packet_create(p3.data,
				p3.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet3);
		}
	}
	ifstream fg("core/players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
	json j;
	fg >> j;
	fg.close();
	PlayerInfo* p = ((PlayerInfo*)(peer->data));
	string username = PlayerDB::getProperName(p->rawName);
	int wls = p->premwl;
	int clothback = p->cloth_back;
	int clothhand = p->cloth_hand;
	int clothface = p->cloth_face;
	int clothhair = p->cloth_hair;
	int clothfeet = p->cloth_feet;
	int clothpants = p->cloth_pants;
	int clothneck = p->cloth_necklace;
	int clothshirt = p->cloth_shirt;
	int clothmask = p->cloth_mask;
	int clothances = p->cloth_ances;
	j["ClothBack"] = clothback;
	j["ClothHand"] = clothhand;
	j["ClothFace"] = clothface;
	j["ClothShirt"] = clothshirt;
	j["ClothPants"] = clothpants;
	j["ClothNeck"] = clothneck;
	j["ClothHair"] = clothhair;
	j["ClothFeet"] = clothfeet;
	j["ClothMask"] = clothmask;
	j["ClothAnces"] = clothances;
	j["effect"] = p->peffect;
	j["premwl"] = p->premwl;
	j["worldsowned"] = ((PlayerInfo*)(peer->data))->worldsowned;
	ofstream fs("core/players/" + ((PlayerInfo*)(peer->data))->rawName + ".json");
	fs << j;
	fs.close();
}
void sendEmoji(ENetPeer* peer, string emoji)
{
	GamePacket p2ssw = packetEnd(appendString(appendInt(appendString(createPacket(), "OnEmoticonDataChanged"), 0), u8"(wl)|ā|1&(yes)|Ă|1&(no)|ă|1&(love)|Ą|1&(oops)|ą|1&(shy)|Ć|1&(wink)|ć|1&(tongue)|Ĉ|1&(agree)|ĉ|1&(sleep)|Ċ|1&(punch)|ċ|1&(music)|Č|1&(build)|č|1&(megaphone)|Ď|1&(sigh)|ď|1&(mad)|Đ|1&(wow)|đ|1&(dance)|Ē|1&(see-no-evil)|ē|1&(bheart)|Ĕ|1&(heart)|ĕ|1&(grow)|Ė|1&(gems)|ė|1&(kiss)|Ę|1&(gtoken)|ę|1&(lol)|Ě|1&(smile)|Ā|1&(cool)|Ĝ|1&(cry)|ĝ|1&(vend)|Ğ|1&(bunny)|ě|1&(cactus)|ğ|1&(pine)|Ĥ|1&(peace)|ģ|1&(terror)|ġ|1&(troll)|Ġ|1&(evil)|Ģ|1&(fireworks)|Ħ|1&(football)|ĥ|1&(alien)|ħ|1&(party)|Ĩ|1&(pizza)|ĩ|1&(clap)|Ī|1&(song)|ī|1&(ghost)|Ĭ|1&(nuke)|ĭ|1&(halo)|Į|1&(turkey)|į|1&(gift)|İ|1&(cake)|ı|1&(heartarrow)|Ĳ|1&(lucky)|ĳ|1&(shamrock)|Ĵ|1&(grin)|ĵ|1&(ill)|Ķ|1&"));
	ENetPacket* packet2ssw = enet_packet_create(p2ssw.data, p2ssw.len, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet2ssw);
	delete p2ssw.data;
}

void sendPData(ENetPeer* peer, PlayerMoving* data)
{
	ENetPeer* currentPeer;

	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (peer != currentPeer)
		{
			if (isHere(peer, currentPeer))
			{
				data->netID = ((PlayerInfo*)(peer->data))->netID;

				SendPacketRaw(4, packPlayerMoving(data), 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
			}
		}
	}
}

void sendPuncheffect(ENetPeer* peer) {
	PlayerInfo* info = ((PlayerInfo*)(peer->data));
	int netID = info->netID;
	int state = getState(info);
	int pro = getState(info);
	int statey = 0;
	if (info->cloth_hand == 6028) statey = 1024;
	if (info->cloth_hand == 6262) statey = 8192;
	if (info->haveGrowId == false) statey = 50000;
	for (ENetPeer* currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			PlayerMoving data;
			data.packetType = 0x14;
			data.characterState = statey;
			data.x = 1000;
			data.y = 100;
			data.punchX = 0;
			data.punchY = 0;
			data.XSpeed = 300;
			data.YSpeed = 600;
			data.netID = netID;
			data.plantingTree = state;
			BYTE* raw = packPlayerMoving(&data);
			int var = info->peffect;
			memcpy(raw + 1, &var, 3);
			SendPacketRaw(4, raw, 56, 0, currentPeer, ENET_PACKET_FLAG_RELIABLE);
		}
	}
}
void sendPuncheffectpeer(ENetPeer* peer, int punch) {
	PlayerInfo* info = ((PlayerInfo*)(peer->data));
	int netID = info->netID;
	int state = getState(info);
	PlayerMoving data;
	float water = 125.0f;
	data.packetType = 0x14;
	data.characterState = ((PlayerInfo*)(peer->data))->characterState; // animation
	data.x = 1000;
	if (((PlayerInfo*)(peer->data))->cloth_hand == 366) {
		data.y = -400;
	}
	else {
		data.y = 400;
	}
	data.punchX = -1;
	data.punchY = -1;
	data.XSpeed = 300;
	if (((PlayerInfo*)(peer->data))->cloth_back == 9472) {
		data.YSpeed = 600;
	}
	else {
		data.YSpeed = 1150;
	}
	data.netID = netID;
	data.plantingTree = state;
	BYTE* raw = packPlayerMoving(&data);
	int var = punch;
	memcpy(raw + 1, &var, 3);
	memcpy(raw + 16, &water, 4);
	SendPacketRaw(4, raw, 56, 0, peer, ENET_PACKET_FLAG_RELIABLE);
}

string packPlayerMoving2(PlayerMoving* dataStruct)
{
	string data;
	data.resize(56);
	STRINT(data, 0) = dataStruct->packetType;
	STRINT(data, 4) = dataStruct->netID;
	STRINT(data, 12) = dataStruct->characterState;
	STRINT(data, 20) = dataStruct->plantingTree;
	STRINT(data, 24) = *(int*)&dataStruct->x;
	STRINT(data, 28) = *(int*)&dataStruct->y;
	STRINT(data, 32) = *(int*)&dataStruct->XSpeed;
	STRINT(data, 36) = *(int*)&dataStruct->YSpeed;
	STRINT(data, 44) = dataStruct->punchX;
	STRINT(data, 48) = dataStruct->punchY;
	return data;
}

inline void sendWrongCmdLog(ENetPeer* peer)
{
	packet::consolemessage(peer, "`4Unknown command. `oEnter `$/help `ofor a list of valid commands.");
}

void sendChatMessage(ENetPeer* peer, int netID, string message)
{
	if (message.length() == 0) return;
	for (char c : message);
	string name = "";
	ENetPeer* currentPeer;
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (((PlayerInfo*)(currentPeer->data))->netID == netID)
			name = ((PlayerInfo*)(currentPeer->data))->displayName;
	}
	GamePacket p;
	GamePacket p2;
	if (((PlayerInfo*)(peer->data))->adminLevel == 1337) {
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `o<`w" + name + "`o> `5" + message));
		p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`5" + message), 0));
	}
	else if (((PlayerInfo*)(peer->data))->adminLevel == 999) {
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `o<`w" + name + "`o> `c" + message));
		p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`c" + message), 0));
	}
	else if (((PlayerInfo*)(peer->data))->adminLevel == 777) {
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `o<`w" + name + "`o> `2" + message));
		p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`2" + message), 0));
	}
	else if (((PlayerInfo*)(peer->data))->adminLevel == 666) {
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `o<`w" + name + "`o> `^" + message));
		p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`^" + message), 0));
	}
	else if (((PlayerInfo*)(peer->data))->adminLevel == 444) {
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `o<`w" + name + "`o> `1" + message));
		p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`1" + message), 0));
	}
	else if (((PlayerInfo*)(peer->data))->adminLevel == 111) {
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `o<`w" + name + "`o> `9" + message));
		p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), "`9" + message), 0));
	}
	else {
		p = packetEnd(appendString(appendString(createPacket(), "OnConsoleMessage"), "CP:_PL:0_OID:_CT:[W]_ `o<`w" + name + "`o> " + message));
		p2 = packetEnd(appendIntx(appendString(appendIntx(appendString(createPacket(), "OnTalkBubble"), netID), message), 0));
	}
	for (currentPeer = server->peers; currentPeer < &server->peers[server->peerCount]; ++currentPeer) {
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED) continue;
		if (isHere(peer, currentPeer)) {
			ENetPacket* packet = enet_packet_create(p.data,
				p.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet);
			ENetPacket* packet2 = enet_packet_create(p2.data,
				p2.len,
				ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(currentPeer, 0, packet2);
		}
	}
	delete p.data;
	delete p2.data;
}

void sendWho(ENetPeer* peer)
{
	ENetPeer* currentPeer;
	string name = "";
	for (currentPeer = server->peers;
		currentPeer < &server->peers[server->peerCount];
		++currentPeer)
	{
		if (currentPeer->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (isHere(peer, currentPeer))
		{
			if (((PlayerInfo*)(currentPeer->data))->isGhost)
				continue;

			gamepacket_t p;
			p.Insert("OnTalkBubble");
			p.Insert(((PlayerInfo*)(currentPeer->data))->netID);
			p.Insert(((PlayerInfo*)(currentPeer->data))->displayName);
			p.Insert(1);
			p.CreatePacket(peer);
		}
	}
}

void addItemToInventory(ENetPeer* peer, int id) {
	PlayerInventory inventory = ((PlayerInfo*)(peer->data))->inventory;
	for (int i = 0; i < inventory.items.size(); i++) {
		if (inventory.items[i].itemID == id && inventory.items[i].itemCount < 200) {
			inventory.items[i].itemCount++;
			return;
		}
	}
	if (inventory.items.size() >= inventory.inventorySize)
		return;
	InventoryItem item;
	item.itemCount = 1;
	item.itemID = id;
	inventory.items.push_back(item);
}

int getSharedUID(ENetPeer* peer, int itemNetID) {
	auto v = ((PlayerInfo*)(peer->data))->item_uids;
	for (auto t = v.begin(); t != v.end(); ++t) {
		if (t->actual_uid == itemNetID) {
			return t->shared_uid;
		}
	}
	return 0;
}

int checkForUIDMatch(ENetPeer* peer, int itemNetID) {
	auto v = ((PlayerInfo*)(peer->data))->item_uids;
	for (auto t = v.begin(); t != v.end(); ++t) {
		if (t->shared_uid == itemNetID) {
			return t->actual_uid;
		}
	}
	return 0;
}
