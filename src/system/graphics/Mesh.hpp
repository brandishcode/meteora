#pragma once

namespace Meteora {
struct Position {
  float x;
  float y;
  float z;
};

class Mesh {
public:
  Mesh(Position position) : position(position) {}
  const Position position;
};
} // namespace Meteora
