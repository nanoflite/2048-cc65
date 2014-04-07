.export _tile_ptr
.export _screen_ptr
.export _color_ptr

.import _tiles

SCREEN = $8000
COLOR = $D800

_tile_ptr:
  .addr _tiles + 25 * 0  
  .addr _tiles + 25 * 1  
  .addr _tiles + 25 * 2  
  .addr _tiles + 25 * 3  
  .addr _tiles + 25 * 4  
  .addr _tiles + 25 * 5  
  .addr _tiles + 25 * 6  
  .addr _tiles + 25 * 7  
  .addr _tiles + 25 * 8  
  .addr _tiles + 25 * 9  
  .addr _tiles + 25 * 10  
  .addr _tiles + 25 * 11  
  .addr _tiles + 25 * 12 
  .addr _tiles + 25 * 13 
  .addr _tiles + 25 * 14  
  .addr _tiles + 25 * 15  
  .addr _tiles + 25 * 16  
  .addr _tiles + 25 * 17  
  .addr _tiles + 25 * 18 

_screen_ptr:
  .addr SCREEN + 0 * 40 + 0
  .addr SCREEN + 0 * 40 + 5
  .addr SCREEN + 0 * 40 + 10
  .addr SCREEN + 0 * 40 + 15
  .addr SCREEN + 0 * 40 + 20
  .addr SCREEN + 0 * 40 + 25
  .addr SCREEN + 0 * 40 + 30
  .addr SCREEN + 0 * 40 + 35
  .addr SCREEN + 5 * 40 + 0
  .addr SCREEN + 5 * 40 + 5
  .addr SCREEN + 5 * 40 + 10
  .addr SCREEN + 5 * 40 + 15
  .addr SCREEN + 5 * 40 + 20
  .addr SCREEN + 5 * 40 + 25
  .addr SCREEN + 5 * 40 + 30
  .addr SCREEN + 5 * 40 + 35
  .addr SCREEN + 10 * 40 + 0
  .addr SCREEN + 10 * 40 + 5
  .addr SCREEN + 10 * 40 + 10
  .addr SCREEN + 10 * 40 + 15
  .addr SCREEN + 10 * 40 + 20
  .addr SCREEN + 10 * 40 + 25
  .addr SCREEN + 10 * 40 + 30
  .addr SCREEN + 10 * 40 + 35
  .addr SCREEN + 15 * 40 + 0
  .addr SCREEN + 15 * 40 + 5
  .addr SCREEN + 15 * 40 + 10
  .addr SCREEN + 15 * 40 + 15
  .addr SCREEN + 15 * 40 + 20
  .addr SCREEN + 15 * 40 + 25
  .addr SCREEN + 15 * 40 + 30
  .addr SCREEN + 15 * 40 + 35
  .addr SCREEN + 20 * 40 + 0
  .addr SCREEN + 20 * 40 + 5
  .addr SCREEN + 20 * 40 + 10
  .addr SCREEN + 20 * 40 + 15
  .addr SCREEN + 20 * 40 + 20
  .addr SCREEN + 20 * 40 + 25
  .addr SCREEN + 20 * 40 + 30
  .addr SCREEN + 20 * 40 + 35

_color_ptr:
  .addr COLOR + 0 * 40 + 0
  .addr COLOR + 0 * 40 + 5
  .addr COLOR + 0 * 40 + 10
  .addr COLOR + 0 * 40 + 15
  .addr COLOR + 0 * 40 + 20
  .addr COLOR + 0 * 40 + 25
  .addr COLOR + 0 * 40 + 30
  .addr COLOR + 0 * 40 + 35
  .addr COLOR + 5 * 40 + 0
  .addr COLOR + 5 * 40 + 5
  .addr COLOR + 5 * 40 + 10
  .addr COLOR + 5 * 40 + 15
  .addr COLOR + 5 * 40 + 20
  .addr COLOR + 5 * 40 + 25
  .addr COLOR + 5 * 40 + 30
  .addr COLOR + 5 * 40 + 35
  .addr COLOR + 10 * 40 + 0
  .addr COLOR + 10 * 40 + 5
  .addr COLOR + 10 * 40 + 10
  .addr COLOR + 10 * 40 + 15
  .addr COLOR + 10 * 40 + 20
  .addr COLOR + 10 * 40 + 25
  .addr COLOR + 10 * 40 + 30
  .addr COLOR + 10 * 40 + 35
  .addr COLOR + 15 * 40 + 0
  .addr COLOR + 15 * 40 + 5
  .addr COLOR + 15 * 40 + 10
  .addr COLOR + 15 * 40 + 15
  .addr COLOR + 15 * 40 + 20
  .addr COLOR + 15 * 40 + 25
  .addr COLOR + 15 * 40 + 30
  .addr COLOR + 15 * 40 + 35
  .addr COLOR + 20 * 40 + 0
  .addr COLOR + 20 * 40 + 5
  .addr COLOR + 20 * 40 + 10
  .addr COLOR + 20 * 40 + 15
  .addr COLOR + 20 * 40 + 20
  .addr COLOR + 20 * 40 + 25
  .addr COLOR + 20 * 40 + 30
  .addr COLOR + 20 * 40 + 35
