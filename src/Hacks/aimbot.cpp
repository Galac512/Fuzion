#include "aimbot.h"
#include "autowall.h"

#include "../Utils/xorstring.h"
#include "../Utils/math.h"
#include "../Utils/entity.h"
#include "../settings.h"
#include "../interfaces.h"
#include <math.h>
#include "../ATGUI/bezier.h"


// Default aimbot settings
bool Settings::Aimbot::enabled = false;
bool Settings::Aimbot::silent = false;
bool Settings::Aimbot::friendly = false;
Bone Settings::Aimbot::bone = Bone::BONE_HEAD;
ButtonCode_t Settings::Aimbot::aimkey = ButtonCode_t::MOUSE_MIDDLE;
bool Settings::Aimbot::aimkeyOnly = false;
bool Settings::Aimbot::Smooth::enabled = false;
float Settings::Aimbot::Smooth::value = 0.5f;
SmoothType Settings::Aimbot::Smooth::type = SmoothType::SLOW_END;
bool Settings::Aimbot::ErrorMargin::enabled = false;
float Settings::Aimbot::ErrorMargin::value = 0.0f;
bool Settings::Aimbot::Random::enabled = false;
float Settings::Aimbot::Random::value = 0.2f;
bool Settings::Aimbot::AutoAim::enabled = false;
float Settings::Aimbot::AutoAim::fov = 180.0f;
bool Settings::Aimbot::AutoAim::realDistance = false;
bool Settings::Aimbot::AutoAim::closestBone = false;
bool Settings::Aimbot::AutoAim::desiredBones[] = {true, true, true, true, true, true, true, // center mass
                                                  false, false, false, false, false, false, false, // left arm
                                                  false, false, false, false, false, false, false, // right arm
                                                  false, false, false, false, false, // left leg
                                                  false, false, false, false, false  // right leg
};
bool Settings::Aimbot::AutoAim::engageLock = false;
bool Settings::Aimbot::AutoAim::engageLockTR = false; // engage lock Target Reacquisition ( re-target after getting a kill when spraying ).
int Settings::Aimbot::AutoAim::engageLockTTR = 700; // Time to Target Reacquisition in ms
bool Settings::Aimbot::AutoWall::enabled = false;
float Settings::Aimbot::AutoWall::value = 10.0f;
bool Settings::Aimbot::AimStep::enabled = false;
float Settings::Aimbot::AimStep::min = 25.0f;
float Settings::Aimbot::AimStep::max = 35.0f;
bool Settings::Aimbot::AutoPistol::enabled = false;
bool Settings::Aimbot::AutoShoot::enabled = false;
bool Settings::Aimbot::AutoShoot::velocityCheck = false;
bool Settings::Aimbot::AutoShoot::autoscope = false;
bool Settings::Aimbot::RCS::enabled = false;
bool Settings::Aimbot::RCS::always_on = false;
float Settings::Aimbot::RCS::valueXMin = 0.5f;
float Settings::Aimbot::RCS::valueXMax = 1.5f;
float Settings::Aimbot::RCS::valueXSpeed = 0.1f;
float Settings::Aimbot::RCS::valueYMin = 0.5f;
float Settings::Aimbot::RCS::valueYMax = 1.5f;
float Settings::Aimbot::RCS::valueYSpeed = 0.5f;
bool Settings::Aimbot::AutoCrouch::enabled = false;
bool Settings::Aimbot::NoShoot::enabled = false;
bool Settings::Aimbot::IgnoreJump::enabled = false;
bool Settings::Aimbot::IgnoreEnemyJump::enabled = false;
bool Settings::Aimbot::SmokeCheck::enabled = false;
bool Settings::Aimbot::FlashCheck::enabled = false;
bool Settings::Aimbot::SpreadLimit::enabled = false;
float Settings::Aimbot::SpreadLimit::value = 0.1f;
bool Settings::Aimbot::Smooth::Salting::enabled = false;
float Settings::Aimbot::Smooth::Salting::multiplier = 0.0f;
bool Settings::Aimbot::Curve::enabled = false;
float Settings::Aimbot::Curve::value[5] = { 0.390f, 0.575f, 0.565f, 0.900f };
bool Settings::Aimbot::AutoSlow::enabled = false;
bool Settings::Aimbot::AutoSlow::goingToSlow = false;
bool Settings::Aimbot::Prediction::enabled = false;
<<<<<<< HEAD
int Settings::Aimbot::Prediction::amount = 8;
=======
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
bool Settings::Aimbot::ScopeControl::enabled = false;

bool Aimbot::aimStepInProgress = false;
std::vector<int64_t> Aimbot::friends = { };
std::vector<long> killTimes = { 0 }; // the Epoch time from when we kill someone

bool shouldAim;
QAngle AimStepLastAngle;
QAngle RCSLastPunch;

int Aimbot::targetAimbot = -1;
const int headVectors = 11;

std::unordered_map<ItemDefinitionIndex, AimbotWeapon_t, Util::IntHash<ItemDefinitionIndex>> Settings::Aimbot::weapons = {
        { ItemDefinitionIndex::INVALID, defaultSettings },
};

static QAngle ApplyErrorToAngle(QAngle* angles, float margin)
{
        QAngle error;
        error.Random(-1.0f, 1.0f);
        error *= margin;
        angles->operator+=(error);
        return error;
}

/* Fills points Vector. True if successful. False if not.  Credits for Original method - ReactiioN */
static bool HeadMultiPoint(C_BasePlayer *player, Vector points[])
{
        matrix3x4_t matrix[128];

        if( !player->SetupBones(matrix, 128, 0x100, 0.f) )
                return false;
        model_t *pModel = player->GetModel();
        if( !pModel )
                return false;

        studiohdr_t *hdr = modelInfo->GetStudioModel(pModel);
        if( !hdr )
                return false;
        mstudiobbox_t *bbox = hdr->pHitbox((int)Hitbox::HITBOX_HEAD, 0);
        if( !bbox )
                return false;

        Vector mins, maxs;
        Math::VectorTransform(bbox->bbmin, matrix[bbox->bone], mins);
        Math::VectorTransform(bbox->bbmax, matrix[bbox->bone], maxs);

        Vector center = ( mins + maxs ) * 0.5f;
        // 0 - center, 1 - forehead, 2 - skullcap, 3 - upperleftear, 4 - upperrightear, 5 - uppernose, 6 - upperbackofhead
        // 7 - leftear, 8 - rightear, 9 - nose, 10 - backofhead
        for( int i = 0; i < headVectors; i++ ) // set all points initially to center mass of head.
                points[i] = center;
        points[1].z += bbox->radius * 0.60f; // morph each point.
        points[2].z += bbox->radius * 1.25f; // ...
        points[3].x += bbox->radius * 0.80f;
        points[3].z += bbox->radius * 0.60f;
        points[4].x -= bbox->radius * 0.80f;
        points[4].z += bbox->radius * 0.90f;
        points[5].y += bbox->radius * 0.80f;
        points[5].z += bbox->radius * 0.90f;
        points[6].y -= bbox->radius * 0.80f;
        points[6].z += bbox->radius * 0.90f;
        points[7].x += bbox->radius * 0.80f;
        points[8].x -= bbox->radius * 0.80f;
        points[9].y += bbox->radius * 0.80f;
        points[10].y -= bbox->radius * 0.80f;

        return true;
}


