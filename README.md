# miniRT
<div style="display: flex; justify-content: center; gap: 16px;">
  <img src="https://github.com/user-attachments/assets/00033fe7-b958-4528-b21f-28b425b40454" width="500" />
  <img src="https://github.com/user-attachments/assets/b7b8ecf1-fd5c-4552-bcdf-830f3452d28c" width="500" />
  <p><em>miniRT 렌더링 예시</em></p>
</div>
miniRT는 42Seoul의 그래픽스 프로젝트로, 간단한 Ray Tracing 렌더러를 구현하는 과제입니다. 본 프로젝트는 카메라, 광원, 기본적인 3D 객체(구, 평면, 원기둥, 원뿔 등)를 이용하여 장면을 해석하고 2D 이미지로 렌더링합니다.

## 🔧 기술 스택

- C (C99)
- MiniLibX (macOS 및 Linux 지원)
- Makefile
- XPM 텍스처 지원
- 벡터 및 행렬 연산 직접 구현
- Phong Reflection 모델
- Bump Mapping 및 텍스처 매핑

## 🖼️ 주요 기능

- `.rt` 포맷으로 작성된 장면 파일 파싱
- 카메라 시점에서의 광선 추적
- 각 객체별 교차점 계산
- 광원에 따른 조명 및 그림자 계산
- 다양한 텍스처 적용
- 실시간 마우스/키보드 인터랙션
- 다양한 장면 테스트 파일 제공 (`scenes/` 폴더 참고)

## 📁 디렉토리 구조
```
miniRT/
├── includes/          # 헤더 파일
├── libft/             # 기본 함수 구현
├── mlx_macbook/       # macOS용 MiniLibX
├── mlx_intel/         # Intel 기반 MiniLibX
├── mlx/               # 공통 MiniLibX
├── textures/          # 텍스처 이미지 파일
├── scenes/            # 테스트용 .rt 장면 파일
├── sources/           # 렌더링, 파싱, 이벤트 처리 등 핵심 로직
├── Makefile
```
## 🚀 실행 방법

```bash
# Clone repository
git clone https://github.com/nowead/miniRT.git
cd miniRT

# Build project
make

# Run with sample scene
./miniRT scenes/test.rt
```

## 📝 .rt 파일 예시
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
sp 0,0,20 20 255,0,0
pl 0,0,0 0,1,0 0,255,0
cy 50,0,20 0,0,1 14 30 0,0,255

A: Ambient light
C: Camera
L: Light
sp: Sphere
pl: Plane
cy: Cylinder
```
## 🎮 조작 방법 (Controls)
```
W / A / S / D : 카메라를 각각 앞 / 왼쪽 / 뒤 / 오른쪽으로 이동

Q / E : 카메라를 하강 / 상승

방향키 : 카메라 시점을 회전 (상/하/좌/우 방향대로)

ESC : 프로그램 종료
```
👨‍💻 기여자

- 민대원 (42Seoul - damin)
- 서성진 (42Seoul - seonseo)
