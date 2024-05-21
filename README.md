# minishell

## 05.21

### errno 처리중
- g_errnum 0이 아닐때 할당하는 번호
- -1 -> ‘“ 안닫혀있을때 -> syntax error errno = 258
- 12 -> 말록 실패(할당안됨)
- 258~ ->  file syntax error 에러 (newline, token…)
- 1 ->  not file error
- 127 -> command not found

### singal 처리
- cat과 같은 명령어만 들어오고 단어를 받을때 ctrl + \ 하면 Quit 3이 나오고 끝내야함
- ctrl + c도 아직 완벽한 동작을 안하는 중

### headerfile
- 전역변수 int g_errnum 추가

### fd
- fd가 3부터가 아니라 이상하게 열리는 경우가 많음

