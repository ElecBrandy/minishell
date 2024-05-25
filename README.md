# minishell

<<<<<<< HEAD
## 실행 부분

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

#### pwd (완)
- _pwd with no options_
- 'print working directory'의 약자로 현재 작업 중인 디렉토리의 절대 경로를 반환

#### cd (완)
- _cd with only a relative or absolute path_
- 인자가 여러개 들어와도 첫번째 인자만 처리
- 인자가 n개인 경우의 오류 -> 첫번째 인자의 메세지만 출력
- `cd` 동작 정리
/*
	ft_cd
	cd with only a relative or absolute path

	인자가 여러개 들어와도 첫번째 인자만 처리
	파싱부분에서 환경변수를 받아오지 못할 경우에 대하여..? 에러처리? 어떤 식으로 넘어오는지?
	unset HOME 한 후 cd $HOME 했을 때
	인자가 n개일때의 오류 -> 메세지상에서 무조건 첫번째 인자

	unset HOME 한 후 cd $HOME 했을 때 
	-> bash: cd: HOME not set

	unset PWD 한 후 cd $PWD 했을 때 //파싱?
	-> bash: cd: PWD not set

	케이스분류
	1. 'HOME'
	- cd $HOME : bash: cd: HOME not set // Error  ::: cd
	- cd : bash: cd: HOME not set ::: cd
	- cd ~ : 정상동작 ::: cd ~

	2. 'HOME='
	- cd $HOME : cd . 처럼 동작 ::: cd
	- cd : cd . 처럼 동작 ::: cd
	- cd ~ : 정상동작 ::: cd ~

	구분1 cd_withnoarg
	- cd $HOME : bash: cd: HOME not set // Error  ::: cd
	- cd : bash: cd: HOME not set ::: cd
	- cd $HOME : cd . 처럼 동작 ::: cd ("$HOME=")
	- cd : cd . 처럼 동작 ::: cd

	구분2 cd_witharg
*/ 

#### exit (완)
- _exit with no options_
- `exit` 동작 정리
	1. 첫번째 인자가 숫자가 아닌경우 
		- 에러메세지 : `minishell: exit: <str>: numeric argument required`
		- 프로세스 : `종료 O`
		- 리턴값 : `255`
	2. 첫번째 인자(number)가 long long 범위를 초과할 경우
		- 에러메세지 : `minishell: exit: <number>: numeric argument required`
		- 프로세스 : `종료 O`
		- 리턴값 : `255`
	3. 인자가 2개 이상인 경우
		- 에러메세지 : `minishell: exit: too many arguments`
		- 프로세스 : `종료 O`
		- 리턴값 : `1`
	4. 정상 동작할 경우
		- 출력 메세지 : `exit`
		- 프로세스 : `종료 O`
		- 리턴값 : `<number> % 256`

#### echo (진행 중)
- _echo with option -n_
- `-n -nnnn -nnnnnn` = `-n`
- `-n -ndf -nnnn` = 출력 `-ndf -nnnn`
- 백슬래시 처리? -> 그냥 무시해야하나
=======
## 05.24

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

### headerfile
- 전역변수 int g_signal_error 추가

### fd
- fd가 3부터가 아니라 이상하게 열리는 경우가 많음

>>>>>>> temp2
