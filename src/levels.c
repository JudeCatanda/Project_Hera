#include <levels.h>
#include <windows.h>

void init_level_data(Level_Details* self) {
  self->File = fopen("./assets/levels/config.txt", "r");
  if(self->File == NULL)
    fprintf(stderr, "Failed to open default levels\n");

  int hash_counter = 0;
  char* buffer;
  while(fgets(buffer, 1000, self->File)) {
    int line_size = strlen(buffer);
    for(int index = 0; index < line_size; index++) {
      if(buffer[index] == '#') {
        hash_counter += 1;
      }
    }
  };
  fclose(self->File);
  printf("Hashes: %d\n", hash_counter);
};
