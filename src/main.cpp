#include <logger.hpp>

#include <graphics/Backend.hpp>

void error_callback(int error, const char *description) {
  LOGGER_ERROR("Error: {} return {}", description, error);
}

int main(void) {
  Meteora::Backend backend;

  backend.init();
  backend.run();

  return 0;
}
