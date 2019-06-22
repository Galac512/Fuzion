#pragma once

// Uncomment to enable buggy/experimental settings.
//#define EXPERIMENTAL_SETTINGS

#include <unordered_map>
#include <map>
#include "vector.h"

/* generic constants */
#define LIFE_ALIVE 0

typedef unsigned long long VPANEL;
typedef unsigned long long HFont;

class IClientMode;
class ILauncherMgr;
class ICommandLine;
class KeyValues;
class CBaseClientState;
struct CGlowObjectManager;

/* function prototypes */
typedef IClientMode* (*GetClientModeFn) (void);
typedef CGlowObjectManager* (*GlowObjectManagerFn) (void);
typedef bool (*MsgFunc_ServerRankRevealAllFn) (float*);
typedef void (*SendClanTagFn) (const char*, const char*);
typedef void (*SetLocalPlayerReadyFn) (const char*);
typedef ILauncherMgr* (*ILauncherMgrCreateFn) (void);
typedef void (*StartDrawingFn) (void*);
typedef void (*FinishDrawingFn) (void*);
typedef CBaseClientState* (*GetLocalClientFn) (int);
typedef bool (*LineGoesThroughSmokeFn) (Vector, Vector, int16_t);
typedef void (*InitKeyValuesFn) (KeyValues*, const char*);
typedef void (*LoadFromBufferFn) (KeyValues*, const char*, const char*, void*, const char*, void*);
typedef ICommandLine* (*CommandLineFn) (void);
//typedef void (*RandomSeedFn)(int);
//typedef float (*RandomFloatFn)(float, float);
//typedef float (*RandomFloatExpFn)(float, float, float);
//typedef int (*RandomIntFn)(int, int);
//typedef float (*RandomGaussianFloatFn)(float, float);
typedef bool (*SetNamedSkyBoxFn)(const char*);

extern Vector lastRayStart;
extern Vector lastRayEnd;

enum class TeamID : int
{
	TEAM_UNASSIGNED,
	TEAM_SPECTATOR,
	TEAM_TERRORIST,
	TEAM_COUNTER_TERRORIST,
};

enum class FontFeature : int
{
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6
};

enum class FontFlags : int
{
	FONTFLAG_NONE = 0,
	FONTFLAG_ITALIC = 0x1,
	FONTFLAG_UNDERLINE = 0x2,
	FONTFLAG_STRIKEOUT = 0x4,
	FONTFLAG_SYMBOL = 0x8,
	FONTFLAG_ANTIALIAS = 0x10,
	FONTFLAG_GAUSSIANBLUR = 0x20,
	FONTFLAG_ROTARY = 0x40,
	FONTFLAG_DROPSHADOW = 0x80,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum class FontDrawType_t : int
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum class ClientFrameStage_t : int
{
	// (haven't run any frames yet)
	FRAME_UNDEFINED = -1,
	FRAME_START,
	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,
	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

enum class ObserverMode_t : int
{
	OBS_MODE_NONE = 0,
	OBS_MODE_DEATHCAM = 1,
	OBS_MODE_FREEZECAM = 2,
	OBS_MODE_FIXED = 3,
	OBS_MODE_IN_EYE = 4,
	OBS_MODE_CHASE = 5,
	OBS_MODE_ROAMING = 6
};

enum class ItemDefinitionIndex : short
{
	INVALID = -1,
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5 = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SHIELD,
	WEAPON_SCAR20,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_SNOWBALL,
	WEAPON_BUMPMINE,
	WEAPON_KNIFE_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER,
	GLOVE_STUDDED_BLOODHOUND = 5027,
	GLOVE_T_SIDE = 5028,
	GLOVE_CT_SIDE = 5029,
	GLOVE_SPORTY = 5030,
	GLOVE_SLICK = 5031,
	GLOVE_LEATHER_WRAP = 5032,
	GLOVE_MOTORCYCLE = 5033,
	GLOVE_SPECIALIST = 5034,
	GLOVE_HYDRA = 5035
};

enum class EClassIds : int
{
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBRC4Target,
	CBreachCharge,
	CBreachChargeProjectile,
	CBreakableProp,
	CBreakableSurface,
	CBumpMine,
	CBumpMineProjectile,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDangerZone,
	CDangerZoneController,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDrone,
	CDronegun,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvGasCanister,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFists,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CGrassBurn,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoMapRegion,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemCash,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMelee,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParadropChopper,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPhysPropAmmoBox,
	CPhysPropLootCrate,
	CPhysPropRadarJammer,
	CPhysPropWeaponUpgrade,
	CPlantedC4,
	CPlasma,
	CPlayerPing,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropCounter,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSnowball,
	CSnowballPile,
	CSnowballProjectile,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CSurvivalSpawnChopper,
	CTablet,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponShield,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	CWorldVguiText,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail,
};

enum class ModelType : int // Something I made up
{
	//name, numOfBones, mdl file.
	//FBI - 89 (player/custom_player/legacy/ctm_fbi_variantd.mdl)
	//GIGN - 93 (player/custom_player/legacy/ctm_gign_variantb.mdl)
	//GSG - 89 (player/custom_player/legacy/ctm_gsg9.mdl)
	//IDF - 94 (player/custom_player/legacy/ctm_idf_variantd.mdl)
	//SAS - 98 (player/custom_player/legacy/ctm_sas_varianta.mdl)
	//SEALS - 89 (player/custom_player/legacy/ctm_st6_variantc.mdl)
	//SWAT - 91 (player/custom_player/legacy/ctm_swat_varianta.mdl)

	//Anarchists - 84 (player/custom_player/legacy/tm_anarchist_varianta.mdl)
	//Balkan - 86 (player/custom_player/legacy/tm_balkan_variantc.mdl)
	//Leet krew - 84 (player/custom_player/legacy/tm_leet_varianta.mdl)
    //Leet krew 2- 85 (player/custom_player/legacy/tm_leet_variantD.mdl)
    //Phoenix - 86 (player/custom_player/legacy/tm_phoenix_variantc.mdl)
	//Professionals - 91 (player/custom_player/legacy/tm_professional_var3.mdl)
	//Separatists - 86 (player/custom_player/legacy/tm_separatist_variantd.mdl)
	UNKNOWN = -1,
	FBI = 0,
	GIGN,
	GSG,
	IDF,
	SAS,
	SEALS,
	SWAT,

	ANARCHIST,
	BALKAN,
	LEETKREW,
    LEETKREW2, // dust 2 re-make
    PHOENIX,
	PROFESSIONAL,
	SEPARATIST

};
enum class DesiredBones : int // used for UI; indexing bool array; map keys for BoneMaps
{
	BONE_PELVIS = 0,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE,
	BONE_LEFT_SHOULDER,
	BONE_LEFT_ARMPIT,
	BONE_LEFT_BICEP,
	BONE_LEFT_ELBOW,
	BONE_LEFT_FOREARM,
	BONE_LEFT_WRIST,

	BONE_RIGHT_COLLARBONE,
	BONE_RIGHT_SHOULDER,
	BONE_RIGHT_ARMPIT,
	BONE_RIGHT_BICEP,
	BONE_RIGHT_ELBOW,
	BONE_RIGHT_FOREARM,
	BONE_RIGHT_WRIST,

	BONE_LEFT_BUTTCHEEK,
	BONE_LEFT_THIGH,
	BONE_LEFT_KNEE,
	BONE_LEFT_ANKLE,
	BONE_LEFT_SOLE,

	BONE_RIGHT_BUTTCHEEK,
	BONE_RIGHT_THIGH,
	BONE_RIGHT_KNEE,
	BONE_RIGHT_ANKLE,
	BONE_RIGHT_SOLE,

};
/*
static const std::map<int,std::string> BoneMapStrings // Used for debugging; putting DesiredBones to strings.
{
		{ (int)DesiredBones::BONE_PELVIS, "PELVIS" },
		{ (int)DesiredBones::BONE_HIP, "HIP" },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, "LOWER SPINE" },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN, "MIDDLE SPINE" },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, "UPPER SPINE" },
		{ (int)DesiredBones::BONE_NECK, "NECK" },
		{ (int)DesiredBones::BONE_HEAD, "HEAD" },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, "LEFT COLLARBONE" },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, "LEFT SHOULDER" },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, "LEFT ARMPIT" },
		{ (int)DesiredBones::BONE_LEFT_BICEP, "LEFT BICEP" },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, "LEFT ELBOW" },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, "LEFT FOREARM" },
		{ (int)DesiredBones::BONE_LEFT_WRIST, "LEFT WRIST" },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, "RIGHT COLLARBONE"},
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, "RIGHT SHOULDER" },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, "RIGHT ARMPIT" },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, "RIGHT BICEP" },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, "RIGHT ELBOW" },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, "RIGHT FOREARM" },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, "RIGHT WRIST" },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, "LEFT BUTTCHEEK" },
		{ (int)DesiredBones::BONE_LEFT_THIGH, "LEFT THIGH" },
		{ (int)DesiredBones::BONE_LEFT_KNEE, "LEFT KNEE" },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, "LEFT ANKLE" },
		{ (int)DesiredBones::BONE_LEFT_SOLE, "LEFT SOLE" },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, "RIGHT BUTTCHEEK" },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, "RIGHT THIGH" },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, "RIGHT KNEE" },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, "RIGHT ANKLE" },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, "RIGHT SOLE" }
};
 */
enum class Bone : int
{
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

};
/* If we cannot identify the model type (perhaps a custom model), these should be the same on most models */
static const std::map<int,int> BoneMapGeneric =
{
		{ (int)DesiredBones::BONE_PELVIS, 0 },
		{ (int)DesiredBones::BONE_HIP, 3 },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, 4 },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,5 },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, 6 },
		{ (int)DesiredBones::BONE_NECK, 7 },
		{ (int)DesiredBones::BONE_HEAD, 8 },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)Bone::INVALID },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)Bone::INVALID }
};

/* Militia, Assault, Office */
enum class BoneCT_FBI : int
{
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 10,
	BONE_LEFT_SHOULDER = 11,
	BONE_LEFT_ARMPIT = 36,
	BONE_LEFT_BICEP = 37,
	BONE_LEFT_ELBOW = 12,
	BONE_LEFT_FOREARM = 34,
	BONE_LEFT_WRIST = 13,

	BONE_RIGHT_COLLARBONE = 38,
	BONE_RIGHT_SHOULDER = 66,
	BONE_RIGHT_ARMPIT = 39,
	BONE_RIGHT_BICEP = 65,
	BONE_RIGHT_ELBOW = 40,
	BONE_RIGHT_FOREARM = 62,
	BONE_RIGHT_WRIST = 41,

	BONE_LEFT_BUTTCHEEK = 71,
	BONE_LEFT_THIGH = 76,
	BONE_LEFT_KNEE = 72,
	BONE_LEFT_ANKLE = 73,
	BONE_LEFT_SOLE = 75,

	BONE_RIGHT_BUTTCHEEK = 80,
	BONE_RIGHT_THIGH = 85,
	BONE_RIGHT_KNEE = 81,
	BONE_RIGHT_ANKLE = 82,
	BONE_RIGHT_SOLE = 83
};
static const std::map<int,int> BoneMapCT_FBI =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneCT_FBI::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneCT_FBI::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneCT_FBI::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneCT_FBI::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneCT_FBI::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneCT_FBI::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneCT_FBI::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneCT_FBI::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneCT_FBI::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneCT_FBI::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneCT_FBI::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneCT_FBI::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneCT_FBI::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneCT_FBI::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneCT_FBI::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneCT_FBI::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneCT_FBI::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneCT_FBI::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneCT_FBI::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneCT_FBI::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneCT_FBI::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneCT_FBI::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneCT_FBI::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneCT_FBI::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneCT_FBI::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneCT_FBI::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneCT_FBI::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneCT_FBI::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneCT_FBI::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneCT_FBI::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneCT_FBI::BONE_RIGHT_SOLE }
};
/* Cobblestone, Italy, Cache */
enum class BoneCT_GIGN: int
{
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 10,
	BONE_LEFT_DELTOID = 38, // The left side has a deltoid for some reason.
	BONE_LEFT_SHOULDER = 11,
	BONE_LEFT_ARMPIT = 36,
	BONE_LEFT_BICEP = 37,
	BONE_LEFT_ELBOW = 12,
	BONE_LEFT_FOREARM = 34,
	BONE_LEFT_WRIST = 13,

	BONE_RIGHT_COLLARBONE = 39,
	BONE_RIGHT_SHOULDER = 40,
	BONE_RIGHT_ARMPIT = 65,
	BONE_RIGHT_BICEP = 66,
	BONE_RIGHT_ELBOW = 41,
	BONE_RIGHT_FOREARM = 63,
	BONE_RIGHT_WRIST = 42,

	BONE_LEFT_BUTTCHEEK = 69,
	BONE_LEFT_THIGH = 74,
	BONE_LEFT_KNEE = 70,
	BONE_LEFT_ANKLE = 71,
	BONE_LEFT_SOLE = 73,

	BONE_RIGHT_BUTTCHEEK = 76,
	BONE_RIGHT_THIGH = 81,
	BONE_RIGHT_KNEE = 77,
	BONE_RIGHT_ANKLE = 78,
	BONE_RIGHT_SOLE = 79,
};
static const std::map<int,int> BoneMapCT_GIGN =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneCT_GIGN::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneCT_GIGN::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneCT_GIGN::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneCT_GIGN::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneCT_GIGN::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneCT_GIGN::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneCT_GIGN::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneCT_GIGN::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneCT_GIGN::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneCT_GIGN::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneCT_GIGN::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneCT_GIGN::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneCT_GIGN::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneCT_GIGN::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneCT_GIGN::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneCT_GIGN::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneCT_GIGN::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneCT_GIGN::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneCT_GIGN::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneCT_GIGN::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneCT_GIGN::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneCT_GIGN::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneCT_GIGN::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneCT_GIGN::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneCT_GIGN::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneCT_GIGN::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneCT_GIGN::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneCT_GIGN::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneCT_GIGN::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneCT_GIGN::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneCT_GIGN::BONE_RIGHT_SOLE }
};

/* Overpass */
enum class BoneCT_GSG: int {
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 9,
	BONE_LEFT_SHOULDER = 10,
	BONE_LEFT_BICEP = 36,
	BONE_LEFT_ELBOW = 11,
	BONE_LEFT_FOREARM = 34,
	BONE_LEFT_WRIST = 12,

	BONE_RIGHT_COLLARBONE = 37,
	BONE_RIGHT_SHOULDER = 38,
	BONE_RIGHT_BICEP = 64,
	BONE_RIGHT_ELBOW = 39,
	BONE_RIGHT_FOREARM = 62,
	BONE_RIGHT_WRIST = 40,

	BONE_LEFT_BUTTCHEEK = 65,
	BONE_LEFT_THIGH = 70,
	BONE_LEFT_KNEE = 66,
	BONE_LEFT_ANKLE = 67,
	BONE_LEFT_SOLE = 69,

	BONE_RIGHT_BUTTCHEEK = 72,
	BONE_RIGHT_THIGH = 77,
	BONE_RIGHT_KNEE = 73,
	BONE_RIGHT_ANKLE = 74,
	BONE_RIGHT_SOLE = 75
};
static const std::map<int,int> BoneMapCT_GSG =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneCT_GSG::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneCT_GSG::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneCT_GSG::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneCT_GSG::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneCT_GSG::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneCT_GSG::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneCT_GSG::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneCT_GSG::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneCT_GSG::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, -1 },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneCT_GSG::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneCT_GSG::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneCT_GSG::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneCT_GSG::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneCT_GSG::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneCT_GSG::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, -1 },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneCT_GSG::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneCT_GSG::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneCT_GSG::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneCT_GSG::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneCT_GSG::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneCT_GSG::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneCT_GSG::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneCT_GSG::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneCT_GSG::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneCT_GSG::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneCT_GSG::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneCT_GSG::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneCT_GSG::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneCT_GSG::BONE_RIGHT_SOLE }
};
/* Dust, Dust2 */
enum class BoneCT_IDF : int
{
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,
	BONE_STERNUM,

