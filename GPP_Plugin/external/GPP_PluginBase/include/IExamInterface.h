#pragma once
#include "IBaseInterface.h"

class IExamInterface : public IBaseInterface
{
public:
	IExamInterface();
	~IExamInterface();

	//WORLD & ENTITIES
	virtual WorldInfo World_GetInfo() const = 0;
	virtual StatisticsInfo World_GetStats() const = 0;

	virtual std::vector<HouseInfo> GetHousesInFOV() const = 0;
	virtual std::vector<EnemyInfo> GetEnemiesInFOV() const = 0;
	virtual std::vector<PurgeZoneInfo> GetPurgeZonesInFOV() const = 0;
	virtual std::vector<ItemInfo> GetItemsInFOV() const = 0;

	virtual const FOVStats& FOV_GetStats() const = 0;

	virtual AgentInfo Agent_GetInfo() const = 0;

	//NAVMESH
	virtual Elite::Vector2 NavMesh_GetClosestPathPoint(Elite::Vector2 goal) const = 0;

	//INVENTORY
	virtual bool Inventory_AddItem(UINT slotId, ItemInfo item) = 0;
	virtual bool Inventory_UseItem(UINT slotId) = 0;
	virtual bool Inventory_RemoveItem(UINT slotId) = 0;
	virtual bool Inventory_GetItem(UINT slotId, ItemInfo& item) = 0;
	virtual UINT Inventory_GetCapacity() const = 0;

	//ITEMS
	virtual bool GrabNearestItem(ItemInfo& item) = 0;	// DEBUG ONLY
	virtual bool GrabItem(const ItemInfo& item) = 0;
	virtual bool DestroyItem(const ItemInfo& item) = 0;

	//DEBUG
	virtual Elite::Vector2 Debug_ConvertScreenToWorld(Elite::Vector2 screenPos) const = 0;
	virtual Elite::Vector2 Debug_ConvertWorldToScreen(Elite::Vector2 worldPos) const = 0;

	//INPUT
	virtual bool Input_IsKeyboardKeyDown(Elite::InputScancode key) const = 0;
	virtual bool Input_IsKeyboardKeyUp(Elite::InputScancode key) const = 0;
	virtual bool Input_IsMouseButtonDown(Elite::InputMouseButton button) const = 0;
	virtual bool Input_IsMouseButtonUp(Elite::InputMouseButton button) const = 0;
	virtual Elite::MouseData Input_GetMouseData(Elite::InputType type, Elite::InputMouseButton button = Elite::InputMouseButton(0)) const = 0;

	//EVENT
	virtual void RequestShutdown() const = 0;
};