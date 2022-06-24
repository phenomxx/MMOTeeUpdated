#ifndef GAME_SERVER_ENTITIES_PIXI_H
#define GAME_SERVER_ENTITIES_PIXI_H

#include <game/server/entity.h>

class CPixi : public CEntity
{
	vec2 m_Motion;
	int m_NextChangeMotionTick;
	vec2 m_SpawnPosition;

public:
	int m_SpawnTick;

	CPixi(CGameWorld* pGameWorld, vec2 Pos);

	virtual void Tick();
	virtual void Snap(int SnappingClient);
};

#endif
