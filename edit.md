# 수정해야하는 것

### export
#### 01
- shell 시작 후 `export | grep PWD` 할 경우 `OLDPWD` 또한 출력되어함.
- 현재 main에서 envp로 받아올때, `export aaa` 이런 식으로 추가된 환경변수의 경우 탐지하지 못하는 것 같음.
- 다른 맥에서도 체크해보기(보류)

### exit
#### 01
- ~~exit ‘  3 ‘ 식으로 공백 들어갈 경우 에러 X~~
- ~~cmd[1] 검사 : `ft_split`으로 공백 자르고 갯수 하나인지 체크하기 -> 그리고 스플릿한 문자 `ft_stroll`에 넘겨주기~~
- ~~그리고 split~~
#### 02
- ~~exit 파이프랑 함께쓰일경우 exit 출력 X~~
- ~~오류메세지는 그대로 출력해야함~~


### 기타
#### 01
- `unset PATH` 이후 명령어 실행 시 `bash: cat: No such file or directory` 나오게 해야함. 현재 세그먼트 오류
#### 02
- `cp /bin/cat ls`(현재 폴더에 cat을 ls 이름으로 복사) 이후 `ls` 실행 시 환경변수 경로의 `ls`가 실행되어야함
- 복사한 ls(cat) 실행 원할 시 `./ls` 해야함
- 일단 먼저 환경변수 단을 찾고, 없으면 경로를 탐색하도록 해야할듯...
#### 03

cat | cat | cat 했을 때 SIGINT 주면 한번에 다 종료되는거

exit 88 | echo $? 했을 때 0 나오는지

./.  ./..  권한없음 등 execve 에러면 종료코드 126
없는 파일 실행하려고 한거면 종료코드 127

없는 $NOT_EXISTS 같은거 그냥 타이핑 했을 때 새로운 프롬프트 나와야 함. 이때, exit코드는 0이어야 함.

echo hello > $NOT_EXISTS 같은거 했을때 ambiguous redirect 나와야 함.

ls $NOT_EXISTS . 했을 때 ls . 만 한거처럼 나와야 함.

export PATH=  해서 PATH값을 비운 후에, cat, ls 같은거 했을 때 ‘No such file or directory’ 에러가 나와야 함.


PATH에서 커맨드를 실행할때, 실제 외부명령 이름과 입력 명령을 모두 lower한 다음 찾아내야함. (cAT, SorT 등등 다 인식)

echo, cd, pwd 등등 모든 빌트인 커맨드는 대소문자 구분을 해서, 소문자만 인식해야함. -> 빌트인 커맨드 들어오면 일단 소문자로 만들고 비교하기


공백이 있는 환경 변수의 값을 인자로 넣었을 때, 해당 공백들이 인자 구분자가 되어야 함. (아래 예시 참고)
$ export L1='hello'
$ export L2=' world'
$ ls $L1L2 ---> ls hello world
$ export LS='ls -l hello | cat < gogo.log'
$ $LS ---> "ls" "-l" "hello" "|" "cat" "<" "gogo.log"
export GG=’           ls -l  ‘ 같은 식으로 공백이 포함된 값 대입 시, 공백이 포함된 채로 환경 변수에 들어가야 함. (env 등으로 확인)
echo $GG 하면 공백들이 인자 구분자가 되지만, echo “$GG” 식으로 보간형식으로 들어갈 경우에는, 인자 구분자가 되지 않음.

echo ” ” ” | cat -e   해서, 공백 두개 나오는지.

#### 완료
- ~~cd 할 때 $PWD, $OLDPWD 설정 되는거~~
- ~~echo |, cat > 같이 문법 오류~~
- ~~> test echo hello world  했을때  echo hello world > test  한거랑 똑같은 결과~~
- ~~cp somefile $NOT_EXISTS 같은거 했을 때 cp usage가 나와야 함~~

### 해석불가
- env제외 모든 빌트인 커맨드는 PATH환경변수가 unset 되었을때, 대소문자 구분 하는거 (소문자만)


