# minishell

## 05.24

### errno 처리중...
- g_signal_error 0이 아닐때 할당하는 번호
- -1 -> ‘“ 안닫혀있을때 && | 뒤에 아무것도 없을때 -> syntax error errno = 258
- -2 -> 아무것도 없이 ; or | 만 있을때
- 12 -> 말록 실패(할당안됨)
- 258 ->  file syntax error 에러 (newline, token…)
- 1 ->  not file error && heredoc 안에서 ctrl + c 
&& redirection 뒤 존재하지 않는 환경변수 또는 공백이 있는 환경변수가 올때 ambiguous redirect
- 127 -> command not found
- 130 -> cat 안에서 ctrl + c
- 131 -> cat 안에서 ctrl + \
- 126 -> $HOME  /Users/dongeunk: is a directory - 이게 문제

### heredoc 처리
- ctrl + c가 bash와 같은 동작을 하지 않음
- fork하여 자식프로세서에서 진행중
- readline말고 gnl을 활용할 가능성이 있어 gnl추가

### headerfile
- 전역변수 int g_signal_error 추가

### fd
- fd가 3부터가 아니라 이상하게 열리는 경우가 많음

