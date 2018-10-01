; Inform NASM where we are to be loaded
org 7C00h
; Inform NASM to encode for i386
bits 16

; Track what has been inputed in an arbitrarily selected chunk in memory
%define hist_array 2000h

_start:
  ; Set up enviornment and variables
  call initialize_game

  ; Admitadly, this is the most sane bit of code I wrote here:
  .game_loop:
    call get_input
    call check_answer  ; Does not return if answer is correct
    jmp .game_loop
; no_return


initialize_game:
  cli  ; Disable interupts

  ; Set screen mode to be fun (640x480, 16 colors)
  mov ax, 0x0012
  int 0x10

  mov di, hist_array  ; Current array_of_previous_inputs offset

  ; Get random number
  xor ax, ax
  int 1ah     ; Get RTC

  ; "Fix" random number by setting it to be 0-9
  mov ax, dx  ; Set up seconds into div
  mov cx, 10  ; Get remainder from 10 div
  xor dx, dx  ; dx needs to be zero for div
  div cx
  mov byte [buffer_answer], dl
ret


; Get input, render input, track input across program run
get_input:
  call display_scene
  ; read input
  xor si, si
  .input_loop:
    call display_input_buffer

    ; Blocking single character input interupt
    xor ax, ax
    int 0x16 

    ; Potential non-blocking method:
    ; AH = 01h
    ; Return:
    ; ZF set if no keystroke available
    ; ZF clear if keystroke available
    ; AH = BIOS scan code
    ; AL = ASCII character

    ; Check if enter was pressed
    cmp ax, 0x1c0d
    je .end

    ; Check if backspace was pressed
    cmp ax, 0x0e08
    jne .continue
      test si, si  ; Igore backspace on empty buffer
        jz .input_loop
      dec si  ; Delete last input (by allowing an overwrite on next line)
      mov byte [si+buffer_input], 0  ; Null-terminate buffer and overwrite last character
      jmp .input_loop
    .continue:

    mov [si+buffer_input], al  ; Save current buffer
    inc si
    mov byte [si+buffer_input], 0  ; Null-terminate buffer

    jmp .input_loop

  .end:
    call clear_scene
    ; Check to see if there were too many characters inputed
    .check_input_length:
      cmp si, 1
      je .check_input
      jg .too_many
      
      .too_few:
        mov ax, data_prompt_input_too_few
        jmp .too_common

      .too_many:
        mov ax, data_prompt_input_too_many
        
      .too_common:
        call display_info

        ; Clear away input buffer
        mov cx, si
        .clear_loop:
          mov bx, cx
          mov byte [bx+buffer_input], 0
          loop .clear_loop

        jmp get_input

    ; Make sure that the inputed byte is an ascii 0-9
    .check_input:
      cmp byte [buffer_input], '0'
        jl .too_many
      
      cmp byte [buffer_input], '9'
        jg .too_many

    ; Save to list of tested characters
    .save_input:
      mov fs, di
      mov byte [fs:0], al
      mov byte [fs:1], 0
      inc di

    ; Setup return value in al
    mov al, [buffer_input]
    sub al, '0'
ret


; Check the input stored in al against the answer generated at the beginning
check_answer:
  ; Compare the intput (rax) to the stored answer
  cmp al, byte [buffer_answer]
  je end        ; Go to the end if they guessed right
  
  jg .too_high  ; If the guess was too high, report and then continue
  
  .too_low:     ; If the guess was too low,  report and then continue
    push data_prompt_guess_too_low  ; Store prompt to print for later
    jmp .print

  .too_high:
    push data_prompt_guess_too_high  ; Store prompt to print for later

  ; Print fancy that input is wrong
  .print:
    call display_wrong
    pop ax
    call display_info
ret 


display_common:
  mov cx, 28
  mov bx, 0000000000001111b
  mov ax, 0x1301
  int 0x10
ret


; Pretty-display boarders and history
display_scene:
  ; Print string
  mov bp, data_prompt_guess 
  xor dx, dx  ; row:dh | col:dl
  call display_common
ret


clear_scene:
  push ax
    mov bp, data_clear
    mov dx, 0100h
    call display_common
    mov dx, 0200h
    call display_common
    mov dx, 0300h
    call display_common
  pop ax
ret:

; Print what the user has entered thus far
display_input_buffer:
  mov bp, buffer_input 
  mov dx, 0101h  ; row:dh | col:dl
  call display_common
ret


display_info:
  mov bp, ax
  mov dx, 0300h  ; row:dh | col:dl
  call display_common
ret


display_wrong:
  mov bp, data_prompt_guess_wrong
  mov dx, 0200h  ; row:dh | col:dl
  call display_common
ret


display_correct:
  mov bp, data_prompt_guess_correct
  mov dx, 0200h  ; row:dh | col:dl
  call display_common
ret


end:
  call display_correct

  .end:
    jmp .end
; No return

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;       Data Section      ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
data_clear:                   db "                            ", 0
data_prompt_guess:            db "Guess a number:             ", 0
data_prompt_guess_too_high:   db "Too high.                   ", 0
data_prompt_guess_too_low:    db "Too low.                    ", 0
data_prompt_guess_correct:    db "Correct!                    ", 0
data_prompt_guess_wrong:      db "Wrong!!                     ", 0

data_prompt_input_too_few:    db "Come on, give me something..", 0
data_prompt_input_too_many:   db "Naw man, 0-9 only.          ", 0

buffer_answer: db 0  ; Buffer to store answer

; Pad the rest of the file with zeros until boot signature
times 512-2 - ($-$$) db 0
dw 0AA55h

buffer_input:  ; Buffer to store input at an arbitrary location (after loaded bootsector) as to not interfere with anything else