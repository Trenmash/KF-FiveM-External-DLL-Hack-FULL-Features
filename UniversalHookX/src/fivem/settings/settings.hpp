#pragma once
#define to_vec4(r, g, b, a) ImColor(r / 255.f, g / 255.f, b / 255.f, a)

namespace settings {
	inline bool init = false;
	inline int auth = 0;
	inline bool can_use_menu = false;
	inline float size = 1.5f;
	inline float particleColour[4] = { 0, 255, 200, 255 };

	inline ImColor particle = ImColor(255, 255, 255, 255);

	namespace fonts {
		inline ImFont* icon = nullptr;
		inline ImFont* icon_big = nullptr;
		inline ImFont* tab_text = nullptr;
		inline ImFont* cheat_name = nullptr;
	}
	namespace Player
	{


		inline bool enable = false;

		inline bool Godmod = false;
		inline bool Semi_Godmod = false;
		inline bool Infinite_Armor = false;
		inline bool SetHealth = false;
		inline bool fastrun = false;
		inline bool SetArmor = false;
		inline int RunSpeedToSet = 1;

		inline int HealthToSet = 100;
		inline int ArmorToSet = 100;
		inline bool NoClip = false;
		inline int noclipspeed = false;
		inline int isNoclipWorking = true;
		inline bool Invisible = false;
		inline bool AntiHS = false;
		inline bool Infinite_stamina = false;
		inline int HotkeyArmor = 0;
		inline int HotkeyHealth = 0;
		inline bool flymode = false;
		inline int ForwardHotkey = 90;
		inline int BackwardHotkey = 0x53;

		inline bool EnableFovChange = false;
		inline bool SuperJump = false;
		inline bool TpToWaypoint = false;
		inline bool NoRagDoll = false;
		inline float FovValue = 50;
		inline bool NoClipSpeed_bool = false;
		inline int Speed = 0;
		inline bool Gravity = false;
		inline bool AirStuck = false;
		inline int Airstuck_hotkey = 0;
		inline bool godnoclip = false;



	}
	namespace Aimbot
	{
		inline bool Aimbot = false;
		inline bool Draw_Fov = false;
		inline bool PreviewTarget = false;
		inline int AimbotFov = 30;
		inline int AimbotSmooth = 1;
		inline int TypeOfTarget = 0;
		inline const char* AimbotTarget[]{ "All", "Only Player", "Only Ped" };
		inline int DistanceAimbotLimit = 150;
		inline int AimbotBone = 0;
		inline const char* AimbotBones[]{ "Head", "Body", "Leg left", "Leg right", "Arm right", "Arm left" };
		inline int AimbotTypes = 0;

		inline const char* AimbotType[]{ "Mouse aim", "Memory aim" };

		inline int Hotkey = 2;
		inline bool rapidfire = false;
		inline bool crosshair = false;
		inline bool silentaim = false;
		inline bool Check_Fov = false;

		inline bool magic = false;
		inline bool aimmousewhilesilent = false;

	}
	namespace aimbot {

		inline bool enabled = false;
		inline bool TriggerBot = false;
		inline bool psygun = false;

		inline int hotkey = 2;

		inline int aimbot_fov = 5;
		inline int smoothhorizontal = 2;
		inline int smoothvertical = 2;

		inline int aimbot_target = 0;
		inline bool ignore_peds = false;
		inline const char* aimbot_target_list[]{ "All", "Only Player", "Only Ped" };

		inline int aimbot_distance = 150;

		inline int aimbot_smooth = 0;

		inline bool distancetestiz = true;

		inline int aimbot_bone = 0;
		inline const char* aimbot_bones_list[]{ "Head", "Neck", "Body" };

		inline int aimbot_type = 1;
		inline const char* aimbot_type_list[]{ "Mouse", "Memory","Silent Aim" };

		inline bool target_lock = false;

		inline bool overide_target = false;
		inline bool view_aim_point = false;

		inline bool auto_shoot = false;

		inline int aimbot_selection = 0;

	}
	namespace peds {
		inline int selected_index = 1;

		inline int selected_index_vehicle = 1;

		inline bool overide_veh = false;
		inline bool overide_ped = false;
	}

	namespace visuals {
		namespace radar {

			inline bool enabled = false;

			inline bool render_ped = false;
			inline bool render_dead = false;

			inline int size_x = 250;
			inline int size_y = 250;

