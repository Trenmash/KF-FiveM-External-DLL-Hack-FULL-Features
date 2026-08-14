#define IMGUI_DEFINE_MATH_OPERATORS
#include "menu.hpp"

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_impl_win32.h"

#include "../utils/utils.hpp"
#include "../hooks/hooks.hpp"

#include "../fivem/features/aimbot.hpp"
#include "../fivem/features/visuals.hpp"
#include "../fivem/features/weapon.hpp"
#include "../fivem/features/self.hpp"

#include "../fivem/settings/settings.hpp"

#include "../fivem/features/lootbag.hpp"
#include "../fivem/features/vehicles.hpp"
#include "../../trebucbd.h"
#include "../../IconsFontAwesome6.h"
#include "..\..\.\Auth.hpp"
#include "..\.\backend.hpp"
#include "..\.\hwid.h"
#include "../../auth.hpp"
#include "fx.hpp"
//
static int selected_index = 1;
static int selectedVeh_index = 1;
using namespace ImGui;
char key_auth[16] = "";


enum heads {
    rage, antiaim, visuals1, settings1, skins, configs, scripts
};

enum sub_heads {
    general, accuracy, exploits, _general, advanced, player1, vehicles,
};

#define ALPHA (ImGuiColorEditFlags_AlphaPreview | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder)
#define NO_ALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoBorder)

bool draw_demo = false;

int selected_cfg = 0;
const char* cfg[]{ "[2287] Video", "[2288] PvP", "[2289] Legit", "[2290] Owner" };

int current_tabs = 1;

char font[200] = "";

bool register_mode = false;
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

namespace image
{
    ID3D11ShaderResourceView* logo = nullptr;

    ID3D11ShaderResourceView* discord = nullptr;

}
DWORD weaponsLlist[] = {
    0x93E220BD, 0xA0973D5E, 0x24B17070, 0x2C3731D9, 0xAB564B93, 0x787F0BB, 0xBA45E8B8, 0x23C9F95C, 0xFDBC8A50, 0x497FACC3, //Throwables
    0x34A67B97, 0xFBAB5776, 0x060EC506, //Miscellaneous
    0xB1CA77B1, 0xA284510B, 0x42BF8A85, 0x7F7497E5, 0x6D544C99, 0x63AB0442, 0x0781FE4A, 0xB62D1F67, //Heavy Weapons
    0x05FC3C11, 0x0C472FE2, 0xA914799, 0xC734385A, 0x6A6C02E0, //Sniper Rifles
    0x9D07F764, 0x7FD62962, 0xDBBD7280, 0x61012683, //Light Machine Guns
    0xBFEFFF6D, 0x394F415C, 0x83BF0278, 0xFAD1F1C9, 0xAF113F99, 0xC0A3098D, 0x969C3D67, 0x7F229F94, 0x84D6FAFD, 0x624FE830, //Assault Rifles
    0x13532244, 0x2BE6766B, 0x78A97CD0, 0xEFE7E2DF, 0x0A3D4D34, 0xDB1AA450, 0xBD248B55, 0x476BF155, //Submachine Guns
    0x1B06D571, 0xBFE256D4, 0x5EF9FEC4, 0x22D8FE39, 0x3656C8C1, 0x99AEEB3B, 0xBFD21232, 0x88374054, 0xD205520E, 0x83839C4, 0x47757124, 0xDC4DB296, 0xC1B3C3D1, 0xCB96392F, 0x97EA20B8, 0xAF3696A1, //Pistols
    0x92A27487, 0x958A4A8F, 0xF9E6AA4B, 0x84BD7BFD, 0x8BB05FD7, 0x440E4788, 0x4E875F73, 0xF9DCBF2D, 0xD8DF3C3C, 0x99B507EA, 0xDD5DF8D9, 0xDFE37640, 0x678B81B1, 0x19044EE0, 0xCD274149, 0x94117305, 0x3813FC08, //Mele
    0x1D073A89, 0x555AF99A, 0x7846A318, 0xE284C527, 0x9D61E50F, 0xA89CB99E, 0x3AABBBAA, 0xEF951FBB, 0x12E82D3D
};

const char* weaponType[]{ "Throwable", "Misc", "Heavy", "Sniper", "Pistol", "Melee", "Light", "SMG", "Rifle", "Shotgun", "Unknown" };


bool myCheckboxValue = false; // Hier wird der Status der Checkbox gespeichert
//namespace fonts

float Height_Y = 0;
float Width_X = 0;
bool enable_esp = 0;
int subtab = 0;
int tab = 0;



static bool checkboxValue = false;


ImFont* fonti;
//save caca
FILE* p_stream;
ImFont* big;
bool loaded = true;
// security
int auth = 2;
int checking = 0;
bool smothing = false;
char Licence[50] = "";
bool logged = false;
bool draw_menu = false;
bool close = true;
int tabs = false;
int sub_selected = 0;
bool load = true;
bool inject = false;

namespace memory
{

    fx::NetLibrary** g_netLibrary;

    std::vector<fx::ResourceImpl*>* g_allResources;

    bool InitMemory()
    {
        const uint64_t resourceModule = (uint64_t)GetModuleHandleA("citizen-resources-core.dll");

        if (!resourceModule)
        {
            MessageBoxA(0, "Couldn't get base address of citizen resources core", 0, 0);

            return false;
        }

        const uint64_t netFiveModule = (uint64_t)GetModuleHandleA("gta-net-five.dll");

        if (!netFiveModule)
        {
            MessageBoxA(0, "Couldn't get base address of gta net five", 0, 0);

            return false;
        }

        g_allResources = (std::vector<fx::ResourceImpl*>*)(resourceModule + 0xAE6C0);

        if (!g_allResources)
        {
            MessageBoxA(0, "no resource", 0, 0);

            return false;
        }

        g_netLibrary = (fx::NetLibrary**)(netFiveModule + 0x1F41D8);

        if (!g_netLibrary)
        {
            MessageBoxA(0, "no net", 0, 0);

            return false;
        }

        return true;
    }

