# minishell

## 05.17

### libft 수정
- ft_strjoin free(s1)제거

### Makefile 수정
- c파일 추가

### parsing 수정
- '$'표시부분 환경변수로 치환완료 ('$'?는 어떤식으로 해야할지 생각, $$도 미정)
- 주석을 제외한 모든 부분 norm검사 통과
- node->path 추가(빌트인 함수를 제외하고 path가 없으면 에러처리로 할 예정)

### headerfile
- 전역변수 int g_errnum 추가

### main file
- 주석 처리를 제외한 부분 norm 통과를 위해 함수 분할
- errornum 작업중 / command not found와 몇몇 에러 출력은 stderror, perror로는 안됨(직접 출력해야하는듯함)

### 3. fd 설정
- head free 할때 node안에 있는 in,out fd 모두 close
- cat << a heredoc이 안읽힘 , fd가 3부터 시작을 안하는 경우?????

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

#### echo (진행 중)
- _echo with option -n_
- `-n -nnnn -nnnnnn` = `-n`
- `-n -ndf -nnnn` = 출력 `-ndf -nnnn`
- 백슬래시 처리? -> 그냥 무시해야하나

#### cd (진행중)
- _cd with only a relative or absolute path_

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

#### exit (진행중)
- _exit with no options_