			inline int zoom = 5;

			inline int opacity = 100;

			inline bool draw_vehicle = false;
			inline int healthbar_type = 0;
			inline const char* healthbar_type_text[]{ "Right", "Left", "Down" };
			inline int box_rounding = 1;
			inline float Dynamicdebug = 1;
			inline ImColor player_dot_circle = ImColor(255, 255, 255, 255);
			inline ImColor local_player_dot_circle = ImColor(255, 0, 0, 255);
			inline ImColor target_player_dot_circle = ImColor(255, 0, 0, 255);


		}
		extern int colorsheme = 0;
		inline const char* colorsheme_list[]{ "White", "Blue", "Pink" };
		inline int menu_alpha = 255;
		inline bool enabled = false;
		inline int master_switch = 0;
		inline const char* esp_type_text[]{ "Dynamic", "Static" };
		inline int esp_type = 0;
		inline bool filled = false;
		inline int healthbar_style = 1;
		inline bool box = false;
		inline int box_round = 0;
		inline bool fiveguardbypass = false;
		inline bool Skeleton_Detailled = false;
		inline bool skeleton = false;
		inline bool skeleton1 = false;
		inline bool armorbar = false;
		inline bool weapon_name = false;
		inline bool playername = false;
		inline bool playerid = false;
		inline bool healthbar = false;
		inline bool snapline = false;
		inline bool circle_at_middle = false;
		inline bool dont_draw_health = false;
		inline bool dont_draw_distance = false;
		inline bool visible_check = false;
		inline int visible_check_type = 0;
		inline const char* visible_check_choice_text[]{ "Visible Only", "Visible / No Visible" };
		inline bool tpped = false;
		inline bool invisibleped = false;
		inline bool killped = false;
		inline float tickness = 0.5f;
		inline bool box_esp = false;
		inline bool invisible_check = false;
		inline int invisible_check_type = 0;
		inline const char* invisible_check_type_text[]{ "Don't Draw Invisible", "Different Colors" };
		inline int box_rounding = 0;
		inline float Dynamicdebug = 1;

		inline bool enable2DRadar = false;

		inline bool draw_dead = false;
		inline bool aim_dead = false;
		inline int dead_opacity = 50;
		inline bool draw_ped = false;
		inline bool draw_self = false;





		inline bool watermark = true;
		inline int render_distance = 200;
		inline int vehicle_distance = 200;
		inline int lootbag_distance = 200;
		inline int skeleton_numbers = 0;
		inline int skeleton_numbers1 = 0;
		inline int skeleton_numbers2 = 0;
		inline int skeleton_numbers3 = 0;
		inline int skeleton_numbers4 = 0;
		inline int skeleton_numbers5 = 0;
		inline int skeleton_numbers6 = 0;
		inline int skeleton_numbers7 = 0;
		inline int skeleton_numbers8 = 0;
		inline int skeleton_numbers9 = 0;
		inline bool preview_target = false;
		inline int preview_style = 0;
		inline bool draw_fov = false;
		inline bool filled_fov = false;

		inline const char* ssxs[]{ "Dot", "Line", "Both" };

		inline bool crosshair = false;

		inline bool language = false;
		inline bool darkmode = true;
		inline bool particles = true;
		inline int crossahir_style = 0;
		inline int HealthbarStyle = 0;
		inline float box_size = 2.00f;
		inline bool health_bar = false;
		inline bool armor_bar = false;
		inline bool health_text = false;
		inline bool player_name = false;
		inline bool distance_text = false;

		inline int nane_type = 0;
		inline const char* name_type_text[]{ "Up", "Down" };

		inline int healthbar_type = 0;
		inline const char* healthbar_type_text[]{ "Right", "Left", "Down" };
		inline const char* sss[]{ "FiveM Reshade Crosshair", "Dot", "Cross" };

		inline int OutlinedText = 0;

