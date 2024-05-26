# minishell

## builtin function
2024.05.26

### env (완)
- _env with no options or arguments_
- bash 상 `env` 입력 시 대문자, 소문자, 대소문자 혼합 조합 모두 인식
- 환경변수 리스트를 순회하며 `=` 이 존재하는 경우만 출력

### export (완)
- _export with no options_
- bash 상 `export` 입력 시 오직 소문자 조합만 인식
- 인자 없는 경우
    - `declare -x key=value` 식으로 env 리스트 전부 출력
    - `declare -x key=""` value가 NULL인 경우
    - `declare -x key` value가 없는 경우
- 인자 있는 경우
    - key, value 각각 유효성 검사하고 env 리스트에 추가

### unset (완)
- _unset with no options_
- bash 상 `unset` 입력 시 오직 소문자 조합만 인식
- 대상을 환경변수에서 삭제 (다중삭제도 가능)
- 중간에 이상한 인자가 들어와도 끝까지 동작 (경고문자 출력은 함)

### pwd (완)
- _pwd with no options_
- bash 상 `pwd` 입력 시 대문자, 소문자, 대소문자 혼합 조합 모두 인식
- 'print working directory'의 약자로 현재 작업 중인 디렉토리의 절대 경로를 반환

#### cd (완)
- _cd with only a relative or absolute path_
- bash 상 `cd` 입력 시 대문자, 소문자, 대소문자 혼합 조합 모두 인식
- 인자가 여러개 들어와도 첫번째 인자만 처리
- 인자가 n개인 경우의 오류 -> 첫번째 인자의 메세지만 출력
- `unset HOME` 이후 `cd ~` 정상작동해야함
- `cd` 동작 정리
    - `cd`
    - `cd .`
    - `cd ~`
    - unset HOME 한 후 `cd $HOME` 했을 때 : `bash: cd: HOME not set`
    - unset PWD 한 후 `cd $PWD` 했을 때 :  `bash: cd: PWD not set`
    - 존재하지 않는 환경변수($AA), cd $AA 했을 때 : 그냥 cd 작동

	환경변수 별 케이스 분류
	1. 'HOME'
	- `cd $HOME`    했을 때 : `bash: cd: HOME not set` -> 작동은 `cd`
	- `cd`          했을 때 : `bash: cd: HOME not set` -> 작동은 `cd`
	- `cd ~`        했을 때 : 정상동작 -> 작동은 `cd $HOME` : (unset 이후 에도 작동해야함)

	2. 'HOME='
    - `cd $HOME`    했을 때 : 작동은 `cd .`
	- `cd`          했을 때 : 작동은 `cd .`
	- `cd ~`        했을 때 : 작동은 `cd $HOME` : (unset 이후 에도 작동해야함)

#### exit (완)
- _exit with no options_
- bash 상 `unset` 입력 시 오직 소문자 조합만 인식
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
- bash 상 `echo` 입력 시 대문자, 소문자, 대소문자 혼합 조합 모두 인식
- echo 옵션
    - `-n -nnnn -nnnnnn` = `-n`
    - `-n -ndf -nnnn` = 출력 `-ndf -nnnn`
- 백슬래시 처리???
