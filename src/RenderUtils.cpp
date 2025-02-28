// void mesh_create_triangle(std::vector<Vertex>& array, float x, float y, float scale) {
//   array.push_back(
//     { x - scale, y - scale }
//   );
//   array.push_back(
//     { x + scale, y - scale }
//   );
//   array.push_back(
//     { x, y + scale }
//   );
// }
// Vertex *mesh_create_triangle_out(Vertex *target, float x, float y, float scale) {
//   /**/target->Position = { x, y };
//   /**/target++;

//   /**/target->Position = { x + scale, y };
//   /**/target++;

//   /**/target->Position = { x + scale, y + scale };
//   /**/target++;

//   target->Position = { x, y };
//   target++;

//   target->Position = { x, y + scale };
//   target++;

//   target->Position = { x + scale, y + scale };
//   target++;

//   return target;
// };