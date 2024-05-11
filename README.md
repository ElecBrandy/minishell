# minishell

- 검색으로 dongwook 하면 어디 고쳤는지 바로 알 수 있음!
- 그리고 바뀌기 전 부분 주석처리 해놨으니 되돌릴때 조금 편하실수도..
- SEG on ~ 이런식으로 커밋메세지가 뭔지 달아놓았읍니다. 혹시 되돌리실때 참고하시면될듯합니

### 05.11 : SEGV on make_node
1. 일단 make랑 실행되는 것 까지 확인
   - 그런데 `make_node` 함수에서 뭔가 에러
   - 일단 `t_node *create_node(void);`, `void append_node(t_node **head, t_node *new_node);` 함수로 나눠서 사용하는걸로 해놓음

``` bash
AddressSanitizer:DEADLYSIGNAL
=================================================================
==71180==ERROR: AddressSanitizer: SEGV on unknown address 0xffffb07020a18643 (pc 0x000104eff704 bp 0x00016af0ae50 sp 0x00016af0ad90 T0)
==71180==The signal is caused by a READ memory access.
    #0 0x104eff704 in make_node parsing_utils.c:53
    #1 0x104f01624 in minishell minishell.c:53
    #2 0x104f01eb4 in main minishell.c:118
```

2. 파이프 존재하지 않을때 SEG 오류
   - `cat a.txt | cat a.txt` 이렇게 입력하면 문제 없이 잘 작동!
   - `cat a.txt` 와 같이 파이프 없을 때 아래 SEG 오류


``` bash
==74140==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x000107902c19 at pc 0x000104e39748 bp 0x00016afce7d0 sp 0x00016afce7c8
WRITE of size 1 at 0x000107902c19 thread T0
    #0 0x104e39744 in add_space parsing_in_pipe.c:141
    #1 0x104e39824 in parsing_in_pipe parsing_in_pipe.c:152
    #2 0x104e3d870 in minishell minishell.c:118
    #3 0x104e3dea8 in main minishell.c:160
    #4 0x19249bf24  (<unknown module>)

0x000107902c19 is located 0 bytes to the right of 9-byte region [0x000107902c10,0x000107902c19)
allocated by thread T0 here:
    #0 0x1052bee68 in wrap_malloc+0x94 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x42e68) (BuildId: f0a7ac5c49bc3abc851181b6f92b308a32000000200000000100000000000b00)
    #1 0x104e386d0 in add_space parsing_in_pipe.c:111
    #2 0x104e39824 in parsing_in_pipe parsing_in_pipe.c:152
    #3 0x104e3d870 in minishell minishell.c:118
    #4 0x104e3dea8 in main minishell.c:160
    #5 0x19249bf24  (<unknown module>)

SUMMARY: AddressSanitizer: heap-buffer-overflow parsing_in_pipe.c:141 in add_space
==74140==ABORTING
[1]    74140 abort      ./minishell
```