		inline bool outlined = false;
		inline const char* OutlinedTextType[]{ "Outlined Text 1", "Outlined Text 2" };
		inline bool friend_visuals = false;
		inline int friend_visuals_check_type = 0;
		inline const char* friend_visuals_check_type_text[]{ "Don't Draw Friends", "Different Colors" };
		inline ImColor health_color = ImColor(255, 255, 255, 255);
		inline ImColor player_name_color = ImColor(255, 255, 255, 255);
		inline ImColor SkelColor = ImColor(255, 255, 255, 255);
		inline ImColor player_name_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor SkelColorVisible = ImColor(252, 3, 23, 255);
		inline ImColor health_color_visible = ImColor(255, 255, 255, 255);
		inline float BoxSize = 1;
		inline int FillBoxAlpha = 70;
		inline ImColor boxcolor = ImColor(255, 255, 255, 255);
		inline ImColor accentcolor_particle = ImColor(255, 255, 255, 255);
		inline ImColor boxcolordead = ImColor(255, 0, 0, 255);
		inline ImColor filledcolor = ImColor(255, 255, 255, 255);
		inline ImColor cornercolor = ImColor(33, 140, 176, 255);
		inline ImColor namecolor = ImColor(255, 255, 255, 255);
		inline ImColor skeleton_color = ImColor(255, 255, 255, 255);
		inline ImColor skeletonfriend_color = ImColor(255, 255, 255, 255);
		inline ImColor weapon_color = ImColor(255, 255, 255, 255);
		inline ImColor snapeline_color = ImColor(255, 255, 255, 255);
		inline ImColor distance_color = ImColor(255, 255, 255, 255);
		inline ImColor head_color = ImColor(255, 255, 255, 255);
		inline ImColor crosshair_color = ImColor(255, 255, 255, 255);
		inline ImColor preview_target_colors = ImColor(255, 255, 255, 255);
		inline ImColor fov_color = ImColor(255, 255, 255, 255);
		//___//
		inline ImColor vehicle_esp_color = ImColor(255, 255, 255, 255);
		inline ImColor vehiclebroken_esp_color = ImColor(255, 255, 255, 255);
		inline ImColor box_color_visible = ImColor(255, 255, 255, 255);
		inline ImColor vehicle_esp_health = ImColor(255, 255, 255, 255);
		inline ImColor vehicle_esp_marker = ImColor(255, 255, 255, 255);
		inline ImColor vehicle_esp_distance = ImColor(255, 255, 255, 255);
		inline ImColor box_color = ImColor(255, 255, 255, 150);
		inline ImColor invisible_color = ImColor(255, 255, 255, 255);

		inline ImColor friends_colors = ImColor(255, 255, 255, 255);




		//___//
		inline ImColor bag_esp_color = ImColor(255, 255, 255, 255);
		inline ImColor bagdistance_esp_color = ImColor(255, 255, 255, 255);
		inline ImColor bagmarker_esp_color = ImColor(255, 255, 255, 255);
		float accent_color[4] = { 0, 255, 200, 139 };
		ImColor get_accent_color(float a = 1.f) {

			return to_vec4(accent_color[0], accent_color[1], accent_color[2], a);
		}
		inline char cfg_name[10] = "";

	}
	namespace vehicles {

		inline bool enable = false;
		inline bool stickycar = false;
		inline bool godmode = false;
		inline bool fastspeed = false;
		inline bool nogravity = false;
		inline bool setmaxhealth = false;
		inline int Speed = 10;
		inline bool unlockcar = false;
		inline bool autostart_vehicle = false;
		inline bool warp_vehicle = false;
		inline bool repaire = false;
		inline bool shift_boost = false;
		inline bool vehicle_speed_bool = false;
		inline int vehicle_speed_value = 0;
		inline bool max_current_vehicle = false;
		inline bool on_car = false;
		inline bool NameESP = false;


		inline int mod_idx = 0;
		inline int primary_color = 0;
		inline int secondary_color = 0;
		inline int add_idx = 0;
		inline bool autodrive = false;

		inline bool spawn_vehicle = false;
		inline char VehicleHashString[15] = "";
		inline char plate_text[8] = "";
		inline bool update_colors = false;
		inline bool update_plate = false;

	};
	namespace vehicle {

		inline bool enabled = false;

		inline bool hornboost = false;
		inline bool vehclip = false;
		inline bool repair = false;
		inline bool vehicle_speed_bool = false;
		inline bool vehicle_repair = false;
		inline int vehicle_speed_value = 0;
		inline bool vehicle_esp = false;
		inline bool vehicle_name = false;
		inline bool vehicleprimcolor = false;
		inline bool vehicle_health = false;
		inline bool vehicle_distance = false;
		inline bool vehicle_snapline = false;
		inline bool vehicle_marker = false;
		inline bool godmod = false;
		inline bool update = false;
		inline char plate_text[8] = "...";

