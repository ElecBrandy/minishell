# minishell

- 검색으로 dongwook 하면 어디 고쳤는지 바로 알 수 있음!
- 그리고 바뀌기 전 부분 주석처리 해놨으니 되돌릴때 조금 편하실수도..
- SEG on ~ 이런식으로 커밋메세지가 뭔지 달아놓았읍니다. 혹시 되돌리실때 참고하시면될듯합니

## 05.11
### 1. SEGV on make_node()
일단 make랑 실행되는 것 까지 확인
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
### 2. SEGV on add_space(char *av)
- 파이프 유무, 리다이렉션 유무와 상관없이 add_space에서 아래 세그오류
  - 리다이렉션이 문자열에 없을 때 `str[u.idx] = '\0';` 여기서 오류
  - 리다이렉션이 문자열에 있을 때 `return (str);` 여기서 오류
- 수정
  - 일단 `cat a.txt > b.txt`와 같이 정상인 경우는 작동
  - 그런데 이제 `cat a.txt >b.txt` 처럼 add_space가 작동해야하는 경우 아직 오류 ㅠㅠ (아래 오류 로그 참조)
  - 로그 보니까 동적할당 한적 없는 곳에 접근하는 듯 것같아여

#### add_space 세그 오류 로그
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

#### add_space 세그 오류 로그
``` bash
=================================================================
==95243==ERROR: AddressSanitizer: attempting free on address which was not malloc()-ed: 0x000106e035f0 in thread T0
    #0 0x1047bafa4 in wrap_free+0x98 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x42fa4) (BuildId: f0a7ac5c49bc3abc851181b6f92b308a32000000200000000100000000000b00)
    #1 0x104331134 in ft_free ft_free.c:19
    #2 0x104332b60 in free_str parsing_free.c:51
    #3 0x104332e64 in free_str_three parsing_free.c:35
    #4 0x104339a30 in minishell minishell.c:115
    #5 0x104339df4 in main minishell.c:150
    #6 0x19249bf24  (<unknown module>)

0x000106e035f0 is located 16 bytes to the right of 16-byte region [0x000106e035d0,0x000106e035e0)
freed by thread T0 here:
    #0 0x1047bafa4 in wrap_free+0x98 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x42fa4) (BuildId: f0a7ac5c49bc3abc851181b6f92b308a32000000200000000100000000000b00)
    #1 0x10433a65c in ft_strtrim+0x1e0 (minishell:arm64+0x10000e65c) (BuildId: b7143f8bc9dc3a2aa274a24ecb8aa24332000000200000000100000000000d00)
    #2 0x10433188c in save_in parsing.c:31
    #3 0x104331f38 in split_flag parsing.c:55
    #4 0x1043323a0 in parsing parsing.c:76
    #5 0x1043392dc in minishell minishell.c:88
    #6 0x104339df4 in main minishell.c:150
    #7 0x19249bf24  (<unknown module>)

previously allocated by thread T0 here:
    #0 0x1047bae68 in wrap_malloc+0x94 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x42e68) (BuildId: f0a7ac5c49bc3abc851181b6f92b308a32000000200000000100000000000b00)
    #1 0x10433abe4 in ft_strldup+0x48 (minishell:arm64+0x10000ebe4) (BuildId: b7143f8bc9dc3a2aa274a24ecb8aa24332000000200000000100000000000d00)
    #2 0x104331878 in save_in parsing.c:30
    #3 0x104331f38 in split_flag parsing.c:55
    #4 0x1043323a0 in parsing parsing.c:76
    #5 0x1043392dc in minishell minishell.c:88
    #6 0x104339df4 in main minishell.c:150
    #7 0x19249bf24  (<unknown module>)

SUMMARY: AddressSanitizer: bad-free (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x42fa4) (BuildId: f0a7ac5c49bc3abc851181b6f92b308a32000000200000000100000000000b00) in wrap_free+0x98
==95243==ABORTING
[1]    95243 abort      ./minishell
```


### 3.
