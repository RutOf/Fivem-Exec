#pragma once
#include <Windows.h>
#include <string>
#include <thread>


struct ProcessWindowData
{
	HWND hWnd;
	unsigned long lProcessId;
};

namespace Hooks
{
    extern D3DMATRIX m_vMatrix;
    HRESULT __stdcall hkD3D11Present(IDXGISwapChain* pSwapChain, UINT SysInterval, UINT Flags);
}

class ScriptHook
{
public:
    ScriptHook();
    ~ScriptHook();

    void Initialize();
    void Release();

    void HookFunction(PVOID *oFunction, PVOID pDetour);
    void UnHookFunction(PVOID *oFunction, PVOID pDetour);
};

namespace common
{
    wchar_t* GetFileNameFromPath(wchar_t* Path)
    {
        wchar_t* LastSlash = NULL;
        for (DWORD i = 0; Path[i] != NULL; i++)
        {
            if (Path[i] == '\\' || Path[i] == '/')
                LastSlash = &Path[i + 1];
        }
        return LastSlash;
    }
    wchar_t* RemoveFileExtension(wchar_t* FullFileName, wchar_t* OutputBuffer, DWORD OutputBufferSize)
    {
        wchar_t* LastDot = NULL;
        for (DWORD i = 0; FullFileName[i] != NULL; i++)
            if (FullFileName[i] == '.')
                LastDot = &FullFileName[i];

        for (DWORD j = 0; j < OutputBufferSize; j++)
        {
            OutputBuffer[j] = FullFileName[j];
            if (&FullFileName[j] == LastDot)
            {
                OutputBuffer[j] = NULL;
                break;
            }
        }
        OutputBuffer[OutputBufferSize - 1] = NULL;
        return OutputBuffer;
    }
}
