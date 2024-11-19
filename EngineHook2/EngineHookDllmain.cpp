#pragma once
#include "pch.h"
#include <iostream>
//#include "include/CompileReflection.h"
//#include "include/EntityFactory.h"
//#include "include/Enums.h"
//#include "include/EUpdateMode.h"
//#include "include/Hash.h"
//#include "include/Pins.h"
//#include "include/Prim.h"
//#include "include/Reflection.h"
//#include "include/SColorRGB.h"
//#include "include/SColorRGBA.h"
//#include "include/SGameUpdateEvent.h"
//#include "include/SOnlineEvent.h"
//#include "include/TArray.h"
//#include "include/THashMap.h"
//#include "include/TMap.h"
//#include "include/TPair.h"
//#include "include/ZAction.h"
//#include "include/ZActor.h"
//#include "include/ZAIGameState.h"
//#include "include/ZApplicationEngineWin32.h"
//#include "include/ZBuffer.h"
//#include "include/ZCameraEntity.h"
//#include "include/ZCollision.h"
//#include "include/ZComponentCreateInfo.h"
//#include "include/ZContentKitManager.h"
//#include "include/ZDelegate.h"
//#include "include/ZEngineAppCommon.h"
//#include "include/ZEntity.h"
//#include "include/ZEntityManager.h"
//#include "include/ZFreeCamera.h"
//#include "include/ZGameContext.h"
//#include "include/ZGameLoopManager.h"
//#include "include/ZGameMode.h"
//#include "include/ZGameStats.h"
//#include "include/ZGameTime.h"
//#include "include/ZGameUIManager.h"
//#include "include/ZGeomEntity.h"
//#include "include/ZHitman5.h"
//#include "include/ZHM5BaseCharacter.h"
//#include "include/ZHM5CrippleBox.h"
//#include "include/ZHM5InputManager.h"
//#include "include/ZHttp.h"
//#include "include/ZInput.h"
//#include "include/ZInputActionManager.h"
//#include "include/ZInventory.h"
//#include "include/ZItem.h"
//#include "include/ZKnowledge.h"
//#include "include/ZLevelManager.h"
//#include "include/ZLobby.h"
//#include "include/ZMath.h"
//#include "include/ZMemory.h"
//#include "include/ZModule.h"
//#include "include/ZObject.h"
//#include "include/ZOutfit.h"
//#include "include/ZPhysics.h"
//#include "include/ZPlayerRegistry.h"
//#include "include/ZPrimitives.h"
//#include "include/ZRakNet.h"
//#include "include/ZRender.h"
//#include "include/ZRepository.h"
//#include "include/ZResource.h"
//#include "include/ZResourceID.h"
//#include "include/ZScene.h"
//#include "include/ZSetpieceEntity.h"
//#include "include/ZSpatialEntity.h"
//#include "include/ZString.h"
//#include "include/ZTypeRegistry.h"

#include "ZSpatialEntity.h"
#include "TArray.h"
#include "TMap.h"
#include "ZBuffer.h"
#include "ZResourceID.h"
#include "ZString.h"

class IResourcePackerContext {};
class IXMLDOMDocument {};
class SGridGuide {
public:
    float m_fLength;
    float m_fCellIntersectMargin;
    unsigned int m_nPriority;
    char padding[4];
    SMatrix m_ToWorldMatrix;
};
class ZGridGuideEntity : ZSpatialEntity // sizeof=0x100
{
    float m_fLength;
    float m_fCellIntersectMargin;
    unsigned int m_nPriority;
    char padding[4];
};
template <typename T> class ZComPtr {
public:
    long long int m_pT;
};
class Vec4 {
public:
    float x;
    float y;
    float z;
    float w;
};
class SGridProperties {
public:
    SGridProperties() {
        vMin = { 0, 0, 0, 0 };
        vMax = { 30, 30, 30, 0 };
        nGridWidth = 10;
        fGridSpacing = 2.25;
        nVisibilityRange = 22;
    }
    Vec4 vMin;
    Vec4 vMax;
    uint32_t nGridWidth;
    float fGridSpacing;
    uint32_t nVisibilityRange;
};


typedef void(*ImportZToolReasoningGridModuleFunc)();
typedef void(*ImportZRuntimePathfinderModule)();

