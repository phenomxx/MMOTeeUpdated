#include <game/server/gamecontext.h>
#include "clanflag.h"

CClanFlag::CClanFlag(CGameWorld* pGameWorld, vec2 Pos)
	: CEntity(pGameWorld, CGameWorld::ENTTYPE_CLANFLAG)
{
	m_Pos = Pos;
	m_ClanID = 0;
	m_Cap = false;
	m_CapTick = 0;

	GameWorld()->InsertEntity(this);
}

void CClanFlag::Tick()
{
	
}

void CClanFlag::Snap(int SnappingClient)
{
	if (NetworkClipped(SnappingClient))
		return;

	CNetObj_Flag* pFlag = (CNetObj_Flag*)Server()->SnapNewItem(NETOBJTYPE_FLAG, TEAM_BLUE, sizeof(CNetObj_Flag));
	if (!pFlag)
		return;

	pFlag->m_X = (int)m_Pos.x;
	pFlag->m_Y = (int)m_Pos.y + 16.0f;
	pFlag->m_Team = TEAM_BLUE;
}
