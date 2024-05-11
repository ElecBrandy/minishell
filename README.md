# minishell

### 05.11
일단 make랑 실행되는 것 까지 확인, 그런데 에러

``` bash
AddressSanitizer:DEADLYSIGNAL
=================================================================
==71180==ERROR: AddressSanitizer: SEGV on unknown address 0xffffb07020a18643 (pc 0x000104eff704 bp 0x00016af0ae50 sp 0x00016af0ad90 T0)
==71180==The signal is caused by a READ memory access.
    #0 0x104eff704 in make_node parsing_utils.c:53
    #1 0x104f01624 in minishell minishell.c:53
    #2 0x104f01eb4 in main minishell.c:118
```
