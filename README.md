# minishell

## 05.25

### errno 처리중...
- g_signal_error 0이 아닐때 할당하는 번호
- -1 -> ‘“ 안닫혀있을때 && | 뒤에 아무것도 없을때 -> syntax error errno = 258
- -2 -> 아무것도 없이 ; or | 만 있을때
- 12 -> 말록 실패(할당안됨)
- 258 ->  file syntax error 에러 (newline, token…)
- 1 ->  not file error && heredoc 안에서 ctrl + c 
&& redirection 뒤 존재하지 않는 환경변수 또는 공백이 있는 환경변수가 올때 ambiguous redirect
- 130 -> cat 안에서 ctrl + c
- 131 -> cat 안에서 ctrl + \
- 127 -> command not found or No such file or directory
- 126 -> $HOME  /Users/dongeunk: is a directory - 이게 문제
- 127, 128 구분하는 것이 문제임
#### errno 추가
- 13 : 접근권한 거부
- 36 : 프로세스의 주소 공간 외부를 가리킬 때 발생
- 2 : 경로 이름이 너무 긴 경우
- 5 : 지정된 디렉토리가 존재하지 않거나, 심볼릭 링크가 중단된 디렉토리의 경우

### headerfile
- 전역변수 int g_signal_error 추가

### fd
- fd가 3부터가 아니라 이상하게 열리는 경우가 많음

## 05.27
### 빌트인 수정중...(g_signal_error)
- envp
	- shell 시작 후 `export | grep PWD` 할 경우 `OLDPWD` 또한 출력되어함.
	- 현재 main에서 envp로 받아올때, `export aaa` 이런 식으로 추가된 환경변수의 경우 탐지하지 못하는 것 같음. - 안되는게 맞음
	- 다른 맥에서도 체크해보기(보류)

### 환경변수 수정중...
- 환경변수 추가로 `export PATH=` 이후에 명령어 실행 시 `bash: cat: No such file or directory` -> 환경변수에 없는 경우 다시 로컬에서 찾아야함.
- ls $NOT_EXISTS . 했을 때 ls . 만 한거처럼 나와야 함.
- export PATH=  해서 PATH값을 비운 후에, cat, ls 같은거 했을 때 ‘No such file or directory’ 에러가 나와야 함.
- `unset PATH` 이후 명령어 실행 시 `bash: cat: No such file or directory` 나오게 해야함.
``` bash
nimishell$ unset PATH
nimishell$ cat
AddressSanitizer:DEADLYSIGNAL
=================================================================
==85334==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000104ccf43e bp 0x7ffeeaf50ee0 sp 0x7ffeeaf50e70 T0)
==85334==The signal is caused by a READ memory access.
==85334==Hint: address points to the zero page.
	#0 0x104ccf43e in find_path parsing_path.c:80
	#1 0x104ccc6a8 in save_in_node parsing_node.c:37
	#2 0x104ccb126 in parsing_in_pipe parsing_in_pipe.c:102
	#3 0x104cd1d3f in parsing_minishell minishell.c:35
	#4 0x104cd1f5a in parsing_check_errno minishell.c:44
	#5 0x104cd23f7 in minishell minishell.c:66
	#6 0x104cd27b9 in readline_minishell minishell.c:101
	#7 0x104cd2984 in main minishell.c:121
	#8 0x7fff67d11cc8 in start+0x0 (libdyld.dylib:x86_64+0x1acc8)
```
### 시그널 처리
- 아직 자식 프로세스에 못 넣었음 ㅠㅠ
- cat | cat | cat 했을 때 SIGINT 주면 한번에 다 종료되는거
- exit 88 | echo $? 했을 때 0 나오는지
- ./.  ./..  권한없음 등 execve 에러면 종료코드 126
- 없는 파일 실행하려고 한거면 종료코드 127 -정상작동
- 없는 $NOT_EXISTS 같은거 그냥 타이핑 했을 때 새로운 프롬프트 나와야 함. 이때, exit코드는 0이어야 함. -정상작동중
- echo hello > $NOT_EXISTS 같은거 했을때 ambiguous redirect 나와야 함. -> 이거 어떻게 할지?  -에러넘버는 우선 같음

### 기타
- 공백이 있는 환경 변수의 값을 인자로 넣었을 때, 해당 공백들이 인자 구분자가 되어야 함. (아래 예시 참고)
``` bash
$ export L1='hello'
$ export L2=' world'
$ ls $L1L2 ---> ls hello world
$ export LS='ls -l hello | cat < gogo.log'
$ $LS ---> "ls" "-l" "hello" "|" "cat" "<" "gogo.log"
```
- export GG=’           ls -l  ‘ 같은 식으로 공백이 포함된 값 대입 시, 공백이 포함된 채로 환경 변수에 들어가야 함. (env 등으로 확인)
- echo $GG 하면 공백들이 인자 구분자가 되지만, echo “$GG” 식으로 보간형식으로 들어갈 경우에는, 인자 구분자가 되지 않음.- echo ” ” ” | cat -e   해서, 공백 두개 나오는지.

### 완료
#### 01
- ~~exit ‘  3 ‘ 식으로 공백 들어갈 경우 에러 X~~
- ~~cmd[1] 검사 : `ft_split`으로 공백 자르고 갯수 하나인지 체크하기 -> 그리고 스플릿한 문자 `ft_stroll`에 넘겨주기~~
- ~~그리고 split~~
#### 02
- ~~exit 파이프랑 함께쓰일경우 exit 출력 X~~
- ~~오류메세지는 그대로 출력해야함~~

#### 03
- ~~cd 할 때 $PWD, $OLDPWD 설정 되는거~~
- ~~echo |, cat > 같이 문법 오류~~
- ~~> test echo hello world  했을때  echo hello world > test  한거랑 똑같은 결과~~
- ~~cp somefile $NOT_EXISTS 같은거 했을 때 cp usage가 나와야 함~~

#### 04
- ~~`cp /bin/cat ls`(현재 폴더에 cat을 ls 이름으로 복사) 이후 `ls` 실행 시 환경변수 경로의 `ls`가 실행되어야 함~~
- ~~복사한 ls(cat) 실행 원할 시 `./ls` 해야함~~
- ~~일단 먼저 환경변수 단을 찾고, 없으면 경로를 탐색하도록 해야할듯...~~

#### 05
- ~~`export`, `unset`, `exit` : 무조건 소문자로만 인식~~
- ~~`echo`, `cd`, `pwd`, `env` : 대문자, 소문자, 혼합 모두 인식~~