static float AutoWallBestSpot(C_BasePlayer *player, Vector &bestSpot)
{
        float bestDamage = Settings::Aimbot::AutoWall::value;
        const std::map<int, int> *modelType = Util::GetModelTypeBoneMap(player);

        static int len = sizeof(Settings::Aimbot::AutoAim::desiredBones) / sizeof(Settings::Aimbot::AutoAim::desiredBones[0]);

        for( int i = 0; i < len; i++ )
        {
                if( !Settings::Aimbot::AutoAim::desiredBones[i] )
                        continue;
                if( i == (int)DesiredBones::BONE_HEAD ) // head multipoint
                {
                        Vector headPoints[headVectors];
                        if( !HeadMultiPoint(player, headPoints) )
                                continue;
                        for( int j = 0; j < headVectors; j++ )
                        {
                                Autowall::FireBulletData data;
                                float spotDamage = Autowall::GetDamage(headPoints[j], !Settings::Aimbot::friendly, data);
                                if( spotDamage > bestDamage )
                                {
                                        bestSpot = headPoints[j];
                                        if( spotDamage > player->GetHealth() )
                                                return spotDamage;
                                        bestDamage = spotDamage;
                                }
                        }
                }
                int boneID = (*modelType).at(i);
                if( boneID == (int)Bone::INVALID ) // bone not available on this modeltype.
                        continue;

                Vector bone3D = player->GetBonePosition(boneID);

                Autowall::FireBulletData data;
                float boneDamage = Autowall::GetDamage(bone3D, !Settings::Aimbot::friendly, data);
                if( boneDamage > bestDamage )
                {
                        bestSpot = bone3D;
                        if( boneDamage > player->GetHealth() )
                                return boneDamage;

                        bestDamage = boneDamage;
                }
        }
        return bestDamage;
}

static float GetRealDistanceFOV(float distance, QAngle angle, CUserCmd* cmd)
{
        /*    n
              w + e
              s        'real distance'
              |
              a point -> x --..  v
              |     ''-- x <- a guy
              |          /
              |         /
              |       /
              | <------------ both of these lines are the same length
              |    /      /
              |   / <-----'
              | /
              o
              localplayer
        */

        Vector aimingAt;
        Math::AngleVectors(cmd->viewangles, aimingAt);
        aimingAt *= distance;

        Vector aimAt;
        Math::AngleVectors(angle, aimAt);
        aimAt *= distance;

        return aimingAt.DistTo(aimAt);
}

static Vector VelocityExtrapolate(C_BasePlayer* player, Vector aimPos, int ticks=1)
{
        return aimPos + (player->GetVelocity() * globalVars->interval_per_tick * ticks);
}

/* Original Credits to: https://github.com/goldenguy00 ( study! study! study! :^) ) */
static Vector GetClosestSpot( CUserCmd* cmd, C_BasePlayer* localPlayer, C_BasePlayer* enemy, AimTargetType aimTargetType = AimTargetType::FOV)
{
        QAngle viewAngles;
        engine->GetViewAngles(viewAngles);

        float tempFov = Settings::Aimbot::AutoAim::fov;
        float tempDistance = Settings::Aimbot::AutoAim::fov * 5.f;

        Vector pVecTarget = localPlayer->GetEyePosition();

        Vector tempSpot = {0,0,0};

        const std::map<int, int> *modelType = Util::GetModelTypeBoneMap(enemy);

        static int len = sizeof(Settings::Aimbot::AutoAim::desiredBones) / sizeof(Settings::Aimbot::AutoAim::desiredBones[0]);
        for( int i = 0; i < len; i++ )
        {
                if( !Settings::Aimbot::AutoAim::desiredBones[i] )
                        continue;

                int boneID = (*modelType).at(i);
                if( boneID == (int)Bone::INVALID )
                        continue;

                Vector cbVecTarget = enemy->GetBonePosition(boneID);

                if( aimTargetType == AimTargetType::FOV )
                {
                        float cbFov = Math::GetFov(viewAngles, Math::CalcAngle(pVecTarget, cbVecTarget));

                        if( cbFov < tempFov )
                        {
                                if( Entity::IsVisibleThroughEnemies(enemy, boneID) )
                                {
                                        tempFov = cbFov;
                                        tempSpot = cbVecTarget;
                                }
                        }
                }
                else if( aimTargetType == AimTargetType::REAL_DISTANCE )
                {
                        float cbDistance = pVecTarget.DistTo(cbVecTarget);
                        float cbRealDistance = GetRealDistanceFOV(cbDistance, Math::CalcAngle(pVecTarget, cbVecTarget), cmd);

                        if( cbRealDistance < tempDistance )
                        {
                                if( Entity::IsVisibleThroughEnemies(enemy, boneID) )
                                {
                                        tempDistance = cbRealDistance;
                                        tempSpot = cbVecTarget;
                                }
                        }
                }
        }
        return tempSpot;
}

