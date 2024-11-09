#include <levels.h>
#include <windows.h>


void init_level_data(Level_Details* self) {
  self->File = fopen("./assets/levels/config.txt", "r");
  
  //HWND win_access = glfwGetWin32Window(self->win);
  //MessageBoxA(win_access, "Hera failed to load level config text file\n(config.txt)\n\n1200", "Level Load Error", MB_OK);

  fclose(self->File);
};