		inline int mod_idx = 0;
		inline int primary_color = 0;
		inline int secondary_color = 0;
		inline int add_idx = 0;

		inline bool update_colors = false;
		inline bool update_plate = false;


	}

	namespace object {

		inline bool object_esp = false;

		inline bool object_name = false;
		inline bool object_distance = false;
		inline bool object_snapline = false;
		inline bool object_marker = false;

	}
	namespace radar {

		bool enabled = false;
		bool enable2DRadar = false;

	}
	namespace weapon {

		inline bool enabled = false;
		static int weapon_current = 0;
		inline const char* weapon_list[]{ "Dagger", "Bat", "Knife", "Machete", "Pistol", "Pistol MK2", "Combat Pistol", "AP Pistol", "Stungun", "Pistol 50", "SNS PISTOL", "SNS Pistol MK2", "Heavy Pistol", "Vintage Pisol", "Flare Gun", "Marksman Pistol", "Revolver", "Revolver MK2", "Double Action", "Micro Smg", "Smg", "Smg MK2", "Assault Smg", "Combat PDW", "Machine Pistol", "Mini Smg", "Pump Shotgun", "Pump Shotgun MK2", "Sawnoff Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "DB Shotgun", "Auto Shotgun", "Assault Rifle", "Assault Rifle MK2", "Carbine Rifle", "Carbine Rifle MK2", "Advanced Rifle", "Special Carbine", "Special Carbine MK2", "Bullpup Rifle", "Bullpup Rifle MK2", "Compact Rifle", "Machine Gun", "Combat MG", "Combat MG MK2", "GUSENBERG", "Sniper Rifle", "AWP", "AWP MK2", "Marksman Rifle", "Marksman Rifle MK2", "RPG", "Grenade Launcher", "MiniGun", "FireWork", "RailGun", "Homing Launcher", "Compact Launcher", "Grenade", "BZGAS", "Smoke Grenade", "Flare", "Molotov", "Sticky BOMB", "Prox Mine", "SnowBall", "Pipe Bomb", "Ball", "Petrol Can", "Fire Extinguisher", "Parachute" };
		inline bool no_recoil = false;
		inline bool no_reload = false;
		inline bool no_spread = false;
		inline bool explosiveammo = false;
		inline bool explo_meele = false;
		inline bool weaponfireammo = false;
		inline bool infinite_range = false;
		inline bool no_hs = false;
		inline bool no_ragdoll = false;
		inline bool never_wanted = false;
		inline bool infinite_stamina = false;
		inline bool teleport_to_waypoint = false;
		inline bool infite_ammo = false;
		inline bool set_ammo = false;
		inline bool damage_boost = false;

		inline float recoil_value = 0;
		inline int reload_value = 100;
		inline int spread_value = 0;
		inline int weapon_range = 1000;
		inline int ammo_to_set = 0;
		inline int int_damage = 150;

		inline bool custom_fov = false;
		inline int scope_fov_value = 50;
		inline bool DoubleTap = false;
		inline int BulletToShot = 2;
		inline bool r_custom_fov = false;
		inline int r_scope_fov_value = 90;
		inline bool s_custom_fov = false;
		inline int s_scope_fov_value = 90;

		namespace weapon_spawning {
			inline bool weapon_spawning = false;

			inline int weapon_current = 0;
			inline const char* weapon_list[]{ "Dagger", "Bat", "Knife", "Machete", "Pistol", "Pistol MK2", "Combat Pistol", "AP Pistol", "Stungun", "Pistol 50", "SNS PISTOL", "SNS Pistol MK2", "Heavy Pistol", "Vintage Pisol", "Flare Gun", "Marksman Pistol", "Revolver", "Revolver MK2", "Double Action", "Micro Smg", "Smg", "Smg MK2", "Assault Smg", "Combat PDW", "Machine Pistol", "Mini Smg", "Pump Shotgun", "Pump Shotgun MK2", "Sawnoff Shotgun", "Assault Shotgun", "Bullpup Shotgun", "Musket", "Heavy Shotgun", "DB Shotgun", "Auto Shotgun", "Assault Rifle", "Assault Rifle MK2", "Carbine Rifle", "Carbine Rifle MK2", "Advanced Rifle", "Special Carbine", "Special Carbine MK2", "Bullpup Rifle", "Bullpup Rifle MK2", "Compact Rifle", "Machine Gun", "Combat MG", "Combat MG MK2", "GUSENBERG", "Sniper Rifle", "AWP", "AWP MK2", "Marksman Rifle", "Marksman Rifle MK2", "RPG", "Grenade Launcher", "MiniGun", "FireWork", "RailGun", "Homing Launcher", "Compact Launcher", "Grenade", "BZGAS", "Smoke Grenade", "Flare", "Molotov", "Sticky BOMB", "Prox Mine", "SnowBall", "Pipe Bomb", "Ball", "Petrol Can", "Fire Extinguisher", "Parachute" };
			inline bool give = false;
			inline bool in_hand = false;
		}
	}
	namespace misc {
		inline bool watermark = true;
		inline bool untrusted_build = true;
		inline bool PlayerList = false;
		inline bool PedList = false;
		inline bool VehicleList = false;
		inline bool menu = true;
		inline bool lock_menu_layout = false;

