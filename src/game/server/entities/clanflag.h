#ifndef GAME_SERVER_ENTITIES_CLANFLAG_H
#define GAME_SERVER_ENTITIES_CLANFLAG_H

#include <game/server/entity.h>

class CClanFlag : public CEntity
{
private:
	bool m_Hidden;
	int m_CoolDownTick;
	int m_ClanID;
	bool m_Cap;
	int m_CapTick;

public:
	int m_Radius = 32 * 7; // 7 blocks

	CClanFlag(CGameWorld* pGameWorld, vec2 Pos);

	virtual void Tick();
	virtual void Snap(int SnappingClient);
};

#endif
