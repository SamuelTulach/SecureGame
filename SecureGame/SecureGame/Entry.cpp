#include "Global.h"

bool LoadEnclave()
{
    if (!IsEnclaveTypeSupported(ENCLAVE_TYPE_VBS))
    {
        MessageBoxA(nullptr, "VBS enclave is not supported (or VBS is disabled)", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    constexpr ENCLAVE_CREATE_INFO_VBS createInfo
    {
        0 /*ENCLAVE_VBS_FLAG_DEBUG*/,
        { 0x10, 0x20, 0x30, 0x40, 0x41, 0x31, 0x21, 0x11 },
    };

    Global::Enclave = CreateEnclave(GetCurrentProcess(),
        nullptr,
        0x10000000,
        0,
        ENCLAVE_TYPE_VBS,
        &createInfo,
        sizeof(ENCLAVE_CREATE_INFO_VBS),
        nullptr);
    if (!Global::Enclave)
    {
        char buffer[256];
        sprintf_s(buffer, "Failed to create enclave: %d", GetLastError());
        MessageBoxA(nullptr, buffer, "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    const DWORD previousMode = GetThreadErrorMode();
    SetThreadErrorMode(previousMode | SEM_FAILCRITICALERRORS, nullptr);

    if (!LoadEnclaveImageW(Global::Enclave, L"SecureCore.dll"))
    {
        char buffer[256];
        sprintf_s(buffer, "Failed to load enclave image: %d", GetLastError());
        MessageBoxA(nullptr, buffer, "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    ENCLAVE_INIT_INFO_VBS initInfo;
    initInfo.Length = sizeof(ENCLAVE_INIT_INFO_VBS);
    initInfo.ThreadCount = 1;

    if (!InitializeEnclave(GetCurrentProcess(), Global::Enclave, &initInfo, initInfo.Length, nullptr))
    {
        char buffer[256];
        sprintf_s(buffer, "Failed to initialize enclave: %d", GetLastError());
        MessageBoxA(nullptr, buffer, "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    Global::TickRoutine = reinterpret_cast<PENCLAVE_ROUTINE>(GetProcAddress(static_cast<HMODULE>(Global::Enclave), "GameTick"));
    if (!Global::TickRoutine)
    {
        MessageBoxA(nullptr, "Failed to get routine", "Error", MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

#if ENABLE_CONSOLE
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
#endif

    if (!LoadEnclave())
        return 1;

    Game game;
    if (!game.Init())
        return 1;

    game.Loop();
    return 0;
}