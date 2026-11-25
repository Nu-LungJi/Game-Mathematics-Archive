# 1단계 · 벡터와 공간기하

**도전 과제** · 마우스로 경사면을 클릭해 교점에 표식을 찍는다. 2D에서는 오른쪽이 +x, 위쪽이 +y이고 양의 각은 반시계 방향이다. 3D에서는 +y가 위이며 외적은 오른손 규칙을 따른다. 거리는 m, 시간은 초로 기록한다.

**학습 일정** · 주 6일, 하루 45-60분. 매주 1-2일은 손풀이, 3-4일은 구현, 5-6일은 실험과 검산에 쓴다. 구현 언어와 엔진은 자유다.

**게임 수학 - 1단계 (벡터, 삼각함수, 평면, 광선)**

[← 전체 과정, 결과물 미리보기](https://github.com/Nu-LungJi/Game-Mathematics-Archive/tree/Master)

## 주차별 목차

- [1주 · 벡터와 이동](#week-1)
- [2주 · 삼각함수와 각도](#week-2)
- [3주 · 내적·외적·투영](#week-3)
- [4주 · 직선·광선·선분](#week-4)
- [5주 · 평면의 방정식](#week-5)
- [6주 · 광선과 평면의 교점](#week-6)

<a id="week-1"></a>

## 1주 · 벡터와 이동

![한 걸음과 목표까지의 거리](./Image%20Archive/week-01.svg)

*같은 방향으로 가더라도 한 프레임의 이동량은 속력과 시간으로 정해진다.*

### 1일차 · 위치와 변위

A=(1,2), B=(4,6)을 모눈에 찍어라. A→B와 B→A를 화살표로 그리고 두 변위와 거리를 구하라.

**변위** : 시작 위치에서 최종 위치까지의 변화량을 나타내는 벡터.

**거리** : 얼마나 이동했는지를 나타내는 스칼라 값.
ex. A(0, 2), B(5, 8) - 변위 = (5, 6) / 거리 = $\sqrt{61}$

<details>
<summary>손풀이 검산</summary>

변위는 (3,4)와 (−3,−4), 거리는 양방향 모두 5다.

</details>

### 2일차 · 속도와 정규화

A에서 B로 초당 2m씩 간다. 단위 방향, 속도, 0.5초 뒤 위치를 차례로 계산하라.

<details>
<summary>손풀이 검산</summary>

(0.6,0.8), (1.2,1.6), (1.6,2.8).

</details>

### 3일차 · 목표 방향으로 한 걸음

| 입력 | 구현할 내용 |
| --- | --- |
| A=(1,2), B=(4,6), 한 걸음 1m | 목표 방향을 정규화해 한 걸음 이동하고 전후 위치를 표시한다. |

**통과 기준**

- ✅ 첫 호출 결과는 (1.6,2.8)이고 이동 거리는 1이다.

<details>
<summary>구현 결과</summary>
  
```cpp
struct Vector2D final {
    Vector2D() : X(0.f), Y(0.f) {}
    Vector2D(float x, float y) : X(x), Y(y) {}
    
    Vector2D operator-(const Vector2D& other) const {
        return {this->X - other.X, this->Y - other.Y};
    }
    Vector2D operator+(const Vector2D& other) const {
        return {this->X + other.X, this->Y + other.Y};
    }
    
    Vector2D operator*(const Vector2D& other) const {
        return {this->X * other.X, this->Y * other.Y};
    }
    Vector2D operator*(const float& param) const {
        return {this->X * param, this->Y * param};
    }
    
    Vector2D operator/(const Vector2D& other) const {
        return {this->X / other.X, this->Y / other.Y};
    }
    Vector2D operator/(const float& param) const {
        return {this->X / param, this->Y / param};
    }
    
    const float Get_Distance() { return std::sqrtf(X * X + Y * Y); }
    
    float X, Y;
};

Vector2D Displacement(Vector2D Start, Vector2D End, float Distance) {
    Vector2D Vector = End - Start;
    Vector2D UnitVec = Vector / Vector.Get_Distance();
    return Start + UnitVec * Distance;
}

int main() {
    float Distance = 1.f;
    Vector2D Result = Displacement({1.f, 2.f}, {4.f, 6.f}, Distance);
    std::cout << "CurPost : { " << Result.X << ", " << Result.Y << " }" << ", Dist : " << Distance << "m"; 
    return 0;
}
```
</details>

### 4일차 · 경과 시간 반영

| 입력 | 구현할 내용 |
| --- | --- |
| A=(1,2), B=(4,6), 속력 2m/s, dt=1 또는 0.25초 | 이동량에 경과 시간을 반영하고 총 1초를 두 방식으로 진행한다. |

**통과 기준**

- ✅ 두 실행 모두 (2.2,3.6)에 도달한다.

<details>
<summary>구현 결과</summary>
  
```cpp
Vector2D MoveTowards(Vector2D Start, Vector2D End, float Velocity, float dt) {
    Vector2D Vector = End - Start;
    Vector2D UnitVec = Vector / Vector.Get_Distance();
    
    return Start + UnitVec * Velocity * dt;
}

int main() {
    Vector2D Start = {1.f, 2.f}, End = {4.f, 6.f};
    float Speed = 2.f;
    float DT = 1.f;
    Vector2D Result = MoveTowards(Start, End, Speed, DT);
    std::cout << "CurPost : { " << Result.X << ", " << Result.Y << " }" << ", Speed : " << Speed << "m/s"
        << ", DeltaTime : " << DT << "\n"; 
    
    DT = 0.25f;
    Vector2D CurPos = Start;
    for (int i = 0; i < 4; ++i) {
        CurPos = MoveTowards(CurPos, End, Speed, DT);
        
        std::cout << "CurPost : { " << CurPos.X << ", " << CurPos.Y << " }" << ", Speed : " << Speed << "m/s"
            << ", DeltaTime : " << DT << "\n"; 
    }

    return 0;
}
```
</details>

### 5일차 · 목표가 멀어지면

| 입력 | 구현할 내용 |
| --- | --- |
| 시작 (1,2), 목표 (4,6) 또는 (7,10), 속력 2m/s, dt=0.5초 | 목표 거리만 바꾸고 첫 프레임에 실제로 이동한 거리를 출력한다. |

**통과 기준**

- ✅ 두 경우 모두 1m다.

<details>
<summary>구현 결과</summary>
  
```cpp
float MovementDistance(Vector2D Start, Vector2D End, float Velocity, float dt) {
    Vector2D Vector = End - Start;
    Vector2D UnitVec = Vector / Vector.Get_Distance();
    Vector2D Result = UnitVec * Velocity * dt;
    
    return Result.Get_Distance();
}

int main() {
    Vector2D Start = {1.f, 2.f}, End = {4.f, 6.f};
    float Speed = 2.f, DT = 0.5f;

    float Result = MovementDistance(Start, End, Speed, DT);
    std::cout << "Start : {" << Start.X << ", " << Start.Y << "}, " << "End : {" << End.X << ", " << End.Y << "}, "
        << "Distance : " << Result << "m\n";
    
    End = {7.f,10.f};
    
    Result = MovementDistance(Start, End, Speed, DT);
    std::cout << "Start : {" << Start.X << ", " << Start.Y << "}, " << "End : {" << End.X << ", " << End.Y << "}, "
        << "Distance : " << Result << "m\n";

    return 0;
}
```
</details>

### 6일차 · 도착 처리

| 입력 | 구현할 내용 |
| --- | --- |
| 시작 (0,0), 목표 (0.3,0.4), 속력 2m/s, dt=1초 | 남은 거리만큼만 전진한다. 도착 후 한 번 더 호출해 같은 점에 머무는지 확인한다. |

**통과 기준**

- ✅ 첫 호출에 정확히 도착하고 두 번째에도 같은 좌표다.
- ✅ 길이 0인 방향을 정규화할 필요가 없다.

<details>
<summary>구현 결과</summary>
  
```cpp
Vector2D MoveTowards(Vector2D Start, Vector2D End, float Velocity, float dt) {
    Vector2D Vector = End - Start;
    
    float Distance = Vector.Get_Distance();
    if (Distance == 0.f) return End;
    
    Vector2D UnitVec = Vector / Distance;
    float Movement = Velocity * dt;
    
    return Distance <= Movement ? End : Start + UnitVec * Movement;
}

int main() {
     Vector2D Start = {0.f, 0.f};
    Vector2D End = {0.3f, 0.4f};

    float Speed = 2.f;
    float DT = 1.f;

    Vector2D First = MoveTowards(Start, End, Speed, DT);
    Vector2D Second = MoveTowards(First, End, Speed, DT);

    return 0;
}
```
</details>

#### 이번 주 실험 기록

- **실행 화면** · 여기에 캡처를 붙이거나 실행 로그를 인용한다.
- **발견한 점** · 목표까지의 거리를 바꿨을 때 첫걸음은 어떻게 달라졌나?

<a id="week-2"></a>

## 2주 · 삼각함수와 각도

![0도를 지나는 회전](./Image%20Archive/week-02.svg)

*350°에서 10°로 갈 때 반시계 방향으로 20°만 돌면 된다.*

### 1일차 · 단위원 그리기

반지름 1인 원에 0°, 90°, 180°, 270°를 표시하고 각각 라디안과 좌표를 써라.

<details>
<summary>손풀이 검산</summary>

라디안은 0, π/2, π, 3π/2이고 좌표는 차례로 (1,0), (0,1), (−1,0), (0,−1)이다.

</details>

### 2일차 · 각도 복원

방향 (−1,1)과 (1,−1)의 각도를 구하라. y/x만 사용하면 두 방향을 구분할 수 있는지 설명하라.

<details>
<summary>손풀이 검산</summary>

135°와 −45°. 비율은 모두 −1이므로 두 성분의 부호를 보존하는 atan2(y,x)가 필요하다.

</details>

### 3일차 · 방향 화살표

| 입력 | 구현할 내용 |
| --- | --- |
| 각도 30°, 길이 2, 시작점 (0,0) | 각도를 삼각함수가 받는 단위로 바꾸고 끝점을 계산해 화살표를 그린다. |

**통과 기준**

- ✅ 끝점은 약 (1.732,1)이다.
- ✅ 삼각함수의 입력 단위를 확인하라.

<details>
<summary>구현 결과</summary>
  
```cpp
Vector2D Get_Coordinate(const float& Degree, const float& Length, Vector2D Start = {0.f, 0.f}) {
    float Radian = DegreeToRadian(Degree);
    return { Start.X + std::cosf(Radian) * Length, Start.Y + std::sinf(Radian) * Length };
}
int main() {
    constexpr float Angle = 30.f;
    constexpr float Length = 2.f;
    Vector2D StartPoint = { 1.f, 1.f };
    
    Vector2D Coord = Get_Coordinate(Angle, Length, StartPoint);
    std::cout << "Coordinate : { " << Coord.X << ", " << Coord.Y << " }" << '\n'; 
}
```
</details>

### 4일차 · 마우스 조준

| 입력 | 구현할 내용 |
| --- | --- |
| 포탑 (2,1), 목표 (2,4)와 (−1,1) | 목표와 포탑의 위치 차에서 조준 각도를 구해 포탑을 회전시킨다. |

**통과 기준**

- ✅ 각각 위쪽 90°, 왼쪽 180°를 가리킨다.
- ✅ −180°도 같은 방향이다.

<details>
<summary>구현 결과</summary>
  
```cpp
float Get_Degree(Vector2D Start, Vector2D Target) {
    Vector2D Direction = Target - Start;
    return RadianToDegree(std::atan2f(Direction.Y, Direction.X));
}
int main() {
    float StartDeg  = Get_Degree({2.f, 1.f}, {2.f, 4.f});
    float EndDeg    = Get_Degree({2.f, 1.f}, {-1.f, 1.f});
    
    std::cout << "Start Degree : " << StartDeg << ", End Degree : " << EndDeg << '\n';
    std::cout << "Rotation Result : " << EndDeg - StartDeg << '\n';
}
```
</details>

### 5일차 · 경계 각도

| 입력 | 구현할 내용 |
| --- | --- |
| 현재→목표 각도 350°→10°, 10°→350°, 0°→180° | 현재 자세에서 목표까지의 부호 있는 최단 회전량을 반환한다. 반 바퀴일 때의 규칙도 정한다. |

**통과 기준**

- ✅ 각각 +20°, −20°다.
- ✅ 정확히 180° 차이일 때 어느 쪽을 택할지도 정하라.

<details>
<summary>구현 결과</summary>
  
```cpp
float Get_MinimumDegree(Vector2D Vec1, Vector2D Vec2) {
    float Diff = RadianToDegree(std::atan2f(Vec2.Y, Vec2.X)) - RadianToDegree(std::atan2f(Vec1.Y, Vec1.X));
    if (Diff > 180.f) Diff -= 360.f;
    else if (Diff <= -180.f) Diff += 360.f;
    
    return Diff;
}
int main() {
    {
        Vector2D Start  = Get_Coordinate(-10, 1, {0.f, 0.f});
        Vector2D End    = Get_Coordinate(10, 1, {0.f, 0.f});
        
        std::cout << "Start : { " << Start.X << ", " << Start.Y << " }" << ", End : { " << End.X << ", " << End.Y << " }" << '\n';
        std::cout << "Rotation Result : " << Get_MinimumDegree(Start, End) << '\n';
    }
    {
        Vector2D Start  = Get_Coordinate(10, 1, {0.f, 0.f});
        Vector2D End    = Get_Coordinate(350, 1, {0.f, 0.f});
        
        std::cout << "Start : { " << Start.X << ", " << Start.Y << " }" << ", End : { " << End.X << ", " << End.Y << " }" << '\n';
        std::cout << "Rotation Result : " << Get_MinimumDegree(Start, End) << '\n';
    }
}
```
</details>

### 6일차 · 회전 속도 제한

| 입력 | 구현할 내용 |
| --- | --- |
| 시작 350°, 목표 10°, 각속도 상한 60°/s, dt=0.1초 | 네 프레임 동안 최단 방향으로 회전하며 프레임별 각도를 출력한다. |

**통과 기준**

- ✅ [0°,360°) 표기로 356°, 2°, 8°, 10°다.
- ✅ 마지막에 목표를 지나치지 않는다.

<details>
<summary>구현 결과</summary>
  
```cpp
float Normalize_Degree(float Degree) {
    Degree = std::fmod(Degree, 360.f);
    if (Degree < 0.f) Degree += 360.f;

    return Degree;
}
int main() {
    int FrameCount = 4;
        
    float StartAngle = 350.f, EndAngel = 10.f;
        
    Vector2D Start  = Get_Coordinate(StartAngle, 1);
    Vector2D End    = Get_Coordinate(EndAngel, 1);
        
    float MaxMovementAmount = Get_MinimumDegree(Start, End);
    bool isPositive = MaxMovementAmount >= 0.f;
    float CurMovementAmount = 0.f;
        
    constexpr float SpeedAngle = 60.f;
    constexpr float DeltaTime = 0.1f;
        
    float DeltaAngle = SpeedAngle * DeltaTime * (isPositive ? 1.f : -1.f);
            
    while (FrameCount--) {
      CurMovementAmount += DeltaAngle;
      if ((isPositive && CurMovementAmount > MaxMovementAmount) || (!isPositive && CurMovementAmount < MaxMovementAmount)) 
         CurMovementAmount = MaxMovementAmount;
            
      float Result = StartAngle + CurMovementAmount; 
      Result = Normalize_Degree(Result);
      std::cout << Result << " ";
    }
}
```
</details>

#### 이번 주 실험 기록

- **실행 화면** · 여기에 캡처를 붙이거나 실행 로그를 인용한다.
- **발견한 점** · 각도가 0°를 지나는 프레임에서 무엇을 확인했나?

#### Extra : 수학적 설명

<table><tr><td width="90%">
Q. 왜 최단 회전량을 -180° ~ +180° 범위로 제한하는지 수학적으로 설명.<br>
A. 두 목표(Edge)가 이루는 각이 -180°보다 더 작아지거나 +180°보다 더 커지는 경우, <br>
  반대 방향의 각도가 더 작기에 반대 방향으로 회전하는 것이 더 짧은 회전 경로가 된다. <br>
  그렇기에 -180°보다 더 작은 경우, 360°를 더하거나, +180°보다 큰 경우, 360°를 빼는 과정을 통해, <br>
  회전 방향의 부호는 유지하면서, 회전량을 -180° ~ +180° 범위로 보정하여 최단 회전량을 구할 수 있게 된다.
</td></tr></table>

<a id="week-3"></a>

## 3주 · 내적·외적·투영

![속도를 두 성분으로 분해](./Image%20Archive/week-03.svg)

*속도 (−3,4)에서 벽 쪽 성분을 제거하면 벽을 따라 움직인다.*

### 1일차 · 시야 판정

정면 (1,0), 전체 시야각 90°인 적이 있다. 방향 (1,1), (0,1), (−2,0)을 정규화하고 정면과 내적하라. 경계도 보인다고 가정하라.

<details>
<summary>손풀이 검산</summary>

내적은 약 0.707, 0, −1이다. cos(45°) 이상인 첫 대상만 보인다.

</details>

### 2일차 · 속도 분해

벽 법선 n=(1,0), 속도 v=(−3,4)를 그리고 법선 방향 성분과 접선 방향 성분을 구하라.

<details>
<summary>손풀이 검산</summary>

법선 성분 (−3,0), 접선 성분 (0,4). 둘을 더하면 원래 속도다.

</details>

### 3일차 · 시야 표시기

| 입력 | 구현할 내용 |
| --- | --- |
| 관찰자 (0,0), 정면 (1,0), 전체 시야각 90°, 목표 (1,1)과 (10,10) | 내적으로 시야를 판정하고 보이는 대상은 초록, 나머지는 회색으로 표시한다. 시야 경계를 포함한다. |

**통과 기준**

- [ ] 거리 제한이 없다면 둘 다 초록이다.
- [ ] 경계 비교에는 작은 수치 오차를 허용한다.

### 4일차 · 삼각형 법선

| 입력 | 구현할 내용 |
| --- | --- |
| A=(0,0,0), B=(1,0,0), C=(0,0,1) | 두 모서리 B−A와 C−A의 외적을 구해 삼각형 중심에서 법선을 그린다. |

**통과 기준**

- [ ] 화살표는 (0,−1,0) 방향이며 삼각형 바닥에 수직이다.

### 5일차 · 꼭짓점 순서

| 입력 | 구현할 내용 |
| --- | --- |
| 직전 삼각형의 꼭짓점 순서 ABC와 ACB | 두 순서에서 얻은 단위 법선을 함께 그리고 그 내적을 출력한다. |

**통과 기준**

- [ ] 법선이 반대로 뒤집힌다.
- [ ] 단위 법선끼리의 내적은 −1이다.

### 6일차 · 벽을 따라 이동

| 입력 | 구현할 내용 |
| --- | --- |
| 접촉 중인 벽의 바깥 법선 (1,0), 속도 (−3,4)와 (3,4) | 벽으로 파고드는 경우에만 속도에서 법선 성분을 제거한다. |

**통과 기준**

- [ ] 입력 속도 (−3,4)는 (0,4), 벽에서 멀어지는 (3,4)는 그대로 (3,4)다.

#### 이번 주 실험 기록

- **실행 화면** · 여기에 캡처를 붙이거나 실행 로그를 인용한다.
- **발견한 점** · 속도에서 어떤 성분을 제거했나?

<a id="week-4"></a>

## 4주 · 직선·광선·선분

![직선과 선분의 최근접점](./Image%20Archive/week-04.svg)

*직선에 내린 발이 선분 밖이면 가까운 끝점 B를 선택한다.*

### 1일차 · 매개변수의 범위

A=(0,2), D=(1,−1)에서 P=A+tD를 그려라. P의 y가 0인 t를 구하고 직선, 광선, A→A+D 선분에 포함되는지 판정하라.

<details>
<summary>손풀이 검산</summary>

t=2, P=(2,0). 직선과 광선에만 포함된다.

</details>

### 2일차 · 수선의 발

A=(0,0), B=(4,0), Q=(3,2)일 때 Q를 직선 AB에 투영하라. P=A+t(B−A)에서 t와 최단거리는?

<details>
<summary>손풀이 검산</summary>

t=0.75, P=(3,0), 거리 2.

</details>

### 3일차 · 매개변수 시각화

| 입력 | 구현할 내용 |
| --- | --- |
| A=(0,2), D=(1,−1), t=−1, 0, 1, 2 | 슬라이더나 콘솔 입력으로 t를 바꿔 점 A+tD를 표시한다. |

**통과 기준**

- [ ] (−1,3), (0,2), (1,1), (2,0) 순서다.

### 4일차 · 선분 최근접점

| 입력 | 구현할 내용 |
| --- | --- |
| A=(0,0), B=(4,0), Q=(3,2). 별도 검사 A=B=(1,1) | 투영 매개변수를 [0,1]로 제한해 선분의 최근접점을 반환하고 길이가 0인 선분도 처리한다. |

**통과 기준**

- [ ] 둘째 날 입력은 (3,0), A=B=(1,1)이면 Q와 관계없이 (1,1)이다.

### 5일차 · 양 끝 검산

| 입력 | 구현할 내용 |
| --- | --- |
| 선분 (0,0)→(4,0), Q=(−2,1), (6,1), (2,1) | 각 Q에서 최근접점으로 선을 긋고 세 결과를 비교한다. |

**통과 기준**

- [ ] 최근접점은 왼쪽 끝, 오른쪽 끝, 내부의 (2,0) 순서다.

### 6일차 · 레이저 피격

| 입력 | 구현할 내용 |
| --- | --- |
| 레이저 (0,0)→(4,0), 캐릭터 반지름 1, 중심 (4,1) 또는 (5,1) | 중심에서 레이저 선분까지의 거리로 접촉을 포함한 피격 여부를 표시한다. |

**통과 기준**

- [ ] 중심 (4,1)은 피격, (5,1)은 거리 √2라서 안전하다.

#### 이번 주 실험 기록

- **실행 화면** · 여기에 캡처를 붙이거나 실행 로그를 인용한다.
- **발견한 점** · 최근접점이 선분 끝에 고정되는 입력은 무엇이었나?

<a id="week-5"></a>

## 5주 · 평면의 방정식

![높이 차와 최단거리](./Image%20Archive/week-05.svg)

*점 (2,3,0)에서 경사면까지 내린 두 선 중 법선과 나란한 선이 더 짧다.*

### 1일차 · 한 점과 법선

점 A=(0,1,0)을 지나고 n=(−1,1,0)에 수직인 평면을 그려라. 평면 위 점 P에 대해 n·(P−A)를 전개하라.

<details>
<summary>손풀이 검산</summary>

−x+y−1=0. (2,3,0)을 대입하면 0이다.

</details>

### 2일차 · 세 점으로 만들기

A=(0,0,0), B=(0,0,2), C=(2,2,0)으로부터 외적으로 법선을 구하고 평면식을 써라. 세 점이 일직선이면 무엇이 달라지는가?

<details>
<summary>손풀이 검산</summary>

법선 (−4,4,0), 평면 y=x. 일직선이면 외적이 0이라 평면 하나를 결정할 수 없다.

</details>

### 3일차 · 경사면 그리기

| 입력 | 구현할 내용 |
| --- | --- |
| A=(0,0,0), B=(0,0,2), C=(2,2,0). 별도 검사 C=(0,0,4) | 삼각형과 중심의 단위 법선을 그린다. 일직선인 입력에는 실패 상태를 반환한다. |

**통과 기준**

- [ ] 법선은 약 (−0.707,0.707,0)이다.
- [ ] 세 꼭짓점 모두 평면식의 값이 0이다.

### 4일차 · 부호 있는 거리

| 입력 | 구현할 내용 |
| --- | --- |
| 평면 y−x=0, 점 (2,3,0), (2,1,0), (2,2,0) | 평면 계수와 점을 받아 부호 있는 거리를 출력한다. |

**통과 기준**

- [ ] 차례로 약 +0.707, −0.707, 0이다.

### 5일차 · 높이와 거리

| 입력 | 구현할 내용 |
| --- | --- |
| 평면 y=x, P=(2,3,0) | 수직 아래로 그은 선과 법선 방향 최단선을 다른 색으로 그리고 끝점·길이를 표시한다. |

**통과 기준**

- [ ] 아래쪽 끝점은 (2,2,0), 최단선 끝점은 (2.5,2.5,0). 길이는 1과 약 0.707이다.

### 6일차 · 법선 배율

| 입력 | 구현할 내용 |
| --- | --- |
| 평면 계수 (−1,1,0,−1), P=(0,3,0), 계수 배율 1, 2, −1 | 계수 전체를 같은 수로 곱한 뒤 부호 있는 거리를 비교한다. |

**통과 기준**

- [ ] 양의 배율에서는 +√2로 같고 음의 배율에서는 −√2로 부호만 뒤집힌다.

#### 이번 주 실험 기록

- **실행 화면** · 여기에 캡처를 붙이거나 실행 로그를 인용한다.
- **발견한 점** · 두 거리 중 어느 값으로 구의 접촉을 판정했나?

<a id="week-6"></a>

## 6주 · 광선과 평면의 교점

![클릭 광선과 경사면](./Image%20Archive/week-06.svg)

*카메라에서 나온 광선이 경사면과 만난 월드 좌표에 표식을 찍는다.*

### 1일차 · 교점 유도

평면 n·P+d=0에 P=O+tD를 대입해 t를 풀어라. O=(0,3,0), D=(1,−1,0), 평면 y=x로 검산하라.

<details>
<summary>손풀이 검산</summary>

t=−(n·O+d)/(n·D). 예시에서는 t=1.5, 교점 (1.5,1.5,0)이다.

</details>

### 2일차 · 교점의 종류

평면 y=0, O=(0,2,0)에서 오른쪽, 위쪽, 아래쪽으로 쏠 때 결과를 예상하라. O가 평면 위이고 방향이 수평이면?

<details>
<summary>손풀이 검산</summary>

차례로 평행, 뒤쪽 교차, 전방 명중이다. 마지막은 광선 전체가 평면에 놓여 교점이 무수히 많다.

</details>

### 3일차 · 교차 함수

| 입력 | 구현할 내용 |
| --- | --- |
| O=(0,3,0), D=(1,−1,0), 평면 y=x. 추가로 −D와 평면에 평행한 방향도 검사 | 명중 여부·t·교점을 반환한다. 평행 판정에 벡터 길이를 고려하고 광선 전체가 평면에 놓이면 별도 상태로 구분한다. |

**통과 기준**

- [ ] 첫날 입력에서 방향을 그대로 썼다면 t=1.5다.
- [ ] 방향을 정규화했다면 t=1.5√2이지만 교점은 같다.
- [ ] −D는 뒤쪽 교차로, 평면에 놓인 광선은 별도 상태로 판정한다.

### 4일차 · 클릭 표식

| 입력 | 구현할 내용 |
| --- | --- |
| 카메라, 클릭 픽셀, 무한 경사면 y=x | 엔진으로 클릭 광선을 만들고 어제의 함수로 교점을 구한다. 명중한 곳에만 표식을 그린다. |

**통과 기준**

- [ ] 클릭을 옮기면 표식이 경사면을 따라가며, 표식 좌표에서 y−x가 거의 0이다.

### 5일차 · 카메라 실험

| 입력 | 구현할 내용 |
| --- | --- |
| 같은 경사면을 보는 두 카메라 각도, 평면 밖에서 출발하는 평행 광선 | 각 시점에서 클릭한 뒤 광선과 표식을 함께 그린다. 평행 광선은 직접 주입한다. |

**통과 기준**

- [ ] 두 시점 모두 표식이 광선 위에 놓인다.
- [ ] 평행하고 평면 밖인 광선에서는 표식이 숨는다.

### 6일차 · 단계 과제 검산

| 입력 | 구현할 내용 |
| --- | --- |
| O=(0,3,0), D=(1,−1,0), y=x 및 새 카메라에서 얻은 명중 예제 한 개 | O,D,t,P를 기록하고 광선식과 평면식 양쪽에 대입해 오차를 출력한다. |

**통과 기준**

- [ ] 명중한 두 예제 모두 t≥0, O+tD≈P, n·P+d≈0을 만족한다.
- [ ] t를 계산할 때 방향 D를 정규화했는지 기록한다.

#### 이번 주 실험 기록

- **실행 화면** · 여기에 캡처를 붙이거나 실행 로그를 인용한다.
- **발견한 점** · 교점을 두 식에 대입했을 때 오차는 얼마였나?