    void ForAllResources(const std::function<void(fx::ResourceImpl*)>& cb)
    {
        for (fx::ResourceImpl* resource : *memory::g_allResources)
        {
            cb(resource);
        }
    }
}
static char searchString[20];
static int selectedResourceIndex = 0;
ImFont* AddCustomDefaultFont(const ImFontConfig* font_cfg_template) {
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImFontConfig font_cfg = font_cfg_template ? *font_cfg_template : ImFontConfig();
    if (!font_cfg_template) {
        font_cfg.OversampleH = font_cfg.OversampleV = 1;
        font_cfg.PixelSnapH = true;
    }
    if (font_cfg.SizePixels <= 0.0f)
        font_cfg.SizePixels = 13.0f * 1.0f;
    if (font_cfg.Name[0] == '\0')
        ImFormatString(font_cfg.Name, IM_ARRAYSIZE(font_cfg.Name), "ProggyClean.ttf, %dpx", (int)font_cfg.SizePixels);
    font_cfg.EllipsisChar = (ImWchar)0x0085;
    font_cfg.GlyphOffset.y = 1.0f * IM_FLOOR(font_cfg.SizePixels / 13.0f); // Add +1 offset per 13 units

    // const char* ttf_compressed_base85 = GetDefaultCompressedFontDataTTFBase85();
    const ImWchar* glyph_ranges = font_cfg.GlyphRanges != NULL ? font_cfg.GlyphRanges : io.Fonts->GetGlyphRangesDefault();
    // ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(trebucbd_compressed_data, trebucbd_compressed_size, font_cfg.SizePixels, &font_cfg, glyph_ranges);

    ImFont* font = io.Fonts->AddFontFromMemoryCompressedTTF(trebucbd_compressed_data, sizeof(trebucbd_compressed_size), 14.f, nullptr, glyph_ranges);
    return font;
}

#include "../dependencies/imgui/custom.hpp"
#include "../dependencies/imgui/bytes.hpp"
#include "../../Encryption.h"
#include "../../xor.h"
#include "../../user_interface.h"
#include "../../skStr.h"
#include "../../IconsFontAwesome6Brands.h"
#include "../../xor.hpp"
#include "../../Fonts.hpp"
#include "../../imguinotify.hpp"
#include "../../bytes.hpp"
#include "../fivem/settings/Menu.hpp"
#include "../dependencies/imgui/gui.hpp"
namespace Menu {

