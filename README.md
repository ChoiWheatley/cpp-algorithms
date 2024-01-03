# cpp-algorithms

본 리포지토리는 https://github.com/ChoiWheatley/choi-workspace `ALGORITHMS` 폴더에서 작업중이던 파일들을 옮겨와 새로 만든 리포지토리입니다. 문제풀이의 편의를 위하여 각 폴더별로 별도로 정의된 CMakeLists.txt가 있어 빌드와 실행, 디버그 및 테스트 (GoogleTest)를 한 번에 수행할 수 있습니다.

## File structure

- `platform/`: 알고리즘 플랫폼
    - `build/`: 바이너리와 그 부산물이 저장되는 디렉토리
    - `useful/`: 자주 쓰는 함수나 매크로 모음
    - `**/main.cc`: main함수가 들어있는 cpp 파일 -> `build/bin/{dir}_app.out` 형식의 바이너리로 컴파일됨
    - `**/test.cc`: Google Test 코드가 들어있는 cpp 파일 -> `build/bin/{dir}_tests.out` 형식의 바이너리로 컴파일됨

## How to build?

```shell
cd {{platform}}
cmake -S . -B build
```