template <typename... Args>
void FastCall(size_t address, Args... args)
{
    reinterpret_cast<void(__fastcall*)(Args...)>(address)(args...);
}

template <typename Ret, typename... Args>
Ret FastCallAndReturn(size_t address, Args... args)
{
    return reinterpret_cast<Ret(__fastcall*)(Args...)>(address)(args...);
}

class ZGridGenerator;
class ZGridExporter {
public:
    class SStreamingRootData {};
    class SBoundingBox {};
    class SCollisionMesh {};
    class SPartitioningCoords {};
    TMap<ZString, unsigned int> m_LayerProps;
    ZComPtr<IXMLDOMDocument> m_pCollisionTypeDefinitions;
    ZComPtr<IXMLDOMDocument> m_pLayerTypeDefinitions;
    IResourcePackerContext* m_pResourcePackerContext;
    ZBuffer* m_PFData;
    TArray<SGridGuide> m_GridGuides;
    TArray<ZGridExporter::SStreamingRootData> m_StreamingRoots;
    ZGridGenerator* m_pGridGenerator;
    SStreamingRootData* m_pCurrentStreamingRoot;
    SBoundingBox* m_pCurrentBoundingBox;

    ZGridExporter() {
        m_LayerProps.m_container.m_nSize = 0;
        m_LayerProps.m_container.m_tree.m_reserved1 = 0;
        m_LayerProps.m_container.m_tree.m_pLeftRoot = 0LL;
        m_LayerProps.m_container.m_tree.m_pRightRoot = 0LL;
        m_LayerProps.m_container.m_tree.m_pNULL = 0LL;
        m_pCollisionTypeDefinitions.m_pT = 0LL;
        m_pLayerTypeDefinitions.m_pT = 0LL;
        m_pResourcePackerContext = 0LL;
        m_PFData = 0LL;
        m_GridGuides.m_pStart = 0LL;
        m_GridGuides.m_pEnd = 0LL;
        m_GridGuides.m_pLast = 0LL;
        m_StreamingRoots.m_pStart = 0LL;
        m_StreamingRoots.m_pEnd = 0LL;
        m_StreamingRoots.m_pLast = 0LL;
    }

    void PackResource()
    {
        uintptr_t toolReasoninggrid = reinterpret_cast<uintptr_t>(GetModuleHandleA("tool.reasoninggrid.dll"));

        IResourcePackerContext* pContext = new IResourcePackerContext();
        ZResourceID* NavpowerSource = new ZResourceID();
        ZResourceID* target = new ZResourceID();
        TMap<ZString, ZString>* options = new TMap<ZString, ZString>();
        FastCall<ZGridExporter*>(toolReasoninggrid + 0x13910, this, pContext, NavpowerSource, target, options);
    }
};
class ZPFAreaRef {};
enum ENavmeshChangeType {};
template <typename A, typename B, typename C, typename D, typename E>
class ZEvent {};
class ZEventNull {};
template <typename T>
class TRefCountPtr {};

template <typename T, typename... V>
class TDefaultHashMapPolicy2 // sizeof=0x0
{
};
class ZPFPath {};
class ZPathfinder : IComponentInterface // sizeof=0x78
{                                       // XREF: .data:char near * g_pPathfinderSingleton/r
public:
    class SAsyncPathRequest {};
    TArray<SAsyncPathRequest> m_asyncRequests;
    ZEvent<ENavmeshChangeType, ZEventNull, ZEventNull, ZEventNull, ZEventNull> m_NavmeshChangedEvent;
    void* m_pNavpowerResource;
    unsigned __int64 m_nNavpowerResourceSize;
    char* m_pNavpowerResourceCopy;
    bool m_bEnableSimulate;
    char pad0[7];
    TArray<TRefCountPtr<ZPFPath> > m_activePaths;

    static int _initializePathfinder() {
        HMODULE hDllRuntimePathfinder = LoadLibrary(TEXT("runtime.pathfinder.dll"));
        if (!hDllRuntimePathfinder)
        {
            std::cerr << "Could not load the runtime.pathfinder.dll DLL!" << std::endl;
            return 1;
        }
        ImportZRuntimePathfinderModule importZRuntimePathfinderModule = (ImportZRuntimePathfinderModule)GetProcAddress(hDllRuntimePathfinder, "?ImportZRuntimePathfinderModule@@YAXXZ");
        if (!importZRuntimePathfinderModule)
        {
            std::cerr << "Could not locate the ImportZRuntimePathfinderModule function!" << std::endl;
            FreeLibrary(hDllRuntimePathfinder);
            return 1;
        }
        importZRuntimePathfinderModule();
        return 0;
    }

