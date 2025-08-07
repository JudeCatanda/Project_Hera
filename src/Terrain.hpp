#pragma once

#include "Texture.hpp"
#include <array>
#include <glad/glad.h>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>
#include <fstream>

#include "AABB.hpp"
#include "Buffer.hpp"
#include "Layout.hpp"
#include "Shader.hpp"
#include "rdoc.hpp"

const float RET_ERR_VEC2 = -1000000.00f;

typedef struct Tile {
    glm::vec2 Position;
    glm::vec2 TexturePosition;
} Tile_t;

class CBaseMapReader {
private:
    //read and write to file
    std::vector<std::string> m_MapFileBuffer;
    int m_nLines = 0;
    std::vector<glm::vec2> m_QuadCoords;
    std::vector<Tile_t> m_Tiles;
    float m_flTileSize;
    void setTilesOnMapRead(void);
public:
    CBaseMapReader() : m_flTileSize(4.0f) {};
    void                                    DumpMap(const char* szFileName);
    void                                    ReadMap(const char* szFileName);
    std::vector<glm::vec2>*                 GetBuffer(void) { return &m_QuadCoords; };
    std::vector<Tile_t>*                    GetTiles(void) { return &m_Tiles; };
    int                                     GetLineCount(void) const { return m_nLines; };
    float                                   GetTileSize(void) const noexcept { return m_flTileSize; };
};

class Terrain {
private:
    int render_count; //moved here
    CShader m_Vertex, m_Fragment;
    CShaderProgram m_ShaderProgram;
    CBaseMapReader m_Reader;
    Layout m_VertexArray;
    Buffer m_VertexBuffer, m_IndexBuffer;
    Texture atlas;
    std::vector<float> m_MeshData;

    float size = 16.0f;
    AABB_Hitbox hitbox;

public:
  RENDERDOC_API_1_5_0 * rdoc_api = nullptr;
  Terrain() = default;
  void create();
  void draw();
  void destroy();
  void test_tg(void);
  // void set_pos(glm::vec2 pos);
};
