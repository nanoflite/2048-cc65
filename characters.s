; Code to initialize custom charset

.export _chars_init
.export _chars_draw_tile

SCREEN = $8000
COLOR = $D800
.import _tiles
.import _attribs
.import _tile_ptr
.import _screen_ptr
.import _color_ptr

.import popax

.importzp ptr1
.importzp ptr2
.importzp ptr3

.code

; Enable custom charset in bank2
.proc _chars_init
  lda   $DD02     ; set data direction to output on port bits 0 and 1 of CIA #2
  ora   #3
  sta   $DD02

  lda   $DD00     ; select bank 2 ($8000-$BFFF) by setting bit pattern 01 to bit 0, 1
  and   #$FC
  ora   #1
  sta   $DD00  

  lda   #$02      ; move screen location to page '0' ($8000), move charset location to page '1', ($8800)
  sta   $D018 

  lda   $D016     ; turn on multi color
  ora   #$10
  sta   $D016

  ; quick fix, set colors here
  lda   #1
  sta   $D020
  sta   $D021
  lda   #11
  sta   $D022
  lda   #0
  sta   $D023

  ; quick fix 2, clear screen here
  lda #$20
  ldx #$00
clear_loop:
  sta SCREEN+$0000,x
  sta SCREEN+$0100,x
  sta SCREEN+$0200,x
  sta SCREEN+$0300,x
  dex
  bne clear_loop

  rts
.endproc

; __fastcall__ chars_draw_tile(unsigned char x, unsigned char y, unsigned char tile)
.proc _chars_draw_tile
  ; Fetch attribute byte (value that goes into color ram)
  ; Attribute __fastcall__ puts last parameter into register A.
  tay
  lda _attribs,y
  sta attribute
  tya

  ; calculate tile address
  asl
  tax
  lda _tile_ptr+0,x
  sta ptr1+0
  lda _tile_ptr+1,x
  sta ptr1+1

  ; calculate screen position
  ; address = SCREEN + 40 * y + x
  ; or...
  ; 8 tiles horizontally
  ; 5 tiles vertically
  ; tile position is limited to 40 screen locations!
  ; that smells like a table to me!
  ; 8 * y + x
  ; asl, asl, asl, adc !
  ; + lookup in table 
  jsr popax
  asl
  asl
  asl
  sta temp
  txa
  clc
  adc temp
  asl
  tax

  ; set screen address
  lda _screen_ptr+0,x
  sta ptr2+0
  lda _screen_ptr+1,x
  sta ptr2+1

  ; set color address
  lda _color_ptr+0,x
  sta ptr3+0
  lda _color_ptr+1,x
  sta ptr3+1
   
  ldx #5
copy_rows:
  ldy #0

copy_columns:  
  lda (ptr1),y
  sta (ptr2),y 
  lda attribute
  sta (ptr3),y
  iny
  cpy #5
  bmi copy_columns

  clc
  lda ptr1+0
  adc #5
  sta ptr1+0
  lda ptr1+1
  adc #0
  sta ptr1+1

  clc
  lda ptr2+0
  adc #40
  sta ptr2+0
  lda ptr2+1 
  adc #0
  sta ptr2+1

  clc
  lda ptr3+0
  adc #40
  sta ptr3+0
  lda ptr3+1
  adc #0
  sta ptr3+1

  dex
  bne copy_rows

  rts
.endproc

.bss

temp:
  .res 1

attribute:
  .res 1

