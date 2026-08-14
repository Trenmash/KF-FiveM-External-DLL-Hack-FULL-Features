#pragma once

#include "../content/classes.hpp"
#include "../settings/settings.hpp"

#include "../content/tahoma.h" // <-- Required font!
static float noclipspeed = 1.00001f;
static bool speed = false;
static bool nogravity = true;




namespace self {

    void options(void) {

        if (settings::self::enabled) {

            hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
            if (!World)
                return;

            hk_Ped* LocalPlayer = World->LocalPlayer();
            if (!LocalPlayer)
                return;

            hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
            if (!LocalPlayer)
                return;

            if (settings::self::godmode) {

                *(bool*)(LocalPlayer + 0x189) = true;
            }
            else {
                *(bool*)(LocalPlayer + 0x189) = false;
            }

            if (settings::self::semigodmode) {

                if (LocalPlayer->GetHealth() < 200)
                    LocalPlayer->SetMaxHealth();
            }
            if (settings::self::Infinite_Armor)
            {
                LocalPlayer->SetArmor(100);

            }
            if (settings::self::NoRagDoll)
            {
                LocalPlayer->Set_Ragdoll(true);
            }
            if (settings::self::nocol)
            {
                DWORD64 addr1 = (DWORD64)World->LocalPlayer()->ObjectNavigation();
                if (addr1) {
                    DWORD64 addr2 = *(DWORD64*)(addr1 + 0x10);
                    if (addr2) {
                        DWORD64 addr3 = *(DWORD64*)(addr2 + 0x20);
                        if (addr3) {
                            DWORD64 addr4 = *(DWORD64*)(addr3 + 0x70);
                            if (addr4) {
                                DWORD64 addr5 = *(DWORD64*)(addr4 + 0x0);
                                if (addr5) {
                                    *(float*)(addr5 + 0x2C) = -1.0f;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                DWORD64 addr1 = (DWORD64)World->LocalPlayer()->ObjectNavigation();
                if (addr1) {
                    DWORD64 addr2 = *(DWORD64*)(addr1 + 0x10);
                    if (addr2) {
                        DWORD64 addr3 = *(DWORD64*)(addr2 + 0x20);
                        if (addr3) {
                            DWORD64 addr4 = *(DWORD64*)(addr3 + 0x70);
                            if (addr4) {
                                DWORD64 addr5 = *(DWORD64*)(addr4 + 0x0);
                                if (addr5) {
                                    *(float*)(addr5 + 0x2C) = 0.25f;
                                }
                            }
                        }
                    }
                }
            }




            if (SAFE_CALL(GetAsyncKeyState)(settings::self::HotkeyArmor) & 0x8000) {

                LocalPlayer->SetArmor(100 * 2);
                settings::self::set_armor = false;
            }

            if (SAFE_CALL(GetAsyncKeyState)(settings::self::HotkeyHealth) & 0x8000) {

                LocalPlayer->SetHealth(100 * 2);
                settings::self::set_health = false;
            }

            if (settings::self::set_health) {

                LocalPlayer->SetHealth(100 * 2);
                settings::self::set_health = false;
            }
            if (settings::self::set_revive) {

                if (LocalPlayer->GetHealth() < 200)
                    LocalPlayer->SetMaxHealth();
                settings::self::set_revive = false;
            }
            if (settings::self::set_armor) {

                LocalPlayer->SetArmor(100 * 2);
                settings::self::set_armor = false;
            }
            if (settings::self::SuperJump)
            {
                LocalPlayer->PlayerInfo()->SetSuperJump(true);
            }
            if (settings::self::fovcganger)
            {
                DWORD64 addr = FiveM::GetCamera();
                uintptr_t CameraData = *(uintptr_t*)(addr + 0x10);
                *(float*)(CameraData + 0x30) = settings::self::FovValue;
                settings::self::fovcganger = false;
            }
            if (settings::self::fastrun) {
                if (FiveM::FiveM_b2944) {
                    *(float*)(*(uint64_t*)(LocalPlayer + FiveM::PlayerInfo) + 0x0D40) = settings::self::RunSpeedToSet;
                }
                else {
                    *(float*)(*(uint64_t*)(LocalPlayer + FiveM::PlayerInfo) + 0x0CF0) = settings::self::RunSpeedToSet;
                }
            }
            if (settings::self::Invisible)
            {
                LocalPlayer->SetInvisible(0X1);


            }
            else {

                LocalPlayer->SetInvisible(0X37);

            }



        }
    }

    void noclip(void) {

        if (settings::self::noclip) {

            hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
            if (!World)
                return;

            hk_Ped* LocalPlayer = World->LocalPlayer();
            if (!LocalPlayer)
                return;

            hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
            if (!Nav)
                return;

            Vector3 ActualPos = LocalPlayer->GetCoordinate();

            if (LocalPlayer->IsInAVehicule() == true) {
                return;
            }
            if (LocalPlayer->GetHealth() < 100)
                return;

            if (SAFE_CALL(GetAsyncKeyState)(VK_LSHIFT))
                speed = true;
            else
                speed = false;

            if (speed)
            {
                noclipspeed = 1.0f;
            }
            else
            {
                noclipspeed = 0.1f;

            }


            Nav->SetRotation(Vector4(0, 0, 0, 0));




            if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_forward) & 0x8000)
            {
                LocalPlayer->SetVelocity();

                DWORD64 addr = FiveM::GetCamera();
                Vector3 TPSangles = *(Vector3*)(addr + 0x40);
                if (TPSangles == Vector3(0, 0, 0))
                {
                    TPSangles = *(Vector3*)(addr + 0x40);
                }
                Vector3 newpos = ActualPos;
                newpos.x += (TPSangles.x * noclipspeed);
                newpos.y += (TPSangles.y * noclipspeed);
                newpos.z += (TPSangles.z * noclipspeed);
                LocalPlayer->SetCoordinate(newpos);
                Nav->SetCoordinate(newpos);
            }

            if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_backward) & 0x8000)
            {
                LocalPlayer->SetVelocity();

                DWORD64 addr = FiveM::GetCamera();
                Vector3 TPSangles = *(Vector3*)(addr + 0x40);
                if (TPSangles == Vector3(0, 0, 0))
                {
                    TPSangles = *(Vector3*)(addr + 0x40);
                }
                Vector3 newpos = ActualPos;
                newpos.x -= (TPSangles.x * noclipspeed);
                newpos.y -= (TPSangles.y * noclipspeed);
                newpos.z -= (TPSangles.z * noclipspeed);
                LocalPlayer->SetCoordinate(newpos);
                Nav->SetCoordinate(newpos);
            }

            if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_left) & 0x8000)
            {
                LocalPlayer->SetVelocity();

                DWORD64 addr = FiveM::GetCamera();
                Vector3 TPSangles = *(Vector3*)(addr + 0x40);
                if (TPSangles == Vector3(0, 0, 0))
                {
                    TPSangles = *(Vector3*)(addr + 0x40);
                }
                Vector3 newpos = ActualPos;
                newpos.x -= (TPSangles.y * noclipspeed);
                newpos.y += (TPSangles.x * noclipspeed);
                newpos.z += (TPSangles.z * noclipspeed);
                LocalPlayer->SetCoordinate(newpos);
                Nav->SetCoordinate(newpos);
            }

            if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_right) & 0x8000)
            {
                LocalPlayer->SetVelocity();

                DWORD64 addr = FiveM::GetCamera();
                Vector3 TPSangles = *(Vector3*)(addr + 0x40);
                if (TPSangles == Vector3(0, 0, 0))
                {
                    TPSangles = *(Vector3*)(addr + 0x40);
                }
                Vector3 newpos = ActualPos;
                newpos.x += (TPSangles.y * noclipspeed);
                newpos.y -= (TPSangles.x * noclipspeed);
                newpos.z -= (TPSangles.z * noclipspeed);
                LocalPlayer->SetCoordinate(newpos);
                Nav->SetCoordinate(newpos);
            }

            //	ENTITY::SET_ENTITY_COLLISION(local_player, false, false);

        }

    }
    void autofarm(void) {
        if (settings::self::autoarm) {

            if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_autofarm)) {
                hk_World* World = (hk_World*)*(uint64_t*)(FiveM::World);
                if (!World)
                    return;

                hk_Ped* LocalPlayer = World->LocalPlayer();
                if (!LocalPlayer)
                    return;

                hk_ObjectNavigationPed* Nav = LocalPlayer->ObjectNavigation();
                if (!LocalPlayer)
                    return;

                hk_ReplayInterface* ReplayInterface = (hk_ReplayInterface*)*(uint64_t*)(FiveM::ReplayInterface);
                hk_PedInterface* PedInterface = ReplayInterface->PedInterface();
                if (PedInterface) {
                    for (int index = 0; index < PedInterface->PedMaximum(); index++) {
                        hk_Ped* Peds = PedInterface->PedList()->Ped(index);
                        if (!Peds)
                            continue;
                        if (Peds == LocalPlayer)
                            continue;

                        bool IsPed = false;

                        auto ped_type = Peds->GetPedType();
                        if (!ped_type) {
                            continue;
                        }
                        ped_type = ped_type << 11 >> 25;

                        if (ped_type != 2) {
                            IsPed = true;
                        }
                        if (!IsPed)
                            continue;

                        auto mypos = LocalPlayer->GetCoordinate();
                        *(Vector3*)(Peds + 0x90) = Vector3(mypos.x, mypos.y + 1, mypos.z);
                        *(float*)(Peds + 0x280) = 0.1f;
                    }
                }
            }
        }
    }
}