static C_BasePlayer* GetClosestPlayerAndSpot(CUserCmd* cmd, bool visibleCheck, Vector* bestSpot, float* bestDamage, AimTargetType aimTargetType = AimTargetType::FOV)
{
<<<<<<< HEAD
        if (Settings::Aimbot::AutoAim::realDistance)
                aimTargetType = AimTargetType::REAL_DISTANCE;

        static C_BasePlayer* lockedOn = nullptr;
        C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
        C_BasePlayer* closestEntity = nullptr;

        float bestFov = Settings::Aimbot::AutoAim::fov;
        float bestRealDistance = Settings::Aimbot::AutoAim::fov * 5.f;

        if( lockedOn )
        {
                if( lockedOn->GetAlive() && !Settings::Aimbot::AutoAim::closestBone && !Entity::IsSpotVisibleThroughEnemies(lockedOn, lockedOn->GetBonePosition((int)Settings::Aimbot::bone)) )
                {
                        lockedOn = nullptr;
                        return nullptr;
                }
                if (!(cmd->buttons & IN_ATTACK || inputSystem->IsButtonDown(Settings::Aimbot::aimkey)) || lockedOn->GetDormant())//|| !Entity::IsVisible(lockedOn, bestBone, 180.f, Settings::ESP::Filters::smokeCheck))
                {
                        lockedOn = nullptr;
                }
                else
                {
                        if( !lockedOn->GetAlive() )
                        {
                                if( Settings::Aimbot::AutoAim::engageLockTR )
                                {
                                        if(Util::GetEpochTime() - killTimes.back() > Settings::Aimbot::AutoAim::engageLockTTR) // if we got the kill over the TTR time, engage another foe.
                                        {
                                                lockedOn = nullptr;
                                        }
                                }
                                return nullptr;
                        }

                        if( Settings::Aimbot::AutoAim::closestBone )
                        {
                                Vector tempSpot = GetClosestSpot(cmd, localplayer, lockedOn, aimTargetType);
                                if( tempSpot.IsZero() )
                                {
                                        return nullptr;
                                }
                                *bestSpot = tempSpot;
                        }
                        else
                        {
                                *bestSpot = lockedOn->GetBonePosition((int)Settings::Aimbot::bone);
                        }

                        return lockedOn;
                }
        }

        for (int i = 1; i < engine->GetMaxClients(); ++i)
        {
                C_BasePlayer* player = (C_BasePlayer*) entityList->GetClientEntity(i);

                if (!player
                    || player == localplayer
                    || player->GetDormant()
                    || !player->GetAlive()
                    || player->GetImmune())
                        continue;

                if (!Settings::Aimbot::friendly && Entity::IsTeamMate(player, localplayer))
                        continue;

                if( !Aimbot::friends.empty() ) // check for friends, if any
                {
                        IEngineClient::player_info_t entityInformation;
                        engine->GetPlayerInfo(i, &entityInformation);

                        if (std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end())
                                continue;
                }

                Aimbot::targetAimbot = i;
                Vector eVecTarget = player->GetBonePosition((int) Settings::Aimbot::bone);
                if( Settings::Aimbot::AutoAim::closestBone )
                {
                        Vector tempSpot = GetClosestSpot(cmd, localplayer, player, aimTargetType);
                        if( tempSpot.IsZero() || !Entity::IsSpotVisibleThroughEnemies(player, tempSpot) )
                                continue;
                        eVecTarget = tempSpot;
                }

                Vector pVecTarget = localplayer->GetEyePosition();
                lastRayStart = pVecTarget;
                lastRayEnd = eVecTarget;

                QAngle viewAngles;
                engine->GetViewAngles(viewAngles);

                float distance = pVecTarget.DistTo(eVecTarget);
                float fov = Math::GetFov(viewAngles, Math::CalcAngle(pVecTarget, eVecTarget));

                if (aimTargetType == AimTargetType::FOV && fov > bestFov)
                        continue;

                float realDistance = GetRealDistanceFOV(distance, Math::CalcAngle(pVecTarget, eVecTarget), cmd);

                if (aimTargetType == AimTargetType::REAL_DISTANCE && realDistance > bestRealDistance)
                        continue;
                if (visibleCheck && !Settings::Aimbot::AutoWall::enabled && !Entity::IsSpotVisible(player, eVecTarget))
                        continue;
                if ( Settings::Aimbot::SmokeCheck::enabled && LineGoesThroughSmoke( localplayer->GetEyePosition( ), eVecTarget, true ) )
                        continue;
                if ( Settings::Aimbot::FlashCheck::enabled && localplayer->IsFlashed() )
                        continue;

                if (Settings::Aimbot::AutoWall::enabled)
                {
                        Vector wallBangSpot = {0,0,0};
                        float damage = AutoWallBestSpot(player, wallBangSpot); // sets Vector Angle, returns damage of hitting that spot.

                        if( !wallBangSpot.IsZero() )
                        {
                                *bestDamage = damage;
                                *bestSpot = wallBangSpot;
                                closestEntity = player;
                                lastRayEnd = wallBangSpot;
                        }
                }
                else
                {
                        closestEntity = player;
                        *bestSpot = eVecTarget;
                        bestFov = fov;
                        bestRealDistance = realDistance;
                }
        }
        if( Settings::Aimbot::AutoAim::engageLock )
        {
                if( !lockedOn )
                {
                        if( (cmd->buttons & IN_ATTACK) || inputSystem->IsButtonDown(Settings::Aimbot::aimkey) )
                        {
                                if( Util::GetEpochTime() - killTimes.back() > 100 ) // if we haven't gotten a kill in under 100ms.
                                {
                                        lockedOn = closestEntity; // This is to prevent a Rare condition when you one-tap someone without the aimbot, it will lock on to another target.
                                }
                        }
                        else
                        {
                                return nullptr;
                        }
                }
        }
        if( bestSpot->IsZero() )
                return nullptr;

        /*
          if( closestEntity )
          {
          IEngineClient::player_info_t playerInfo;
          engine->GetPlayerInfo(closestEntity->GetIndex(), &playerInfo);
          cvar->ConsoleDPrintf("%s is Closest.\n", playerInfo.name);
          }
        */

        return closestEntity;
=======
	if (Settings::Aimbot::AutoAim::realDistance)
		aimTargetType = AimTargetType::REAL_DISTANCE;

	static C_BasePlayer* lockedOn = nullptr;
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	C_BasePlayer* closestEntity = nullptr;

	float bestFov = Settings::Aimbot::AutoAim::fov;
	float bestRealDistance = Settings::Aimbot::AutoAim::fov * 5.f;

	if( lockedOn )
	{
		if( lockedOn->GetAlive() && !Settings::Aimbot::AutoAim::closestBone && !Entity::IsSpotVisibleThroughEnemies(lockedOn, lockedOn->GetBonePosition((int)Settings::Aimbot::bone)) )
		{
			lockedOn = nullptr;
			return nullptr;
		}
		if (!(cmd->buttons & IN_ATTACK || inputSystem->IsButtonDown(Settings::Aimbot::aimkey)) || lockedOn->GetDormant())//|| !Entity::IsVisible(lockedOn, bestBone, 180.f, Settings::ESP::Filters::smokeCheck))
		{
			lockedOn = nullptr;
		}
		else
		{
			if( !lockedOn->GetAlive() )
			{
				if( Settings::Aimbot::AutoAim::engageLockTR )
				{
					if(Util::GetEpochTime() - killTimes.back() > Settings::Aimbot::AutoAim::engageLockTTR) // if we got the kill over the TTR time, engage another foe.
					{
						lockedOn = nullptr;
					}
				}
				return nullptr;
			}

			if( Settings::Aimbot::AutoAim::closestBone )
			{
				Vector tempSpot = GetClosestSpot(cmd, localplayer, lockedOn, aimTargetType);
				if( tempSpot.IsZero() )
				{
					return nullptr;
				}
				*bestSpot = tempSpot;
			}
			else
			{
				*bestSpot = lockedOn->GetBonePosition((int)Settings::Aimbot::bone);
			}

			return lockedOn;
		}
	}

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BasePlayer* player = (C_BasePlayer*) entityList->GetClientEntity(i);

		if (!player
			|| player == localplayer
			|| player->GetDormant()
			|| !player->GetAlive()
			|| player->GetImmune())
			continue;

		if (!Settings::Aimbot::friendly && Entity::IsTeamMate(player, localplayer))
			continue;

		if( !Aimbot::friends.empty() ) // check for friends, if any
		{
			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(i, &entityInformation);

			if (std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end())
				continue;
		}

		Aimbot::targetAimbot = i;
		Vector eVecTarget = player->GetBonePosition((int) Settings::Aimbot::bone);
		if( Settings::Aimbot::AutoAim::closestBone )
		{
			Vector tempSpot = GetClosestSpot(cmd, localplayer, player, aimTargetType);
			if( tempSpot.IsZero() || !Entity::IsSpotVisibleThroughEnemies(player, tempSpot) )
				continue;
			eVecTarget = tempSpot;
		}

		Vector pVecTarget = localplayer->GetEyePosition();
        lastRayStart = pVecTarget;
        lastRayEnd = eVecTarget;

		QAngle viewAngles;
		engine->GetViewAngles(viewAngles);

		float distance = pVecTarget.DistTo(eVecTarget);
		float fov = Math::GetFov(viewAngles, Math::CalcAngle(pVecTarget, eVecTarget));

		if (aimTargetType == AimTargetType::FOV && fov > bestFov)
			continue;

		float realDistance = GetRealDistanceFOV(distance, Math::CalcAngle(pVecTarget, eVecTarget), cmd);

		if (aimTargetType == AimTargetType::REAL_DISTANCE && realDistance > bestRealDistance)
			continue;
		if (visibleCheck && !Settings::Aimbot::AutoWall::enabled && !Entity::IsSpotVisible(player, eVecTarget))
			continue;
		if ( Settings::Aimbot::SmokeCheck::enabled && LineGoesThroughSmoke( localplayer->GetEyePosition( ), eVecTarget, true ) )
			continue;
		if ( Settings::Aimbot::FlashCheck::enabled && localplayer->IsFlashed() )
			continue;

		if (Settings::Aimbot::AutoWall::enabled)
		{
			Vector wallBangSpot = {0,0,0};
			float damage = AutoWallBestSpot(player, wallBangSpot); // sets Vector Angle, returns damage of hitting that spot.

			if( !wallBangSpot.IsZero() )
			{
				*bestDamage = damage;
				*bestSpot = wallBangSpot;
				closestEntity = player;
				lastRayEnd = wallBangSpot;
			}
		}
		else
		{
			closestEntity = player;
			*bestSpot = eVecTarget;
			bestFov = fov;
			bestRealDistance = realDistance;
		}
	}
	if( Settings::Aimbot::AutoAim::engageLock )
	{
		if( !lockedOn )
		{
			if( (cmd->buttons & IN_ATTACK) || inputSystem->IsButtonDown(Settings::Aimbot::aimkey) )
			{
				if( Util::GetEpochTime() - killTimes.back() > 100 ) // if we haven't gotten a kill in under 100ms.
				{
					lockedOn = closestEntity; // This is to prevent a Rare condition when you one-tap someone without the aimbot, it will lock on to another target.
				}
			}
			else
			{
				return nullptr;
			}
		}
	}
	if( bestSpot->IsZero() )
		return nullptr;

	/*
	if( closestEntity )
	{
		IEngineClient::player_info_t playerInfo;
		engine->GetPlayerInfo(closestEntity->GetIndex(), &playerInfo);
		cvar->ConsoleDPrintf("%s is Closest.\n", playerInfo.name);
	}
	*/

	return closestEntity;
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
}

