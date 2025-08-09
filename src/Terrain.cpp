#include "Terrain.hpp"

#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#undef LOG_ERROR
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__);

const unsigned int points_per_quad = 4;
const unsigned int indices_per_quad = 6;

glm::vec2 cell_size;

void Terrain::create() {

  m_Reader.ReadMap(GET_PATH_FROM_MAPS_DIR("level0")"//test.map");
  render_count = m_Reader.GetLineCount();

  m_Vertex.Create(GET_SHADERS_PATH("terrain.vert.glsl"), GL_VERTEX_SHADER);
  m_Fragment.Create(GET_SHADERS_PATH("terrain.frag.glsl"), GL_FRAGMENT_SHADER);
  m_ShaderProgram.CreateProgram(&m_Vertex, &m_Fragment);

  m_VertexArray.CreateAndBind();

  this->atlas.create(std::string(GET_TEXTURES_PATH("parts.atlas.png")), GL_TEXTURE_2D, GL_RGBA, GL_RGBA);
  this->atlas.bind_and_set_active(GL_TEXTURE1);
  glUniform1i(glGetUniformLocation(m_ShaderProgram.GetHandle(), "tex1"), 1);
  cell_size = glm::vec2(16.0f);
  if(!this->atlas.is_image_valid())
    LOG_DEBUG("the image was invalid for some reason!");

  const float kflTileSize = m_Reader.GetTileSize();
  m_MeshData = {
    -kflTileSize, -kflTileSize,
     kflTileSize, -kflTileSize,
     kflTileSize,  kflTileSize,
    -kflTileSize,  kflTileSize,
  };

  m_MeshIndices = {
      0, 1, 2,
      2, 3, 0
  };

  for(Tile_t& tile : *m_Reader.GetTiles()) {
    m_TilePositions.push_back(tile.Position);
  }
  m_TilePositionsGPU.Create(m_TilePositions.size() * sizeof(glm::vec2), m_TilePositions.data(), GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  m_VertexArray.SetVertexAttrib(3, 2, GL_FLOAT, 2 * sizeof(float), (const void*)0);

  m_VertexBuffer.Create(m_MeshData.size() * sizeof(float), m_MeshData.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  m_VertexArray.SetVertexAttrib(0, 2, GL_FLOAT, 2 * sizeof(float), (const void*)0);


  m_VertexArray.SetDivisor(3, 1);

  m_IndexBuffer.Create(m_MeshIndices.size() * sizeof(unsigned int), m_MeshIndices.data(), GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

  m_VertexArray.Unbind();
}

void Terrain::draw() {
  m_ShaderProgram.BindProgram();
  this->atlas.bind_and_set_active(GL_TEXTURE1);

  m_VertexArray.Bind();

  this->hitbox.size = this->size; //fix this later

  glDrawElementsInstanced(GL_TRIANGLES, m_MeshIndices.size(), GL_UNSIGNED_INT, 0, render_count);
  
  m_ShaderProgram.UnbindProgram();
  m_VertexArray.Unbind();
}

void Terrain::destroy() {
  m_ShaderProgram.Destroy();
  m_VertexArray.Destroy();
  m_VertexBuffer.Destroy();
}

void Terrain::test_tg(void) {
  //for testing
}

void CBaseMapReader::ReadMap(const char* szFileName) {
  std::ifstream Handle(szFileName);
  std::string CurrentLine;
  std::size_t CommaLocation;
  std::string NumBuffX, NumBuffY;
  const float kflTileSpace = 8.0f;
  

  if (!Handle.is_open()) {
    LOG_ERROR("Cannot load map name %s, does not exist", szFileName);
  }

  while(std::getline(Handle, CurrentLine)) {
    bool CurrentLineClosed = false;
    CurrentLineClosed = (CurrentLine.find(';') == std::string::npos) ? false : true;
    if(!CurrentLineClosed) {
      LOG_ERROR("Expected \";\"");
      return;
    }
    CurrentLine = CurrentLine.substr(0, CurrentLine.find(';'));
    CommaLocation = CurrentLine.find(',');
    if(CommaLocation == std::string::npos) {
      LOG_ERROR("Map loading Error! comma was not found!");
      return;
    }
    NumBuffX = CurrentLine.substr(0, CommaLocation);
    NumBuffY = CurrentLine.substr(CommaLocation + 1);

    float PosX = static_cast<float>(std::stoi(NumBuffX)) * kflTileSpace; //convert str to fl
    float PosY = static_cast<float>(std::stoi(NumBuffY)) * kflTileSpace;

    LOG_DEBUG("Parsed: x = %f, y = %f", PosX, PosY);
    m_QuadCoords.push_back(glm::vec2(PosX, PosY));

    ++m_nLines;
  }
  LOG_DEBUG("We are expected to render %d quads", m_nLines);
  setTilesOnMapRead();
};

void CBaseMapReader::setTilesOnMapRead(void) {
    for(glm::vec2& vecPosition : m_QuadCoords) {
        m_Tiles.push_back({ .Position = vecPosition, .TexturePosition = glm::vec2(0.0f) });
    };
};