    static ZPathfinder* globalPathfinderWithFunction() {
        _initializePathfinder();
        uintptr_t runtimePathfinder = reinterpret_cast<uintptr_t>(GetModuleHandleA("runtime.pathfinder.dll"));
        return FastCallAndReturn<ZPathfinder*>(runtimePathfinder + 0x120A0);
    }

    static ZPathfinder* globalPathfinderFromVar() {
        _initializePathfinder();
        uintptr_t runtimePathfinder = reinterpret_cast<uintptr_t>(GetModuleHandleA("runtime.pathfinder.dll"));
        return reinterpret_cast<ZPathfinder*>(runtimePathfinder + 0x120A0);
    }

    static void GetAllStaticAreas(TArray<ZPFAreaRef>* pfAreas) {
        uintptr_t runtimePathfinder = reinterpret_cast<uintptr_t>(GetModuleHandleA("runtime.pathfinder.dll"));
        ZPathfinder* g_pPathfinderSingleton = globalPathfinderFromVar();
        FastCallAndReturn<ZPathfinder*>(runtimePathfinder + 0x1DFB0, g_pPathfinderSingleton, pfAreas);
    }
};
class ZGridGenerator
{
public:
    class SGCell;
    const TArray<ZGridExporter::SCollisionMesh>* m_CollisionMeshes;
    const THashMap<ZGridExporter::SPartitioningCoords, ZGridExporter::SCollisionMesh, TDefaultHashMapPolicy2<ZGridExporter::SPartitioningCoords, ZGridExporter::SCollisionMesh> >* m_PartitioningData;
    const TArray<ZGridExporter::SBoundingBox>* m_BoundingBoxes;
    const TArray<SGridGuide> *m_GridGuides;
    bool m_bGenerateOldVisibilityData;
    char pad0[7];
    TMap<int, TArray<ZGridGenerator::SGCell> > m_Waypoints;
    TMap<int, TArray<short> > m_WaypointMap;
    TArray<ZPFAreaRef> m_pfAreas;
    unsigned int m_nPassedDistanceToObject;
    unsigned int m_nPassedRayAABBIntersect;
    unsigned int m_nRayCheckCount;
    char pad1[4];
    ZGridGenerator() {
        TArray<ZGridExporter::SCollisionMesh> CollisionMeshes;
        THashMap<ZGridExporter::SPartitioningCoords, ZGridExporter::SCollisionMesh, TDefaultHashMapPolicy2<ZGridExporter::SPartitioningCoords, ZGridExporter::SCollisionMesh> > partitioningData;
        TArray<ZGridExporter::SBoundingBox> BoundingBoxes;
        TArray<SGridGuide> GridGuides;
        bool bGenerateOldVisibilityData = false;

        TArray<ZPFAreaRef>* p_m_pfAreas; // rdi
        this->m_CollisionMeshes = &CollisionMeshes;
        this->m_PartitioningData = &partitioningData;
        this->m_BoundingBoxes = &BoundingBoxes;
        p_m_pfAreas = &this->m_pfAreas;
        this->m_GridGuides = &GridGuides;
        this->m_bGenerateOldVisibilityData = bGenerateOldVisibilityData;
        this->m_Waypoints.m_container.m_nSize = 0;
        this->m_Waypoints.m_container.m_tree.m_reserved1 = 0;
        this->m_Waypoints.m_container.m_tree.m_pLeftRoot = 0LL;
        this->m_Waypoints.m_container.m_tree.m_pRightRoot = 0LL;
        this->m_Waypoints.m_container.m_tree.m_pNULL = 0LL;
        this->m_WaypointMap.m_container.m_nSize = 0;
        this->m_WaypointMap.m_container.m_tree.m_reserved1 = 0;
        this->m_WaypointMap.m_container.m_tree.m_pLeftRoot = 0LL;
        this->m_WaypointMap.m_container.m_tree.m_pRightRoot = 0LL;
        this->m_WaypointMap.m_container.m_tree.m_pNULL = 0LL;
        this->m_pfAreas.m_pStart = 0LL;
        this->m_pfAreas.m_pEnd = 0LL;
        this->m_pfAreas.m_pLast = 0LL;
        this->m_nPassedDistanceToObject = 0LL;
        this->m_nRayCheckCount = 0;
        //ZPathfinder::GetAllStaticAreas(p_m_pfAreas);
    }
    void GenerateGrid()
    {
        uintptr_t toolReasoninggrid = reinterpret_cast<uintptr_t>(GetModuleHandleA("tool.reasoninggrid.dll"));

        FastCall<ZGridGenerator*>(toolReasoninggrid + 0x20F80, this);
    }

