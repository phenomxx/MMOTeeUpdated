/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <game/server/gamecontext.h>
#include "pixi.h"

CPixi::CPixi(CGameWorld* pGameWorld, vec2 Pos)
	: CEntity(pGameWorld, CGameWorld::ENTTYPE_PIXI)
{
	m_Pos = Pos;
	m_Motion = vec2(0, 0);
	m_SpawnTick = -1;
	m_SpawnPosition = m_Pos;
	GameWorld()->InsertEntity(this);
}

void CPixi::Tick()
{
	if (m_SpawnTick != -1) {
		if (m_SpawnTick <= Server()->Tick())
			m_SpawnTick = -1;

		return;
	}

	if (Server()->Tick() >= m_NextChangeMotionTick) {
		m_NextChangeMotionTick = Server()->Tick() + rand() % 100;

		m_Motion = vec2(-1 + rand() % 3, -1 + rand() % 3);
	}
	if (GameServer()->Collision()->CheckPoint(m_Pos + m_Motion)) {
		m_Motion = -m_Motion;
	}

	for (int i = 0; i < GameServer()->m_PixiBarriers.size(); i++) {
		if (distance(GameServer()->m_PixiBarriers[i], m_Pos) <= 32.f) {
			m_Pos = m_SpawnPosition;
		}
	}

	m_Pos += m_Motion * 2;
}

void CPixi::Snap(int SnappingClient)
{
	if (m_SpawnTick != -1)
		return;
	if (NetworkClipped(SnappingClient))
		return;

	CNetObj_Projectile* pObj = static_cast<CNetObj_Projectile*>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_ID, sizeof(CNetObj_Projectile)));
	if (!pObj)
		return;

	pObj->m_Type = WEAPON_HAMMER;
	pObj->m_X = (int)m_Pos.x;
	pObj->m_Y = (int)m_Pos.y;
	pObj->m_VelX = 0;
	pObj->m_VelY = 0;
	pObj->m_StartTick = Server()->Tick();
}