	BONE_LEFT_COLLARBONE, // 10
	BONE_LEFT_DELTOID = 11,
	BONE_LEFT_ELBOW = 12,
	BONE_LEFT_WRIST = 13,
	BONE_LEFT_FOREARM = 35,
	BONE_LEFT_BICEP = 37,
	BONE_LEFT_SHOULDER = 38,
	BONE_LEFT_ARMPIT = 39,

	BONE_RIGHT_COLLARBONE = 40,
	BONE_RIGHT_DELTOID = 41,
	BONE_RIGHT_ELBOW = 42,
	BONE_RIGHT_WRIST = 43,
	BONE_RIGHT_FOREARM = 65,
	BONE_RIGHT_BICEP = 67,
	BONE_RIGHT_SHOULDER = 68,
	BONE_RIGHT_ARMPIT = 69,

	BONE_LEFT_BUTTCHEEK = 70,
	BONE_LEFT_THIGH = 75,
	BONE_LEFT_KNEE = 71,
	BONE_LEFT_ANKLE = 72,
	BONE_LEFT_SOLE = 73,

	BONE_RIGHT_BUTTCHEEK = 77,
	BONE_RIGHT_THIGH = 82,
	BONE_RIGHT_KNEE = 78,
	BONE_RIGHT_ANKLE = 79,
	BONE_RIGHT_SOLE = 80

};
static const std::map<int,int> BoneMapCT_IDF =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneCT_IDF::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneCT_IDF::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneCT_IDF::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneCT_IDF::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneCT_IDF::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneCT_IDF::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneCT_IDF::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneCT_IDF::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneCT_IDF::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneCT_IDF::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneCT_IDF::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneCT_IDF::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneCT_IDF::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneCT_IDF::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneCT_IDF::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneCT_IDF::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneCT_IDF::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneCT_IDF::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneCT_IDF::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneCT_IDF::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneCT_IDF::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneCT_IDF::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneCT_IDF::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneCT_IDF::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneCT_IDF::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneCT_IDF::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneCT_IDF::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneCT_IDF::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneCT_IDF::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneCT_IDF::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneCT_IDF::BONE_RIGHT_SOLE }
};
/* Train, Aztec, Nuke */
enum class BoneCT_Seals : int
{
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 9,
	BONE_LEFT_SHOULDER = 10,
	BONE_LEFT_BICEP = 36,
	BONE_LEFT_ELBOW = 11,
	BONE_LEFT_FOREARM = 34,
	BONE_LEFT_WRIST = 12,

	BONE_RIGHT_COLLARBONE = 37,
	BONE_RIGHT_SHOULDER = 38,
	BONE_RIGHT_BICEP = 64,
	BONE_RIGHT_ELBOW = 39,
	BONE_RIGHT_FOREARM = 62,
	BONE_RIGHT_WRIST = 40,

	BONE_LEFT_BUTTCHEEK = 65,
	BONE_LEFT_THIGH = 70,
	BONE_LEFT_KNEE = 66,
	BONE_LEFT_ANKLE = 67,
	BONE_LEFT_SOLE = 69,

	BONE_RIGHT_BUTTCHEEK = 72,
	BONE_RIGHT_THIGH = 77,
	BONE_RIGHT_KNEE = 73,
	BONE_RIGHT_ANKLE = 74,
	BONE_RIGHT_SOLE = 75
};
static const std::map<int,int> BoneMapCT_Seals =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneCT_Seals::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneCT_Seals::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneCT_Seals::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneCT_Seals::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneCT_Seals::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneCT_Seals::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneCT_Seals::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneCT_Seals::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneCT_Seals::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, -1 },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneCT_Seals::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneCT_Seals::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneCT_Seals::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneCT_Seals::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneCT_Seals::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneCT_Seals::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT,  -1 },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneCT_Seals::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneCT_Seals::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneCT_Seals::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneCT_Seals::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneCT_Seals::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneCT_Seals::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneCT_Seals::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneCT_Seals::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneCT_Seals::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneCT_Seals::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneCT_Seals::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneCT_Seals::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneCT_Seals::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneCT_Seals::BONE_RIGHT_SOLE }
};
/* Inferno, Shorttrain, Mirage */
enum class BoneCT_SAS: int {
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 10,
	BONE_LEFT_SHOULDER = 11,
	BONE_LEFT_ARMPIT = 36,
	BONE_LEFT_BICEP = 37,
	BONE_LEFT_ELBOW = 12,
	BONE_LEFT_FOREARM = 34,
	BONE_LEFT_WRIST = 13,

	BONE_RIGHT_COLLARBONE = 39,
	BONE_RIGHT_SHOULDER = 40,
	BONE_RIGHT_ARMPIT = 65,
	BONE_RIGHT_BICEP = 66,
	BONE_RIGHT_ELBOW = 41,
	BONE_RIGHT_FOREARM = 63,
	BONE_RIGHT_WRIST = 42,

	BONE_LEFT_BUTTCHEEK = 72,
	BONE_LEFT_THIGH = 77,
	BONE_LEFT_KNEE = 73,
	BONE_LEFT_ANKLE = 74,
	BONE_LEFT_SOLE = 76,

	BONE_RIGHT_BUTTCHEEK = 81,
	BONE_RIGHT_THIGH = 87,
	BONE_RIGHT_KNEE = 82,
	BONE_RIGHT_ANKLE = 83,
	BONE_RIGHT_SOLE = 84,
};
static const std::map<int,int> BoneMapCT_SAS =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneCT_SAS::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneCT_SAS::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneCT_SAS::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneCT_SAS::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneCT_SAS::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneCT_SAS::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneCT_SAS::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneCT_SAS::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneCT_SAS::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneCT_SAS::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneCT_SAS::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneCT_SAS::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneCT_SAS::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneCT_SAS::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneCT_SAS::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneCT_SAS::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneCT_SAS::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneCT_SAS::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneCT_SAS::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneCT_SAS::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneCT_SAS::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneCT_SAS::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneCT_SAS::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneCT_SAS::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneCT_SAS::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneCT_SAS::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneCT_SAS::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneCT_SAS::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneCT_SAS::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneCT_SAS::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneCT_SAS::BONE_RIGHT_SOLE }
};
/* Vertigo */
enum class BoneCT_SWAT: int {
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_RIGHT_COLLARBONE = 11,
	BONE_RIGHT_SHOULDER = 12,
	BONE_RIGHT_ARMPIT = 37,
	BONE_RIGHT_BICEP = 38,
	BONE_RIGHT_ELBOW = 13,
	BONE_RIGHT_FOREARM = 37,
	BONE_RIGHT_WRIST = 14,

	BONE_LEFT_COLLARBONE = 39,
	BONE_LEFT_SHOULDER = 40,
	BONE_LEFT_ARMPIT = 65,
	BONE_LEFT_BICEP = 66,
	BONE_LEFT_ELBOW = 41,
	BONE_LEFT_FOREARM = 63,
	BONE_LEFT_WRIST = 42,

	BONE_LEFT_BUTTCHEEK = 67,
	BONE_LEFT_THIGH = 72,
	BONE_LEFT_KNEE = 68,
	BONE_LEFT_ANKLE = 69,
	BONE_LEFT_SOLE = 71,

	BONE_RIGHT_BUTTCHEEK = 74,
	BONE_RIGHT_THIGH = 79,
	BONE_RIGHT_KNEE = 75,
	BONE_RIGHT_ANKLE = 76,
	BONE_RIGHT_SOLE = 77
};
static const std::map<int,int> BoneMapCT_SWAT =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneCT_SWAT::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneCT_SWAT::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneCT_SWAT::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneCT_SWAT::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneCT_SWAT::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneCT_SWAT::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneCT_SWAT::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneCT_SWAT::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneCT_SWAT::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneCT_SWAT::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneCT_SWAT::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneCT_SWAT::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneCT_SWAT::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneCT_SWAT::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneCT_SWAT::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneCT_SWAT::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneCT_SWAT::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneCT_SWAT::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneCT_SWAT::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneCT_SWAT::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneCT_SWAT::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneCT_SWAT::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneCT_SWAT::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneCT_SWAT::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneCT_SWAT::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneCT_SWAT::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneCT_SWAT::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneCT_SWAT::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneCT_SWAT::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneCT_SWAT::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneCT_SWAT::BONE_RIGHT_SOLE }
};
/* Office */
enum class BoneT_Anarchist : int
{
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 11,
	BONE_LEFT_SHOULDER = 12,
	BONE_LEFT_ARMPIT = 37,
	BONE_LEFT_ELBOW = 13,
	BONE_LEFT_FOREARM = 35,
	BONE_LEFT_WRIST = 14,

	BONE_RIGHT_COLLARBONE = 39,
	BONE_RIGHT_SHOULDER = 40,
	BONE_RIGHT_ARMPIT = 65,
	BONE_RIGHT_ELBOW = 41,
	BONE_RIGHT_FOREARM = 63,
	BONE_RIGHT_WRIST = 42,

	BONE_LEFT_BUTTCHEEK = 67,
	BONE_LEFT_THIGH = 72,
	BONE_LEFT_KNEE = 68,
	BONE_LEFT_ANKLE = 69,
	BONE_LEFT_SOLE = 71,

	BONE_RIGHT_BUTTCHEEK = 74,
	BONE_RIGHT_THIGH = 79,
	BONE_RIGHT_KNEE = 75,
	BONE_RIGHT_ANKLE = 76,
	BONE_RIGHT_SOLE = 78

};
static const std::map<int,int> BoneMapT_Anarchist =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneT_Anarchist::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneT_Anarchist::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneT_Anarchist::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneT_Anarchist::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneT_Anarchist::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneT_Anarchist::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneT_Anarchist::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneT_Anarchist::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneT_Anarchist::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneT_Anarchist::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, -1 },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneT_Anarchist::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneT_Anarchist::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneT_Anarchist::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneT_Anarchist::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneT_Anarchist::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneT_Anarchist::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, -1 },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneT_Anarchist::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneT_Anarchist::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneT_Anarchist::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneT_Anarchist::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneT_Anarchist::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneT_Anarchist::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneT_Anarchist::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneT_Anarchist::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneT_Anarchist::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneT_Anarchist::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneT_Anarchist::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneT_Anarchist::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneT_Anarchist::BONE_RIGHT_SOLE }
};
enum class BoneT_Balkan: int {
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 9,
	BONE_LEFT_SHOULDER = 10,
	BONE_LEFT_ARMPIT = 35,
	BONE_LEFT_BICEP = 36,
	BONE_LEFT_ELBOW = 11,
	BONE_LEFT_FOREARM = 33,
	BONE_LEFT_WRIST = 12,

	BONE_RIGHT_COLLARBONE = 37,
	BONE_RIGHT_SHOULDER = 38,
	BONE_RIGHT_ARMPIT = 63,
	BONE_RIGHT_BICEP = 64,
	BONE_RIGHT_ELBOW = 39,
	BONE_RIGHT_FOREARM = 61,
	BONE_RIGHT_WRIST = 40,

	BONE_LEFT_BUTTCHEEK = 65,
	BONE_LEFT_THIGH = 70,
	BONE_LEFT_KNEE = 66,
	BONE_LEFT_ANKLE = 67,
	BONE_LEFT_SOLE = 69,

	BONE_RIGHT_BUTTCHEEK = 72,
	BONE_RIGHT_THIGH = 77,
	BONE_RIGHT_KNEE = 73,
	BONE_RIGHT_ANKLE = 74,
	BONE_RIGHT_SOLE = 76
};
static const std::map<int,int> BoneMapT_Balkan =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneT_Balkan::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneT_Balkan::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneT_Balkan::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneT_Balkan::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneT_Balkan::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneT_Balkan::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneT_Balkan::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneT_Balkan::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneT_Balkan::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneT_Balkan::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneT_Balkan::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneT_Balkan::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneT_Balkan::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneT_Balkan::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneT_Balkan::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneT_Balkan::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneT_Balkan::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneT_Balkan::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneT_Balkan::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneT_Balkan::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneT_Balkan::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneT_Balkan::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneT_Balkan::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneT_Balkan::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneT_Balkan::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneT_Balkan::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneT_Balkan::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneT_Balkan::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneT_Balkan::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneT_Balkan::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneT_Balkan::BONE_RIGHT_SOLE }
};
/* Dust, Dust2, Mirage */
enum class BoneT_Leet : int
{
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 9,
	BONE_LEFT_SHOULDER = 10,
	BONE_LEFT_ARMPIT = 35,
	BONE_LEFT_BICEP = 36,
	BONE_LEFT_ELBOW = 11,
	BONE_LEFT_FOREARM = 33,
	BONE_LEFT_WRIST = 12,

	BONE_RIGHT_COLLARBONE = 37,
	BONE_RIGHT_SHOULDER = 38,
	BONE_RIGHT_ARMPIT = 63,
	BONE_RIGHT_BICEP = 64,
	BONE_RIGHT_ELBOW = 39,
	BONE_RIGHT_FOREARM = 61,
	BONE_RIGHT_WRIST = 40,

	BONE_LEFT_BUTTCHEEK = 65,
	BONE_LEFT_THIGH = 70,
	BONE_LEFT_KNEE = 66,
	BONE_LEFT_ANKLE = 67,
	BONE_LEFT_SOLE = 68,

	BONE_RIGHT_BUTTCHEEK = 72,
	BONE_RIGHT_THIGH = 77,
	BONE_RIGHT_KNEE = 73,
	BONE_RIGHT_ANKLE = 74,
	BONE_RIGHT_SOLE = 75

};
static const std::map<int,int> BoneMapT_Leet =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneT_Leet::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneT_Leet::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneT_Leet::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneT_Leet::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneT_Leet::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneT_Leet::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneT_Leet::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneT_Leet::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneT_Leet::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneT_Leet::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneT_Leet::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneT_Leet::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneT_Leet::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneT_Leet::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneT_Leet::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneT_Leet::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneT_Leet::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneT_Leet::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneT_Leet::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneT_Leet::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneT_Leet::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneT_Leet::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneT_Leet::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneT_Leet::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneT_Leet::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneT_Leet::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneT_Leet::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneT_Leet::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneT_Leet::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneT_Leet::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneT_Leet::BONE_RIGHT_SOLE }
};
enum class BoneT_Leet2 : int {
    INVALID = -1,
    BONE_PELVIS = 0,
    LEAN_ROOT,
    CAM_DRIVER,
    BONE_HIP,
    BONE_LOWER_SPINAL_COLUMN,
    BONE_MIDDLE_SPINAL_COLUMN,
    BONE_UPPER_SPINAL_COLUMN,
    BONE_NECK,
    BONE_HEAD,

    BONE_LEFT_COLLARBONE = 10,
    BONE_LEFT_SHOULDER = 11,
    BONE_LEFT_ARMPIT = 11,
    BONE_LEFT_BICEP = 37,
    BONE_LEFT_ELBOW = 12,
    BONE_LEFT_FOREARM = 35,
    BONE_LEFT_WRIST = 13,

    BONE_RIGHT_COLLARBONE = 38,
    BONE_RIGHT_SHOULDER = 39,
    BONE_RIGHT_ARMPIT = 39,
    BONE_RIGHT_BICEP = 65,
    BONE_RIGHT_ELBOW = 40,
    BONE_RIGHT_FOREARM = 63,
    BONE_RIGHT_WRIST = 41,

    BONE_LEFT_BUTTCHEEK = 66,
    BONE_LEFT_THIGH = 71,
    BONE_LEFT_KNEE = 67,
    BONE_LEFT_ANKLE = 68,
    BONE_LEFT_SOLE = 69,

