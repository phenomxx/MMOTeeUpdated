/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <game/server/gamecontext.h>
#include "pets.h"

CPet::CPet(CGameWorld* pGameWorld, vec2 Pos, int OwnerID, int Type)
	: CEntity(pGameWorld, CGameWorld::ENTTYPE_PET)
{
	m_Pos = Pos;
	m_Type = Type;
	m_OwnerID = OwnerID;
	GameWorld()->InsertEntity(this);

	for (int i = 0; i < NUM_PARTICLES_AROUND_PET + NUM_PARTICLES_AROUND_IGOR + 1; i++) {
		m_IDs[i] = Server()->SnapNewID();
	}
}

CPet::~CPet() {
	for (int i = 0; i < NUM_PARTICLES_AROUND_PET + NUM_PARTICLES_AROUND_IGOR + 1; i++) {
		Server()->SnapFreeID(m_IDs[i]);
	}
}

void CPet::Tick()
{
	if (GameServer()->m_apPlayers[m_OwnerID])
		if (GameServer()->m_apPlayers[m_OwnerID]->GetCharacter())
			if (GameServer()->m_apPlayers[m_OwnerID]->GetCharacter()->m_Core.m_Angle > 400)
				m_Pos = GameServer()->m_apPlayers[m_OwnerID]->GetCharacter()->m_Pos + vec2(48, -48 + sin(Server()->Tick() / 12.f) * 15.f);
			else
				m_Pos = GameServer()->m_apPlayers[m_OwnerID]->GetCharacter()->m_Pos + vec2(-48, -48 + sin(Server()->Tick() / 12.f) * 15.f);
		else
			Destroy();
	else
		Destroy();
}

void CPet::Snap(int SnappingClient)
{
	if (NetworkClipped(SnappingClient))
		return;

	// Рисуем тело в виде патрона от грены
	{
		CNetObj_Projectile* pObj = static_cast<CNetObj_Projectile*>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_IDs[NUM_PARTICLES_AROUND_PET], sizeof(CNetObj_Projectile)));
		if (!pObj)
			return;

		pObj->m_Type = WEAPON_GRENADE;
		pObj->m_X = (int)m_Pos.x;
		pObj->m_Y = (int)m_Pos.y;
		pObj->m_VelX = 0;
		pObj->m_VelY = 0;
		pObj->m_StartTick = Server()->Tick();
	}

	// Рисуем херовины вокруг
	for (int i = 0; i < NUM_PARTICLES_AROUND_PET; i++) {
		CNetObj_Projectile* pObj = static_cast<CNetObj_Projectile*>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_IDs[i], sizeof(CNetObj_Projectile)));
		if (!pObj)
			return;

		pObj->m_Type = WEAPON_HAMMER;
		pObj->m_X = m_Pos.x + cos(Server()->Tick() / 10.f * 0.5f - pi / NUM_PARTICLES_AROUND_PET * i * 2) * 30.f;
		pObj->m_Y = m_Pos.y + sin(Server()->Tick() / 10.f * 0.5f - pi / NUM_PARTICLES_AROUND_PET * i * 2) * 30.f;
		pObj->m_StartTick = Server()->Tick();
	}

	if (m_Type == PET_IGOR) {
		for (int i = 0; i < NUM_PARTICLES_AROUND_IGOR; i++) {
			CNetObj_Projectile* pObj = static_cast<CNetObj_Projectile*>(Server()->SnapNewItem(NETOBJTYPE_PROJECTILE, m_IDs[NUM_PARTICLES_AROUND_PET + 1 + i], sizeof(CNetObj_Projectile)));
			if (!pObj)
				return;

			pObj->m_Type = WEAPON_RIFLE;
			pObj->m_X = m_Pos.x + cos(Server()->Tick() / 10.f * 0.5f - pi / NUM_PARTICLES_AROUND_IGOR * i * 2) * 40.f;
			pObj->m_Y = m_Pos.y + sin(Server()->Tick() / 10.f * 0.5f - pi / NUM_PARTICLES_AROUND_IGOR * i * 2) * 40.f;
			pObj->m_StartTick = Server()->Tick();
		}
	}
}
