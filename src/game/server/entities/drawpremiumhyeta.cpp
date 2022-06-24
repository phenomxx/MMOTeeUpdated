#include <game/server/gamecontext.h>
#include "drawpremiumhyeta.h"

CDrawPremiumHyeta::CDrawPremiumHyeta(CGameWorld* pGameWorld, int TargetID)
	: CEntity(pGameWorld, CGameWorld::ENTTYPE_DRAWPREMIUM)
{
	m_OwnerID = TargetID;
	GameWorld()->InsertEntity(this);

	for (int i = 0; i < NUM_PREMIUM_PARTICLES + NUM_PREMIUM_HYETA; i++) {
		m_IDs[i] = Server()->SnapNewID();
	}
}

CDrawPremiumHyeta::~CDrawPremiumHyeta() {
	for (int i = 0; i < NUM_PREMIUM_PARTICLES + NUM_PREMIUM_HYETA; i++) {
		Server()->SnapFreeID(m_IDs[i]);
	}
}

void CDrawPremiumHyeta::Tick()
{
	if (GameServer()->m_apPlayers[m_OwnerID])
		if (GameServer()->m_apPlayers[m_OwnerID]->GetCharacter())
			m_Pos = GameServer()->m_apPlayers[m_OwnerID]->GetCharacter()->m_Core.m_Pos;
		else
			Destroy();
	else
		Destroy();
}

void CDrawPremiumHyeta::Snap(int SnappingClient)
{
	for (int i = 0; i < NUM_PREMIUM_PARTICLES; i++) {
		CNetObj_Projectile* pObj = static_cast<CNetObj_Projectile*>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_IDs[i], sizeof(CNetObj_Projectile)));
		if (!pObj)
			return;

		pObj->m_Type = WEAPON_HAMMER;
		pObj->m_X = m_Pos.x + cos(Server()->Tick() / 10.f * 0.5f - pi / NUM_PREMIUM_PARTICLES * i * 2) * (50.f + sin(Server()->Tick() / 10.f) * 15.f);
		pObj->m_Y = m_Pos.y + sin(Server()->Tick() / 10.f * 0.5f - pi / NUM_PREMIUM_PARTICLES * i * 2) * (50.f + sin(Server()->Tick() / 10.f) * 15.f);
		pObj->m_StartTick = Server()->Tick();
	}

	for (int i = 0; i < NUM_PREMIUM_HYETA; i++) {
		CNetObj_Pickup* pObj = static_cast<CNetObj_Pickup*>(Server()->SnapNewItem(NETOBJTYPE_PICKUP, m_IDs[NUM_PREMIUM_PARTICLES + i], sizeof(CNetObj_Pickup)));
		if (!pObj)
			return;

		pObj->m_Type = 0;
		pObj->m_X = m_Pos.x + cos(Server()->Tick() / 10.f * 0.5f - pi / NUM_PREMIUM_HYETA * i * 2 - (1.f - sin(Server()->Tick() / 20.f)) * 2.f) * 70.f;
		pObj->m_Y = m_Pos.y + sin(Server()->Tick() / 10.f * 0.5f - pi / NUM_PREMIUM_HYETA * i * 2 - (1.f - sin(Server()->Tick() / 20.f)) * 2.f) * 70.f;
	}
}
