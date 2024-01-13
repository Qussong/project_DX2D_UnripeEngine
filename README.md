# project_DX2D_UnripeEngine
DirectX 2D Engine

**_24/01/09_** :<br>
&nbsp;&nbsp;- Unripe 엔진 초기화<br>
&nbsp;&nbsp;- type 재정의 (types.h)<br>
&nbsp;&nbsp;- Device, Context, SwapChain 분리 (CGraphics)<br>

**_24/01/10_** :<br>
&nbsp;&nbsp;- Time, Path, Key Manager 추가
&nbsp;&nbsp;- SimpleMath 라이브러리 추가

**_24/01/12_** :<br>
&nbsp;&nbsp;- PathMgr ) contentPath -> resourcePath, ShaderPath 변경 (Getter : GetResourcePath, GetShaderPath)<br>
&nbsp;&nbsp;- CEngine ) 사각형 출력 test 코드 추가<br>
&nbsp;&nbsp;&nbsp;&nbsp;<img src="./ReadMe/print_Rect.png" width=250><br>
&nbsp;&nbsp;- Debug 용 콘솔창 출력 코드 추가<br>
&nbsp;&nbsp;- main) 메모리 누수 체크 코드 추가<br>
&nbsp;&nbsp;- CEngine) 상수버퍼 생성코드 추가 및 쉐이더 코드에 바인딩<br>
&nbsp;&nbsp;- 좌,우 방향키로 Rectangle 위치 조정 코드 추가<br>

**_24/01/13_** :<br>
&nbsp;&nbsp;- CEntity 클래스 추가 ← 모든 객체의 기본 ( member : id, name )<br>
&nbsp;&nbsp;- CAsset 클래스 추가 ( ASSET_TYPE 열거형 추가 )<br>
&nbsp;&nbsp;- CMesh 클래스 추가 ( VB, IB 생성 및 세팅, DrawIndexed() )<br>
&nbsp;&nbsp;- CShader 클래스 추가<br>
&nbsp;&nbsp;- CGraphicShader 클래스 추가(VS, PS 생성 및 세팅)