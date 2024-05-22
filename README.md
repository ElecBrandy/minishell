# minishell

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

### 빌트인 함수

#### env (완)
- _env with no options or arguments_
- env 리스트를 순회하며 `=` 이 존재하는 경우만 출력

#### export (완)
- _export with no options_
- 인자 없는 경우
    - `declare -x key=value` 식으로 env 리스트 전부 출력
    - `declare -x key=""` value가 NULL인 경우
    - `declare -x key` value가 없는 경우
- 인자 있는 경우
    - key, value 각각 유효성검사하고 env 리스트에 추가

#### unset (완)
- _unset with no options_
- 대상을 환경변수에서 삭제 (다중삭제도 가능)
- 중간에 이상한 인자가 들어와도 끝까지 동작 (경고문자 출력은 함)

#### echo (완)
- _echo with option -n_
- `-n -nnnn -nnnnnn` = `-n`
- `-n -ndf -nnnn` = 출력 `-ndf -nnnn`

#### pwd (완)
- _pwd with no options_
- 'print working directory'의 약자로 현재 작업 중인 디렉토리의 절대 경로를 반환

#### cd (진행중)
- _cd with only a relative or absolute path_ 

#### exit (진행중)
- _exit with no options_


