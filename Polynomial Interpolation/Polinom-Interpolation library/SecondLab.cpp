#include "Interpolation.h"
//#include "/Users/userr/source/repos/numericalmethods/interpolation_1 (LABA 1)/interpolation_1 (LABA 1)/Table_Function.h"
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
  {
    break;
  }
  case DLL_THREAD_ATTACH:
    break;
  case DLL_THREAD_DETACH:
    break;
  case DLL_PROCESS_DETACH:
    break;
  }
  return TRUE;
}