    void GenerateWaypointNodes()
    {
        uintptr_t toolReasoninggrid = reinterpret_cast<uintptr_t>(GetModuleHandleA("tool.reasoninggrid.dll"));

        SGridProperties properties = SGridProperties();

        FastCall<ZGridGenerator*>(toolReasoninggrid + 0x21C20, this, &properties);
    }
};
class ZMutex {
    uint64_t m_ipl[5];
    unsigned int m_nUniqueID;
};
class SDebugRenderViewport {
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
};
class IRenderDebugRender {
public:
    enum PRIMTYPE : __int32
    {                                       // XREF: ZDebugRender::PRIMTYPE/r
        PT_LINES = 0x0,
        PT_TRIANGLES = 0x1,
        MAX_NUM_PRIMTYPES = 0x2,
    };
};
class SDebugVertex // sizeof=0x20
{                                       // XREF: ZDebugRender/r
                                        // ZDebugRender/r
    float p[3];
    unsigned int c;
    float t[3];
    unsigned int nObjectID;
};
template <typename T, typename V>
// ZDelegate<void __cdecl(ZDebugRender*),  ZDelegate<void __cdecl(ZDebugRender*)
class TBag // sizeof=0x18
{                                       // XREF: ZDebugRender/r
    TArray<V> m_container;
};

class ZDebugRender;

class SDebugRenderPrim // sizeof=0x18
{                                       // XREF: TDeleteHelper<SDebugRenderPrim>/r
public:
    SDebugVertex * pVertices;
    unsigned int nNumVerts;
    IRenderDebugRender::PRIMTYPE nPrimType;
    int nRef;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};
template <typename T, typename I, typename V, typename J>
class THashMap2 // sizeof=0x20
{
    unsigned int m_nSize;
    unsigned int m_iFree;
    SHashMapInfo<TPair<ZSpatialEntity* const, unsigned int> > m_info;
};
template <typename T, int>
class THashArray  // sizeof=0x20
{                                       // XREF: ZDebugRender::SRenderDebugChannel/r
    THashMap<ZSpatialEntity*, unsigned int, TDefaultHashMapPolicy2<ZSpatialEntity*, unsigned int> >* m_pIndexMap;
    TArray<ZSpatialEntity*> m_Array;
};
template<typename T, int V>
class TFixedArray2
{
public:
    T* m_pStart;
    T* m_pEnd;
};

class ZDebugRender // sizeof=0x4DA0
{
public:
    typedef IRenderDebugRender::PRIMTYPE PRIMTYPE;

    class SRenderDebugDrawUpdates;

    class SRenderDebugChannel // sizeof=0x40
    {                                       // XREF: ZDebugRender/r
        THashArray<ZSpatialEntity*, 16> m_Entities;
        THashMap<
            ZDelegate<void __cdecl(ZDebugRender*)>,
            ZDebugRender::SRenderDebugDrawUpdates,
            TDefaultHashMapPolicy2<
                ZDelegate<ZDebugRender*>,
                SRenderDebugDrawUpdates
            >
        > m_DrawUpdates;
    };
    class SClipPlanes4 // sizeof=0x40
    {                                       // XREF: ZFixedArrayData<ZDebugRender::SClipPlanes4,8>/r
        float4 x4;
        float4 y4;
        float4 z4;
        float4 w4;
    };

