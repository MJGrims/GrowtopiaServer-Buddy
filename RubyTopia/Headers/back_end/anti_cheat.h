#pragma once

void PathFindingCore(ENetPeer* peer, int xs, int ys)
{

	try {
		int Square = xs + (ys * 100);
		string gayname = ((PlayerInfo*)(peer->data))->rawName;
		WorldInfo* world = getPlyersWorld(peer);
		if (world->items[Square].PosFind == Square)
		{
			packet::consolemessage(peer, "`4[CHEAT DETECTED] " + gayname + " STOP CHEATING!");
			enet_peer_disconnect_later(peer, 0);
		}

	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
}