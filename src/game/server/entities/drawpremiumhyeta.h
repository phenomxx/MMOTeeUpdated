#ifndef GAME_SERVER_ENTITIES_DRAWPREMIUMHYETA_H
#define GAME_SERVER_ENTITIES_DRAWPREMIUMHYETA_H

#include <game/server/entity.h>

class CDrawPremiumHyeta : public CEntity
{
private:
	enum { NUM_PREMIUM_PARTICLES = 8, NUM_PREMIUM_HYETA = 6 };
	int m_IDs[NUM_PREMIUM_PARTICLES + NUM_PREMIUM_HYETA];

	int m_OwnerID;

public:
	CDrawPremiumHyeta(CGameWorld* pGameWorld, int TargetID);
	~CDrawPremiumHyeta();

	virtual void Tick();
	virtual void Snap(int SnappingClient);
};

#endif