		inline int menu_size_x = 550 * 1.2;
		inline int menu_size_y = 430 * 1.2;
	}

	namespace self {
		inline bool enable = false;
		inline bool enabled = false;
		inline bool autoarm = false;
		inline bool testcar = false;
		inline bool tptowaypoint = false;
		inline bool randomoutfit = false;
		inline bool godmode = false;
		inline bool PedList = false;
		inline bool fovcganger = false;
		inline bool NoRagDoll = false;
		inline bool Invisible = false;
		inline bool Infinite_Armor = false;
		inline bool nocol = false;
		inline bool pysgun = true;
		inline bool no_hs = false;
		inline bool no_ragdoll = false;
		inline bool teleport_to_waypoint = false;
		inline bool SuperJump = false;
		inline bool Set_Ragdoll = false;


		inline bool never_wanted = false;
		inline bool desync = false;
		inline int FovValue = 0;
		inline bool give_health = false;
		inline bool give_armor = false;
		inline int give_health_amnt = 100;
		inline int give_armor_amnt = 100;
		inline bool fastrun = false;
		inline bool revive = false;
		inline bool semigodmode = false;
		inline bool fiveguardbypass = false;
		inline bool set_armor = false;
		inline bool set_health = false;
		inline bool set_revive = false;
		inline bool noclip = false;
		inline int health = 0;
		inline int armor = 0;
		inline float RunSpeedToSet = 1;
		inline int hotkey_noclip = 0;
		inline int hotkey_vehclip = 0;
		inline int hotkey_blockmenu = 0;
		inline int hotkey_autofarm = 0;
		inline int HotkeyArmor = 0;
		inline int HotkeyHealth = 0;

		inline int hotkey_forward = 0x57;
		inline int hotkey_left = 0x41;
		inline int hotkey_right = 0x44;
		inline int hotkey_backward = 0x53;
		inline bool noclipspeed = false;
		inline float noclipspeedlol = 1.00000f;



		inline int hotkey_lootbagesp = 0;
		inline int hotkey_vehicleesp = 0;
		inline int hotkey_explosiveammo = 0;
		inline int hotkey_damage = 0;
		inline int hotkey_recoil = 0;
		inline int hotkey_vehicle = 0;
		inline int hotkey_revive = 0;

	}


	namespace tempcolor
	{
		inline float menu_color[4] = { 140.f, 131.f, 214.f, 255.f };
		inline float box_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float box[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float health_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float particle[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float filled[4] = { 255.f, 255.f, 255.f, 125.f };
		inline float corner[4] = { 33.f, 140.f, 176.f, 255.f };
		inline float skeleton[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float weapon[4] = { 33.f, 140.f, 176.f, 255.f };
		inline float head[4] = { 33.f, 140.f, 176.f, 255.f };
		inline float name[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float snapline[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float health_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float distance[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float preview_target[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float player_name_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float player_name_color[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float fov_color[4] = { 255.f, 255.f, 255.f, 255.f };
		//_//_//_/_/_/_/_/_/_/
		inline float bag_espg[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float vehicle_esp[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float bagmarker[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float bagdistanccolor[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float vehiclebrokencolor[4] = { 255.f, 0.f, 0.f, 255.f };
		inline float vehicleesphealth[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float vehiclemarker[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float vehicledistance[4] = { 255.f, 255.f, 255.f, 255.f };
		inline float box_color_visible[4] = { 255.f, 255.f, 255.f, 255.f };
	}



}