    BONE_RIGHT_BUTTCHEEK = 73,
    BONE_RIGHT_THIGH = 78,
    BONE_RIGHT_KNEE = 74,
    BONE_RIGHT_ANKLE = 75,
    BONE_RIGHT_SOLE = 77
};
static const std::map<int, int> BoneMapT_Leet2 =
{
        { ( int ) DesiredBones::BONE_PELVIS,               ( int ) BoneT_Leet2::BONE_PELVIS },
        { ( int ) DesiredBones::BONE_HIP,                  ( int ) BoneT_Leet2::BONE_HIP },
        { ( int ) DesiredBones::BONE_LOWER_SPINAL_COLUMN,  ( int ) BoneT_Leet2::BONE_LOWER_SPINAL_COLUMN },
        { ( int ) DesiredBones::BONE_MIDDLE_SPINAL_COLUMN, ( int ) BoneT_Leet2::BONE_MIDDLE_SPINAL_COLUMN },
        { ( int ) DesiredBones::BONE_UPPER_SPINAL_COLUMN,  ( int ) BoneT_Leet2::BONE_UPPER_SPINAL_COLUMN },
        { ( int ) DesiredBones::BONE_NECK,                 ( int ) BoneT_Leet2::BONE_NECK },
        { ( int ) DesiredBones::BONE_HEAD,                 ( int ) BoneT_Leet2::BONE_HEAD },
        { ( int ) DesiredBones::BONE_LEFT_COLLARBONE,      ( int ) BoneT_Leet2::BONE_LEFT_COLLARBONE },
        { ( int ) DesiredBones::BONE_LEFT_SHOULDER,        ( int ) BoneT_Leet2::BONE_LEFT_SHOULDER },
        { ( int ) DesiredBones::BONE_LEFT_ARMPIT,          ( int ) BoneT_Leet2::BONE_LEFT_ARMPIT },
        { ( int ) DesiredBones::BONE_LEFT_BICEP,           ( int ) BoneT_Leet2::BONE_LEFT_BICEP },
        { ( int ) DesiredBones::BONE_LEFT_ELBOW,           ( int ) BoneT_Leet2::BONE_LEFT_ELBOW },
        { ( int ) DesiredBones::BONE_LEFT_FOREARM,         ( int ) BoneT_Leet2::BONE_LEFT_FOREARM },
        { ( int ) DesiredBones::BONE_LEFT_WRIST,           ( int ) BoneT_Leet2::BONE_LEFT_WRIST },
        { ( int ) DesiredBones::BONE_RIGHT_COLLARBONE,     ( int ) BoneT_Leet2::BONE_RIGHT_COLLARBONE },
        { ( int ) DesiredBones::BONE_RIGHT_SHOULDER,       ( int ) BoneT_Leet2::BONE_RIGHT_SHOULDER },
        { ( int ) DesiredBones::BONE_RIGHT_ARMPIT,         ( int ) BoneT_Leet2::BONE_RIGHT_ARMPIT },
        { ( int ) DesiredBones::BONE_RIGHT_BICEP,          ( int ) BoneT_Leet2::BONE_RIGHT_BICEP },
        { ( int ) DesiredBones::BONE_RIGHT_ELBOW,          ( int ) BoneT_Leet2::BONE_RIGHT_ELBOW },
        { ( int ) DesiredBones::BONE_RIGHT_FOREARM,        ( int ) BoneT_Leet2::BONE_RIGHT_FOREARM },
        { ( int ) DesiredBones::BONE_RIGHT_WRIST,          ( int ) BoneT_Leet2::BONE_RIGHT_WRIST },
        { ( int ) DesiredBones::BONE_LEFT_BUTTCHEEK,       ( int ) BoneT_Leet2::BONE_LEFT_BUTTCHEEK },
        { ( int ) DesiredBones::BONE_LEFT_THIGH,           ( int ) BoneT_Leet2::BONE_LEFT_THIGH },
        { ( int ) DesiredBones::BONE_LEFT_KNEE,            ( int ) BoneT_Leet2::BONE_LEFT_KNEE },
        { ( int ) DesiredBones::BONE_LEFT_ANKLE,           ( int ) BoneT_Leet2::BONE_LEFT_ANKLE },
        { ( int ) DesiredBones::BONE_LEFT_SOLE,            ( int ) BoneT_Leet2::BONE_LEFT_SOLE },
        { ( int ) DesiredBones::BONE_RIGHT_BUTTCHEEK,      ( int ) BoneT_Leet2::BONE_RIGHT_BUTTCHEEK },
        { ( int ) DesiredBones::BONE_RIGHT_THIGH,          ( int ) BoneT_Leet2::BONE_RIGHT_THIGH },
        { ( int ) DesiredBones::BONE_RIGHT_KNEE,           ( int ) BoneT_Leet2::BONE_RIGHT_KNEE },
        { ( int ) DesiredBones::BONE_RIGHT_ANKLE,          ( int ) BoneT_Leet2::BONE_RIGHT_ANKLE },
        { ( int ) DesiredBones::BONE_RIGHT_SOLE,           ( int ) BoneT_Leet2::BONE_RIGHT_SOLE }
};
/* Aztec, Cobblestone, Assault, Militia, Cache, Nuke */
enum class BoneT_Phoenix : int {
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 9,
	BONE_LEFT_SHOULDER = 10,
	BONE_LEFT_ARMPIT = 35,
	BONE_LEFT_BICEP = 36,
	BONE_LEFT_ELBOW = 11,
	BONE_LEFT_FOREARM = 33,
	BONE_LEFT_WRIST = 12,

	BONE_RIGHT_COLLARBONE = 37,
	BONE_RIGHT_SHOULDER = 38,
	BONE_RIGHT_ARMPIT = 63,
	BONE_RIGHT_BICEP = 64,
	BONE_RIGHT_ELBOW = 39,
	BONE_RIGHT_FOREARM = 61,
	BONE_RIGHT_WRIST = 40,

	BONE_LEFT_BUTTCHEEK = 65,
	BONE_LEFT_THIGH = 70,
	BONE_LEFT_KNEE = 66,
	BONE_LEFT_ANKLE = 67,
	BONE_LEFT_SOLE = 69,

	BONE_RIGHT_BUTTCHEEK = 72,
	BONE_RIGHT_THIGH = 77,
	BONE_RIGHT_KNEE = 73,
	BONE_RIGHT_ANKLE = 74,
	BONE_RIGHT_SOLE = 76
};
static const std::map<int,int> BoneMapT_Phoenix =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneT_Phoenix::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneT_Phoenix::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneT_Phoenix::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneT_Phoenix::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneT_Phoenix::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneT_Phoenix::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneT_Phoenix::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneT_Phoenix::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneT_Phoenix::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneT_Phoenix::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneT_Phoenix::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneT_Phoenix::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneT_Phoenix::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneT_Phoenix::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneT_Phoenix::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneT_Phoenix::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneT_Phoenix::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneT_Phoenix::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneT_Phoenix::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneT_Phoenix::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneT_Phoenix::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneT_Phoenix::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneT_Phoenix::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneT_Phoenix::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneT_Phoenix::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneT_Phoenix::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneT_Phoenix::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneT_Phoenix::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneT_Phoenix::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneT_Phoenix::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneT_Phoenix::BONE_RIGHT_SOLE }
};
/* Bank, Vertigo, Safehouse */
enum class BoneT_Professional : int {
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 10,
	BONE_LEFT_SHOULDER = 11,
	BONE_LEFT_ARMPIT = 36,
	BONE_LEFT_BICEP = 37,
	BONE_LEFT_ELBOW = 12,
	BONE_LEFT_FOREARM = 34,
	BONE_LEFT_WRIST = 13,

	BONE_RIGHT_COLLARBONE = 38,
	BONE_RIGHT_SHOULDER = 39,
	BONE_RIGHT_ARMPIT = 64,
	BONE_RIGHT_BICEP = 65,
	BONE_RIGHT_ELBOW = 40,
	BONE_RIGHT_FOREARM = 62,
	BONE_RIGHT_WRIST = 41,

	BONE_LEFT_BUTTCHEEK = 70,
	BONE_LEFT_THIGH = 75,
	BONE_LEFT_KNEE = 71,
	BONE_LEFT_ANKLE = 72,
	BONE_LEFT_SOLE = 74,

	BONE_RIGHT_BUTTCHEEK = 77,
	BONE_RIGHT_THIGH = 82,
	BONE_RIGHT_KNEE = 78,
	BONE_RIGHT_ANKLE = 79,
	BONE_RIGHT_SOLE = 80,
};
static const std::map<int,int> BoneMapT_Professional =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneT_Professional::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneT_Professional::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneT_Professional::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneT_Professional::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneT_Professional::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneT_Professional::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneT_Professional::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneT_Professional::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneT_Professional::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneT_Professional::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneT_Professional::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneT_Professional::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneT_Professional::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneT_Professional::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneT_Professional::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneT_Professional::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneT_Professional::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneT_Professional::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneT_Professional::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneT_Professional::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneT_Professional::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneT_Professional::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneT_Professional::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneT_Professional::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneT_Professional::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneT_Professional::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneT_Professional::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneT_Professional::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneT_Professional::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneT_Professional::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneT_Professional::BONE_RIGHT_SOLE }
};
/* Inferno, Italy */
enum class BoneT_Separatist : int {
	INVALID = -1,
	BONE_PELVIS = 0,
	LEAN_ROOT,
	CAM_DRIVER,
	BONE_HIP,
	BONE_LOWER_SPINAL_COLUMN,
	BONE_MIDDLE_SPINAL_COLUMN,
	BONE_UPPER_SPINAL_COLUMN,
	BONE_NECK,
	BONE_HEAD,

	BONE_LEFT_COLLARBONE = 9,
	BONE_LEFT_SHOULDER = 10,
	BONE_LEFT_ARMPIT = 35,
	BONE_LEFT_BICEP = 36,
	BONE_LEFT_ELBOW = 11,
	BONE_LEFT_FOREARM = 33,
	BONE_LEFT_WRIST = 12,

	BONE_RIGHT_COLLARBONE = 37,
	BONE_RIGHT_SHOULDER = 38,
	BONE_RIGHT_ARMPIT = 63,
	BONE_RIGHT_BICEP = 64,
	BONE_RIGHT_ELBOW = 39,
	BONE_RIGHT_FOREARM = 61,
	BONE_RIGHT_WRIST = 40,

	BONE_LEFT_BUTTCHEEK = 65,
	BONE_LEFT_THIGH = 70,
	BONE_LEFT_KNEE = 66,
	BONE_LEFT_ANKLE = 67,
	BONE_LEFT_SOLE = 79,

	BONE_RIGHT_BUTTCHEEK = 72,
	BONE_RIGHT_THIGH = 77,
	BONE_RIGHT_KNEE = 73,
	BONE_RIGHT_ANKLE = 74,
	BONE_RIGHT_SOLE = 75
};
static const std::map<int,int> BoneMapT_Separatist =
{
		{ (int)DesiredBones::BONE_PELVIS, (int)BoneT_Separatist::BONE_PELVIS },
		{ (int)DesiredBones::BONE_HIP, (int)BoneT_Separatist::BONE_HIP },
		{ (int)DesiredBones::BONE_LOWER_SPINAL_COLUMN, (int)BoneT_Separatist::BONE_LOWER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_MIDDLE_SPINAL_COLUMN,(int)BoneT_Separatist::BONE_MIDDLE_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_UPPER_SPINAL_COLUMN, (int)BoneT_Separatist::BONE_UPPER_SPINAL_COLUMN },
		{ (int)DesiredBones::BONE_NECK, (int)BoneT_Separatist::BONE_NECK },
		{ (int)DesiredBones::BONE_HEAD, (int)BoneT_Separatist::BONE_HEAD },
		{ (int)DesiredBones::BONE_LEFT_COLLARBONE, (int)BoneT_Separatist::BONE_LEFT_COLLARBONE },
		{ (int)DesiredBones::BONE_LEFT_SHOULDER, (int)BoneT_Separatist::BONE_LEFT_SHOULDER },
		{ (int)DesiredBones::BONE_LEFT_ARMPIT, (int)BoneT_Separatist::BONE_LEFT_ARMPIT },
		{ (int)DesiredBones::BONE_LEFT_BICEP, (int)BoneT_Separatist::BONE_LEFT_BICEP },
		{ (int)DesiredBones::BONE_LEFT_ELBOW, (int)BoneT_Separatist::BONE_LEFT_ELBOW },
		{ (int)DesiredBones::BONE_LEFT_FOREARM, (int)BoneT_Separatist::BONE_LEFT_FOREARM },
		{ (int)DesiredBones::BONE_LEFT_WRIST, (int)BoneT_Separatist::BONE_LEFT_WRIST },
		{ (int)DesiredBones::BONE_RIGHT_COLLARBONE, (int)BoneT_Separatist::BONE_RIGHT_COLLARBONE },
		{ (int)DesiredBones::BONE_RIGHT_SHOULDER, (int)BoneT_Separatist::BONE_RIGHT_SHOULDER },
		{ (int)DesiredBones::BONE_RIGHT_ARMPIT, (int)BoneT_Separatist::BONE_RIGHT_ARMPIT },
		{ (int)DesiredBones::BONE_RIGHT_BICEP, (int)BoneT_Separatist::BONE_RIGHT_BICEP },
		{ (int)DesiredBones::BONE_RIGHT_ELBOW, (int)BoneT_Separatist::BONE_RIGHT_ELBOW },
		{ (int)DesiredBones::BONE_RIGHT_FOREARM, (int)BoneT_Separatist::BONE_RIGHT_FOREARM },
		{ (int)DesiredBones::BONE_RIGHT_WRIST, (int)BoneT_Separatist::BONE_RIGHT_WRIST },
		{ (int)DesiredBones::BONE_LEFT_BUTTCHEEK, (int)BoneT_Separatist::BONE_LEFT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_LEFT_THIGH, (int)BoneT_Separatist::BONE_LEFT_THIGH },
		{ (int)DesiredBones::BONE_LEFT_KNEE, (int)BoneT_Separatist::BONE_LEFT_KNEE },
		{ (int)DesiredBones::BONE_LEFT_ANKLE, (int)BoneT_Separatist::BONE_LEFT_ANKLE },
		{ (int)DesiredBones::BONE_LEFT_SOLE, (int)BoneT_Separatist::BONE_LEFT_SOLE },
		{ (int)DesiredBones::BONE_RIGHT_BUTTCHEEK, (int)BoneT_Separatist::BONE_RIGHT_BUTTCHEEK },
		{ (int)DesiredBones::BONE_RIGHT_THIGH, (int)BoneT_Separatist::BONE_RIGHT_THIGH },
		{ (int)DesiredBones::BONE_RIGHT_KNEE, (int)BoneT_Separatist::BONE_RIGHT_KNEE },
		{ (int)DesiredBones::BONE_RIGHT_ANKLE, (int)BoneT_Separatist::BONE_RIGHT_ANKLE },
		{ (int)DesiredBones::BONE_RIGHT_SOLE, (int)BoneT_Separatist::BONE_RIGHT_SOLE }
};

enum class Hitbox : int
{
	HITBOX_HEAD = 0,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_SPINE,
	HITBOX_LEGS,
	HITBOX_ARMS,
};

enum class HitGroups : int
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD,
	HITGROUP_CHEST,
	HITGROUP_STOMACH,
	HITGROUP_LEFTARM,
	HITGROUP_RIGHTARM,
	HITGROUP_LEFTLEG,
	HITGROUP_RIGHTLEG,
	HITGROUP_GEAR
};

enum class CSWeaponType : int
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	FUZION_TOP_SECRET_WEAPONTYPE_CONFIDENTIAL_DO_NOT_STEAL,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN

};

struct DefItem_t
{
	DefItem_t(const char* displayName,
			  const char* entityName,
			  const char* entityModel,
			  const char* killIcon = nullptr)
	{
		this->displayName = displayName;
		this->entityName = entityName;
		this->entityModel = entityModel;
		this->killIcon = killIcon;
	}

	const char* displayName = nullptr;
	const char* entityName = nullptr;
	const char* entityModel = nullptr;
	const char* killIcon = nullptr;
};

struct AttribItem_t
{
	void Reset()
	{
		this->entityQuality = -1;
		this->fallbackSeed = -1;
		this->fallbackPaintKit = -1;
		this->fallbackStatTrak = -1;
		this->fallbackStatTrak = -1;
		this->itemDefinitionIndex = ItemDefinitionIndex::INVALID;
		this->customName = "";
	}

