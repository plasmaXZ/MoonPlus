script_name("Shoot from vehicle example")
script_author("plasma")
script_description("Shoots from both sides of a vehicle with a submachine gun when pressing LMB.")
script_version("1.0")

local vk = require "lib.vkeys"
local mad = require "MoonAdditions"
local mps = require "MoonPlus"

local key = vk.VK_LBUTTON

local function shoot_from_vehicle(player_pointer, vehicle_pointer)
	if not mps.is_ped_pointer_valid(player_pointer) then
		return
	end
	if not mps.is_vehicle_pointer_valid(vehicle_pointer) then
		return
	end
	
	local player = mps.ped.from_memory(player_pointer)
	local slot = player.active_weapon_slot
	if slot ~= mps.weapon_slot.SUB_MACHINE_GUN then
		return
	end
	
	local weapon = mps.weapon.from_ped(player_pointer, slot)
	weapon:fire_instant_hit_from_car(vehicle_pointer, false, true)
	weapon:fire_instant_hit_from_car(vehicle_pointer, true, false)
end

function main()
	while true do
		if isPlayerPlaying(PLAYER_HANDLE) and isCharInAnyCar(PLAYER_PED) then
			local vehicle = getCarCharIsUsing(PLAYER_PED)
			if isKeyDown(key) then
				shoot_from_vehicle(getCharPointer(PLAYER_PED), getCarPointer(vehicle))
			end
		end
		
		wait(100)
	end
end