    ZMutex m_mutex;
    SVector2 m_vTextOffset;
    SDebugRenderViewport m_Viewport;
    bool m_bInScene;
    bool m_bOrtho;
    char pad0[2];
    float m_fOrthoScale;
    SMatrix m_WorldToView;
    SMatrix m_ViewToWorld;
    SMatrix m_Projection;
    bool m_bInside_xBegin;
    char pad1[3];
    ZDebugRender::PRIMTYPE m_CurrentType;
    SMatrix44 m_mCurrentMatrix;
    SDebugVertex m_CurrentVertex;
    unsigned int m_lWantedColor;
    unsigned int m_lWantedObjectID;
    unsigned int m_lCurrentObjectID;
    unsigned int m_lVertexCount;
    SDebugVertex m_Vertices[512];
    unsigned int m_lCurrentDrawMode;
    char pad2[4];
    unsigned __int64 m_lCurrentTextureId;
    unsigned int m_lWantedDrawMode;
    char pad3[4];
    unsigned __int64 m_lWantedTextureId;
    bool m_bWantedTextureIsPtr;
    char pad4[3];
    float m_fFontSize[2];
    char pad5[4];
    TBag<ZDelegate<void __cdecl(ZDebugRender*)>, TArray<ZDelegate<void __cdecl(ZDebugRender*)> > > m_DrawUpdateFullScreenEntries;
    bool m_bDrawUpdateConsole;
    char pad6[7];
    ZDelegate<void __cdecl(ZDebugRender*)> m_DrawUpdateConsole;
    IRenderDebugRender * m_pRenderDebugRender;
    SDebugRenderPrim * m_DebugPrims;
    bool m_bHasDebugPrims;
    char pad7[7];
    ZDebugRender::SRenderDebugChannel m_DebugChannels[30];
    TFixedArray2<ZDebugRender::SClipPlanes4, 8> m_aClipPlanes4;
    unsigned int m_nNumClipPlanesSoA;
    char pad8[12];
    float4 m_avClipPlanes[32];

};
class SRenderDebugDrawUpdates // sizeof=0x28
{                                       // XREF: TPair<ZDelegate<void __cdecl(ZDebugRender *)> const ,ZDebugRender::SRenderDebugDrawUpdates>/r
                                        // ?RegisterForDrawUpdate@ZDebugRender@@QEAAXPEAVZEntityImpl@@W4EDebugChannel@@AEBV?$ZDelegate@$$A6AXPEAVZDebugRender@@@Z@@@Z_0/r ...
    ZDelegate<void __cdecl(ZDebugRender*)> m_Delegate;
    // XREF: ZDebugRender::RegisterForDrawUpdate(ZEntityImpl *,EDebugChannel,ZDelegate<void (ZDebugRender *)> const &)+84/w
    // ZDebugRender::RegisterForDrawUpdate(ZEntityImpl *,EDebugChannel,ZDelegate<void (ZDebugRender *)> const &)+92/w ...
    ZEntityImpl* m_pEntity;             // XREF: ZDebugRender::RegisterForDrawUpdate(ZEntityImpl *,EDebugChannel,ZDelegate<void (ZDebugRender *)> const &)+AF/w
    // ZDebugRender::RegisterForDrawUpdate(EDebugChannel,ZDelegate<void (ZDebugRender *)> const &)+A2/w
};
class ZBoundedEntity : ZSpatialEntity // sizeof=0x110
{                                       // XREF: ZRenderableEntity/r
                                        // ZGateEntity/r ...
    SVector3 m_vCenter;
    SVector3 m_vHalfSize;
    char pad[8];
};

//class ZRenderableEntity : ZBoundedEntity // sizeof=0x130
//{                                       // XREF: ZCameraEntity/r
//                                        // ZRenderDestinationScreenEntity/r ...
//    unsigned __int8 m_nChangedFlag;
//    __int8 m_bIgnoreRooms : 1;
//    __int8 m_bPerformVisibilityTest : 1;
//    __int8 m_bDontDraw : 1;
//    __int8 m_bActiveRenderGraphNode : 1;
//    char pad0;
//    unsigned __int8 m_nRenderType;
//    char pad1;
//    unsigned int m_nBaseFlags;
//    ZRenderGraphNode *m_pRenderGraphData;
//    unsigned int m_nRenderBaseIndex;
//    char pad2[12];
//};