static void RCS(QAngle& angle, C_BasePlayer* player, CUserCmd* cmd)
{
        if (!Settings::Aimbot::RCS::enabled)
                return;

        if (!(cmd->buttons & IN_ATTACK))
                return;

        bool hasTarget = Settings::Aimbot::AutoAim::enabled && shouldAim && player;

        if (!Settings::Aimbot::RCS::always_on && !hasTarget)
                return;

        C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
        QAngle CurrentPunch = *localplayer->GetAimPunchAngle();

        float valueX = Settings::Aimbot::RCS::valueXMin+(Settings::Aimbot::RCS::valueXMax-Settings::Aimbot::RCS::valueXMin)*(1.f-std::exp(-localplayer->GetShotsFired()*std::pow(Settings::Aimbot::RCS::valueXSpeed, 4.f)));
        float valueY = Settings::Aimbot::RCS::valueYMin+(Settings::Aimbot::RCS::valueYMax-Settings::Aimbot::RCS::valueYMin)*(1.f-std::exp(-localplayer->GetShotsFired()*std::pow(Settings::Aimbot::RCS::valueYSpeed, 4.f)));
        if ( Settings::Aimbot::silent || hasTarget )
        {
                angle.x -= CurrentPunch.x * valueX;
                angle.y -= CurrentPunch.y * valueY;
        }
        else if (localplayer->GetShotsFired() > 1)
        {
                QAngle NewPunch = { CurrentPunch.x - RCSLastPunch.x, CurrentPunch.y - RCSLastPunch.y, 0 };

                angle.x -= NewPunch.x * valueX;
                angle.y -= NewPunch.y * valueY;
        }

        RCSLastPunch = CurrentPunch;
}
static void AimStep(C_BasePlayer* player, QAngle& angle, CUserCmd* cmd)
{
        if (!Settings::Aimbot::AimStep::enabled)
                return;

        if (!Settings::Aimbot::AutoAim::enabled)
                return;

        if (Settings::Aimbot::Smooth::enabled)
                return;

        if (!shouldAim)
                return;

        if (!Aimbot::aimStepInProgress)
                AimStepLastAngle = cmd->viewangles;

        if (!player)
                return;

        float fov = Math::GetFov(AimStepLastAngle, angle);

        Aimbot::aimStepInProgress = ( fov > (Math::float_rand(Settings::Aimbot::AimStep::min, Settings::Aimbot::AimStep::max)) );

        if (!Aimbot::aimStepInProgress)
                return;

        cmd->buttons &= ~(IN_ATTACK); // aimstep in progress, don't shoot.

        QAngle deltaAngle = AimStepLastAngle - angle;

        Math::NormalizeAngles(deltaAngle);
        float randX = Math::float_rand(Settings::Aimbot::AimStep::min, std::min(Settings::Aimbot::AimStep::max, fov));
        float randY = Math::float_rand(Settings::Aimbot::AimStep::min, std::min(Settings::Aimbot::AimStep::max, fov));
        if (deltaAngle.y < 0)
                AimStepLastAngle.y += randY;
        else
                AimStepLastAngle.y -= randY;

        if(deltaAngle.x < 0)
                AimStepLastAngle.x += randX;
        else
                AimStepLastAngle.x -= randX;

        angle = AimStepLastAngle;
}

static void Salt(float& smooth)
{
        float sine = sin (globalVars->tickcount);
        float salt = sine * Settings::Aimbot::Smooth::Salting::multiplier;
        float oval = smooth + salt;
        smooth *= oval;
}

static void Smooth(C_BasePlayer* player, Vector bestSpot, C_BasePlayer* localplayer, Vector localEye,  QAngle& angle, int& pPred)
{
        if (!Settings::Aimbot::Smooth::enabled)
                return;

        if (!shouldAim || !player)
                return;

        if (Settings::Aimbot::silent)
                return;

        QAngle viewAngles;
        engine->GetViewAngles(viewAngles);

        QAngle delta = angle - viewAngles;
        Math::NormalizeAngles(delta);

        float smooth = powf(Settings::Aimbot::Smooth::value, 0.4f); // Makes more slider space for actual useful values

        smooth = std::min(0.99f, smooth);

        if (Settings::Aimbot::Smooth::Salting::enabled)
                Salt(smooth);

        QAngle toChange = {0,0,0};

        SmoothType type = Settings::Aimbot::Smooth::type;

        if (type == SmoothType::SLOW_END)
                toChange = delta - (delta * smooth);
        else if (type == SmoothType::CONSTANT || type == SmoothType::FAST_END)
        {
                float coeff = (1.0f - smooth) / delta.Length() * 4.f;

                if (type == SmoothType::FAST_END)
                        coeff = powf(coeff, 2.f) * 10.f;

                coeff = std::min(1.f, coeff);
                toChange = delta * coeff;
        }

        if (Settings::Aimbot::Curve::enabled)
        {
                float progress = toChange.y / delta.y;

<<<<<<< HEAD
                if (progress < .999f)
                {
                        toChange.x = ImGui::BezierValue(progress, Settings::Aimbot::Curve::value) * delta.x;
                        //cvar->ConsoleColorPrintf(ColorRGBA(255, 0, 0), XORSTR("ToChange = { %f., %f }\nProgress = %f\n"), toChange.y, toChange.x, progress);
                }
        }
=======
	cmd->buttons |= IN_BULLRUSH | IN_DUCK;
}
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81

	if (Settings::Aimbot::Prediction::enabled)
	{
		static QAngle lastDelta = delta;
		if (delta.Length() > lastDelta.Length())
		{
			lastDelta = delta;
			pPred = std::min(Settings::Aimbot::Prediction::amount, pPred+(int)(2*lastDelta.Length()/delta.Length()));
		}
		else
			pPred = std::max(1, pPred-1);
		/*Vector theta = {0, 0, 0};
		  Math::AngleVectors(toChange, theta);
		  float ticks = (bestSpot.y + theta.y ) / (localEye.y + (player->GetVelocity() * globalVars->interval_per_tick).y);

		  pPred = std::min(Settings::Aimbot::Prediction::amount, (int)(ticks));*/
	}

        angle = viewAngles + toChange;
}

