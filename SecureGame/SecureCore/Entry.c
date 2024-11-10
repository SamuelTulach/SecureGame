#include <winenclave.h>

__declspec(dllexport) const IMAGE_ENCLAVE_CONFIG __enclave_config =
{
    sizeof(IMAGE_ENCLAVE_CONFIG),
    IMAGE_ENCLAVE_MINIMUM_CONFIG_SIZE,
    0 /*IMAGE_ENCLAVE_POLICY_DEBUGGABLE*/,
    0,
    0,
    0,
    { 0xFE, 0xFE },
    { 0x01, 0x01 },
    0,
    0,
    0x10000000,
    16,
    IMAGE_ENCLAVE_FLAG_PRIMARY_IMAGE
};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(hModule);
    UNREFERENCED_PARAMETER(reason);
    UNREFERENCED_PARAMETER(lpReserved);
    return TRUE;
}