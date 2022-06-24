#ifndef GAME_SERVER_ENTITIES_WINGS_H
#define GAME_SERVER_ENTITIES_WINGS_H

#include <game/server/entity.h>
#include <game/server/gamecontext.h>

class CWings : public CEntity
{
	vec2 m_Poss[80];
	int m_IDs[80];

	int m_ClientID;

public:
	CWings(CGameWorld* pGameWorld, vec2 Pos, int ClientID);
	~CWings();

	virtual void Tick();
	virtual void Snap(int SnappingClient);
};

#endif