static void AutoCrouch(C_BasePlayer* player, CUserCmd* cmd)
{
        if (!Settings::Aimbot::AutoCrouch::enabled)
                return;

        if (!player)
                return;

        cmd->buttons |= IN_BULLRUSH | IN_DUCK;
}

static void AutoSlow(C_BasePlayer* player, float& forward, float& sideMove, float& bestDamage, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd)
{

        if (!Settings::Aimbot::AutoSlow::enabled)
        {
                Settings::Aimbot::AutoSlow::goingToSlow = false;
                return;
        }

        if (!player)
        {
                Settings::Aimbot::AutoSlow::goingToSlow = false;
                return;
        }

        float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();

        if (nextPrimaryAttack > globalVars->curtime){
                Settings::Aimbot::AutoSlow::goingToSlow = false;
                return;
        }

        Settings::Aimbot::AutoSlow::goingToSlow = true;

        C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

        C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
        if (!activeWeapon || activeWeapon->GetAmmo() == 0)
                return;

        if( Settings::Aimbot::SpreadLimit::enabled )
        {
                if( (activeWeapon->GetSpread() + activeWeapon->GetInaccuracy()) > Settings::Aimbot::SpreadLimit::value )
                {
                        cmd->buttons |= IN_WALK;
                        forward = -forward;
                        sideMove = -sideMove;
                        cmd->upmove = 0;
                }
        }
        else if( localplayer->GetVelocity().Length() > (activeWeapon->GetCSWpnData()->GetMaxPlayerSpeed() / 3) ) // https://youtu.be/ZgjYxBRuagA
        {
                cmd->buttons |= IN_WALK;
                forward = -forward;
                sideMove = -sideMove;
                cmd->upmove = 0;
        }
}

static void AutoCock(C_BasePlayer* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
        if (!Settings::Aimbot::AutoShoot::enabled)
                return;

        if (Settings::Aimbot::AimStep::enabled && Aimbot::aimStepInProgress)
                return;

        if (*activeWeapon->GetItemDefinitionIndex() != ItemDefinitionIndex::WEAPON_REVOLVER)
                return;

        if(activeWeapon->GetAmmo() == 0)
                return;
        if (cmd->buttons & IN_USE)
                return;

        cmd->buttons |= IN_ATTACK;
        float postponeFireReadyTime = activeWeapon->GetPostPoneReadyTime();
        if (postponeFireReadyTime > 0)
        {
                if (postponeFireReadyTime < globalVars->curtime)
                {
                        if (player)
                                return;
                        cmd->buttons &= ~IN_ATTACK;
                }
        }
}

static void AutoCock(C_BasePlayer* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
    if (!Settings::Aimbot::AutoShoot::enabled)
        return;

    if (Settings::Aimbot::AimStep::enabled && Aimbot::aimStepInProgress)
        return;

    if (*activeWeapon->GetItemDefinitionIndex() != ItemDefinitionIndex::WEAPON_REVOLVER)
        return;

    if(activeWeapon->GetAmmo() == 0)
        return;
    if (cmd->buttons & IN_USE)
        return;

    cmd->buttons |= IN_ATTACK;
    float postponeFireReadyTime = activeWeapon->GetPostPoneReadyTime();
    if (postponeFireReadyTime > 0)
    {
        if (postponeFireReadyTime < globalVars->curtime)
        {
            if (player)
                return;
            cmd->buttons &= ~IN_ATTACK;
        }
    }
}

static void AutoPistol(C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
        if (!Settings::Aimbot::AutoPistol::enabled)
                return;

        if (!activeWeapon || activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_PISTOL)
                return;

        if (activeWeapon->GetNextPrimaryAttack() < globalVars->curtime)
                return;

<<<<<<< HEAD
        if (*activeWeapon->GetItemDefinitionIndex() != ItemDefinitionIndex::WEAPON_REVOLVER)
                cmd->buttons &= ~IN_ATTACK;
=======
    if (*activeWeapon->GetItemDefinitionIndex() != ItemDefinitionIndex::WEAPON_REVOLVER)
        cmd->buttons &= ~IN_ATTACK;
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
}

static void AutoShoot(C_BasePlayer* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
        if (!Settings::Aimbot::AutoShoot::enabled)
                return;

        if (Settings::Aimbot::AimStep::enabled && Aimbot::aimStepInProgress)
                return;

        if (!player || activeWeapon->GetAmmo() == 0)
                return;

        CSWeaponType weaponType = activeWeapon->GetCSWpnData()->GetWeaponType();
        if (weaponType == CSWeaponType::WEAPONTYPE_KNIFE || weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
                return;

        if (cmd->buttons & IN_USE)
                return;

        C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

<<<<<<< HEAD
        if (Settings::Aimbot::AutoShoot::autoscope && activeWeapon->GetCSWpnData()->GetZoomLevels() > 0 && !localplayer->IsScoped())
                cmd->buttons |= IN_ATTACK2;
=======
	if (Settings::Aimbot::AutoShoot::autoscope && Util::Items::IsScopeable(*activeWeapon->GetItemDefinitionIndex()) && !localplayer->IsScoped())
		cmd->buttons |= IN_ATTACK2;
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81

        if( Settings::Aimbot::AutoShoot::velocityCheck && localplayer->GetVelocity().Length() > (activeWeapon->GetCSWpnData()->GetMaxPlayerSpeed() / 3) )
                return;
        if( Settings::Aimbot::SpreadLimit::enabled && ((activeWeapon->GetSpread() + activeWeapon->GetInaccuracy()) > Settings::Aimbot::SpreadLimit::value))
                return;

        float nextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();

<<<<<<< HEAD
        if (!(*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER))
        {
                if (nextPrimaryAttack > globalVars->curtime)
                        cmd->buttons &= ~IN_ATTACK;
                else
                        cmd->buttons |= IN_ATTACK;
        }
=======
    if (!(*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER))
    {
        if (nextPrimaryAttack > globalVars->curtime)
            cmd->buttons &= ~IN_ATTACK;
        else
            cmd->buttons |= IN_ATTACK;
    }
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
}

static void NoShoot(C_BaseCombatWeapon* activeWeapon, C_BasePlayer* player, CUserCmd* cmd)
{
        if (player && Settings::Aimbot::NoShoot::enabled)
        {
                if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_C4)
                        return;

                if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
                        cmd->buttons &= ~IN_ATTACK2;
                else
                        cmd->buttons &= ~IN_ATTACK;
        }
}