//class ZRenderGraphNode : ZVTablePaddingRemover // sizeof=0x48
//{           
//    enum TYPE : __int8
//    {                                       
//         GEOM = 0x0,
//         LINKED = 0x1,
//         PARTICLEEMITTER = 0x2,
//         SPEEDTREE = 0x3,
//         SPATIAL = 0x4,
//         LIGHT = 0x5,
//         CAMERA = 0x6,
//         MATERIAL = 0x7,
//         POSTFILTER = 0x8,
//         RAIN = 0x9,
//         RAINMODIFIER = 0xA,
//         RAINSIMULATION = 0xB,
//         COMPOSITOR = 0xC,
//         DESTINATION = 0xD,
//         VIDEO_PLAYER = 0xE,
//         UI = 0xF,
//         VOLUMELIGHT = 0x10,
//         FOGBOX = 0x11,
//         CROWDENTITY = 0x12,
//         SCATTER = 0x13,
//         MIRROR = 0x14,
//         BOXREFLECTION = 0x15,
//         RENDERGLOBAL = 0x16,
//         WATERPARAMETERS = 0x17,
//         ATMOSPHERICSCATTERING = 0x18,
//         TYPE_SIZE = 0x19,
//         RENDERABLE_TYPE_MASK = 0xF,
//         RENDERABLE_TYPE_FIRST = 0x0,
//         RENDERABLE_TYPE_LAST = 0x3,
//     };
//    unsigned int m_nFlags; 
//    float m_fTessellationOffset;
//    float m_fTessellationMaxDistRcp;
//    char pad0[4];
//    ZRenderableEntity* m_pRenderable;
//    int m_Base;                        
//    unsigned __int16 m_nRoomID;
//    unsigned __int16 m_nRoomIDOverlap[2];
//    ZRenderGraphNode::TYPE m_nType;
//    unsigned __int8 m_nTessellationMaxTessellation;
//    unsigned int m_nGridIndex;
//    __int32 m_eTessellationMode : 2;     
//    __int32 m_eTessellationFactorMode : 2;
//    char pad1[15];
//    ZString m_sDebugName;              
// };
//class ZRenderGraphNodeCamera : ZRenderGraphNode // sizeof=0x3E8390
//{
//    char pad0[8];
//    SMatrix m_mObjectToWorldPrev;
//    SReflectCamera m_State;
//    unsigned int m_nWidth;
//    unsigned int m_nHeight;
//    int m_nEnableDOFOverride;
//    float m_fBaseFovY;
//    float m_fGateClipDistanceScale;
//    float m_fStableFovY;
//    float m_fLODZoomFactor;
//    unsigned int m_nBoxReflectionsEmissive;
//    float m_fExportNearZ;
//    float m_fExportFarZ;
//    char pad1[8];
//    ZRenderSuperSample m_SuperSample;
//    TAutoReleasePointer<ZRenderTexture2D> m_pPrevColorTexture;
//    TAutoReleasePointer<ZRenderShaderResourceView> m_pPrevColorSRV;
//    TAutoReleasePointer<ZRenderTexture2D> m_pPrevDepthTexture;
//    TAutoReleasePointer<ZRenderShaderResourceView> m_pPrevDepthSRV;
//    SMatrix m_mPrevViewProj;
//    TArray<int> m_OSDNodes;
//    TArray<ZRenderGraphNode*> m_RootNodes;
//    ZRenderDebugRenderBuffer * m_pRenderDebugRenderBuffer;
//    char pad2[8];
//    SQV m_CameraCutLasTransform;
//    SRoomInsideOutsideInfo m_InsideOutsideInfo;
//    SRoomInsideOutsideInfo m_LastInsideOutsideInfo;
//    unsigned __int16 m_nStickyRoomId;
//    unsigned __int16 m_nNumOverlappingRooms;
//    unsigned __int16 m_aOverlappingRooms[32];
//    unsigned __int16 m_nInsideGate;
//    __int8 m_bActive = 1;
//    __int8 m_bAllocated = 1;
//    __int8 m_bIsOrtho = 1;
//    __int8 m_bCameraBufferAllocated = 1;
//    __int8 m_bRainVisibleLastFrame = 1;
//    __int8 m_bRainRefraction = 1;
//    bool pad3;
//    bool pad4;
//    char pad5[5];
//    SRenderTexture2DAccess m_SampleGBufferTextureGPU[1];
//    SRenderTexture2DAccess m_SampleGBufferTextureCPU[1];
//    unsigned int m_iSampleGBufferIndex;
//    char pad6[12];
//};

