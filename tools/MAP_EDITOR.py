import pygame, sys
import tkinter as tk
from tkinter import filedialog

# Settings
TILE_SIZE = 8
GRID_W, GRID_H = 200, 200
ZOOM_STEP = 0.1
AXIS_COLOR = (200, 200, 200)
GRID_COLOR = (70, 70, 70)

pygame.init()
font = pygame.font.SysFont(None, 24)
clock = pygame.time.Clock()

# Initialize tkinter for file dialogs (hidden window)
root = tk.Tk()
root.withdraw()

screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
fullscreen = True
tiles = set()  # Simple set of (x, y) coordinates
zoom = 1.0
offset_x = (GRID_W * TILE_SIZE) / 2
offset_y = (GRID_H * TILE_SIZE) / 2
panning = False
current_file = None

def save_map():
    global current_file
    if current_file is None:
        save_map_as()
    else:
        with open(current_file, "w") as f:
            for x, y in tiles:
                f.write(f"{x},{y};\n")
        print(f"Saved {len(tiles)} tiles to {current_file}")

def save_map_as():
    global current_file
    filename = filedialog.asksaveasfilename(
        title="Save Map",
        defaultextension=".map",
        filetypes=[("Map files", "*.map"), ("All files", "*.*")]
    )
    if filename:
        current_file = filename
        with open(current_file, "w") as f:
            for x, y in tiles:
                f.write(f"{x},{y};\n")
        print(f"Saved {len(tiles)} tiles to {current_file}")

def load_map():
    global current_file, tiles
    filename = filedialog.askopenfilename(
        title="Open Map",
        filetypes=[("Map files", "*.map"), ("All files", "*.*")]
    )
    if filename:
        current_file = filename
        tiles = set()
        try:
            with open(current_file, "r") as f:
                content = f.read().strip()
                if content:
                    lines = content.split('\n')
                    for line in lines:
                        line = line.strip()
                        if line and line.endswith(';'):
                            coords = line[:-1].split(',')
                            if len(coords) == 2:
                                try:
                                    x, y = int(coords[0]), int(coords[1])
                                    tiles.add((x, y))
                                except ValueError:
                                    continue
            print(f"Loaded {len(tiles)} tiles from {current_file}")
        except FileNotFoundError:
            print("File not found!")

def new_map():
    global current_file, tiles
    current_file = None
    tiles = set()
    print("Created new map")

while True:
    mx, my = pygame.mouse.get_pos()
    world_x = mx / zoom + offset_x
    world_y = my / zoom + offset_y
    grid_x = int(world_x // TILE_SIZE)
    grid_y = GRID_H - 1 - int(world_y // TILE_SIZE)

    for e in pygame.event.get():
        if e.type == pygame.QUIT:
            pygame.quit()
            root.destroy()
            sys.exit()
        if e.type == pygame.KEYDOWN:
            if e.key == pygame.K_F11:
                fullscreen = not fullscreen
                screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN if fullscreen else pygame.RESIZABLE)
            elif e.key == pygame.K_s and pygame.key.get_mods() & pygame.KMOD_CTRL:
                if pygame.key.get_mods() & pygame.KMOD_SHIFT:
                    save_map_as()
                else:
                    save_map()
            elif e.key == pygame.K_o and pygame.key.get_mods() & pygame.KMOD_CTRL:
                load_map()
            elif e.key == pygame.K_n and pygame.key.get_mods() & pygame.KMOD_CTRL:
                new_map()
        if e.type == pygame.MOUSEWHEEL:
            if pygame.key.get_mods() & pygame.KMOD_CTRL:
                if e.y > 0:  # scroll up
                    zoom += ZOOM_STEP
                elif e.y < 0 and zoom > ZOOM_STEP * 2:  # scroll down
                    zoom -= ZOOM_STEP
        if e.type == pygame.MOUSEBUTTONDOWN:
            if e.button == 2:  # middle to pan
                panning = True
                pan_start = (mx, my)
                orig_off = (offset_x, offset_y)
            elif -GRID_W <= grid_x < GRID_W and -GRID_H <= grid_y < GRID_H:
                if e.button == 1 and (grid_x, grid_y) not in tiles:
                    tiles.add((grid_x, grid_y))
                elif e.button == 3 and (grid_x, grid_y) in tiles:
                    tiles.remove((grid_x, grid_y))
        if e.type == pygame.MOUSEBUTTONUP and e.button == 2:
            panning = False
        if e.type == pygame.MOUSEMOTION and panning:
            dx = (pan_start[0] - mx) / zoom
            dy = (pan_start[1] - my) / zoom
            offset_x = orig_off[0] + dx
            offset_y = orig_off[1] + dy

    buttons = pygame.mouse.get_pressed()
    if buttons[0] and -GRID_W <= grid_x < GRID_W and -GRID_H <= grid_y < GRID_H:
        tiles.add((grid_x, grid_y))
    if buttons[2] and (grid_x, grid_y) in tiles:
        tiles.remove((grid_x, grid_y))

    screen.fill((30, 30, 30))

    # Grid lines
    for gx in range(-GRID_W, GRID_W+1):
        x = (gx * TILE_SIZE - offset_x) * zoom
        pygame.draw.line(screen, GRID_COLOR, (x, 0), (x, screen.get_height()))
    for gy in range(-GRID_H, GRID_H+1):
        y = (GRID_H * TILE_SIZE - gy * TILE_SIZE - offset_y) * zoom
        pygame.draw.line(screen, GRID_COLOR, (0, y), (screen.get_width(), y))

    # Axes
    center_x = -offset_x * zoom
    center_y = (GRID_H * TILE_SIZE - offset_y) * zoom
    pygame.draw.line(screen, AXIS_COLOR, (center_x, 0), (center_x, screen.get_height()))
    pygame.draw.line(screen, AXIS_COLOR, (0, center_y), (screen.get_width(), center_y))

    # Tiles
    for x, y in tiles:
        rx = (x * TILE_SIZE - offset_x) * zoom
        ry = ((GRID_H - y - 1) * TILE_SIZE - offset_y) * zoom
        pygame.draw.rect(screen, (120, 180, 255), (rx, ry, TILE_SIZE * zoom, TILE_SIZE * zoom))

    # Cursor highlight
    if -GRID_W <= grid_x < GRID_W and -GRID_H <= grid_y < GRID_H:
        rx = (grid_x * TILE_SIZE - offset_x) * zoom
        ry = ((GRID_H - grid_y - 1) * TILE_SIZE - offset_y) * zoom
        pygame.draw.rect(screen, (255, 255, 0), (rx, ry, TILE_SIZE * zoom, TILE_SIZE * zoom), 2)

    # UI Info
    filename_display = current_file.split('/')[-1] if current_file else "Untitled"
    info_lines = [
        f"File: {filename_display} | Cursor: ({grid_x},{grid_y}) | Zoom: {zoom:.2f} | Tiles: {len(tiles)}",
        "Controls: Ctrl+N=New, Ctrl+O=Open, Ctrl+S=Save, Ctrl+Shift+S=Save As"
    ]
    
    for i, line in enumerate(info_lines):
        info = font.render(line, True, (220, 220, 220))
        screen.blit(info, (10, 10 + i * 25))

    pygame.display.flip()
    clock.tick(120)