static void FixMouseDeltas(CUserCmd* cmd, const QAngle &angle, const QAngle &oldAngle)
{
        if( !shouldAim )
                return;
        QAngle delta = angle - oldAngle;
        float sens = cvar->FindVar(XORSTR("sensitivity"))->GetFloat();
        float m_pitch = cvar->FindVar(XORSTR("m_pitch"))->GetFloat();
        float m_yaw = cvar->FindVar(XORSTR("m_yaw"))->GetFloat();
        float zoomMultiplier = cvar->FindVar("zoom_sensitivity_ratio_mouse")->GetFloat();

        Math::NormalizeAngles(delta);

        cmd->mousedx = -delta.y / ( m_yaw * sens * zoomMultiplier );
        cmd->mousedy = delta.x / ( m_pitch * sens * zoomMultiplier );
}

static bool ApplyRandom(C_BasePlayer* player, Vector& bestSpot)
{
	if (!Settings::Aimbot::Random::enabled)
		return false;

	static C_BasePlayer* oldPlayer = player;
	static Vector random = {0.f, 0.f, 0.f};

	if (player != oldPlayer)
	{
		random.x = Math::float_rand(-Settings::Aimbot::Random::value, Settings::Aimbot::Random::value);
		random.y = Math::float_rand(-Settings::Aimbot::Random::value, Settings::Aimbot::Random::value);

		matrix3x4_t matrix[128];

		if( !player->SetupBones(matrix, 128, 0x100, 0.f) )
			return false;
		model_t *pModel = player->GetModel();
		if( !pModel )
			return false;

		studiohdr_t *hdr = modelInfo->GetStudioModel(pModel);
		if( !hdr )
			return false;
		mstudiobbox_t *bbox = hdr->pHitbox((int)Settings::Aimbot::bone, 0);
		if( !bbox )
			return false;

		random.x += Math::float_rand(bbox->bbmin.x, bbox->bbmax.x)*Settings::Aimbot::Random::value;
		random.y += Math::float_rand(bbox->bbmin.y, bbox->bbmax.y)*Settings::Aimbot::Random::value;
		random.z += Math::float_rand(bbox->bbmin.z, bbox->bbmax.z)*Settings::Aimbot::Random::value;
	}

	bestSpot += random;
	oldPlayer = player;

	return true;
}

void Aimbot::CreateMove(CUserCmd* cmd)
{
        C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
        if (!localplayer || !localplayer->GetAlive())
                return;

<<<<<<< HEAD
        Aimbot::UpdateValues();
=======
	if (Settings::Aimbot::IgnoreJump::enabled && (!(localplayer->GetFlags() & FL_ONGROUND) && localplayer->GetMoveType() != MOVETYPE_LADDER))
		return;
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81

        if (!Settings::Aimbot::enabled)
                return;

        QAngle oldAngle;
        engine->GetViewAngles(oldAngle);
        float oldForward = cmd->forwardmove;
        float oldSideMove = cmd->sidemove;

<<<<<<< HEAD
        QAngle angle = cmd->viewangles;
        static bool newTarget = true;
        static QAngle lastRandom = {0,0,0};
        Vector localEye = localplayer->GetEyePosition();


	static int pPred = 1;
	if (!Settings::Aimbot::Prediction::enabled || !Settings::Aimbot::Smooth::enabled)
		pPred = 1;

        shouldAim = Settings::Aimbot::AutoShoot::enabled;
=======
	if (Settings::Aimbot::ScopeControl::enabled)
	{
		if (Util::Items::IsScopeable(*activeWeapon->GetItemDefinitionIndex()) && !localplayer->IsScoped())
			return;
	}

    Vector bestSpot = {0,0,0};
	float bestDamage = 0.0f;
	C_BasePlayer* player = GetClosestPlayerAndSpot(cmd, !Settings::Aimbot::AutoWall::enabled, &bestSpot, &bestDamage);

	if (player)
	{
		if (Settings::Aimbot::IgnoreEnemyJump::enabled && (!(player->GetFlags() & FL_ONGROUND) && player->GetMoveType() != MOVETYPE_LADDER))
			return;

		if (Settings::Aimbot::AutoAim::enabled)
		{
			if (cmd->buttons & IN_ATTACK && !Settings::Aimbot::aimkeyOnly)
				shouldAim = true;

			if (inputSystem->IsButtonDown(Settings::Aimbot::aimkey))
				shouldAim = true;

			Settings::Debug::AutoAim::target = bestSpot; // For Debug showing aimspot.
			if (shouldAim)
			{
				if (Settings::Aimbot::Prediction::enabled)
				{
					localEye = VelocityExtrapolate(localplayer, localEye); // get eye pos next tick
					bestSpot = VelocityExtrapolate(player, bestSpot); // get target pos next tick
				}
				angle = Math::CalcAngle(localEye, bestSpot);

				if (Settings::Aimbot::ErrorMargin::enabled)
				{
					static int lastShotFired = 0;
					if ((localplayer->GetShotsFired() > lastShotFired) || newTarget) //get new random spot when firing a shot or when aiming at a new target
						lastRandom = ApplyErrorToAngle(&angle, Settings::Aimbot::ErrorMargin::value);

					angle += lastRandom;
					lastShotFired = localplayer->GetShotsFired();
				}
				newTarget = false;
			}
		}
	}
	else // No player to Shoot
	{
        Settings::Debug::AutoAim::target = {0,0,0};
        newTarget = true;
        lastRandom = {0,0,0};
    }

    AimStep(player, angle, cmd);
	AutoCrouch(player, cmd);
	AutoSlow(player, oldForward, oldSideMove, bestDamage, activeWeapon, cmd);
	AutoPistol(activeWeapon, cmd);
	AutoShoot(player, activeWeapon, cmd);
	AutoCock(player, activeWeapon, cmd);
	RCS(angle, player, cmd);
	Smooth(player, angle);
	NoShoot(activeWeapon, player, cmd);

    Math::NormalizeAngles(angle);
    Math::ClampAngles(angle);

	FixMouseDeltas(cmd, angle, oldAngle);
	cmd->viewangles = angle;

    Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

	if( !Settings::Aimbot::silent )
    	engine->SetViewAngles(cmd->viewangles);
}
void Aimbot::FireGameEvent(IGameEvent* event)
{
	if (!event)
		return;
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81

        if (Settings::Aimbot::IgnoreJump::enabled && (!(localplayer->GetFlags() & FL_ONGROUND) && localplayer->GetMoveType() != MOVETYPE_LADDER))
                return;

        C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
        if (!activeWeapon || activeWeapon->GetInReload())
                return;

        CSWeaponType weaponType = activeWeapon->GetCSWpnData()->GetWeaponType();
        if (weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE || weaponType == CSWeaponType::WEAPONTYPE_KNIFE)
                return;

	if (Settings::Aimbot::ScopeControl::enabled)
	{
		if (activeWeapon->GetCSWpnData()->GetZoomLevels() > 0 && !localplayer->IsScoped())
			return;
	}

        Vector bestSpot = {0.f,0.f,0.f};
        float bestDamage = 0.0f;
        C_BasePlayer* player = GetClosestPlayerAndSpot(cmd, !Settings::Aimbot::AutoWall::enabled, &bestSpot, &bestDamage);

	ApplyRandom(player, bestSpot);
	
        if (player)
        {
                if (Settings::Aimbot::IgnoreEnemyJump::enabled && (!(player->GetFlags() & FL_ONGROUND) && player->GetMoveType() != MOVETYPE_LADDER))
                        return;

                if (Settings::Aimbot::AutoAim::enabled)
                {
                        if (cmd->buttons & IN_ATTACK && !Settings::Aimbot::aimkeyOnly)
				shouldAim = true;

                        if (inputSystem->IsButtonDown(Settings::Aimbot::aimkey))
                                shouldAim = true;

                        Settings::Debug::AutoAim::target = bestSpot; // For Debug showing aimspot.
                        if ( shouldAim )
                        {
                                if ( Settings::Aimbot::Prediction::enabled )
                                {
                                        localEye = VelocityExtrapolate( localplayer, localEye, pPred ); // get eye pos next tick
                                        bestSpot = VelocityExtrapolate( player, bestSpot, pPred ); // get target pos next tick
                                }
                                angle = Math::CalcAngle(localEye, bestSpot);

                                if ( Settings::Aimbot::ErrorMargin::enabled )
                                {
                                        static int lastShotFired = 0;
                                        if ( ( localplayer->GetShotsFired( ) > lastShotFired ) || newTarget )//get new random spot when firing a shot or when aiming at a new target
                                                lastRandom = ApplyErrorToAngle( &angle, Settings::Aimbot::ErrorMargin::value );

                                        angle += lastRandom;

                                        lastShotFired = localplayer->GetShotsFired();
                                }
                                newTarget = false;
                        }
		}
	}
	else // No player to Shoot
        {
                Settings::Debug::AutoAim::target = {0,0,0};
                newTarget = true;
                lastRandom = {0,0,0};
        }

        AimStep(player, angle, cmd);
        AutoCrouch(player, cmd);
        AutoSlow(player, oldForward, oldSideMove, bestDamage, activeWeapon, cmd);
        AutoPistol(activeWeapon, cmd);
        AutoShoot(player, activeWeapon, cmd);
        AutoCock(player, activeWeapon, cmd);
        RCS(angle, player, cmd);
        Smooth(player, bestSpot, localplayer, localEye, angle, pPred);
        NoShoot(activeWeapon, player, cmd);

        Math::NormalizeAngles(angle);
        Math::ClampAngles(angle);

        FixMouseDeltas(cmd, angle, oldAngle);
        cmd->viewangles = angle;

        Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);

        if( !Settings::Aimbot::silent )
                engine->SetViewAngles(cmd->viewangles);
}
void Aimbot::FireGameEvent(IGameEvent* event)
{
        if (!event)
                return;

        if (strcmp(event->GetName(), XORSTR("player_connect_full")) == 0 || strcmp(event->GetName(), XORSTR("cs_game_disconnected")) == 0 )
        {
                if (event->GetInt(XORSTR("userid")) && engine->GetPlayerForUserID(event->GetInt(XORSTR("userid"))) != engine->GetLocalPlayer())
                        return;
                Aimbot::friends.clear();
        }
        if( strcmp(event->GetName(), XORSTR("player_death")) == 0 )
        {
                int attacker_id = engine->GetPlayerForUserID(event->GetInt(XORSTR("attacker")));
                int deadPlayer_id = engine->GetPlayerForUserID(event->GetInt(XORSTR("userid")));

                if (attacker_id == deadPlayer_id) // suicide
                        return;

                if (attacker_id != engine->GetLocalPlayer())
                        return;

                killTimes.push_back(Util::GetEpochTime());
        }
}