class ZComponentCreateInfo // sizeof=0x58
{                                      

public:
    struct SArgumentInfo // sizeof=0x10
    {                                       // XREF: ZComponentCreateInfo/r
        STypeID * m_type;
        const void* m_pData;
    };
    //ZComponentCreateInfo() {};
    //ZComponentCreateInfo(int m_nCount, const SArgumentInfo m_aArguments[5]) : m_nCount(m_nCount), m_aArguments{ m_aArguments[0], m_aArguments[1], m_aArguments[2], m_aArguments[3], m_aArguments[4] } {}
    int m_nCount;                      
    char pad[4] = { '\0', '\0', '\0', '\0' };
    SArgumentInfo m_aArguments[5];
};
class IResourcePacker{};
template <typename T, typename V, int>
class SCreatePolicy {
public:
    static void Create(ZComponentCreateInfo* zComponentCreateInfo) {
        uintptr_t toolReasoningGrid = reinterpret_cast<uintptr_t>(GetModuleHandleA("tool.reasoninggrid.dll"));
        uintptr_t SCreatePolicy_LT_ZGridExporter_IResourcePacker_GT_Create = toolReasoningGrid + 0x29160;
        FastCall<>(SCreatePolicy_LT_ZGridExporter_IResourcePacker_GT_Create, toolReasoningGrid, &zComponentCreateInfo);
    }
};

DWORD WINAPI MainThread(HMODULE hModule)
{
    HMODULE hDllToolReasoningGrid = LoadLibrary(TEXT("tool.reasoninggrid.dll"));
    if (!hDllToolReasoningGrid)
    {
        std::cerr << "Could not load the tool.reasoninggrid.dll DLL!" << std::endl;
        return 1;
    }
    ImportZToolReasoningGridModuleFunc importZToolReasoningGridModuleFunc = (ImportZToolReasoningGridModuleFunc)GetProcAddress(hDllToolReasoningGrid, "?ImportZToolReasoningGridModule@@YAXXZ");
            importZToolReasoningGridModuleFunc();

    if (!importZToolReasoningGridModuleFunc)
    {
        std::cerr << "Could not locate the ImportZToolReasoningGridModuleFunc function!" << std::endl;
        FreeLibrary(hDllToolReasoningGrid);
        return 1;
    }
    importZToolReasoningGridModuleFunc();

    while (true)
    {
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            ZGridGenerator gridGenerator;
            gridGenerator.GenerateGrid();
            //ZGridExporter gridExporter;
            //gridExporter.PackResource();
            //ZGridGenerator gridGenerator;
            //gridGenerator.GenerateWaypointNodes();

            //uintptr_t runtimeDebug = reinterpret_cast<uintptr_t>(GetModuleHandleA("runtime.debug.dll"));
            //ZDebugRender* zDebugRender = FastCallAndReturn<ZDebugRender*>(runtimeDebug + 0x13BF0);
            //FastCall<>(runtimeDebug + 0x1D43, zDebugRender, 100, 50, 50, 50);
            //uintptr_t runtimeRender = reinterpret_cast<uintptr_t>(GetModuleHandleA("runtime.render.dll"));
            //FastCall<>(runtimeRender + 0x33308C, zDebugRender, 1);
            //ZRenderGraphNodeCamera zRenderGraphNodeCamera;
            //FastCall<>(runtimeRender + 0xE5430, &zRenderGraphNodeCamera);
            //ZComponentCreateInfo zComponentCreateInfo;
            //zComponentCreateInfo.m_nCount = 1;
            //ZComponentCreateInfo::SArgumentInfo arg0;
            //STypeID arg0Type;
            //arg0Type.m_nTypeNum
            //arg0.m_type = 
            //zComponentCreateInfo.m_aArguments[0] = arg0;
            //SCreatePolicy<ZGridExporter, IResourcePacker, 0>::Create(&zComponentCreateInfo);
            int x = 0;
        }
        if (GetAsyncKeyState(VK_F4) & 1)
        {
            break;
        }

        Sleep(5);
    }

    FreeConsole();

    FreeLibraryAndExitThread(hModule, 0);

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        HANDLE hdl = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);

        if (hdl)
        {
            CloseHandle(hdl);
        }

        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

