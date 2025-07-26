#include "rdoc.hpp"
#include <iostream>
#include <cassert>

#undef LOG_ERROR
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__);

void get_render_doc(RENDERDOC_API_1_5_0* rdoc_api) {
  HMODULE hmod = LoadLibraryA(".//renderdoc.dll");
  if(!hmod)
    LOG_ERROR("Cannot load the dll");
  auto GetAPI = (pRENDERDOC_GetAPI)GetProcAddress(hmod, "RENDERDOC_GetAPI");
  if(!GetAPI)
    LOG_ERROR("Unable to get the function GetAPI!");
  GetAPI(eRENDERDOC_API_Version_1_5_0, (void **)&rdoc_api);
};