	ItemDefinitionIndex itemDefinitionIndex = ItemDefinitionIndex::INVALID;
	int fallbackPaintKit = -1;
	float fallbackWear = -1;
	int fallbackSeed = -1;
	int fallbackStatTrak = -1;
	int entityQuality = -1;
	std::string customName;
};


enum GrenadeType : int
{
	FLASH,
	SMOKE,
	MOLOTOV,
	HEGRENADE
};

enum ThrowType : int
{
	NORMAL,
	RUN,
	JUMP,
	WALK
};

enum TracerEffects_t : int
{
    ASSRIFLE,
    PISTOL,
    SMG,
    RIFLE,
    TASER, // Also known as "Kisak Snot"
    MACH,
    SHOT,

    TASER_FALLBACK,
    TASER_FALLBACK2,
    TASER_WIRE1A,
    TASER_WIRE2,
    TASER_WIRE1B,
    ORIGINAL,
    BACKUP,
    FIFTY_CAL,
    FIFTY_CAL_GLOW,
    FIFTY_CAL_LOW,
    FIFTY_CAL_LOW_GLOW,
};

enum class CCSGOAnimStatePoses : int
{
  ACT_RESET,
  ACT_IDLE,
  ACT_TRANSITION,
  ACT_COVER,
  ACT_COVER_MED,
  ACT_COVER_LOW,
  ACT_WALK,
  ACT_WALK_AIM,
  ACT_WALK_CROUCH,
  ACT_WALK_CROUCH_AIM,
  ACT_RUN,
  ACT_RUN_AIM,
  ACT_RUN_CROUCH,
  ACT_RUN_CROUCH_AIM,
  ACT_RUN_PROTECTED,
  ACT_SCRIPT_CUSTOM_MOVE,
  ACT_RANGE_ATTACK1,
  ACT_RANGE_ATTACK2,
  ACT_RANGE_ATTACK1_LOW,
  ACT_RANGE_ATTACK2_LOW,
  ACT_DIESIMPLE,
  ACT_DIEBACKWARD,
  ACT_DIEFORWARD,
  ACT_DIEVIOLENT,
  ACT_DIERAGDOLL,
  ACT_FLY,
  ACT_HOVER,
  ACT_GLIDE,
  ACT_SWIM,
  ACT_JUMP,
  ACT_HOP,
  ACT_LEAP,
  ACT_LAND,
  ACT_CLIMB_UP,
  ACT_CLIMB_DOWN,
  ACT_CLIMB_DISMOUNT,
  ACT_SHIPLADDER_UP,
  ACT_SHIPLADDER_DOWN,
  ACT_STRAFE_LEFT,
  ACT_STRAFE_RIGHT,
  ACT_ROLL_LEFT,
  ACT_ROLL_RIGHT,
  ACT_TURN_LEFT,
  ACT_TURN_RIGHT,
  ACT_CROUCH,
  ACT_CROUCHIDLE,
  ACT_STAND,
  ACT_USE,
  ACT_ALIEN_BURROW_IDLE,
  ACT_ALIEN_BURROW_OUT,
  ACT_SIGNAL1,
  ACT_SIGNAL2,
  ACT_SIGNAL3,
  ACT_SIGNAL_ADVANCE,
  ACT_SIGNAL_FORWARD,
  ACT_SIGNAL_GROUP,
  ACT_SIGNAL_HALT,
  ACT_SIGNAL_LEFT,
  ACT_SIGNAL_RIGHT,
  ACT_SIGNAL_TAKECOVER,
  ACT_LOOKBACK_RIGHT,
  ACT_LOOKBACK_LEFT,
  ACT_COWER,
  ACT_SMALL_FLINCH,
  ACT_BIG_FLINCH,
  ACT_MELEE_ATTACK1,
  ACT_MELEE_ATTACK2,
  ACT_RELOAD,
  ACT_RELOAD_START,
  ACT_RELOAD_FINISH,
  ACT_RELOAD_LOW,
  ACT_ARM,
  ACT_DISARM,
  ACT_DROP_WEAPON,
  ACT_DROP_WEAPON_SHOTGUN,
  ACT_PICKUP_GROUND,
  ACT_PICKUP_RACK,
  ACT_IDLE_ANGRY,
  ACT_IDLE_RELAXED,
  ACT_IDLE_STIMULATED,
  ACT_IDLE_AGITATED,
  ACT_IDLE_STEALTH,
  ACT_IDLE_HURT,
  ACT_WALK_RELAXED,
  ACT_WALK_STIMULATED,
  ACT_WALK_AGITATED,
  ACT_WALK_STEALTH,
  ACT_RUN_RELAXED,
  ACT_RUN_STIMULATED,
  ACT_RUN_AGITATED,
  ACT_RUN_STEALTH,
  ACT_IDLE_AIM_RELAXED,
  ACT_IDLE_AIM_STIMULATED,
  ACT_IDLE_AIM_AGITATED,
  ACT_IDLE_AIM_STEALTH,
  ACT_WALK_AIM_RELAXED,
  ACT_WALK_AIM_STIMULATED,
  ACT_WALK_AIM_AGITATED,
  ACT_WALK_AIM_STEALTH,
  ACT_RUN_AIM_RELAXED,
  ACT_RUN_AIM_STIMULATED,
  ACT_RUN_AIM_AGITATED,
  ACT_RUN_AIM_STEALTH,
  ACT_CROUCHIDLE_STIMULATED,
  ACT_CROUCHIDLE_AIM_STIMULATED,
  ACT_CROUCHIDLE_AGITATED,
  ACT_WALK_HURT,
  ACT_RUN_HURT,
  ACT_SPECIAL_ATTACK1,
  ACT_SPECIAL_ATTACK2,
  ACT_COMBAT_IDLE,
  ACT_WALK_SCARED,
  ACT_RUN_SCARED,
  ACT_VICTORY_DANCE,
  ACT_DIE_HEADSHOT,
  ACT_DIE_CHESTSHOT,
  ACT_DIE_GUTSHOT,
  ACT_DIE_BACKSHOT,
  ACT_FLINCH_HEAD,
  ACT_FLINCH_CHEST,
  ACT_FLINCH_STOMACH,
  ACT_FLINCH_LEFTARM,
  ACT_FLINCH_RIGHTARM,
  ACT_FLINCH_LEFTLEG,
  ACT_FLINCH_RIGHTLEG,
  ACT_FLINCH_PHYSICS,
  ACT_FLINCH_HEAD_BACK,
  ACT_FLINCH_HEAD_LEFT,
  ACT_FLINCH_HEAD_RIGHT,
  ACT_FLINCH_CHEST_BACK,
  ACT_FLINCH_STOMACH_BACK,
  ACT_FLINCH_CROUCH_FRONT,
  ACT_FLINCH_CROUCH_BACK,
  ACT_FLINCH_CROUCH_LEFT,
  ACT_FLINCH_CROUCH_RIGHT,
  ACT_IDLE_ON_FIRE,
  ACT_WALK_ON_FIRE,
  ACT_RUN_ON_FIRE,
  ACT_RAPPEL_LOOP,
  ACT_180_LEFT,
  ACT_180_RIGHT,
  ACT_90_LEFT,
  ACT_90_RIGHT,
  ACT_STEP_LEFT,
  ACT_STEP_RIGHT,
  ACT_STEP_BACK,
  ACT_STEP_FORE,
  ACT_GESTURE_RANGE_ATTACK1,
  ACT_GESTURE_RANGE_ATTACK2,
  ACT_GESTURE_MELEE_ATTACK1,
  ACT_GESTURE_MELEE_ATTACK2,
  ACT_GESTURE_RANGE_ATTACK1_LOW,
  ACT_GESTURE_RANGE_ATTACK2_LOW,
  ACT_MELEE_ATTACK_SWING_GESTURE,
  ACT_GESTURE_SMALL_FLINCH,
  ACT_GESTURE_BIG_FLINCH,
  ACT_GESTURE_FLINCH_BLAST,
  ACT_GESTURE_FLINCH_BLAST_SHOTGUN,
  ACT_GESTURE_FLINCH_BLAST_DAMAGED,
  ACT_GESTURE_FLINCH_BLAST_DAMAGED_SHOTGUN,
  ACT_GESTURE_FLINCH_HEAD,
  ACT_GESTURE_FLINCH_CHEST,
  ACT_GESTURE_FLINCH_STOMACH,
  ACT_GESTURE_FLINCH_LEFTARM,
  ACT_GESTURE_FLINCH_RIGHTARM,
  ACT_GESTURE_FLINCH_LEFTLEG,
  ACT_GESTURE_FLINCH_RIGHTLEG,
  ACT_GESTURE_TURN_LEFT,
  ACT_GESTURE_TURN_RIGHT,
  ACT_GESTURE_TURN_LEFT45,
  ACT_GESTURE_TURN_RIGHT45,
  ACT_GESTURE_TURN_LEFT90,
  ACT_GESTURE_TURN_RIGHT90,
  ACT_GESTURE_TURN_LEFT45_FLAT,
  ACT_GESTURE_TURN_RIGHT45_FLAT,
  ACT_GESTURE_TURN_LEFT90_FLAT,
  ACT_GESTURE_TURN_RIGHT90_FLAT,
  ACT_BARNACLE_HIT,
  ACT_BARNACLE_PULL,
  ACT_BARNACLE_CHOMP,
  ACT_BARNACLE_CHEW,
  ACT_DO_NOT_DISTURB,
  ACT_SPECIFIC_SEQUENCE,
  ACT_VM_DRAW,
  ACT_VM_HOLSTER,
  ACT_VM_IDLE,
  ACT_VM_FIDGET,
  ACT_VM_PULLBACK,
  ACT_VM_PULLBACK_HIGH,
  ACT_VM_PULLBACK_LOW,
  ACT_VM_THROW,
  ACT_VM_PULLPIN,
  ACT_VM_PRIMARYATTACK,
  ACT_VM_SECONDARYATTACK,
  ACT_VM_RELOAD,
  ACT_VM_DRYFIRE,
  ACT_VM_HITLEFT,
  ACT_VM_HITLEFT2,
  ACT_VM_HITRIGHT,
  ACT_VM_HITRIGHT2,
  ACT_VM_HITCENTER,
  ACT_VM_HITCENTER2,
  ACT_VM_MISSLEFT,
  ACT_VM_MISSLEFT2,
  ACT_VM_MISSRIGHT,
  ACT_VM_MISSRIGHT2,
  ACT_VM_MISSCENTER,
  ACT_VM_MISSCENTER2,
  ACT_VM_HAULBACK,
  ACT_VM_SWINGHARD,
  ACT_VM_SWINGMISS,
  ACT_VM_SWINGHIT,
  ACT_VM_IDLE_TO_LOWERED,
  ACT_VM_IDLE_LOWERED,
  ACT_VM_LOWERED_TO_IDLE,
  ACT_VM_RECOIL1,
  ACT_VM_RECOIL2,
  ACT_VM_RECOIL3,
  ACT_VM_PICKUP,
  ACT_VM_RELEASE,
  ACT_VM_ATTACH_SILENCER,
  ACT_VM_DETACH_SILENCER,
  ACT_VM_EMPTY_FIRE,
  ACT_VM_EMPTY_RELOAD,
  ACT_VM_EMPTY_DRAW,
  ACT_VM_EMPTY_IDLE,
  ACT_SLAM_STICKWALL_IDLE,
  ACT_SLAM_STICKWALL_ND_IDLE,
  ACT_SLAM_STICKWALL_ATTACH,
  ACT_SLAM_STICKWALL_ATTACH2,
  ACT_SLAM_STICKWALL_ND_ATTACH,
  ACT_SLAM_STICKWALL_ND_ATTACH2,
  ACT_SLAM_STICKWALL_DETONATE,
  ACT_SLAM_STICKWALL_DETONATOR_HOLSTER,
  ACT_SLAM_STICKWALL_DRAW,
  ACT_SLAM_STICKWALL_ND_DRAW,
  ACT_SLAM_STICKWALL_TO_THROW,
  ACT_SLAM_STICKWALL_TO_THROW_ND,
  ACT_SLAM_STICKWALL_TO_TRIPMINE_ND,
  ACT_SLAM_THROW_IDLE,
  ACT_SLAM_THROW_ND_IDLE,
  ACT_SLAM_THROW_THROW,
  ACT_SLAM_THROW_THROW2,
  ACT_SLAM_THROW_THROW_ND,
  ACT_SLAM_THROW_THROW_ND2,
  ACT_SLAM_THROW_DRAW,
  ACT_SLAM_THROW_ND_DRAW,
  ACT_SLAM_THROW_TO_STICKWALL,
  ACT_SLAM_THROW_TO_STICKWALL_ND,
  ACT_SLAM_THROW_DETONATE,
  ACT_SLAM_THROW_DETONATOR_HOLSTER,
  ACT_SLAM_THROW_TO_TRIPMINE_ND,
  ACT_SLAM_TRIPMINE_IDLE,
  ACT_SLAM_TRIPMINE_DRAW,
  ACT_SLAM_TRIPMINE_ATTACH,
  ACT_SLAM_TRIPMINE_ATTACH2,
  ACT_SLAM_TRIPMINE_TO_STICKWALL_ND,
  ACT_SLAM_TRIPMINE_TO_THROW_ND,
  ACT_SLAM_DETONATOR_IDLE,
  ACT_SLAM_DETONATOR_DRAW,
  ACT_SLAM_DETONATOR_DETONATE,
  ACT_SLAM_DETONATOR_HOLSTER,
  ACT_SLAM_DETONATOR_STICKWALL_DRAW,
  ACT_SLAM_DETONATOR_THROW_DRAW,
  ACT_SHOTGUN_RELOAD_START,
  ACT_SHOTGUN_RELOAD_FINISH,
  ACT_SHOTGUN_PUMP,
  ACT_SMG2_IDLE2,
  ACT_SMG2_FIRE2,
  ACT_SMG2_DRAW2,
  ACT_SMG2_RELOAD2,
  ACT_SMG2_DRYFIRE2,
  ACT_SMG2_TOAUTO,
  ACT_SMG2_TOBURST,
  ACT_PHYSCANNON_UPGRADE,
  ACT_RANGE_ATTACK_AR1,
  ACT_RANGE_ATTACK_AR2,
  ACT_RANGE_ATTACK_AR2_LOW,
  ACT_RANGE_ATTACK_AR2_GRENADE,
  ACT_RANGE_ATTACK_HMG1,
  ACT_RANGE_ATTACK_ML,
  ACT_RANGE_ATTACK_SMG1,
  ACT_RANGE_ATTACK_SMG1_LOW,
  ACT_RANGE_ATTACK_SMG2,
  ACT_RANGE_ATTACK_SHOTGUN,
  ACT_RANGE_ATTACK_SHOTGUN_LOW,
  ACT_RANGE_ATTACK_PISTOL,
  ACT_RANGE_ATTACK_PISTOL_LOW,
  ACT_RANGE_ATTACK_SLAM,
  ACT_RANGE_ATTACK_TRIPWIRE,
  ACT_RANGE_ATTACK_THROW,
  ACT_RANGE_ATTACK_SNIPER_RIFLE,
  ACT_RANGE_ATTACK_RPG,
  ACT_MELEE_ATTACK_SWING,
  ACT_RANGE_AIM_LOW,
  ACT_RANGE_AIM_SMG1_LOW,
  ACT_RANGE_AIM_PISTOL_LOW,
  ACT_RANGE_AIM_AR2_LOW,
  ACT_COVER_PISTOL_LOW,
  ACT_COVER_SMG1_LOW,
  ACT_GESTURE_RANGE_ATTACK_AR1,
  ACT_GESTURE_RANGE_ATTACK_AR2,
  ACT_GESTURE_RANGE_ATTACK_AR2_GRENADE,
  ACT_GESTURE_RANGE_ATTACK_HMG1,
  ACT_GESTURE_RANGE_ATTACK_ML,
  ACT_GESTURE_RANGE_ATTACK_SMG1,
  ACT_GESTURE_RANGE_ATTACK_SMG1_LOW,
  ACT_GESTURE_RANGE_ATTACK_SMG2,
  ACT_GESTURE_RANGE_ATTACK_SHOTGUN,
  ACT_GESTURE_RANGE_ATTACK_PISTOL,
  ACT_GESTURE_RANGE_ATTACK_PISTOL_LOW,
  ACT_GESTURE_RANGE_ATTACK_SLAM,
  ACT_GESTURE_RANGE_ATTACK_TRIPWIRE,
  ACT_GESTURE_RANGE_ATTACK_THROW,
  ACT_GESTURE_RANGE_ATTACK_SNIPER_RIFLE,
  ACT_GESTURE_MELEE_ATTACK_SWING,
  ACT_IDLE_RIFLE,
  ACT_IDLE_SMG1,
  ACT_IDLE_ANGRY_SMG1,
  ACT_IDLE_PISTOL,
  ACT_IDLE_ANGRY_PISTOL,
  ACT_IDLE_ANGRY_SHOTGUN,
  ACT_IDLE_STEALTH_PISTOL,
  ACT_IDLE_PACKAGE,
  ACT_WALK_PACKAGE,
  ACT_IDLE_SUITCASE,
  ACT_WALK_SUITCASE,
  ACT_IDLE_SMG1_RELAXED,
  ACT_IDLE_SMG1_STIMULATED,
  ACT_WALK_RIFLE_RELAXED,
  ACT_RUN_RIFLE_RELAXED,
  ACT_WALK_RIFLE_STIMULATED,
  ACT_RUN_RIFLE_STIMULATED,
  ACT_IDLE_AIM_RIFLE_STIMULATED,
  ACT_WALK_AIM_RIFLE_STIMULATED,
  ACT_RUN_AIM_RIFLE_STIMULATED,
  ACT_IDLE_SHOTGUN_RELAXED,
  ACT_IDLE_SHOTGUN_STIMULATED,
  ACT_IDLE_SHOTGUN_AGITATED,
  ACT_WALK_ANGRY,
  ACT_POLICE_HARASS1,
  ACT_POLICE_HARASS2,
  ACT_IDLE_MANNEDGUN,
  ACT_IDLE_MELEE,
  ACT_IDLE_ANGRY_MELEE,
  ACT_IDLE_RPG_RELAXED,
  ACT_IDLE_RPG,
  ACT_IDLE_ANGRY_RPG,
  ACT_COVER_LOW_RPG,
  ACT_WALK_RPG,
  ACT_RUN_RPG,
  ACT_WALK_CROUCH_RPG,
  ACT_RUN_CROUCH_RPG,
  ACT_WALK_RPG_RELAXED,
  ACT_RUN_RPG_RELAXED,
  ACT_WALK_RIFLE,
  ACT_WALK_AIM_RIFLE,
  ACT_WALK_CROUCH_RIFLE,
  ACT_WALK_CROUCH_AIM_RIFLE,
  ACT_RUN_RIFLE,
  ACT_RUN_AIM_RIFLE,
  ACT_RUN_CROUCH_RIFLE,
  ACT_RUN_CROUCH_AIM_RIFLE,
  ACT_RUN_STEALTH_PISTOL,
  ACT_WALK_AIM_SHOTGUN,
  ACT_RUN_AIM_SHOTGUN,
  ACT_WALK_PISTOL,
  ACT_RUN_PISTOL,
  ACT_WALK_AIM_PISTOL,
  ACT_RUN_AIM_PISTOL,
  ACT_WALK_STEALTH_PISTOL,
  ACT_WALK_AIM_STEALTH_PISTOL,
  ACT_RUN_AIM_STEALTH_PISTOL,
  ACT_RELOAD_PISTOL,
  ACT_RELOAD_PISTOL_LOW,
  ACT_RELOAD_SMG1,
  ACT_RELOAD_SMG1_LOW,
  ACT_RELOAD_SHOTGUN,
  ACT_RELOAD_SHOTGUN_LOW,
  ACT_GESTURE_RELOAD,
  ACT_GESTURE_RELOAD_PISTOL,
  ACT_GESTURE_RELOAD_SMG1,
  ACT_GESTURE_RELOAD_SHOTGUN,
  ACT_BUSY_LEAN_LEFT,
  ACT_BUSY_LEAN_LEFT_ENTRY,
  ACT_BUSY_LEAN_LEFT_EXIT,
  ACT_BUSY_LEAN_BACK,
  ACT_BUSY_LEAN_BACK_ENTRY,
  ACT_BUSY_LEAN_BACK_EXIT,
  ACT_BUSY_SIT_GROUND,
  ACT_BUSY_SIT_GROUND_ENTRY,
  ACT_BUSY_SIT_GROUND_EXIT,
  ACT_BUSY_SIT_CHAIR,
  ACT_BUSY_SIT_CHAIR_ENTRY,
  ACT_BUSY_SIT_CHAIR_EXIT,
  ACT_BUSY_STAND,
  ACT_BUSY_QUEUE,
  ACT_DUCK_DODGE,
  ACT_DIE_BARNACLE_SWALLOW,
  ACT_GESTURE_BARNACLE_STRANGLE,
  ACT_PHYSCANNON_DETACH,
  ACT_PHYSCANNON_ANIMATE,
  ACT_PHYSCANNON_ANIMATE_PRE,
  ACT_PHYSCANNON_ANIMATE_POST,
  ACT_DIE_FRONTSIDE,
  ACT_DIE_RIGHTSIDE,
  ACT_DIE_BACKSIDE,
  ACT_DIE_LEFTSIDE,
  ACT_DIE_CROUCH_FRONTSIDE,
  ACT_DIE_CROUCH_RIGHTSIDE,
  ACT_DIE_CROUCH_BACKSIDE,
  ACT_DIE_CROUCH_LEFTSIDE,
  ACT_OPEN_DOOR,
  ACT_DI_ALYX_ZOMBIE_MELEE,
  ACT_DI_ALYX_ZOMBIE_TORSO_MELEE,
  ACT_DI_ALYX_HEADCRAB_MELEE,
  ACT_DI_ALYX_ANTLION,
  ACT_DI_ALYX_ZOMBIE_SHOTGUN64,
  ACT_DI_ALYX_ZOMBIE_SHOTGUN26,
  ACT_READINESS_RELAXED_TO_STIMULATED,
  ACT_READINESS_RELAXED_TO_STIMULATED_WALK,
  ACT_READINESS_AGITATED_TO_STIMULATED,
  ACT_READINESS_STIMULATED_TO_RELAXED,
  ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED,
  ACT_READINESS_PISTOL_RELAXED_TO_STIMULATED_WALK,
  ACT_READINESS_PISTOL_AGITATED_TO_STIMULATED,
  ACT_READINESS_PISTOL_STIMULATED_TO_RELAXED,
  ACT_IDLE_CARRY,
  ACT_WALK_CARRY,
  ACT_STARTDYING,
  ACT_DYINGLOOP,
  ACT_DYINGTODEAD,
  ACT_RIDE_MANNED_GUN,
  ACT_VM_SPRINT_ENTER,
  ACT_VM_SPRINT_IDLE,
  ACT_VM_SPRINT_LEAVE,
  ACT_FIRE_START,
  ACT_FIRE_LOOP,
  ACT_FIRE_END,
  ACT_CROUCHING_GRENADEIDLE,
  ACT_CROUCHING_GRENADEREADY,
  ACT_CROUCHING_PRIMARYATTACK,
  ACT_OVERLAY_GRENADEIDLE,
  ACT_OVERLAY_GRENADEREADY,
  ACT_OVERLAY_PRIMARYATTACK,
  ACT_OVERLAY_SHIELD_UP,
  ACT_OVERLAY_SHIELD_DOWN,
  ACT_OVERLAY_SHIELD_UP_IDLE,
  ACT_OVERLAY_SHIELD_ATTACK,
  ACT_OVERLAY_SHIELD_KNOCKBACK,
  ACT_SHIELD_UP,
  ACT_SHIELD_DOWN,
  ACT_SHIELD_UP_IDLE,
  ACT_SHIELD_ATTACK,
  ACT_SHIELD_KNOCKBACK,
  ACT_CROUCHING_SHIELD_UP,
  ACT_CROUCHING_SHIELD_DOWN,
  ACT_CROUCHING_SHIELD_UP_IDLE,
  ACT_CROUCHING_SHIELD_ATTACK,
  ACT_CROUCHING_SHIELD_KNOCKBACK,
  ACT_TURNRIGHT45,
  ACT_TURNLEFT45,
  ACT_TURN,
  ACT_OBJ_ASSEMBLING,
  ACT_OBJ_DISMANTLING,
  ACT_OBJ_STARTUP,
  ACT_OBJ_RUNNING,
  ACT_OBJ_IDLE,
  ACT_OBJ_PLACING,
  ACT_OBJ_DETERIORATING,
  ACT_OBJ_UPGRADING,
  ACT_DEPLOY,
  ACT_DEPLOY_IDLE,
  ACT_UNDEPLOY,
  ACT_CROSSBOW_DRAW_UNLOADED,
  ACT_GAUSS_SPINUP,
  ACT_GAUSS_SPINCYCLE,
  ACT_VM_PRIMARYATTACK_SILENCED,
  ACT_VM_RELOAD_SILENCED,
  ACT_VM_DRYFIRE_SILENCED,
  ACT_VM_IDLE_SILENCED,
  ACT_VM_DRAW_SILENCED,
  ACT_VM_IDLE_EMPTY_LEFT,
  ACT_VM_DRYFIRE_LEFT,
  ACT_VM_IS_DRAW,
  ACT_VM_IS_HOLSTER,
  ACT_VM_IS_IDLE,
  ACT_VM_IS_PRIMARYATTACK,
  ACT_PLAYER_IDLE_FIRE,
  ACT_PLAYER_CROUCH_FIRE,
  ACT_PLAYER_CROUCH_WALK_FIRE,
  ACT_PLAYER_WALK_FIRE,
  ACT_PLAYER_RUN_FIRE,
  ACT_IDLETORUN,
  ACT_RUNTOIDLE,
  ACT_VM_DRAW_DEPLOYED,
  ACT_HL2MP_IDLE_MELEE,
  ACT_HL2MP_RUN_MELEE,
  ACT_HL2MP_IDLE_CROUCH_MELEE,
  ACT_HL2MP_WALK_CROUCH_MELEE,
  ACT_HL2MP_GESTURE_RANGE_ATTACK_MELEE,
  ACT_HL2MP_GESTURE_RELOAD_MELEE,
  ACT_HL2MP_JUMP_MELEE,
  ACT_VM_FIZZLE,
  ACT_MP_STAND_IDLE,
  ACT_MP_CROUCH_IDLE,
  ACT_MP_CROUCH_DEPLOYED_IDLE,
  ACT_MP_CROUCH_DEPLOYED,
  ACT_MP_DEPLOYED_IDLE,
  ACT_MP_RUN,
  ACT_MP_WALK,
  ACT_MP_AIRWALK,
  ACT_MP_CROUCHWALK,
  ACT_MP_SPRINT,
  ACT_MP_JUMP,
  ACT_MP_JUMP_START,
  ACT_MP_JUMP_FLOAT,
  ACT_MP_JUMP_LAND,
  ACT_MP_JUMP_IMPACT_N,
  ACT_MP_JUMP_IMPACT_E,
  ACT_MP_JUMP_IMPACT_W,
  ACT_MP_JUMP_IMPACT_S,
  ACT_MP_JUMP_IMPACT_TOP,
  ACT_MP_DOUBLEJUMP,
  ACT_MP_SWIM,
  ACT_MP_DEPLOYED,
  ACT_MP_SWIM_DEPLOYED,
  ACT_MP_VCD,
  ACT_MP_ATTACK_STAND_PRIMARYFIRE,
  ACT_MP_ATTACK_STAND_PRIMARYFIRE_DEPLOYED,
  ACT_MP_ATTACK_STAND_SECONDARYFIRE,
  ACT_MP_ATTACK_STAND_GRENADE,
  ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,
  ACT_MP_ATTACK_CROUCH_PRIMARYFIRE_DEPLOYED,
  ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,
  ACT_MP_ATTACK_CROUCH_GRENADE,
  ACT_MP_ATTACK_SWIM_PRIMARYFIRE,
  ACT_MP_ATTACK_SWIM_SECONDARYFIRE,
  ACT_MP_ATTACK_SWIM_GRENADE,
  ACT_MP_ATTACK_AIRWALK_PRIMARYFIRE,
  ACT_MP_ATTACK_AIRWALK_SECONDARYFIRE,
  ACT_MP_ATTACK_AIRWALK_GRENADE,
  ACT_MP_RELOAD_STAND,
  ACT_MP_RELOAD_STAND_LOOP,
  ACT_MP_RELOAD_STAND_END,
  ACT_MP_RELOAD_CROUCH,
  ACT_MP_RELOAD_CROUCH_LOOP,
  ACT_MP_RELOAD_CROUCH_END,
  ACT_MP_RELOAD_SWIM,
  ACT_MP_RELOAD_SWIM_LOOP,
  ACT_MP_RELOAD_SWIM_END,
  ACT_MP_RELOAD_AIRWALK,
  ACT_MP_RELOAD_AIRWALK_LOOP,
  ACT_MP_RELOAD_AIRWALK_END,
  ACT_MP_ATTACK_STAND_PREFIRE,
  ACT_MP_ATTACK_STAND_POSTFIRE,
  ACT_MP_ATTACK_STAND_STARTFIRE,
  ACT_MP_ATTACK_CROUCH_PREFIRE,
  ACT_MP_ATTACK_CROUCH_POSTFIRE,
  ACT_MP_ATTACK_SWIM_PREFIRE,
  ACT_MP_ATTACK_SWIM_POSTFIRE,
  ACT_MP_STAND_PRIMARY,
  ACT_MP_CROUCH_PRIMARY,
  ACT_MP_RUN_PRIMARY,
  ACT_MP_WALK_PRIMARY,
  ACT_MP_AIRWALK_PRIMARY,
  ACT_MP_CROUCHWALK_PRIMARY,
  ACT_MP_JUMP_PRIMARY,
  ACT_MP_JUMP_START_PRIMARY,
  ACT_MP_JUMP_FLOAT_PRIMARY,
  ACT_MP_JUMP_LAND_PRIMARY,
  ACT_MP_SWIM_PRIMARY,
  ACT_MP_DEPLOYED_PRIMARY,
  ACT_MP_SWIM_DEPLOYED_PRIMARY,
  ACT_MP_ATTACK_STAND_PRIMARY,
  ACT_MP_ATTACK_STAND_PRIMARY_DEPLOYED,
  ACT_MP_ATTACK_CROUCH_PRIMARY,
  ACT_MP_ATTACK_CROUCH_PRIMARY_DEPLOYED,
  ACT_MP_ATTACK_SWIM_PRIMARY,
  ACT_MP_ATTACK_AIRWALK_PRIMARY,
  ACT_MP_RELOAD_STAND_PRIMARY,
  ACT_MP_RELOAD_STAND_PRIMARY_LOOP,
  ACT_MP_RELOAD_STAND_PRIMARY_END,
  ACT_MP_RELOAD_CROUCH_PRIMARY,
  ACT_MP_RELOAD_CROUCH_PRIMARY_LOOP,
  ACT_MP_RELOAD_CROUCH_PRIMARY_END,
  ACT_MP_RELOAD_SWIM_PRIMARY,
  ACT_MP_RELOAD_SWIM_PRIMARY_LOOP,
  ACT_MP_RELOAD_SWIM_PRIMARY_END,
  ACT_MP_RELOAD_AIRWALK_PRIMARY,
  ACT_MP_RELOAD_AIRWALK_PRIMARY_LOOP,
  ACT_MP_RELOAD_AIRWALK_PRIMARY_END,
  ACT_MP_ATTACK_STAND_GRENADE_PRIMARY,
  ACT_MP_ATTACK_CROUCH_GRENADE_PRIMARY,
  ACT_MP_ATTACK_SWIM_GRENADE_PRIMARY,
  ACT_MP_ATTACK_AIRWALK_GRENADE_PRIMARY,
  ACT_MP_STAND_SECONDARY,
  ACT_MP_CROUCH_SECONDARY,
  ACT_MP_RUN_SECONDARY,
  ACT_MP_WALK_SECONDARY,
  ACT_MP_AIRWALK_SECONDARY,
  ACT_MP_CROUCHWALK_SECONDARY,
  ACT_MP_JUMP_SECONDARY,
  ACT_MP_JUMP_START_SECONDARY,
  ACT_MP_JUMP_FLOAT_SECONDARY,
  ACT_MP_JUMP_LAND_SECONDARY,
  ACT_MP_SWIM_SECONDARY,
  ACT_MP_ATTACK_STAND_SECONDARY,
  ACT_MP_ATTACK_CROUCH_SECONDARY,
  ACT_MP_ATTACK_SWIM_SECONDARY,
  ACT_MP_ATTACK_AIRWALK_SECONDARY,
  ACT_MP_RELOAD_STAND_SECONDARY,
  ACT_MP_RELOAD_STAND_SECONDARY_LOOP,
  ACT_MP_RELOAD_STAND_SECONDARY_END,
  ACT_MP_RELOAD_CROUCH_SECONDARY,
  ACT_MP_RELOAD_CROUCH_SECONDARY_LOOP,
  ACT_MP_RELOAD_CROUCH_SECONDARY_END,
  ACT_MP_RELOAD_SWIM_SECONDARY,
  ACT_MP_RELOAD_SWIM_SECONDARY_LOOP,
  ACT_MP_RELOAD_SWIM_SECONDARY_END,
  ACT_MP_RELOAD_AIRWALK_SECONDARY,
  ACT_MP_RELOAD_AIRWALK_SECONDARY_LOOP,
  ACT_MP_RELOAD_AIRWALK_SECONDARY_END,
  ACT_MP_ATTACK_STAND_GRENADE_SECONDARY,
  ACT_MP_ATTACK_CROUCH_GRENADE_SECONDARY,
  ACT_MP_ATTACK_SWIM_GRENADE_SECONDARY,
  ACT_MP_ATTACK_AIRWALK_GRENADE_SECONDARY,
  ACT_MP_STAND_MELEE,
  ACT_MP_CROUCH_MELEE,
  ACT_MP_RUN_MELEE,
  ACT_MP_WALK_MELEE,
  ACT_MP_AIRWALK_MELEE,
  ACT_MP_CROUCHWALK_MELEE,
  ACT_MP_JUMP_MELEE,
  ACT_MP_JUMP_START_MELEE,
  ACT_MP_JUMP_FLOAT_MELEE,
  ACT_MP_JUMP_LAND_MELEE,
  ACT_MP_SWIM_MELEE,
  ACT_MP_ATTACK_STAND_MELEE,
  ACT_MP_ATTACK_STAND_MELEE_SECONDARY,
  ACT_MP_ATTACK_CROUCH_MELEE,
  ACT_MP_ATTACK_CROUCH_MELEE_SECONDARY,
  ACT_MP_ATTACK_SWIM_MELEE,
  ACT_MP_ATTACK_AIRWALK_MELEE,
  ACT_MP_ATTACK_STAND_GRENADE_MELEE,
  ACT_MP_ATTACK_CROUCH_GRENADE_MELEE,
  ACT_MP_ATTACK_SWIM_GRENADE_MELEE,
  ACT_MP_ATTACK_AIRWALK_GRENADE_MELEE,
  ACT_MP_STAND_ITEM1,
  ACT_MP_CROUCH_ITEM1,
  ACT_MP_RUN_ITEM1,
  ACT_MP_WALK_ITEM1,
  ACT_MP_AIRWALK_ITEM1,
  ACT_MP_CROUCHWALK_ITEM1,
  ACT_MP_JUMP_ITEM1,
  ACT_MP_JUMP_START_ITEM1,
  ACT_MP_JUMP_FLOAT_ITEM1,
  ACT_MP_JUMP_LAND_ITEM1,
  ACT_MP_SWIM_ITEM1,
  ACT_MP_ATTACK_STAND_ITEM1,
  ACT_MP_ATTACK_STAND_ITEM1_SECONDARY,
  ACT_MP_ATTACK_CROUCH_ITEM1,
  ACT_MP_ATTACK_CROUCH_ITEM1_SECONDARY,
  ACT_MP_ATTACK_SWIM_ITEM1,
  ACT_MP_ATTACK_AIRWALK_ITEM1,
  ACT_MP_STAND_ITEM2,
  ACT_MP_CROUCH_ITEM2,
  ACT_MP_RUN_ITEM2,
  ACT_MP_WALK_ITEM2,
  ACT_MP_AIRWALK_ITEM2,
  ACT_MP_CROUCHWALK_ITEM2,
  ACT_MP_JUMP_ITEM2,
  ACT_MP_JUMP_START_ITEM2,
  ACT_MP_JUMP_FLOAT_ITEM2,
  ACT_MP_JUMP_LAND_ITEM2,
  ACT_MP_SWIM_ITEM2,
  ACT_MP_ATTACK_STAND_ITEM2,
  ACT_MP_ATTACK_STAND_ITEM2_SECONDARY,
  ACT_MP_ATTACK_CROUCH_ITEM2,
  ACT_MP_ATTACK_CROUCH_ITEM2_SECONDARY,
  ACT_MP_ATTACK_SWIM_ITEM2,
  ACT_MP_ATTACK_AIRWALK_ITEM2,
  ACT_MP_GESTURE_FLINCH,
  ACT_MP_GESTURE_FLINCH_PRIMARY,
  ACT_MP_GESTURE_FLINCH_SECONDARY,
  ACT_MP_GESTURE_FLINCH_MELEE,
  ACT_MP_GESTURE_FLINCH_ITEM1,
  ACT_MP_GESTURE_FLINCH_ITEM2,
  ACT_MP_GESTURE_FLINCH_HEAD,
  ACT_MP_GESTURE_FLINCH_CHEST,
  ACT_MP_GESTURE_FLINCH_STOMACH,
  ACT_MP_GESTURE_FLINCH_LEFTARM,
  ACT_MP_GESTURE_FLINCH_RIGHTARM,
  ACT_MP_GESTURE_FLINCH_LEFTLEG,
  ACT_MP_GESTURE_FLINCH_RIGHTLEG,
  ACT_MP_GRENADE1_DRAW,
  ACT_MP_GRENADE1_IDLE,
  ACT_MP_GRENADE1_ATTACK,
  ACT_MP_GRENADE2_DRAW,
  ACT_MP_GRENADE2_IDLE,
  ACT_MP_GRENADE2_ATTACK,
  ACT_MP_PRIMARY_GRENADE1_DRAW,
  ACT_MP_PRIMARY_GRENADE1_IDLE,
  ACT_MP_PRIMARY_GRENADE1_ATTACK,
  ACT_MP_PRIMARY_GRENADE2_DRAW,
  ACT_MP_PRIMARY_GRENADE2_IDLE,
  ACT_MP_PRIMARY_GRENADE2_ATTACK,
  ACT_MP_SECONDARY_GRENADE1_DRAW,
  ACT_MP_SECONDARY_GRENADE1_IDLE,
  ACT_MP_SECONDARY_GRENADE1_ATTACK,
  ACT_MP_SECONDARY_GRENADE2_DRAW,
  ACT_MP_SECONDARY_GRENADE2_IDLE,
  ACT_MP_SECONDARY_GRENADE2_ATTACK,
  ACT_MP_MELEE_GRENADE1_DRAW,
  ACT_MP_MELEE_GRENADE1_IDLE,
  ACT_MP_MELEE_GRENADE1_ATTACK,
  ACT_MP_MELEE_GRENADE2_DRAW,
  ACT_MP_MELEE_GRENADE2_IDLE,
  ACT_MP_MELEE_GRENADE2_ATTACK,
  ACT_MP_ITEM1_GRENADE1_DRAW,
  ACT_MP_ITEM1_GRENADE1_IDLE,
  ACT_MP_ITEM1_GRENADE1_ATTACK,
  ACT_MP_ITEM1_GRENADE2_DRAW,
  ACT_MP_ITEM1_GRENADE2_IDLE,
  ACT_MP_ITEM1_GRENADE2_ATTACK,
  ACT_MP_ITEM2_GRENADE1_DRAW,
  ACT_MP_ITEM2_GRENADE1_IDLE,
  ACT_MP_ITEM2_GRENADE1_ATTACK,
  ACT_MP_ITEM2_GRENADE2_DRAW,
  ACT_MP_ITEM2_GRENADE2_IDLE,
  ACT_MP_ITEM2_GRENADE2_ATTACK,
  ACT_MP_STAND_BUILDING,
  ACT_MP_CROUCH_BUILDING,
  ACT_MP_RUN_BUILDING,
  ACT_MP_WALK_BUILDING,
  ACT_MP_AIRWALK_BUILDING,
  ACT_MP_CROUCHWALK_BUILDING,
  ACT_MP_JUMP_BUILDING,
  ACT_MP_JUMP_START_BUILDING,
  ACT_MP_JUMP_FLOAT_BUILDING,
  ACT_MP_JUMP_LAND_BUILDING,
  ACT_MP_SWIM_BUILDING,
  ACT_MP_ATTACK_STAND_BUILDING,
  ACT_MP_ATTACK_CROUCH_BUILDING,
  ACT_MP_ATTACK_SWIM_BUILDING,
  ACT_MP_ATTACK_AIRWALK_BUILDING,
  ACT_MP_ATTACK_STAND_GRENADE_BUILDING,
  ACT_MP_ATTACK_CROUCH_GRENADE_BUILDING,
  ACT_MP_ATTACK_SWIM_GRENADE_BUILDING,
  ACT_MP_ATTACK_AIRWALK_GRENADE_BUILDING,
  ACT_MP_STAND_PDA,
  ACT_MP_CROUCH_PDA,
  ACT_MP_RUN_PDA,
  ACT_MP_WALK_PDA,
  ACT_MP_AIRWALK_PDA,
  ACT_MP_CROUCHWALK_PDA,
  ACT_MP_JUMP_PDA,
  ACT_MP_JUMP_START_PDA,
  ACT_MP_JUMP_FLOAT_PDA,
  ACT_MP_JUMP_LAND_PDA,
  ACT_MP_SWIM_PDA,
  ACT_MP_ATTACK_STAND_PDA,
  ACT_MP_ATTACK_SWIM_PDA,
  ACT_MP_GESTURE_VC_HANDMOUTH,
  ACT_MP_GESTURE_VC_FINGERPOINT,
  ACT_MP_GESTURE_VC_FISTPUMP,
  ACT_MP_GESTURE_VC_THUMBSUP,
  ACT_MP_GESTURE_VC_NODYES,
  ACT_MP_GESTURE_VC_NODNO,
  ACT_MP_GESTURE_VC_HANDMOUTH_PRIMARY,
  ACT_MP_GESTURE_VC_FINGERPOINT_PRIMARY,
  ACT_MP_GESTURE_VC_FISTPUMP_PRIMARY,
  ACT_MP_GESTURE_VC_THUMBSUP_PRIMARY,
  ACT_MP_GESTURE_VC_NODYES_PRIMARY,
  ACT_MP_GESTURE_VC_NODNO_PRIMARY,
  ACT_MP_GESTURE_VC_HANDMOUTH_SECONDARY,
  ACT_MP_GESTURE_VC_FINGERPOINT_SECONDARY,
  ACT_MP_GESTURE_VC_FISTPUMP_SECONDARY,
  ACT_MP_GESTURE_VC_THUMBSUP_SECONDARY,
  ACT_MP_GESTURE_VC_NODYES_SECONDARY,
  ACT_MP_GESTURE_VC_NODNO_SECONDARY,
  ACT_MP_GESTURE_VC_HANDMOUTH_MELEE,
  ACT_MP_GESTURE_VC_FINGERPOINT_MELEE,
  ACT_MP_GESTURE_VC_FISTPUMP_MELEE,
  ACT_MP_GESTURE_VC_THUMBSUP_MELEE,
  ACT_MP_GESTURE_VC_NODYES_MELEE,
  ACT_MP_GESTURE_VC_NODNO_MELEE,
  ACT_MP_GESTURE_VC_HANDMOUTH_ITEM1,
  ACT_MP_GESTURE_VC_FINGERPOINT_ITEM1,
  ACT_MP_GESTURE_VC_FISTPUMP_ITEM1,
  ACT_MP_GESTURE_VC_THUMBSUP_ITEM1,
  ACT_MP_GESTURE_VC_NODYES_ITEM1,
  ACT_MP_GESTURE_VC_NODNO_ITEM1,
  ACT_MP_GESTURE_VC_HANDMOUTH_ITEM2,
  ACT_MP_GESTURE_VC_FINGERPOINT_ITEM2,
  ACT_MP_GESTURE_VC_FISTPUMP_ITEM2,
  ACT_MP_GESTURE_VC_THUMBSUP_ITEM2,
  ACT_MP_GESTURE_VC_NODYES_ITEM2,
  ACT_MP_GESTURE_VC_NODNO_ITEM2,
  ACT_MP_GESTURE_VC_HANDMOUTH_BUILDING,
  ACT_MP_GESTURE_VC_FINGERPOINT_BUILDING,
  ACT_MP_GESTURE_VC_FISTPUMP_BUILDING,
  ACT_MP_GESTURE_VC_THUMBSUP_BUILDING,
  ACT_MP_GESTURE_VC_NODYES_BUILDING,
  ACT_MP_GESTURE_VC_NODNO_BUILDING,
  ACT_MP_GESTURE_VC_HANDMOUTH_PDA,
  ACT_MP_GESTURE_VC_FINGERPOINT_PDA,
  ACT_MP_GESTURE_VC_FISTPUMP_PDA,
  ACT_MP_GESTURE_VC_THUMBSUP_PDA,
  ACT_MP_GESTURE_VC_NODYES_PDA,
  ACT_MP_GESTURE_VC_NODNO_PDA,
  ACT_VM_UNUSABLE,
  ACT_VM_UNUSABLE_TO_USABLE,
  ACT_VM_USABLE_TO_UNUSABLE,
  ACT_PRIMARY_VM_DRAW,
  ACT_PRIMARY_VM_HOLSTER,
  ACT_PRIMARY_VM_IDLE,
  ACT_PRIMARY_VM_PULLBACK,
  ACT_PRIMARY_VM_PRIMARYATTACK,
  ACT_PRIMARY_VM_SECONDARYATTACK,
  ACT_PRIMARY_VM_RELOAD,
  ACT_PRIMARY_VM_DRYFIRE,
  ACT_PRIMARY_VM_IDLE_TO_LOWERED,
  ACT_PRIMARY_VM_IDLE_LOWERED,
  ACT_PRIMARY_VM_LOWERED_TO_IDLE,
  ACT_SECONDARY_VM_DRAW,
  ACT_SECONDARY_VM_HOLSTER,
  ACT_SECONDARY_VM_IDLE,
  ACT_SECONDARY_VM_PULLBACK,
  ACT_SECONDARY_VM_PRIMARYATTACK,
  ACT_SECONDARY_VM_SECONDARYATTACK,
  ACT_SECONDARY_VM_RELOAD,
  ACT_SECONDARY_VM_DRYFIRE,
  ACT_SECONDARY_VM_IDLE_TO_LOWERED,
  ACT_SECONDARY_VM_IDLE_LOWERED,
  ACT_SECONDARY_VM_LOWERED_TO_IDLE,
  ACT_MELEE_VM_DRAW,
  ACT_MELEE_VM_HOLSTER,
  ACT_MELEE_VM_IDLE,
  ACT_MELEE_VM_PULLBACK,
  ACT_MELEE_VM_PRIMARYATTACK,
  ACT_MELEE_VM_SECONDARYATTACK,
  ACT_MELEE_VM_RELOAD,
  ACT_MELEE_VM_DRYFIRE,
  ACT_MELEE_VM_IDLE_TO_LOWERED,
  ACT_MELEE_VM_IDLE_LOWERED,
  ACT_MELEE_VM_LOWERED_TO_IDLE,
  ACT_PDA_VM_DRAW,
  ACT_PDA_VM_HOLSTER,
  ACT_PDA_VM_IDLE,
  ACT_PDA_VM_PULLBACK,
  ACT_PDA_VM_PRIMARYATTACK,
  ACT_PDA_VM_SECONDARYATTACK,
  ACT_PDA_VM_RELOAD,
  ACT_PDA_VM_DRYFIRE,
  ACT_PDA_VM_IDLE_TO_LOWERED,
  ACT_PDA_VM_IDLE_LOWERED,
  ACT_PDA_VM_LOWERED_TO_IDLE,
  ACT_ITEM1_VM_DRAW,
  ACT_ITEM1_VM_HOLSTER,
  ACT_ITEM1_VM_IDLE,
  ACT_ITEM1_VM_PULLBACK,
  ACT_ITEM1_VM_PRIMARYATTACK,
  ACT_ITEM1_VM_SECONDARYATTACK,
  ACT_ITEM1_VM_RELOAD,
  ACT_ITEM1_VM_DRYFIRE,
  ACT_ITEM1_VM_IDLE_TO_LOWERED,
  ACT_ITEM1_VM_IDLE_LOWERED,
  ACT_ITEM1_VM_LOWERED_TO_IDLE,
  ACT_ITEM2_VM_DRAW,
  ACT_ITEM2_VM_HOLSTER,
  ACT_ITEM2_VM_IDLE,
  ACT_ITEM2_VM_PULLBACK,
  ACT_ITEM2_VM_PRIMARYATTACK,
  ACT_ITEM2_VM_SECONDARYATTACK,
  ACT_ITEM2_VM_RELOAD,
  ACT_ITEM2_VM_DRYFIRE,
  ACT_ITEM2_VM_IDLE_TO_LOWERED,
  ACT_ITEM2_VM_IDLE_LOWERED,
  ACT_ITEM2_VM_LOWERED_TO_IDLE,
  ACT_RELOAD_SUCCEED,
  ACT_RELOAD_FAIL,
  ACT_WALK_AIM_AUTOGUN,
  ACT_RUN_AIM_AUTOGUN,
  ACT_IDLE_AUTOGUN,
  ACT_IDLE_AIM_AUTOGUN,
  ACT_RELOAD_AUTOGUN,
  ACT_CROUCH_IDLE_AUTOGUN,
  ACT_RANGE_ATTACK_AUTOGUN,
  ACT_JUMP_AUTOGUN,
  ACT_IDLE_AIM_PISTOL,
  ACT_WALK_AIM_DUAL,
  ACT_RUN_AIM_DUAL,
  ACT_IDLE_DUAL,
  ACT_IDLE_AIM_DUAL,
  ACT_RELOAD_DUAL,
  ACT_CROUCH_IDLE_DUAL,
  ACT_RANGE_ATTACK_DUAL,
  ACT_JUMP_DUAL,
  ACT_IDLE_SHOTGUN,
  ACT_IDLE_AIM_SHOTGUN,
  ACT_CROUCH_IDLE_SHOTGUN,
  ACT_JUMP_SHOTGUN,
  ACT_IDLE_AIM_RIFLE,
  ACT_RELOAD_RIFLE,
  ACT_CROUCH_IDLE_RIFLE,
  ACT_RANGE_ATTACK_RIFLE,
  ACT_JUMP_RIFLE,
  ACT_SLEEP,
  ACT_WAKE,
  ACT_FLICK_LEFT,
  ACT_FLICK_LEFT_MIDDLE,
  ACT_FLICK_RIGHT_MIDDLE,
  ACT_FLICK_RIGHT,
  ACT_SPINAROUND,
  ACT_PREP_TO_FIRE,
  ACT_FIRE,
  ACT_FIRE_RECOVER,
  ACT_SPRAY,
  ACT_PREP_EXPLODE,
  ACT_EXPLODE,
  ACT_DOTA_IDLE,
  ACT_DOTA_RUN,
  ACT_DOTA_ATTACK,
  ACT_DOTA_ATTACK_EVENT,
  ACT_DOTA_DIE,
  ACT_DOTA_FLINCH,
  ACT_DOTA_DISABLED,
  ACT_DOTA_CAST_ABILITY_1,
  ACT_DOTA_CAST_ABILITY_2,
  ACT_DOTA_CAST_ABILITY_3,
  ACT_DOTA_CAST_ABILITY_4,
  ACT_DOTA_OVERRIDE_ABILITY_1,
  ACT_DOTA_OVERRIDE_ABILITY_2,
  ACT_DOTA_OVERRIDE_ABILITY_3,
  ACT_DOTA_OVERRIDE_ABILITY_4,
  ACT_DOTA_CHANNEL_ABILITY_1,
  ACT_DOTA_CHANNEL_ABILITY_2,
  ACT_DOTA_CHANNEL_ABILITY_3,
  ACT_DOTA_CHANNEL_ABILITY_4,
  ACT_DOTA_CHANNEL_END_ABILITY_1,
  ACT_DOTA_CHANNEL_END_ABILITY_2,
  ACT_DOTA_CHANNEL_END_ABILITY_3,
  ACT_DOTA_CHANNEL_END_ABILITY_4,
  ACT_MP_RUN_SPEEDPAINT,
  ACT_MP_LONG_FALL,
  ACT_MP_TRACTORBEAM_FLOAT,
  ACT_MP_DEATH_CRUSH,
  ACT_MP_RUN_SPEEDPAINT_PRIMARY,
  ACT_MP_DROWNING_PRIMARY,
  ACT_MP_LONG_FALL_PRIMARY,
  ACT_MP_TRACTORBEAM_FLOAT_PRIMARY,
  ACT_MP_DEATH_CRUSH_PRIMARY,
  ACT_DIE_STAND,
  ACT_DIE_STAND_HEADSHOT,
  ACT_DIE_CROUCH,
  ACT_DIE_CROUCH_HEADSHOT,
  ACT_CSGO_NULL,
  ACT_CSGO_DEFUSE,
  ACT_CSGO_DEFUSE_WITH_KIT,
  ACT_CSGO_FLASHBANG_REACTION,
  ACT_CSGO_FIRE_PRIMARY,
  ACT_CSGO_FIRE_PRIMARY_OPT_1,
  ACT_CSGO_FIRE_PRIMARY_OPT_2,
  ACT_CSGO_FIRE_SECONDARY,
  ACT_CSGO_FIRE_SECONDARY_OPT_1,
  ACT_CSGO_FIRE_SECONDARY_OPT_2,
  ACT_CSGO_RELOAD,
  ACT_CSGO_RELOAD_START,
  ACT_CSGO_RELOAD_LOOP,
  ACT_CSGO_RELOAD_END,
  ACT_CSGO_OPERATE,
  ACT_CSGO_DEPLOY,
  ACT_CSGO_CATCH,
  ACT_CSGO_SILENCER_DETACH,
  ACT_CSGO_SILENCER_ATTACH,
  ACT_CSGO_TWITCH,
  ACT_CSGO_TWITCH_BUYZONE,
  ACT_CSGO_PLANT_BOMB,
  ACT_CSGO_IDLE_TURN_BALANCEADJUST,
  ACT_CSGO_IDLE_ADJUST_STOPPEDMOVING,
  ACT_CSGO_ALIVE_LOOP,
  ACT_CSGO_FLINCH,
  ACT_CSGO_FLINCH_HEAD,
  ACT_CSGO_FLINCH_MOLOTOV,
  ACT_CSGO_JUMP,
  ACT_CSGO_FALL,
  ACT_CSGO_CLIMB_LADDER,
  ACT_CSGO_LAND_LIGHT,
  ACT_CSGO_LAND_HEAVY,
  ACT_CSGO_EXIT_LADDER_TOP,
  ACT_CSGO_EXIT_LADDER_BOTTOM,
};

