/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_ENTITIES_PET_H
#define GAME_SERVER_ENTITIES_PET_H

#include <game/server/entity.h>

class CPet : public CEntity
{
private:
	int m_OwnerID;
	int m_Type;

	enum { NUM_PARTICLES_AROUND_PET = 5, NUM_PARTICLES_AROUND_IGOR = 5 };

	int m_IDs[NUM_PARTICLES_AROUND_PET + NUM_PARTICLES_AROUND_IGOR + 1];

public:
	CPet(CGameWorld* pGameWorld, vec2 Pos, int OwnerID, int Type);
	~CPet();

	virtual void Tick();
	virtual void Snap(int SnappingClient);
};

#endif
