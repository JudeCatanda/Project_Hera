#include "Terrain.hpp"

#undef def_as_ptr
//This function will be removed soon... remove all instance of it
#define def_as_ptr(name) typeof(this->name) *name = &this->name
#undef LOG_DEBUG
#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#undef LOG_ERROR
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__);
#define glCall(statement)\
  statement;\
  while(GLenum err = glGetError())\
    LOG_ERROR("AH SHIT!!! %d @line: %d", err, __LINE__);

const unsigned int max_vertex_counts = 50000;//renamed soon to max_quads_count
const unsigned int points_per_quad = 4;
const unsigned int indices_per_quad = 6;

glm::vec2 cell_size;

void Terrain::create() {

  m_Reader.ReadMap(GET_PATH_FROM_MAPS_DIR("level0")"//test.map");
  render_count = m_Reader.GetLineCount();

  //this->rdoc_api->StartFrameCapture(nullptr, nullptr);
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

  //SHADER LAYOUT: (OLD CODE... USE SAME SHADER LAYOUT)
  //5 (vec2) tex_pos
  //0 (vec2) mesh_buffer
  // texture_positions_buffer->Create((max_vertex_counts * points_per_quad) * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  // vao->SetVertexAttrib(5, 2, GL_FLOAT, sizeof(glm::vec2), (const void*)0);
  //
  // std::vector<glm::vec2> vec = this->tg.get_vector();
  // mesh_buffer->Create((render_count * points_per_quad) * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  // vao->SetVertexAttrib(0, 2, GL_FLOAT, sizeof(glm::vec2), (const void *)0);
  
  const float kflTileSize = m_Reader.GetTileSize();
  m_MeshData = {
    -kflTileSize, -kflTileSize,
     kflTileSize, -kflTileSize,
     kflTileSize,  kflTileSize,

     kflTileSize,  kflTileSize,
    -kflTileSize,  kflTileSize,
    -kflTileSize, -kflTileSize
  };
  m_VertexBuffer.Create(m_MeshData.size(), m_MeshData.data(), GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  m_VertexArray.SetVertexAttrib(0, 2, GL_FLOAT, 2 * sizeof(float), (const void*)0);
  

  m_VertexBuffer.Unbind();
  m_VertexArray.Unbind();

}

void Terrain::draw() {
  m_ShaderProgram.BindProgram();
  this->atlas.bind_and_set_active(GL_TEXTURE1);
  m_VertexArray.Bind();

  this->hitbox.size = this->size; //fix this later

  //glDrawArrays(GL_TRIANGLES, 0, (max_vertex_counts * points_per_quad)); //if not using indices
  //glDrawElements(GL_TRIANGLES, (render_count * points_per_quad), GL_UNSIGNED_INT, nullptr);
  glDrawArrays(GL_TRIANGLES, 0, render_count);
  
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

    float PosX = static_cast<float>(std::stoi(NumBuffX)); //convert str to fl
    float PosY = static_cast<float>(std::stoi(NumBuffY));

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