    void styledark()
    {
        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowRounding = 6;
        style.ChildRounding = 7;
        style.ScrollbarSize = 2.0f;
        style.FrameRounding = 1.5f;
        style.Colors[ImGuiCol_Text] = ImColor(230, 230, 230);         // Text color
        style.Colors[ImGuiCol_TextDisabled] = ImColor(0.40f, 0.40f, 0.40f, 1.00f); // Disabled text color
        style.Colors[ImGuiCol_WindowBg] = ImColor(18, 18, 18);     // Window background color
        style.Colors[ImGuiCol_ChildBg] = ImColor(20, 19, 19);      // Blue child window background color with reduced alpha
        style.Colors[ImGuiCol_PopupBg] = ImColor(28, 27, 27);        // Popup background color
        style.Colors[ImGuiCol_Border] = ImColor(26, 26, 26);
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        style.Colors[ImGuiCol_FrameBg] = ImColor(102, 102, 102);      // Frame background color
        style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.40f, 0.75f, 0.60f);// Blue frame background color when hovered
        style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.35f, 0.35f, 0.35f, 0.70f); // Frame background color when active
        style.Colors[ImGuiCol_TitleBg] = ImColor(13, 13, 13);        // Title background color
        style.Colors[ImGuiCol_TitleBgActive] = ImColor(13, 13, 13);  // Title background color when active
        style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(13, 13, 13);  // Title background color when collapsed
        style.Colors[ImGuiCol_MenuBarBg] = ImColor(26, 26, 26);    // Menu bar background color
        style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(46, 46, 46);
        style.Colors[ImGuiCol_CheckMark] = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);    // Checkbox checkmark color
        style.Colors[ImGuiCol_Button] = ImColor(10, 104, 255, 255);        // Button color
        style.Colors[ImGuiCol_ButtonHovered] = ImColor(10, 82, 199);    // Blue button color when hovered
        style.Colors[ImGuiCol_ButtonActive] = ImColor(10, 82, 199);    // Button color when active
        style.Colors[ImGuiCol_Header] = ImVec4(0.30f, 0.30f, 0.30f, 0.70f);        // Header color
        style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.80f); // Header color when hovered
        style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.50f, 0.50f, 0.50f, 0.80f);  // Header color when active
        style.Colors[ImGuiCol_Separator] = ImColor(28, 27, 27);     // Separator
        style.Colors[ImGuiCol_SeparatorHovered] = ImColor(46, 46, 46); // Separator color when hovered
        style.Colors[ImGuiCol_SeparatorActive] = ImColor(46, 46, 46);
        style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);     // Resize grip color
        style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.60f, 0.60f, 0.60f, 0.70f); // Resize grip color when hovered
        style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);// Resize grip color when active
        style.Colors[ImGuiCol_Tab] = ImVec4(0.15f, 0.15f, 0.15f, 0.86f);           // Tab color
        style.Colors[ImGuiCol_TabHovered] = ImVec4(0.00f, 0.40f, 0.75f, 0.80f);    // Blue tab color when hovered
        style.Colors[ImGuiCol_TabActive] = ImVec4(0.23f, 0.23f, 0.23f, 0.85f);     // Tab color when active
        style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.08f, 0.08f, 0.08f, 0.97f);   // Tab color when unfocused
        style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.13f, 0.13f, 0.13f, 0.97f); // Tab color when unfocused and active
        style.Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);     // Plot lines color
        style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.00f, 0.40f, 0.75f, 1.00f); // Blue plot lines color when hovered
        style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f); // Plot histogram color
        style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.00f, 0.40f, 0.75f, 1.00f); // Blue plot histogram color when hovered
        style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f); // Selected text background color

        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
        static const ImWchar icons_ranges_brands[] = { ICON_MIN_FAB, ICON_MAX_16_FAB, 0 };
        ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
        ImFont* FontAwesome = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 14.f, &icons_config, icons_ranges);
        ImFont* FontAwesomeBrands = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa_brands_400_compressed_data, fa_brands_400_compressed_size, 14.f, &icons_config, icons_ranges_brands);
    }

    void InitializeContext(HWND hwnd) {
        if (ImGui::GetCurrentContext())
            return;

        ImGui::CreateContext();
        ImGui_ImplWin32_Init(hwnd);


        if (settings::visuals::darkmode) {
            ImGui::StyleColorsDark();
        }
        else {
            ImGui::StyleColorsLight();
        }


        ImGui::CreateContext();
        ImGuiIO* io = &ImGui::GetIO();
        io->ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        io->IniFilename = nullptr;
        io->LogFilename = nullptr;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);
        io->Fonts->AddFontFromMemoryTTF(museo500_binary, sizeof museo500_binary, 15.0f);
        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
        static const ImWchar icons_ranges_brands[] = { ICON_MIN_FAB, ICON_MAX_16_FAB, 0 };
        ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
        ImFont* FontAwesome = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa6_solid_compressed_data, fa6_solid_compressed_size, 15.f, &icons_config, icons_ranges);
        ImFont* FontAwesomeBrands = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(fa_brands_400_compressed_data, fa_brands_400_compressed_size, 15.f, &icons_config, icons_ranges_brands);

        // Our state
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        ImFont* TitleFont = io->Fonts->AddFontFromMemoryCompressedTTF(trebucbd_compressed_data, trebucbd_compressed_size, 30, nullptr, io->Fonts->GetGlyphRangesDefault());
        ImGui::MergeIconsWithLatestFont(16.f, false);

    }
    void styledark1()
    {
        ImGuiStyle* Style = &ImGui::GetStyle();
        ImVec4* Colors = Style->Colors;

        Style->ChildRounding = 3;

        Colors[ImGuiCol_Border] = ImVec4(ImColor(255, 255, 255, 0));
        Colors[ImGuiCol_WindowBg] = ImVec4(ImColor(0, 0, 0, 0));
        Colors[ImGuiCol_ChildBg] = ImVec4(ImColor(20, 20, 20, 175));
        Colors[ImGuiCol_Text] = ImVec4(ImColor(255, 255, 255, 255));
        Colors[ImGuiCol_Separator] = ImVec4(ImColor(45, 45, 45, 135));
        Colors[ImGuiCol_CheckMark] = ImVec4(ImColor(2, 106, 191, 175));
        Colors[ImGuiCol_PopupBg] = ImVec4(ImColor(20, 20, 20, 175));
        Colors[ImGuiCol_Button] = ImVec4(ImColor(26, 26, 26));
        Colors[ImGuiCol_ButtonActive] = ImVec4(ImColor(10, 104, 255, 255));
        Colors[ImGuiCol_ButtonHovered] = ImVec4(ImColor(10, 104, 255, 255));
        //Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
        //Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
        //Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);

        Colors[ImGuiCol_FrameBg] = ImVec4(ImColor(20, 20, 20, 255));
        Colors[ImGuiCol_FrameBgHovered] = ImVec4(ImColor(33, 32, 32, 255));
        Colors[ImGuiCol_FrameBgActive] = ImVec4(ImColor(28, 28, 28, 255));


        Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
        Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
        Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

        Colors[ImGuiCol_Separator] = Colors[ImGuiCol_Border];
        Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
        Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 0.00f);
        Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0);
        Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0);
        Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0);
        Colors[ImGuiCol_Tab] = ImLerp(Colors[ImGuiCol_Header], Colors[ImGuiCol_TitleBgActive], 0.80f);
        Colors[ImGuiCol_TabHovered] = Colors[ImGuiCol_HeaderHovered];
        Colors[ImGuiCol_TabActive] = ImLerp(Colors[ImGuiCol_HeaderActive], Colors[ImGuiCol_TitleBgActive], 0.60f);
        Colors[ImGuiCol_TabUnfocused] = ImLerp(Colors[ImGuiCol_Tab], Colors[ImGuiCol_TitleBg], 0.80f);
        Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(Colors[ImGuiCol_TabActive], Colors[ImGuiCol_TitleBg], 0.40f);
        Colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
        Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
        Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);   // Prefer using Alpha=1.0 here
        Colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);   // Prefer using Alpha=1.0 here
        Colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
        Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
        Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
        Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
        Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
    }
    char PrintConsoleText[256];
    void consoleprint(const std::string& channel, const std::string& message) {
        using consoleprint1 = void(__fastcall*)(const std::string&, const std::string&);

        // Get the module handle for conhost-v2.dll
        HMODULE hModule = GetModuleHandleA("conhost-v2.dll");
        if (hModule == nullptr) {
            MessageBoxA(NULL, "Failed to find the conhost DLL", "Error", MB_OK);
            return;
        }

        // Get the address of the function
        FARPROC procAddress = GetProcAddress(hModule, "?Print@ConHost@@YAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0@Z");
        if (procAddress == nullptr) {
            MessageBoxA(NULL, "Failed to find the function offset", "Error", MB_OK);
            return;
        }

        // Cast the address to the function pointer type
        consoleprint1 address = reinterpret_cast<consoleprint1>(procAddress);

        // Ensure the function pointer is valid
        if (!address) {
            MessageBoxA(NULL, "Function pointer is null", "Error", MB_OK);
            return;
        }

        // Prepare the fixed channel and message
        const std::string fixedChannel = "script:" + channel;
        const std::string fixedMessage = message + "\n";

        // Call the function
        address(fixedChannel, fixedMessage);
    }
    #define MAX_RGB 255.0
    ImVec4 ToVec4(float r, float g, float b, float a)
    {
        return ImVec4(r / MAX_RGB, g / MAX_RGB, b / MAX_RGB, a / MAX_RGB);
    }

    static ImVec4 active = ToVec4(10, 104, 255, 255);
    static ImVec4 inactive = ToVec4(125, 125, 125, 85);

    void CenterTextEx(const char* text, float width, int lineId, bool separator)
    {
        if (text == nullptr)
            return;

        ImGui::Spacing();
        ImGui::SameLine((width / 2) - (ImGui::CalcTextSize(text).x / 2));
        ImGui::Text(text);
        ImGui::Spacing();

    }
    void Render() {

        if (loaded == false) {

        }

        if (loaded) {
            draw_menu = true;
            if (auth == 2) {

                bool notify = false;
                   if (!notify) {
                       notify = false;
                   }
                if (draw_menu) {
                    /* setup_circles( );
                     draw_circles_and_lines(ImColor(255,255,255));*/



                    aimbot::hook();
                    visuals::player_esp();
                    hook::vehicle();
                    visuals::lootbag();
                    weapon::hook();
                    self::options();
                    self::noclip();
                    self::autofarm();

                    if (settings::visuals::draw_fov) {

                        if (settings::visuals::filled_fov) {
                            ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2), settings::aimbot::aimbot_fov * 10, ImColor(0, 0, 0, 90), 100.0f);
                            ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2), settings::aimbot::aimbot_fov * 10, settings::visuals::fov_color, 100.0f);
                        }
                        else {

                            ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2), settings::aimbot::aimbot_fov * 10, settings::visuals::fov_color, 100.0f);
                        }
                    }
                    if (settings::misc::watermark) {

                        ImGui::SetNextWindowPos(ImVec2(20, 1040));

                        if (ImGui::Begin(skCrypt("My Dick"), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove))
                        {
                            ImGui::Text(skCrypt("KX Cheats [%s] | b2699      "));
                        }
                        ImGui::End();
                    }
                    if (settings::visuals::crosshair) {
                        if (settings::visuals::crossahir_style == 0) {

                            auto draw = ImGui::GetBackgroundDrawList();
                            draw->AddCircle(ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2), 2, settings::visuals::crosshair_color, 0, 3.0f);
                            draw->AddCircle(ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2), 2, settings::visuals::crosshair_color, 0, 3.0f);
                        }

                        if (settings::visuals::crossahir_style == 1) {

                            auto draw = ImGui::GetBackgroundDrawList();
                            draw->AddCircle(ImVec2(FiveM::WindowSize.x / 2, FiveM::WindowSize.y / 2), 3, settings::visuals::crosshair_color, 100, 0.0f);
                        }

                        if (settings::visuals::crossahir_style == 2) {

                            auto draw = ImGui::GetBackgroundDrawList();

                            auto drx = FiveM::WindowSize.x / 2;
                            auto dry = FiveM::WindowSize.y / 2;

                            draw->AddLine({ drx - 10, dry }, { drx + 10, dry }, settings::visuals::crosshair_color);
                            draw->AddLine({ drx, dry - 10 }, { drx, dry + 10 }, settings::visuals::crosshair_color);
                        }
                    }
                    if (SAFE_CALL(GetAsyncKeyState)(settings::self::hotkey_noclip) & 1) {

                        settings::self::noclip = !settings::self::noclip;
                    }


                }
            }
        }
        else {

            exit(3);
        }





        ImGui::GetIO().MouseDrawCursor = bShowMenu;

        if (!bShowMenu)
            return;

        if (loaded) {
            {
            }
            if (loaded) {

                if (auth == 3) {

                    ImGuiIO& io = ImGui::GetIO();

                    auto windows_x = io.DisplaySize.x / 2;
                    auto windows_y = io.DisplaySize.y / 2;

                    auto myWindowX = windows_x - 250 / 2;
                    auto myWindowY = windows_y - 250 / 2;

                    ImGui::SetNextWindowPos(ImVec2(myWindowX, myWindowY));
                    ImGui::SetNextWindowSize(ImVec2(250, 250));

                    if (ImGui::Begin("##Offline", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {

                        ImGui::Text(" Sync is currently offline.");

                        if (ImGui::Button(E("Exit"), ImVec2(165, 27))) {

                            exit(0);
                        }
                    }
                    ImGui::End();
                }

                if (auth == 4) {

                    ImGuiIO& io = ImGui::GetIO();

                    auto windows_x = io.DisplaySize.x / 2;
                    auto windows_y = io.DisplaySize.y / 2;

                    auto myWindowX = windows_x - 250 / 2;
                    auto myWindowY = windows_y - 250 / 2;

                    ImGui::SetNextWindowPos(ImVec2(myWindowX, myWindowY));
                    ImGui::SetNextWindowSize(ImVec2(250, 250));

                    if (ImGui::Begin("##BlackLISTED", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {

                        ImGui::Text("You are blacklisted from Sync");
                        if (ImGui::Button(E("Exit"), ImVec2(165, 27))) {

                            abort();
                            exit(0);
                        }

                    }
                    ImGui::End();
                }
            }
            ImGui::EndChild();
                styledark();
                static ImVec2 WindowPos;
                ImGui::SetNextWindowSize(ImVec2(650, 450));
                ImGui::Begin(skCrypt("KXONETOP#1"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);
                {
                    const auto& pWindowDrawList = ImGui::GetWindowDrawList();
                    ImGui::PushFont(big);
                    ImGui::SameLine();
                    ImDrawList* draw = ImGui::GetWindowDrawList();
                    const auto& p = ImGui::GetWindowPos();
                    ImVec2 CursorPos = ImGui::GetCursorScreenPos();
                    WindowPos = CursorPos;
                    ImGui::SetCursorPosX(80);
                    ImGui::SetCursorPosY(12);
                    ImGui::BeginChild("##TopBar", ImVec2(ImGui::GetContentRegionAvail().x, 60), true, ImGuiWindowFlags_NoScrollbar);
                    {

                        if (Menu::Tab == 0)
                        {
                            ImGui::SetCursorPos(ImVec2(10, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.5f);
                            if (custom_interface::subtab(" Combat ", 0 == sub_selected)) {
                                sub_selected = 0;
                            }
                            ImGui::SetCursorPos(ImVec2(45, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 45.5f);
                            if (custom_interface::subtab(" Weapon ", 1 == sub_selected)) {
                                sub_selected = 1;
                            }
                        }
                        if (Menu::Tab == 1)
                        {
                            ImGui::SetCursorPos(ImVec2(10, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.5f);
                            if (custom_interface::subtab(" Visuals ", 2 == sub_selected)) {
                                sub_selected = 2;
                            }
                            ImGui::SetCursorPos(ImVec2(45, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 45.5f);
                            if (custom_interface::subtab(" Vehicle ", 3 == sub_selected)) {
                                sub_selected = 3;
                            }
                        }
                        if (Menu::Tab == 2)
                        {
                            ImGui::SetCursorPos(ImVec2(10, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.5f);
                            if (custom_interface::subtab(" Self ", 4 == sub_selected)) {
                                sub_selected = 4;
                            }
                            ImGui::SetCursorPos(ImVec2(45, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 45.5f);
                            if (custom_interface::subtab(" Object ", 10 == sub_selected)) {
                                sub_selected = 10;
                            }
                        }
                        if (Menu::Tab == 3)
                        {
                            ImGui::SetCursorPos(ImVec2(10, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.5f);
                            if (custom_interface::subtab(" Options ", 6 == sub_selected)) {
                                sub_selected = 6;
                            }
                        }
                        if (Menu::Tab == 4)
                        {
                            ImGui::SetCursorPos(ImVec2(10, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.5f);
                            if (custom_interface::subtab(" Player ", 7 == sub_selected)) {
                                sub_selected = 7;
                            }
                            ImGui::SetCursorPos(ImVec2(45, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 45.5f);
                            if (custom_interface::subtab(" Vehicle ", 8 == sub_selected)) {
                                sub_selected = 8;
                            }
                        }
                        if (Menu::Tab == 5)
                        {
                            ImGui::SetCursorPos(ImVec2(10, 20));
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.5f);
                            if (custom_interface::subtab(" Configs ", 9 == sub_selected)) {
                                sub_selected = 9;
                            }
                        }

                    }
                    ImGui::EndChild();


                    ImGui::PushFont(big);
                    ImGui::SameLine();
                    ImGui::SetCursorPos(ImVec2(5, 12));
                    ImGui::BeginChild(E("##LeftSide"), ImVec2(70, ImGui::GetContentRegionAvail().y), true, ImGuiWindowFlags_NoScrollbar);
                    {
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 1);

                        ImGui::NewLine();
                        ImGui::NewLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 0 ? active : inactive);
                        CenterTextEx(ICON_FA_CROSSHAIRS, 75, 0, 0);
                        if (ImGui::IsItemClicked()) Menu::Tab = 0;

                        ImGui::NewLine();
                        ImGui::NewLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 1 ? active : inactive);
                        CenterTextEx(ICON_FA_EYE, 75, 0, 0);
                        if (ImGui::IsItemClicked()) Menu::Tab = 1;

                        ImGui::NewLine();
                        ImGui::NewLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 2 ? active : inactive);
                        CenterTextEx(ICON_FA_USER, 75, 0, 0);
                        if (ImGui::IsItemClicked()) Menu::Tab = 2;

                        ImGui::NewLine();
                        ImGui::NewLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 3 ? active : inactive);
                        CenterTextEx(ICON_FA_CAR, 75, 0, 0);
                        if (ImGui::IsItemClicked()) Menu::Tab = 3;

                        ImGui::NewLine();
                        ImGui::NewLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 4 ? active : inactive);
                        CenterTextEx(ICON_FA_GLOBE, 75, 0, 0);
                        if (ImGui::IsItemClicked()) Menu::Tab = 4;

                        ImGui::NewLine();
                        ImGui::NewLine();
                        ImGui::PushStyleColor(ImGuiCol_Text, Menu::Tab == 5 ? active : inactive);
                        CenterTextEx(ICON_FA_SAVE, 75, 0, 0);
                        if (ImGui::IsItemClicked()) Menu::Tab = 5;

                        ImGui::PopStyleColor(6);


                    }
                    ImGui::EndChild();
                    if (sub_selected == 6)
                    {
                        ImGui::SetCursorPosY(200);
                        ImGui::SetCursorPosX(290);
                        ImGui::Text("Soon back again..!");


                    }
                    if (sub_selected == 7)
                    {
                        ImGui::SetCursorPosY(200);
                        ImGui::SetCursorPosX(290);
                        ImGui::Text("Soon back again..!");


                    }
                    if (sub_selected == 8)
                    {
                        ImGui::SetCursorPosY(200);
                        ImGui::SetCursorPosX(290);
                        ImGui::Text("Soon back again..!");


                    }
                    if (sub_selected == 10)
                    {

                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(100);
                        ImGui::BeginChild("Preview", ImVec2(265, 160), TRUE);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 7.5f);
                        ImGui::Text("Object Settings");
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Auto Farm"), &settings::self::autoarm);
                        ImGui::SameLine();
                        ImGui::TextColored(ImColor(232, 168, 30), "(!)"); // Symbol in Rot neben der Checkbox

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Text("May You Will Get Banned From Some Anticheats [USE IT AT OWN RISK].");
                            ImGui::EndTooltip();
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Hotkey(E("Hotkey :   "), &settings::self::hotkey_autofarm, ImVec2(90, 20));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button("Au-to Farm Keys", ImVec2(238, 30)))
                        {

                        }
                        ImGui::EndChild();
                    }
                    if (sub_selected == 0)
                    {
                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(100);
                        ImGui::BeginChild("Self", ImVec2(255, 320), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Aim assis"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Enable"), &settings::aimbot::enabled);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Hotkey(E("key"), &settings::aimbot::hotkey, ImVec2(90, 20));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Maximun FOV"), &settings::visuals::draw_fov);
                        if (settings::visuals::draw_fov) {

                            ImGui::SameLine();
                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 7.5f);
                            ImGui::ColorEdit4((E("##colorfov")), settings::tempcolor::fov_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                            settings::visuals::fov_color.Value.x = settings::tempcolor::fov_color[0];
                            settings::visuals::fov_color.Value.y = settings::tempcolor::fov_color[1];
                            settings::visuals::fov_color.Value.z = settings::tempcolor::fov_color[2];
                            settings::visuals::fov_color.Value.w = settings::tempcolor::fov_color[3];

                            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                            ImGui::Checkbox(E("Draw Filled FOV"), &settings::visuals::filled_fov);
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Target Peds"), &settings::aimbot::ignore_peds);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Target Dead"), &settings::visuals::aim_dead);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Combo(E("Aim Bone"), &settings::aimbot::aimbot_bone, settings::aimbot::aimbot_bones_list, IM_ARRAYSIZE(settings::aimbot::aimbot_bones_list));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox("Enable Weapon Options", &settings::weapon::enabled);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("No Recoil"), &settings::weapon::no_recoil);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("No Spread"), &settings::weapon::no_spread);
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::Checkbox(E("Unlimited Range"), &settings::weapon::infinite_range);
                        ImGui::EndChild();

                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(370);
                        ImGui::BeginChild("Preview", ImVec2(255, 225), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Aim settings"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderInt(E("Smoothing"), &settings::aimbot::aimbot_smooth, 0, 100);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderInt(E("Maximun Distance"), &settings::aimbot::aimbot_distance, 0, 1000);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderInt("Maximun FOV", &settings::aimbot::aimbot_fov, 0, 180);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderFloat(E("Recoil"), &settings::weapon::recoil_value, 0.0, 5.0);
                        ImGui::EndChild();



                    }
                    if (sub_selected == 1)
                    {
                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(100);
                        ImGui::BeginChild("Self", ImVec2(255, 225), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Weapons"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Enable"), &settings::weapon::enabled);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Damage Boost"), &settings::weapon::damage_boost);
                        ImGui::SameLine();
                        ImGui::TextColored(ImColor(232, 168, 30), "(!)"); // Symbol in Rot neben der Checkbox

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Text("May You Will Get Banned From Some Anticheats [USE IT AT OWN RISK].");
                            ImGui::EndTooltip();
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Infinite Ammo"), &settings::weapon::infite_ammo);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Explosive Ammo"), &settings::weapon::explosiveammo);
                        ImGui::SameLine();
                        ImGui::TextColored(ImColor(232, 168, 30), "(!)"); // Symbol in Rot neben der Checkbox

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Text("May You Will Get Banned From Some Anticheats [USE IT AT OWN RISK].");
                            ImGui::EndTooltip();
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Hotkey(E("Key : "), &settings::self::hotkey_explosiveammo, ImVec2(90, 20));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button("Explosive keys", ImVec2(220, 30)))
                        {

                        }
                        ImGui::EndChild();

                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(370);
                        ImGui::BeginChild("Preview", ImVec2(255, 255), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Weapons settings"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderInt(E("Maximun Distance"), &settings::visuals::render_distance, 0, 1000);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderInt(E("Damage"), &settings::weapon::int_damage, 0, 1000);
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::SliderInt(E("Ammount : "), &settings::weapon::ammo_to_set, 0, 999);
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //if (ImGui::Button("Give Ammo", ImVec2(220, 30)))
                        //{
                        //    settings::weapon::set_ammo = true;
                        //}
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::Checkbox("DoubleTab", &settings::weapon::DoubleTap);
                        //ImGui::SameLine();
                        //ImGui::TextColored(ImColor(232, 168, 30), "(!)"); // Symbol in Rot neben der Checkbox

                        //if (ImGui::IsItemHovered())
                        //{
                        //    ImGui::BeginTooltip();
                        //    ImGui::Text("May You Will Get Banned From Some Anticheats [USE IT AT OWN RISK].");
                        //    ImGui::EndTooltip();
                        //}
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::SliderInt("Bullet To Shoot :", &settings::weapon::BulletToShot, 1, 50, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                        ImGui::EndChild();



                    }
                    if (sub_selected == 2)
                    {
                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(100);
                        ImGui::BeginChild("Self11asd", ImVec2(255, 355), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Visuals"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox("Enable", &settings::visuals::enabled);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Box"), &settings::visuals::box_esp);
                        if (settings::visuals::box_esp) {
                            ImGui::SameLine();

                            ImGui::ColorEdit4(E(("##ColosqsqrBo44")), settings::tempcolor::box_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                            settings::visuals::box_color_visible.Value.x = settings::tempcolor::box_color_visible[0];
                            settings::visuals::box_color_visible.Value.y = settings::tempcolor::box_color_visible[1];
                            settings::visuals::box_color_visible.Value.z = settings::tempcolor::box_color_visible[2];
                            settings::visuals::box_color_visible.Value.w = settings::tempcolor::box_color_visible[3];
                        }
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::Combo(E("Box Type"), &settings::visuals::esp_type, settings::visuals::esp_type_text, IM_ARRAYSIZE(settings::visuals::esp_type_text));
                        //if (settings::visuals::box_esp) {
                        //    ImGui::SameLine();

                        //    ImGui::ColorEdit4(E(("##ColosqsqrBo44")), settings::tempcolor::box_color_visible, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                        //    settings::visuals::box_color_visible.Value.x = settings::tempcolor::box_color_visible[0];
                        //    settings::visuals::box_color_visible.Value.y = settings::tempcolor::box_color_visible[1];
                        //    settings::visuals::box_color_visible.Value.z = settings::tempcolor::box_color_visible[2];
                        //    settings::visuals::box_color_visible.Value.w = settings::tempcolor::box_color_visible[3];
                        //}
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::SliderInt(E("Box Rounding"), &settings::visuals::box_rounding, 0, 5);
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::Checkbox(E("Filled Box"), &settings::visuals::filled);
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::Checkbox(E("Outlined Box"), &settings::visuals::outlined);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Health Bar"), &settings::visuals::healthbar);
                        static const char* Healthbar[3] = { "Side", "Bottom", "Top" };
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Combo("Heal Type", &settings::visuals::healthbar_style, Healthbar, 3);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Armor Bar"), &settings::visuals::armorbar);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Head Circle"), &settings::visuals::circle_at_middle);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((E("##headahas")), settings::tempcolor::head, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                        settings::visuals::head_color.Value.x = settings::tempcolor::head[0];
                        settings::visuals::head_color.Value.y = settings::tempcolor::head[1];
                        settings::visuals::head_color.Value.z = settings::tempcolor::head[2];
                        settings::visuals::head_color.Value.w = settings::tempcolor::head[3];
                        ImGui::EndChild();

                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(370);
                        ImGui::BeginChild("Preview", ImVec2(255, 90), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Visuals settings"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderInt(E("Maximun Distance"), &settings::visuals::render_distance, 0, 1000);
                        ImGui::EndChild();

                        ImGui::SetCursorPosY(185);
                        ImGui::SetCursorPosX(370);
                        ImGui::BeginChild("Friend", ImVec2(255, 170), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Friend"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Skeleton"), &settings::visuals::skeleton);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((E("##skssss")), settings::tempcolor::skeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                        settings::visuals::skeleton_color.Value.x = settings::tempcolor::skeleton[0];
                        settings::visuals::skeleton_color.Value.y = settings::tempcolor::skeleton[1];
                        settings::visuals::skeleton_color.Value.z = settings::tempcolor::skeleton[2];
                        settings::visuals::skeleton_color.Value.w = settings::tempcolor::skeleton[3];
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Distance"), &settings::visuals::dont_draw_distance);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((E("##distance")), settings::tempcolor::distance, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                        settings::visuals::distance_color.Value.x = settings::tempcolor::distance[0];
                        settings::visuals::distance_color.Value.y = settings::tempcolor::distance[1];
                        settings::visuals::distance_color.Value.z = settings::tempcolor::distance[2];
                        settings::visuals::distance_color.Value.w = settings::tempcolor::distance[3];
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Weapon Name"), &settings::visuals::weapon_name);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((E("##weapon")), settings::tempcolor::weapon, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                        settings::visuals::weapon_color.Value.x = settings::tempcolor::weapon[0];
                        settings::visuals::weapon_color.Value.y = settings::tempcolor::weapon[1];
                        settings::visuals::weapon_color.Value.z = settings::tempcolor::weapon[2];
                        settings::visuals::weapon_color.Value.w = settings::tempcolor::weapon[3];
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Show Npcs"), &settings::visuals::draw_ped);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Snapline"), &settings::visuals::snapline);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((E("##snapline")), settings::tempcolor::snapline, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoBorder);
                        settings::visuals::snapeline_color.Value.x = settings::tempcolor::snapline[0];
                        settings::visuals::snapeline_color.Value.y = settings::tempcolor::snapline[1];
                        settings::visuals::snapeline_color.Value.z = settings::tempcolor::snapline[2];
                        settings::visuals::snapeline_color.Value.w = settings::tempcolor::snapline[3];
                        ImGui::EndChild();



                    }
                    if (sub_selected == 3)
                    {
                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(100);
                        ImGui::BeginChild("Self11asd", ImVec2(255, 255), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Vehicle"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Enable"), &settings::vehicle::vehicle_esp);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Vehicle Name"), &settings::vehicle::vehicle_name);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((("##52352gfgfddaspl")), settings::tempcolor::vehicle_esp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                        settings::visuals::vehicle_esp_color.Value.x = settings::tempcolor::vehicle_esp[0];
                        settings::visuals::vehicle_esp_color.Value.y = settings::tempcolor::vehicle_esp[1];
                        settings::visuals::vehicle_esp_color.Value.z = settings::tempcolor::vehicle_esp[2];
                        settings::visuals::vehicle_esp_color.Value.w = settings::tempcolor::vehicle_esp[3];
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Vehicle Distance"), &settings::vehicle::vehicle_distance);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((("##52352d231312aspl")), settings::tempcolor::vehicledistance, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                        settings::visuals::vehicle_esp_distance.Value.x = settings::tempcolor::vehicledistance[0];
                        settings::visuals::vehicle_esp_distance.Value.y = settings::tempcolor::vehicledistance[1];
                        settings::visuals::vehicle_esp_distance.Value.z = settings::tempcolor::vehicledistance[2];
                        settings::visuals::vehicle_esp_distance.Value.w = settings::tempcolor::vehicledistance[3];
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Vehicle Health"), &settings::vehicle::vehicle_health);
                        ImGui::SameLine();
                        ImGui::ColorEdit4((("##52352daspl")), settings::tempcolor::vehicleesphealth, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                        settings::visuals::vehicle_esp_health.Value.x = settings::tempcolor::vehicleesphealth[0];
                        settings::visuals::vehicle_esp_health.Value.y = settings::tempcolor::vehicleesphealth[1];
                        settings::visuals::vehicle_esp_health.Value.z = settings::tempcolor::vehicleesphealth[2];
                        settings::visuals::vehicle_esp_health.Value.w = settings::tempcolor::vehicleesphealth[3];
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Vehicle Marker"), &settings::vehicle::vehicle_marker);
                        ImGui::SameLine();
                        ImGui::ColorEdit4("##5235dvaaafva2daspl", settings::tempcolor::vehiclemarker, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
                        settings::visuals::vehicle_esp_marker.Value.x = settings::tempcolor::vehiclemarker[0];
                        settings::visuals::vehicle_esp_marker.Value.y = settings::tempcolor::vehiclemarker[1];
                        settings::visuals::vehicle_esp_marker.Value.z = settings::tempcolor::vehiclemarker[2];
                        settings::visuals::vehicle_esp_marker.Value.w = settings::tempcolor::vehiclemarker[3];
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(("Vehicle Snapline"), &settings::vehicle::vehicle_snapline);
                        ImGui::EndChild();

                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(370);
                        ImGui::BeginChild("Preview", ImVec2(255, 90), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Vehicle settings"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderInt(("Render Distance"), &settings::visuals::vehicle_distance, 0, 1000);
                        ImGui::EndChild();



                    }
                    if (sub_selected == 4)
                    {
                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(100);
                        ImGui::BeginChild("Self11asd", ImVec2(255, 255), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Player"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Enable"), &settings::self::enabled);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox("Godmode", &settings::self::godmode);
                        ImGui::SameLine();
                        ImGui::TextColored(ImColor(232, 168, 30), "(!)"); // Symbol in Rot neben der Checkbox

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Text("May You Will Get Banned From Some Anticheats [USE IT AT OWN RISK].");
                            ImGui::EndTooltip();
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox("Semi GodMode", &settings::self::semigodmode);
                        ImGui::SameLine();
                        ImGui::TextColored(ImColor(232, 168, 30), "(!)"); // Symbol in Rot neben der Checkbox

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Text("May You Will Get Banned From Some Anticheats [USE IT AT OWN RISK].");
                            ImGui::EndTooltip();
                        }
                        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        //ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        //ImGui::Checkbox(E("No Collistion"), &settings::self::nocol);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button("Heal", ImVec2(220, 30)))
                        {
                            settings::self::set_health = true;
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button(("Armor"), ImVec2(220, 30)))
                        {

                            settings::self::set_armor = true;
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Infinite Armor"), &settings::self::Infinite_Armor);
                        ImGui::EndChild();

                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(370);
                        ImGui::BeginChild("Preview", ImVec2(255, 230), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Player settings"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox("Noclip", &settings::self::noclip);
                        ImGui::SameLine();
                        ImGui::TextColored(ImColor(232, 168, 30), "(!)"); // Symbol in Rot neben der Checkbox

                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::Text("May You Will Get Banned From Some Anticheats [USE IT AT OWN RISK].");
                            ImGui::EndTooltip();
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Hotkey(E("Key  "), &settings::self::hotkey_noclip, ImVec2(100, 20));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button("No-clip keys", ImVec2(220, 30)))
                        {

                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox("Fast Run", &settings::self::fastrun);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::SliderFloat((E("Run Speed")), &settings::self::RunSpeedToSet, 1.0, 5.0, nullptr, ImGuiSliderFlags_AlwaysClamp || ImGuiSliderFlags_NoInput);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Invisible "), &settings::self::Invisible);
                        ImGui::EndChild();



                    }
                    if (sub_selected == 9)
                    {
                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(100);
                        ImGui::BeginChild("Self11asd", ImVec2(255, 255), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Misc"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Watermark"), &settings::misc::watermark);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Checkbox(E("Crosshair"), &settings::visuals::crosshair);
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Combo(E("Crosshair Type"), &settings::visuals::crossahir_style, settings::visuals::sss, IM_ARRAYSIZE(settings::visuals::sss));
                        ImGui::EndChild();


                        ImGui::SetCursorPosY(85);
                        ImGui::SetCursorPosX(370);
                        ImGui::BeginChild("Preview", ImVec2(255, 230), TRUE);
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(ImColor(255, 255, 255, 200)));
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 9.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
                        ImGui::Text(E("Player settings"));
                        ImGui::PopStyleColor();
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button("Load", ImVec2(220, 30)))
                        {

                            FILE* p_stream;

                            // open file for (extended) reading
                            fopen_s(&p_stream, cfg[selected_cfg], "r+");

                            // set file pointer to 0
                            fseek(p_stream, 0, SEEK_SET);

                            // Aimbot
                            fread_s(&settings::aimbot::enabled, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&settings::aimbot::aimbot_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::smoothhorizontal, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::smoothvertical, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_target, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::hotkey, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_bone, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_type, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_selection, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Visuals
                            fread_s(&settings::visuals::enabled, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&settings::visuals::master_switch, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::box, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::box_round, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::filled, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::playername, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::playername, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::weapon_name, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::snapline, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::healthbar, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::armorbar, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::dont_draw_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::circle_at_middle, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::skeleton, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::watermark, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::render_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_dead, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_ped, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_self, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::preview_target, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::filled_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::crosshair, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::crossahir_style, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Vehicle
                            fread_s(&settings::vehicle::vehicle_esp, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::vehicle::vehicle_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::vehicle::vehicle_health, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::vehicle::vehicle_snapline, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Object
                            fread_s(&settings::object::object_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::object::object_esp, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::object::object_snapline, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Weapon
                            fread_s(&settings::weapon::enabled, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&settings::weapon::no_recoil, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::no_reload, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::no_spread, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::infinite_range, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::infite_ammo, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::damage_boost, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::recoil_value, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::spread_value, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::weapon_range, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::ammo_to_set, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::int_damage, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::custom_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::scope_fov_value, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&font, sizeof(bool), sizeof(bool), 1, p_stream);

                            fclose(p_stream);
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button("Save", ImVec2(220, 30)))
                        {

                            FILE* p_stream;

                            // open file for (extended) reading
                            fopen_s(&p_stream, cfg[selected_cfg], "w+");

                            // set file pointer to 0
                            fseek(p_stream, 0, SEEK_SET);

                            // Aimbot
                            fwrite(&settings::aimbot::enabled, sizeof(bool), 1, p_stream);

                            fwrite(&settings::aimbot::aimbot_fov, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::smoothhorizontal, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::smoothvertical, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::aimbot_distance, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::aimbot_target, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::hotkey, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::aimbot_bone, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::aimbot_type, sizeof(bool), 1, p_stream);
                            fwrite(&settings::aimbot::aimbot_selection, sizeof(bool), 1, p_stream);

                            // Visuals
                            fwrite(&settings::visuals::enabled, sizeof(bool), 1, p_stream);

                            fwrite(&settings::visuals::master_switch, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::box, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::box_round, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::filled, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::playername, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::playername, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::weapon_name, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::snapline, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::healthbar, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::armorbar, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::dont_draw_distance, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::circle_at_middle, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::skeleton, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::watermark, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::render_distance, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::draw_dead, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::draw_ped, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::draw_self, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::preview_target, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::draw_fov, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::filled_fov, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::crosshair, sizeof(bool), 1, p_stream);
                            fwrite(&settings::visuals::crossahir_style, sizeof(bool), 1, p_stream);

                            // Vehicle
                            fwrite(&settings::vehicle::vehicle_esp, sizeof(bool), 1, p_stream);
                            fwrite(&settings::vehicle::vehicle_distance, sizeof(bool), 1, p_stream);
                            fwrite(&settings::vehicle::vehicle_health, sizeof(bool), 1, p_stream);
                            fwrite(&settings::vehicle::vehicle_snapline, sizeof(bool), 1, p_stream);

                            // Object
                            fwrite(&settings::object::object_distance, sizeof(bool), 1, p_stream);
                            fwrite(&settings::object::object_esp, sizeof(bool), 1, p_stream);
                            fwrite(&settings::object::object_snapline, sizeof(bool), 1, p_stream);

                            // Weapon
                            fwrite(&settings::weapon::enabled, sizeof(bool), 1, p_stream);

                            fwrite(&settings::weapon::no_recoil, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::no_reload, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::no_spread, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::infinite_range, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::infite_ammo, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::damage_boost, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::recoil_value, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::spread_value, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::weapon_range, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::ammo_to_set, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::int_damage, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::custom_fov, sizeof(bool), 1, p_stream);
                            fwrite(&settings::weapon::scope_fov_value, sizeof(bool), 1, p_stream);

                            fwrite(&font, sizeof(bool), 1, p_stream);

                            fclose(p_stream);
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        if (ImGui::Button("Delete", ImVec2(220, 30)))
                        {
                            FILE* p_stream;

                            // open file for (extended) reading
                            fopen_s(&p_stream, cfg[selected_cfg], "r+");

                            // set file pointer to 0
                            fseek(p_stream, 0, SEEK_SET);

                            // Aimbot
                            fread_s(&settings::aimbot::enabled, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&settings::aimbot::aimbot_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::smoothhorizontal, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::smoothvertical, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_target, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::hotkey, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_bone, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_type, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::aimbot::aimbot_selection, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Visuals
                            fread_s(&settings::visuals::enabled, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&settings::visuals::master_switch, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::box, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::box_round, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::filled, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::playername, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::playername, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::weapon_name, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::snapline, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::healthbar, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::armorbar, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::dont_draw_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::circle_at_middle, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::skeleton, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::watermark, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::render_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_dead, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_ped, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_self, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::preview_target, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::draw_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::filled_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::crosshair, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::visuals::crossahir_style, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Vehicle
                            fread_s(&settings::vehicle::vehicle_esp, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::vehicle::vehicle_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::vehicle::vehicle_health, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::vehicle::vehicle_snapline, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Object
                            fread_s(&settings::object::object_distance, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::object::object_esp, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::object::object_snapline, sizeof(bool), sizeof(bool), 1, p_stream);

                            // Weapon
                            fread_s(&settings::weapon::enabled, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&settings::weapon::no_recoil, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::no_reload, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::no_spread, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::infinite_range, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::infite_ammo, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::damage_boost, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::recoil_value, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::spread_value, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::weapon_range, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::ammo_to_set, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::int_damage, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::custom_fov, sizeof(bool), sizeof(bool), 1, p_stream);
                            fread_s(&settings::weapon::scope_fov_value, sizeof(bool), sizeof(bool), 1, p_stream);

                            fread_s(&font, sizeof(bool), sizeof(bool), 1, p_stream);

                            fclose(p_stream);
                        }
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 7.5f);
                        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5.5f);
                        ImGui::Hotkey("Menu Key", &Menu::menu_key, ImVec2(100, 20));
                        ImGui::EndChild();


                    }
                }
                ImGui::End();
            

        }
        else {

            exit(3);
        }
    }
}
