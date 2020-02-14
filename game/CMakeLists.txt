set(game_SRCS
  action.cpp
  actionframe.cpp
  collision.cpp
  collisionscreen.cpp
  inputcondition.cpp
  input.cpp
  plane.cpp
  rect.cpp
  screen.cpp
  screenelement.cpp
  sprite.cpp
)

add_library(game SHARED ${game_SRCS})
target_link_libraries(game common)