void Aimbot::UpdateValues()
{
<<<<<<< HEAD
        C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
        C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
        if (!activeWeapon)
                return;

        ItemDefinitionIndex index = ItemDefinitionIndex::INVALID;
        if (Settings::Aimbot::weapons.find(*activeWeapon->GetItemDefinitionIndex()) != Settings::Aimbot::weapons.end())
                index = *activeWeapon->GetItemDefinitionIndex();

        const AimbotWeapon_t& currentWeaponSetting = Settings::Aimbot::weapons.at(index);

        Settings::Aimbot::enabled = currentWeaponSetting.enabled;
        Settings::Aimbot::silent = currentWeaponSetting.silent;
        Settings::Aimbot::friendly = currentWeaponSetting.friendly;
        Settings::Aimbot::bone = currentWeaponSetting.bone;
        Settings::Aimbot::aimkey = currentWeaponSetting.aimkey;
        Settings::Aimbot::aimkeyOnly = currentWeaponSetting.aimkeyOnly;
        Settings::Aimbot::Smooth::enabled = currentWeaponSetting.smoothEnabled;
        Settings::Aimbot::Smooth::value = currentWeaponSetting.smoothAmount;
        Settings::Aimbot::Smooth::type = currentWeaponSetting.smoothType;
        Settings::Aimbot::ErrorMargin::enabled = currentWeaponSetting.errorMarginEnabled;
        Settings::Aimbot::ErrorMargin::value = currentWeaponSetting.errorMarginValue;
        Settings::Aimbot::Random::enabled = currentWeaponSetting.randomEnabled;
        Settings::Aimbot::Random::value = currentWeaponSetting.randomValue;
        Settings::Aimbot::Curve::enabled = currentWeaponSetting.curveEnabled;
        Settings::Aimbot::Curve::value[0] = currentWeaponSetting.curveValue[0];
        Settings::Aimbot::Curve::value[1] = currentWeaponSetting.curveValue[1];
        Settings::Aimbot::Curve::value[2] = currentWeaponSetting.curveValue[2];
        Settings::Aimbot::Curve::value[3] = currentWeaponSetting.curveValue[3];
        Settings::Aimbot::AutoAim::enabled = currentWeaponSetting.autoAimEnabled;
        Settings::Aimbot::AutoAim::fov = currentWeaponSetting.autoAimFov;
        Settings::Aimbot::AutoAim::closestBone = currentWeaponSetting.closestBone;
        Settings::Aimbot::AutoAim::engageLock = currentWeaponSetting.engageLock;
        Settings::Aimbot::AutoAim::engageLockTR = currentWeaponSetting.engageLockTR;
        Settings::Aimbot::AutoAim::engageLockTTR = currentWeaponSetting.engageLockTTR;
        Settings::Aimbot::AimStep::enabled = currentWeaponSetting.aimStepEnabled;
        Settings::Aimbot::AimStep::min = currentWeaponSetting.aimStepMin;
        Settings::Aimbot::AimStep::max = currentWeaponSetting.aimStepMax;
        Settings::Aimbot::AutoPistol::enabled = currentWeaponSetting.autoPistolEnabled;
        Settings::Aimbot::AutoShoot::enabled = currentWeaponSetting.autoShootEnabled;
        Settings::Aimbot::AutoShoot::autoscope = currentWeaponSetting.autoScopeEnabled;
        Settings::Aimbot::RCS::enabled = currentWeaponSetting.rcsEnabled;
        Settings::Aimbot::RCS::always_on = currentWeaponSetting.rcsAlwaysOn;
        Settings::Aimbot::RCS::valueXMin = currentWeaponSetting.rcsAmountXMin;
        Settings::Aimbot::RCS::valueXMax = currentWeaponSetting.rcsAmountXMax;
        Settings::Aimbot::RCS::valueXSpeed = currentWeaponSetting.rcsAmountXSpeed;
        Settings::Aimbot::RCS::valueYMin = currentWeaponSetting.rcsAmountYMin;
        Settings::Aimbot::RCS::valueYMax = currentWeaponSetting.rcsAmountYMax;
        Settings::Aimbot::RCS::valueYSpeed = currentWeaponSetting.rcsAmountYSpeed;
        Settings::Aimbot::NoShoot::enabled = currentWeaponSetting.noShootEnabled;
        Settings::Aimbot::IgnoreJump::enabled = currentWeaponSetting.ignoreJumpEnabled;
	Settings::Aimbot::IgnoreEnemyJump::enabled = currentWeaponSetting.ignoreEnemyJumpEnabled;
        Settings::Aimbot::Smooth::Salting::enabled = currentWeaponSetting.smoothSaltEnabled;
        Settings::Aimbot::Smooth::Salting::multiplier = currentWeaponSetting.smoothSaltMultiplier;
        Settings::Aimbot::SmokeCheck::enabled = currentWeaponSetting.smokeCheck;
        Settings::Aimbot::FlashCheck::enabled = currentWeaponSetting.flashCheck;
        Settings::Aimbot::SpreadLimit::enabled = currentWeaponSetting.spreadLimitEnabled;
        Settings::Aimbot::SpreadLimit::value = currentWeaponSetting.spreadLimit;
        Settings::Aimbot::AutoWall::enabled = currentWeaponSetting.autoWallEnabled;
        Settings::Aimbot::AutoWall::value = currentWeaponSetting.autoWallValue;
        Settings::Aimbot::AutoSlow::enabled = currentWeaponSetting.autoSlow;
	Settings::Aimbot::Prediction::enabled = currentWeaponSetting.predEnabled;
	Settings::Aimbot::Prediction::amount = currentWeaponSetting.predAmount;
	Settings::Aimbot::ScopeControl::enabled = currentWeaponSetting.scopeControlEnabled;

        for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
                Settings::Aimbot::AutoAim::desiredBones[bone] = currentWeaponSetting.desiredBones[bone];

        Settings::Aimbot::AutoAim::realDistance = currentWeaponSetting.autoAimRealDistance;
=======
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon)
		return;

	ItemDefinitionIndex index = ItemDefinitionIndex::INVALID;
	if (Settings::Aimbot::weapons.find(*activeWeapon->GetItemDefinitionIndex()) != Settings::Aimbot::weapons.end())
		index = *activeWeapon->GetItemDefinitionIndex();

	const AimbotWeapon_t& currentWeaponSetting = Settings::Aimbot::weapons.at(index);

	Settings::Aimbot::enabled = currentWeaponSetting.enabled;
	Settings::Aimbot::silent = currentWeaponSetting.silent;
	Settings::Aimbot::friendly = currentWeaponSetting.friendly;
	Settings::Aimbot::bone = currentWeaponSetting.bone;
	Settings::Aimbot::aimkey = currentWeaponSetting.aimkey;
	Settings::Aimbot::aimkeyOnly = currentWeaponSetting.aimkeyOnly;
	Settings::Aimbot::Smooth::enabled = currentWeaponSetting.smoothEnabled;
	Settings::Aimbot::Smooth::value = currentWeaponSetting.smoothAmount;
	Settings::Aimbot::Smooth::type = currentWeaponSetting.smoothType;
	Settings::Aimbot::ErrorMargin::enabled = currentWeaponSetting.errorMarginEnabled;
	Settings::Aimbot::ErrorMargin::value = currentWeaponSetting.errorMarginValue;
	Settings::Aimbot::AutoAim::enabled = currentWeaponSetting.autoAimEnabled;
	Settings::Aimbot::AutoAim::fov = currentWeaponSetting.autoAimFov;
	Settings::Aimbot::AutoAim::closestBone = currentWeaponSetting.closestBone;
	Settings::Aimbot::AutoAim::engageLock = currentWeaponSetting.engageLock;
	Settings::Aimbot::AutoAim::engageLockTR = currentWeaponSetting.engageLockTR;
	Settings::Aimbot::AutoAim::engageLockTTR = currentWeaponSetting.engageLockTTR;
	Settings::Aimbot::AimStep::enabled = currentWeaponSetting.aimStepEnabled;
	Settings::Aimbot::AimStep::min = currentWeaponSetting.aimStepMin;
	Settings::Aimbot::AimStep::max = currentWeaponSetting.aimStepMax;
	Settings::Aimbot::AutoPistol::enabled = currentWeaponSetting.autoPistolEnabled;
	Settings::Aimbot::AutoShoot::enabled = currentWeaponSetting.autoShootEnabled;
	Settings::Aimbot::AutoShoot::autoscope = currentWeaponSetting.autoScopeEnabled;
	Settings::Aimbot::RCS::enabled = currentWeaponSetting.rcsEnabled;
	Settings::Aimbot::RCS::always_on = currentWeaponSetting.rcsAlwaysOn;
	Settings::Aimbot::RCS::valueX = currentWeaponSetting.rcsAmountX;
	Settings::Aimbot::RCS::valueY = currentWeaponSetting.rcsAmountY;
	Settings::Aimbot::NoShoot::enabled = currentWeaponSetting.noShootEnabled;
	Settings::Aimbot::IgnoreJump::enabled = currentWeaponSetting.ignoreJumpEnabled;
	Settings::Aimbot::IgnoreEnemyJump::enabled = currentWeaponSetting.ignoreEnemyJumpEnabled;
	Settings::Aimbot::Smooth::Salting::enabled = currentWeaponSetting.smoothSaltEnabled;
	Settings::Aimbot::Smooth::Salting::multiplier = currentWeaponSetting.smoothSaltMultiplier;
	Settings::Aimbot::SmokeCheck::enabled = currentWeaponSetting.smokeCheck;
	Settings::Aimbot::FlashCheck::enabled = currentWeaponSetting.flashCheck;
	Settings::Aimbot::SpreadLimit::enabled = currentWeaponSetting.spreadLimitEnabled;
	Settings::Aimbot::SpreadLimit::value = currentWeaponSetting.spreadLimit;
	Settings::Aimbot::AutoWall::enabled = currentWeaponSetting.autoWallEnabled;
	Settings::Aimbot::AutoWall::value = currentWeaponSetting.autoWallValue;
	Settings::Aimbot::AutoSlow::enabled = currentWeaponSetting.autoSlow;
	Settings::Aimbot::ScopeControl::enabled = currentWeaponSetting.scopeControlEnabled;

	for (int bone = (int) DesiredBones::BONE_PELVIS; bone <= (int) DesiredBones::BONE_RIGHT_SOLE; bone++)
		Settings::Aimbot::AutoAim::desiredBones[bone] = currentWeaponSetting.desiredBones[bone];

	Settings::Aimbot::AutoAim::realDistance = currentWeaponSetting.autoAimRealDistance;
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81
}
