# minishell

## 05.15
### ~~1. 의문의 엔터 (완)~~
- 미니쉘 진입 후 예를 들어 `cat a.txt`시 결과가 나온 히후 다시 nimishell$ 문구와 함께 명령어를 입력하려면 엔터를 한번 더 쳐야 진입이 가능했던 것
- 파이프가 없을 경우 자식 프로세서를 기다리지않고 부모프로세서가 먼저 시작해서 그런 경우 -> **`wait_process`를 통해서 자식 프로세서가 끝나는 것을 기다리고 실행되게 끔 수정**

### ~~2. 의문의 종료~~
- 파이프를 여러 개 사용했을시 결과 출력 후 바로 종료되는 문제
- `minishell.c`의 142줄 주석 처리 시 무한반복
- 아마도 위와 같은 문제로 예상됨 (readline 그 부분을 주석처리하면 무한 반복나옴) / 파이프로 연결이 안되있는 현상으로 매우 가능성이 높음
- **`fork_process` 종료 전 다음 명령어 실행을 위해 입출력 fd를 초기화해서 해결한듯?**

### 3. fd 설정?
- 자식 프로세스에서 `redirect_io(node->in_fd, node->out_fd);` 함수를 통해 노드의 입출력을 그대로 적용하고 있는데, 노드의 내용을 보니 0번 노드 이후로 in_fd와 out_fd 모두 1로 찍혀있는 듯
- 그래서 자식 프로세스에서 노드 입출력을 적용할 경우 통신이 끊겨 무한 로딩 나는 경우 발생
- 해당 함수 주석 처리하고, 리다이렉션 없는 경우 정상 동작

#### 예시
``` C
cat a.txt | cat a.txt | cat a.txt | cat a.txt | grep a
cat a.txt
cat a.txt
cat a.txt
cat a.txt
grep a
fork_cnt : 5
saf
asdf
asdf
safdsa

--- Node 0 ---
Node details:
Path: None
in_fd: 0, out_fd: 1
Commands:
  cmd[0]: cat
  cmd[1]: a.txt


--- Node 1 ---
Node details:
Path: None
in_fd: 1, out_fd: 1
Commands:
  cmd[0]: cat
  cmd[1]: a.txt


--- Node 2 ---
Node details:
Path: None
in_fd: 1, out_fd: 1
Commands:
  cmd[0]: cat
  cmd[1]: a.txt


--- Node 3 ---
Node details:
Path: None
in_fd: 1, out_fd: 1
Commands:
  cmd[0]: cat
  cmd[1]: a.txt


--- Node 4 ---
Node details:
Path: None
in_fd: 1, out_fd: 1
Commands:
  cmd[0]: grep
  cmd[1]: a
```