enum ClearFlags_t {
	VIEW_CLEAR_COLOR = 0x1, // 1
	VIEW_CLEAR_DEPTH = 0x2, // 2
	VIEW_CLEAR_FULL_TARGET = 0x4, // 4
	VIEW_NO_DRAW = 0x8, // 8
	VIEW_CLEAR_OBEY_STENCIL = 0x10,// 16 Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,// 32
};

enum RenderViewInfo_t {
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = ( 1 << 0 ), // 1
	RENDERVIEW_DRAWHUD = ( 1 << 1 ), // 2
	RENDERVIEW_SUPPRESSMONITORRENDERING = ( 1 << 2 ), // 4
};

struct GrenadeInfo
{
	GrenadeType gType;
	Vector pos;
	QAngle angle;
	ThrowType tType;
	std::string name;
	GrenadeInfo(GrenadeType gType, Vector pos, QAngle angle,ThrowType tType, std::string name)
	{
		this->gType = gType;
		this->pos = pos;
		this->angle = angle;
		this->tType = tType;
		this->name = name;
	}
};

const std::map<ItemDefinitionIndex, DefItem_t> ItemDefinitionIndexMap = {
		{ ItemDefinitionIndex::INVALID,						{ "<-Default->", "DEFAULT", "", "" } },
		{ ItemDefinitionIndex::WEAPON_DEAGLE,				{ "#SFUI_WPNHUD_DesertEagle", "weapon_deagle", "models/weapons/v_pist_deagle.mdl", "deagle" } },
		{ ItemDefinitionIndex::WEAPON_ELITE,				{ "#SFUI_WPNHUD_Elites", "weapon_elite", "models/weapons/v_pist_elite.mdl", "elite" } },
		{ ItemDefinitionIndex::WEAPON_FIVESEVEN,			{ "#SFUI_WPNHUD_FiveSeven", "weapon_fiveseven", "models/weapons/v_pist_fiveseven.mdl", "fiveseven" } },
		{ ItemDefinitionIndex::WEAPON_GLOCK,				{ "#SFUI_WPNHUD_Glock18", "weapon_glock", "models/weapons/v_pist_glock18.mdl", "glock" } },
		{ ItemDefinitionIndex::WEAPON_AK47,					{ "#SFUI_WPNHUD_AK47", "weapon_ak47", "models/weapons/v_rif_ak47.mdl", "ak47" } },
		{ ItemDefinitionIndex::WEAPON_AUG,					{ "#SFUI_WPNHUD_Aug", "weapon_aug", "models/weapons/v_rif_aug.mdl", "aug" } },
		{ ItemDefinitionIndex::WEAPON_AWP,					{ "#SFUI_WPNHUD_AWP", "weapon_awp", "models/weapons/v_snip_awp.mdl", "awp" } },
		{ ItemDefinitionIndex::WEAPON_FAMAS,				{ "#SFUI_WPNHUD_Famas", "weapon_famas", "models/weapons/v_rif_famas.mdl", "famas" } },
		{ ItemDefinitionIndex::WEAPON_G3SG1,				{ "#SFUI_WPNHUD_G3SG1", "weapon_g3sg1", "models/weapons/v_snip_g3sg1.mdl", "g3sg1" } },
		{ ItemDefinitionIndex::WEAPON_GALILAR,				{ "#SFUI_WPNHUD_GalilAR", "weapon_galilar", "models/weapons/v_rif_galilar.mdl", "galilar" } },
		{ ItemDefinitionIndex::WEAPON_M249,					{ "#SFUI_WPNHUD_M249", "weapon_m249", "models/weapons/v_mach_m249para.mdl", "m249" } },
		{ ItemDefinitionIndex::WEAPON_M4A1,					{ "#SFUI_WPNHUD_M4A1", "weapon_m4a1", "models/weapons/v_rif_m4a1.mdl", "m4a1" } },
		{ ItemDefinitionIndex::WEAPON_MAC10,				{ "#SFUI_WPNHUD_MAC10", "weapon_mac10", "models/weapons/v_smg_mac10.mdl", "mac10" } },
		{ ItemDefinitionIndex::WEAPON_P90,					{ "#SFUI_WPNHUD_P90", "weapon_p90", "models/weapons/v_smg_p90.mdl", "p90" } },
		{ ItemDefinitionIndex::WEAPON_UMP45,				{ "#SFUI_WPNHUD_UMP45", "weapon_ump45", "models/weapons/v_smg_ump45.mdl", "ump45" } },
        { ItemDefinitionIndex::WEAPON_MP5,                  { "#SFUI_WPNHUD_MP5SD", "weapon_mp5sd", "models/weapons/v_smg_mp5sd.mdl", "mp5sd" } },
		{ ItemDefinitionIndex::WEAPON_XM1014,				{ "#SFUI_WPNHUD_xm1014", "weapon_xm1014", "models/weapons/v_shot_xm1014.mdl", "xm1014" } },
		{ ItemDefinitionIndex::WEAPON_BIZON,				{ "#SFUI_WPNHUD_Bizon", "weapon_bizon", "models/weapons/v_smg_bizon.mdl", "bizon" } },
		{ ItemDefinitionIndex::WEAPON_MAG7,					{ "#SFUI_WPNHUD_Mag7", "weapon_mag7", "models/weapons/v_shot_mag7.mdl", "mag7" } },
		{ ItemDefinitionIndex::WEAPON_NEGEV,				{ "#SFUI_WPNHUD_Negev", "weapon_negev", "models/weapons/v_mach_negev.mdl", "negev" } },
		{ ItemDefinitionIndex::WEAPON_SAWEDOFF,				{ "#SFUI_WPNHUD_Sawedoff", "weapon_sawedoff", "models/weapons/v_shot_sawedoff.mdl", "sawedoff" } },
		{ ItemDefinitionIndex::WEAPON_TEC9,					{ "#SFUI_WPNHUD_Tec9", "weapon_tec9", "models/weapons/v_pist_tec9.mdl", "tec9" } },
		{ ItemDefinitionIndex::WEAPON_TASER,				{ "#SFUI_WPNHUD_Taser", "weapon_taser", "models/weapons/v_eq_taser.mdl", "taser" } },
		{ ItemDefinitionIndex::WEAPON_HKP2000,				{ "#SFUI_WPNHUD_HKP2000", "weapon_hkp2000", "models/weapons/v_pist_hkp2000.mdl", "hkp2000" } },
		{ ItemDefinitionIndex::WEAPON_MP7,					{ "#SFUI_WPNHUD_MP7", "weapon_mp7", "models/weapons/v_smg_mp7.mdl", "mp7" } },
		{ ItemDefinitionIndex::WEAPON_MP9,					{ "#SFUI_WPNHUD_MP9", "weapon_mp9", "models/weapons/v_smg_mp9.mdl", "mp9" } },
		{ ItemDefinitionIndex::WEAPON_NOVA,					{ "#SFUI_WPNHUD_Nova", "weapon_nova", "models/weapons/v_shot_nova.mdl", "nova" } },
		{ ItemDefinitionIndex::WEAPON_P250,					{ "#SFUI_WPNHUD_P250", "weapon_p250", "models/weapons/v_pist_p250.mdl", "p250" } },
		{ ItemDefinitionIndex::WEAPON_SCAR20,				{ "#SFUI_WPNHUD_SCAR20", "weapon_scar20", "models/weapons/v_snip_scar20.mdl", "scar20" } },
		{ ItemDefinitionIndex::WEAPON_SG556,				{ "#SFUI_WPNHUD_SG556", "weapon_sg556", "models/weapons/v_rif_sg556.mdl", "sg556" } },
		{ ItemDefinitionIndex::WEAPON_SSG08,				{ "#SFUI_WPNHUD_SSG08", "weapon_ssg08", "models/weapons/v_snip_ssg08.mdl", "ssg08" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE,				{ "#SFUI_WPNHUD_Knife", "weapon_knife", "models/weapons/v_knife_default_ct.mdl", "knife_default_ct" } },
		{ ItemDefinitionIndex::WEAPON_FLASHBANG,			{ "#SFUI_WPNHUD_FLASHBANG", "weapon_flashbang", "models/weapons/v_eq_flashbang.mdl", "flashbang" } },
		{ ItemDefinitionIndex::WEAPON_HEGRENADE,			{ "#SFUI_WPNHUD_HE_Grenade", "weapon_hegrenade", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade" } },
		{ ItemDefinitionIndex::WEAPON_SMOKEGRENADE,			{ "#SFUI_WPNHUD_Smoke_Grenade", "weapon_smokegrenade", "models/weapons/v_eq_smokegrenade.mdl", "smokegrenade" } },
		{ ItemDefinitionIndex::WEAPON_MOLOTOV,				{ "#SFUI_WPNHUD_MOLOTOV", "weapon_molotov", "models/weapons/v_eq_molotov.mdl", "inferno" } },
		{ ItemDefinitionIndex::WEAPON_DECOY,				{ "#SFUI_WPNHUD_DECOY", "weapon_decoy", "models/weapons/v_eq_decoy.mdl", "decoy" } },
		{ ItemDefinitionIndex::WEAPON_INCGRENADE,			{ "#SFUI_WPNHUD_IncGrenade", "weapon_incgrenade", "models/weapons/v_eq_incendiarygrenade.mdl", "inferno" } },
		{ ItemDefinitionIndex::WEAPON_C4,					{ "#SFUI_WPNHUD_C4", "weapon_c4", "models/weapons/v_ied.mdl" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_T,				{ "#SFUI_WPNHUD_Knife", "weapon_knife_t", "models/weapons/v_knife_default_t.mdl", "knife_t" } },
		{ ItemDefinitionIndex::WEAPON_M4A1_SILENCER,		{ "#SFUI_WPNHUD_M4_SILENCER", "weapon_m4a1_silencer", "models/weapons/v_rif_m4a1_s.mdl", "m4a1_silencer" } },
		{ ItemDefinitionIndex::WEAPON_USP_SILENCER,			{ "#SFUI_WPNHUD_USP_SILENCER", "weapon_usp_silencer", "models/weapons/v_pist_223.mdl", "usp_silencer" } },
		{ ItemDefinitionIndex::WEAPON_CZ75A,				{ "#SFUI_WPNHUD_CZ75", "weapon_cz75a", "models/weapons/v_pist_cz_75.mdl", "cz75a" } },
		{ ItemDefinitionIndex::WEAPON_REVOLVER,				{ "#SFUI_WPNHUD_REVOLVER", "weapon_revolver", "models/weapons/v_pist_revolver.mdl", "revolver" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_BAYONET,		{ "#SFUI_WPNHUD_KnifeBayonet", "weapon_knife_bayonet", "models/weapons/v_knife_bayonet.mdl", "bayonet" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_FLIP,			{ "#SFUI_WPNHUD_KnifeFlip", "weapon_knife_flip", "models/weapons/v_knife_flip.mdl", "knife_flip" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_GUT,			{ "#SFUI_WPNHUD_KnifeGut", "weapon_knife_gut", "models/weapons/v_knife_gut.mdl", "knife_gut" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_KARAMBIT,		{ "#SFUI_WPNHUD_KnifeKaram", "weapon_knife_karambit", "models/weapons/v_knife_karam.mdl", "knife_karambit" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_M9_BAYONET,		{ "#SFUI_WPNHUD_KnifeM9", "weapon_knife_m9_bayonet", "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_TACTICAL,		{ "#SFUI_WPNHUD_KnifeTactical", "weapon_knife_tactical", "models/weapons/v_knife_tactical.mdl", "knife_tactical" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_FALCHION,		{ "#SFUI_WPNHUD_knife_falchion_advanced", "weapon_knife_falchion", "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_SURVIVAL_BOWIE,	{ "#SFUI_WPNHUD_knife_survival_bowie", "weapon_knife_survival_bowie", "models/weapons/v_knife_survival_bowie.mdl", "knife_survival_bowie" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_BUTTERFLY,		{ "#SFUI_WPNHUD_Knife_Butterfly", "weapon_knife_butterfly", "models/weapons/v_knife_butterfly.mdl", "knife_butterfly" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_PUSH,			{ "#SFUI_WPNHUD_knife_push", "weapon_knife_push", "models/weapons/v_knife_push.mdl", "knife_push" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_URSUS,			{ "#SFUI_WPNHUD_knife_ursus", "weapon_knife_ursus", "models/weapons/v_knife_ursus.mdl", "knife_ursus" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_GYPSY_JACKKNIFE,{ "#SFUI_WPNHUD_knife_gypsy_jackknife", "weapon_knife_gypsy_jackknife", "models/weapons/v_knife_gypsy_jackknife.mdl", "knife_gypsy_jackknife" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_STILETTO,		{ "#SFUI_WPNHUD_knife_stiletto", "weapon_knife_stiletto", "models/weapons/v_knife_stiletto.mdl", "knife_stiletto" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_WIDOWMAKER,		{ "#SFUI_WPNHUD_knife_widowmaker", "weapon_knife_widowmaker", "models/weapons/v_knife_widowmaker.mdl", "knife_widowmaker" } },
		{ ItemDefinitionIndex::WEAPON_KNIFE_GHOST,			{ "#SFUI_WPNHUD_knife_ghost", "weapon_knife_ghost", "models/weapons/v_knife_ghost.mdl", "knife_ghost" } },
		{ ItemDefinitionIndex::WEAPON_KNIFEGG,				{ "#SFUI_WPNHUD_Knife_GG", "weapon_knifegg", "models/weapons/v_knife_gg.mdl", "knifegg" } },
		{ ItemDefinitionIndex::GLOVE_STUDDED_BLOODHOUND,	{ "#CSGO_Wearable_t_studdedgloves", "studded_bloodhound_gloves", "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl" } },
		{ ItemDefinitionIndex::GLOVE_T_SIDE,				{ "#CSGO_Wearable_t_defaultgloves", "t_gloves", "models/weapons/v_models/arms/glove_fingerless/v_glove_fingerless.mdl" } },
		{ ItemDefinitionIndex::GLOVE_CT_SIDE,				{ "#CSGO_Wearable_ct_defaultgloves", "ct_gloves", "models/weapons/v_models/arms/glove_hardknuckle/v_glove_hardknuckle.mdl" } },
		{ ItemDefinitionIndex::GLOVE_SPORTY,				{ "#CSGO_Wearable_v_sporty_glove", "sporty_gloves", "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl" } },
		{ ItemDefinitionIndex::GLOVE_SLICK,					{ "#CSGO_Wearable_v_slick_glove", "slick_gloves", "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl" } },
		{ ItemDefinitionIndex::GLOVE_LEATHER_WRAP,			{ "#CSGO_Wearable_v_leather_handwrap", "leather_handwraps", "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl" } },
		{ ItemDefinitionIndex::GLOVE_MOTORCYCLE,			{ "#CSGO_Wearable_v_motorcycle_glove", "motorcycle_gloves", "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl" } },
		{ ItemDefinitionIndex::GLOVE_SPECIALIST,			{ "#CSGO_Wearable_v_specialist_glove", "specialist_gloves", "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl" } },
		{ ItemDefinitionIndex::WEAPON_FISTS,                { "#SFUI_WPNHUD_Fists", "weapon_fists", "models/weapons/v_fists.mdl", "fists"} },
		{ ItemDefinitionIndex::WEAPON_SHIELD,               { "#SFUI_WPNHUD_Shield", "weapon_shield", "models/weapons/v_shield.mdf"} },
		{ ItemDefinitionIndex::WEAPON_HEALTHSHOT,           { "#SFUI_WPNHUD_Healthshot", "weapon_healthshot", "models/weapons/v_healthshot.mdl"} },
		{ ItemDefinitionIndex::WEAPON_TAGRENADE,            { "#SFUI_WPNHUD_TAGrenade", "weapon_tagrenade", "models/weapons/v_sonar_bomb.mdl"} },
		{ ItemDefinitionIndex::WEAPON_BREACHCHARGE,         { "#SFUI_WPNHUD_BreachCharge", "weapon_breachcharge", "models/weapons/v_breachcharge.mdl", "breachcharge"} },
		{ ItemDefinitionIndex::WEAPON_TABLET,               { "#SFUI_WPNHUD_Tablet", "weapon_tablet", "models/weapons/v_tablet.mdl"} },
		{ ItemDefinitionIndex::WEAPON_AXE,                  { "#SFUI_WPNHUD_Axe", "weapon_axe", "models/weapons/v_axe.mdl", "axe"} },
		{ ItemDefinitionIndex::WEAPON_HAMMER,               { "#SFUI_WPNHUD_Hammer", "weapon_hammer", "models/weapons/v_hammer.mdl", "hammer"} },
		{ ItemDefinitionIndex::WEAPON_SPANNER,              { "#SFUI_WPNHUD_Spanner", "weapon_spanner", "models/weapons/v_spanner.mdl", "spanner"} },
		{ ItemDefinitionIndex::WEAPON_FIREBOMB,             { "#SFUI_WPNHUD_FIREBOMB", "weapon_firebomb", "models/weapons/v_eq_molotov.mdl", "inferno"} },
		{ ItemDefinitionIndex::WEAPON_DIVERSION,            { "#SFUI_WPNHUD_Diversion", "weapon_diversion", "models/weapons/v_eq_decoy.mdl", "decoy"} },
		{ ItemDefinitionIndex::WEAPON_FRAG_GRENADE,         { "#SFUI_WPNHUD_frag_Grenade", "weapon_frag_grenade", "models/weapons/v_eq_fraggrenade.mdl", "hegrenade"} },
<<<<<<< HEAD
		{ ItemDefinitionIndex::WEAPON_BUMPMINE, 			{ "#SFUI_WPNHUD_BUMPMINE", "weapon_bumpmine", "models/weapons/v_eq_fraggrenade.mdl"} }};
=======
		{ ItemDefinitionIndex::WEAPON_BUMPMINE, 			{ "#SFUI_WPNHUD_BUMPMINE", "weapon_bumpmine", "models/weapons/v_eq_fraggrenade.mdl"} }
};
>>>>>>> d03935cdc19d2b5c3bb08ff65fc25781b27f9d81

#define FL_ONGROUND				(1<<0)	// At rest / on the ground
#define FL_DUCKING				(1<<1)	// Player flag -- Player is fully crouched
#define FL_WATERJUMP			(1<<2)	// player jumping out of water
#define FL_ONTRAIN				(1<<3)	// Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
#define FL_INRAIN				(1<<4)	// Indicates the entity is standing in rain
#define FL_FROZEN				(1<<5)	// Player is frozen for 3rd person camera
#define FL_ATCONTROLS			(1<<6)	// Player can't move, but keeps key inputs for controlling another entity
#define FL_CLIENT				(1<<7)	// Is a player
#define FL_FAKECLIENT			(1<<8)	// Fake client, simulated server side; don't send network messages to them
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define FL_INWATER				(1<<9)	// In water

#define CONTENTS_EMPTY			0		// No contents

#define CONTENTS_SOLID			0x1		// an eye is never valid in a solid
#define CONTENTS_WINDOW			0x2		// translucent, but not watery (glass)
#define CONTENTS_AUX			0x4
#define CONTENTS_GRATE			0x8		// alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_SLIME			0x10
#define CONTENTS_WATER			0x20
#define CONTENTS_BLOCKLOS		0x40	// block AI line of sight
#define CONTENTS_OPAQUE			0x80	// things that cannot be seen through (may be non-solid though)
#define LAST_VISIBLE_CONTENTS	CONTENTS_OPAQUE

#define ALL_VISIBLE_CONTENTS (LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define CONTENTS_TESTFOGVOLUME	0x100
#define CONTENTS_UNUSED			0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
// CONTENTS_OPAQUE + SURF_NODRAW count as CONTENTS_OPAQUE (shadow-casting toolsblocklight textures)
#define CONTENTS_BLOCKLIGHT		0x400

#define CONTENTS_TEAM1			0x800	// per team contents used to differentiate collisions
#define CONTENTS_TEAM2			0x1000	// between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE		0x4000

// remaining contents are non-visible, and don't eat brushes
#define CONTENTS_AREAPORTAL		0x8000

#define CONTENTS_PLAYERCLIP		0x10000
#define CONTENTS_MONSTERCLIP	0x20000

// currents can be added to any other contents, and may be mixed
#define CONTENTS_CURRENT_0		0x40000
#define CONTENTS_CURRENT_90		0x80000
#define CONTENTS_CURRENT_180	0x100000
#define CONTENTS_CURRENT_270	0x200000
#define CONTENTS_CURRENT_UP		0x400000
#define CONTENTS_CURRENT_DOWN	0x800000

#define CONTENTS_ORIGIN			0x1000000	// removed before bsping an entity

#define CONTENTS_MONSTER		0x2000000	// should never be on a brush, only in game
#define CONTENTS_DEBRIS			0x4000000
#define CONTENTS_DETAIL			0x8000000	// brushes to be added after vis leafs
#define CONTENTS_TRANSLUCENT	0x10000000	// auto set if any surface has trans
#define CONTENTS_LADDER			0x20000000
#define CONTENTS_HITBOX			0x40000000	// use accurate hitboxes on trace

#define MASK_SHOT	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)

// These are given to FindMaterial to reference the texture groups that show up on the
#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

#define MAXSTUDIOBONES 128
#define BONE_USED_BY_HITBOX 0x100

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define SURF_LIGHT		0x0001		// value will hold the light strength
#define SURF_SKY2D		0x0002		// don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define SURF_SKY		0x0004		// don't draw, but add to skybox
#define SURF_WARP		0x0008		// turbulent water warp
#define SURF_TRANS		0x0010
#define SURF_NOPORTAL	0x0020	// the surface can not have a portal placed on it
#define SURF_TRIGGER	0x0040	// FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define SURF_NODRAW		0x0080	// don't bother referencing the texture

#define SURF_HINT		0x0100	// make a primary bsp splitter

#define SURF_SKIP		0x0200	// completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT	0x0400	// Don't calculate light
#define SURF_BUMPLIGHT	0x0800	// calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS	0x1000	// Don't receive shadows
#define SURF_NODECALS	0x2000	// Don't receive decals
#define SURF_NOPAINT	SURF_NODECALS	// the surface can not have paint placed on it
#define SURF_NOCHOP		0x4000	// Don't subdivide patches on this surface
#define SURF_HITBOX		0x8000	// surface is part of a hitbox

#define MASK_ALL					(0xFFFFFFFF)
// everything that is normally solid
#define MASK_SOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// everything that blocks player movement
#define MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks npc movement
#define MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
// blocks fluid movement
#define MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
// water physics in these contents
#define MASK_WATER					(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
// everything that blocks lighting
#define MASK_OPAQUE					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS		(MASK_OPAQUE|CONTENTS_MONSTER)
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS		(MASK_BLOCKLOS|CONTENTS_MONSTER)
// everything that blocks line of sight for players
#define MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS		(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
// bullets see these as solid
#define MASK_SHOT					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
// bullets see these as solid, except monsters (world+brush only)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC_FLUID	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL		(CONTENTS_WATER|CONTENTS_SLIME)

// UNDONE: This is untested, any moving water
#define MASK_CURRENT				(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define MASK_DEADSOLID				(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

#define SEQUENCE_DEFAULT_DRAW						0
#define SEQUENCE_DEFAULT_IDLE1						1
#define SEQUENCE_DEFAULT_IDLE2						2
#define SEQUENCE_DEFAULT_LIGHT_MISS1				3
#define SEQUENCE_DEFAULT_LIGHT_MISS2				4
#define SEQUENCE_DEFAULT_HEAVY_MISS1				9
#define SEQUENCE_DEFAULT_HEAVY_HIT1					10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB				11
#define SEQUENCE_DEFAULT_LOOKAT01					12

#define SEQUENCE_BUTTERFLY_DRAW						0
#define SEQUENCE_BUTTERFLY_DRAW2					1
#define SEQUENCE_BUTTERFLY_LOOKAT01					13
#define SEQUENCE_BUTTERFLY_LOOKAT03					15

#define SEQUENCE_FALCHION_IDLE1						1
#define SEQUENCE_FALCHION_HEAVY_MISS1				8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP		9
#define SEQUENCE_FALCHION_LOOKAT01					12
#define SEQUENCE_FALCHION_LOOKAT02					13

#define SEQUENCE_DAGGERS_IDLE1						1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 				2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 				6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 				11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 				12

#define SEQUENCE_BOWIE_IDLE1 						1
