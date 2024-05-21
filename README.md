# minishell

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

#### echo (완)
- _echo with option -n_
- `-n -nnnn -nnnnnn` = `-n`
- `-n -ndf -nnnn` = 출력 `-ndf -nnnn`

#### pwd (완)
- _pwd with no options_
- 'print working directory'의 약자로 현재 작업 중인 디렉토리의 절대 경로를 반환

#### cd (진행중)
- _cd with only a relative or absolute path_
- 

#### exit (진행중)
- _exit with no options_


