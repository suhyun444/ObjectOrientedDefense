# Class Diagram 수정 사항 — #3 Strategy(타게팅) + #1 Template Method(Tower) + StrongestTargeting 신규 전략 반영

> **목적**: 기존 클래스 다이어그램을 현재 코드 상태에 정합시키기 위해, **수정해야 할 클래스와 수정 방법**을 정리한다.
> drawio를 직접 편집하기 전 참고용 변경 목록(체크리스트)이다.

---

## 0. 배경

기존 다이어그램(`ObjectOrientedDefense_ClassDiagram.drawio`, `ObjectOrientedDefense_Entity_ClassDiagram.drawio`,
워크트리 `classdiagram.md` 학습 노트)은 **#3·#1 적용 이전 상태**다.

현재 다이어그램의 Tower 모습:
- 메서드 `#findMostAdvancedTarget(): Monster*` 보유
- 순수가상 `getTarget()`, `fire()`, `createProjectile()` 3개
- `ITargetingStrategy` / `MostAdvancedTargeting` 클래스 **없음**

실제 코드는 이미 #3(타게팅 Strategy) → #1(Template Method) 순으로 적용 완료된 상태이고,
이후 **신규 타게팅 전략 `StrongestTargeting`(사거리 내 최대 체력 몬스터)이 추가되어 IceTower가 이를 사용**하도록
변경되었다. 아래 변경을 모두 반영해야 한다.

---

## 1. 수정해야 할 클래스 요약

| # | 클래스 | 구분 | 핵심 변경 |
|---|--------|------|----------|
| 1 | `Tower` | **수정** | `findMostAdvancedTarget`·`getTarget`·`fire` 제거, `targetingStrategy` 멤버 추가, `selectTarget`(private)·`setTargetingStrategy`(protected) 추가, hook은 `createProjectile`만 |
| 2 | `ITargetingStrategy` | **신규 (인터페이스)** | 타게팅 알고리즘 추상 계약 |
| 3 | `MostAdvancedTargeting` | **신규 (구현 클래스)** | 기존 findMostAdvanced 로직 이전. Tower 기본 전략 |
| 4 | `StrongestTargeting` | **신규 (구현 클래스)** | 사거리 내 최대 체력 몬스터 선택. IceTower가 사용 |
| 5 | `Monster` | **수정** | `getHealth(): int` getter 추가 (StrongestTargeting이 체력 비교에 사용) |
| 6 | `BasicTower` | **수정** | `getTarget`·`fire` override 제거 |
| 7 | `IceTower` | **수정** | `getTarget`·`fire` override 제거, 생성자에서 `StrongestTargeting` 주입 |
| 8 | `SniperTower` | **수정** | `getTarget`·`fire` override 제거 |
| 9 | `ExplosionTower` | **수정** | `getTarget`·`fire` override 제거 |

---

## 2. 클래스별 상세 수정 (Before → After)

### 2-1. `Tower` (추상 클래스) — 수정

**속성 구획**

| 변경 | 항목 |
|------|------|
| ➕ 추가 | `- targetingStrategy: unique_ptr<ITargetingStrategy>` |
| (유지) | `# description: TowerDescription`, `# level: int`, `# gridPosition: Vector2i`, `- alive: bool`, `- fireCooldown: float`, `+ monstersProvider: function` |

**메서드 구획**

| 변경 | 항목 |
|------|------|
| ➖ 제거 | `# findMostAdvancedTarget(): Monster*` |
| ➕ 추가 | `- selectTarget(monsters): Monster*` (private, `targetingStrategy`에 위임) |
| ➕ 추가 | `# setTargetingStrategy(s: unique_ptr<ITargetingStrategy>): void` (protected, 서브클래스가 전략 교체) |
| (유지) | `+ getDescription()`, `+ getLevel()`, `+ upgrade()`, `+ kill()`, `+ update()`, `+ render(window)` 등 |

**순수가상(추상 메서드) 구획**

| 변경 | 항목 |
|------|------|
| ➖ 제거 | `getTarget()` |
| ➖ 제거 | `fire()` |
| (유지) | `createProjectile(target): Projectile*` ← **유일하게 남는 hook** |

> 의미: `update()`가 "쿨다운 → `selectTarget()` → `createProjectile()` → 재충전" 골격을 직접 가진 **Template Method**가 됨.
> 타게팅은 `selectTarget()`이 합성된 `targetingStrategy`에 위임(#3), 투사체 생성만 서브클래스 hook(#1).

---

### 2-2. `ITargetingStrategy` — 신규 인터페이스

- **파일**: `ITargetingStrategy.h`
- **draw.io 스타일**: 🟢 인터페이스 (`fillColor=#d5e8d4;strokeColor=#82b366;` / `<<interface>>`)
- **순수가상 메서드**:
  - `+ selectTarget(origin: Vector2f, range: float, monsters: vector<shared_ptr<Monster>>): shared_ptr<Monster>`
- **설명**: 타게팅 알고리즘의 추상 계약. Tower 내부 상태에 의존하지 않고 `(origin, range, monsters)`만 입력으로 받음

---

### 2-3. `MostAdvancedTargeting` — 신규 구현 클래스

- **파일**: `MostAdvancedTargeting.h` / `.cpp`
- **draw.io 스타일**: 🔵 일반 클래스 (`fillColor=#dae8fc;strokeColor=#6c8ebf;`)
- **상속**: `ITargetingStrategy` 구현 (→ Realization)
- **메서드**:
  - `+ selectTarget(origin, range, monsters): shared_ptr<Monster>` (override) — 사거리 내 가장 앞선(waypointIndex 최대) 몬스터 선택
- **설명**: 기존 `Tower::findMostAdvancedTarget()` 로직을 그대로 이전한 기본 전략

---

### 2-4. `StrongestTargeting` — 신규 구현 클래스

- **파일**: `StrongestTargeting.h` / `.cpp`
- **draw.io 스타일**: 🔵 일반 클래스 (`fillColor=#dae8fc;strokeColor=#6c8ebf;`)
- **상속**: `ITargetingStrategy` 구현 (→ Realization)
- **메서드**:
  - `+ selectTarget(origin, range, monsters): shared_ptr<Monster>` (override) — 사거리 내 **체력이 가장 높은**(`getHealth()` 최대) 몬스터 선택 (동률은 먼저 발견된 몬스터)
- **설명**: IceTower가 생성자에서 주입해 사용하는 전략. `MostAdvancedTargeting`과 형제 관계(같은 인터페이스 구현)

---

### 2-5. `Monster` — 수정

- **메서드 구획**: `+ getHealth(): int` getter 추가
- **설명**: `StrongestTargeting`이 체력을 비교하기 위해 필요. 기존 박스의 나머지는 변경 없음.

---

### 2-6 ~ 2-9. `BasicTower` / `IceTower` / `SniperTower` / `ExplosionTower` — 수정

- **공통 변경**: `getTarget()`, `fire()` override **제거**. `createProjectile()` override만 유지.
- **`IceTower` 추가 변경**: 생성자에서 `setTargetingStrategy(std::make_unique<StrongestTargeting>())` 호출 → 기본 전략(MostAdvanced)을 StrongestTargeting으로 교체.
- 기존 다이어그램에서 이 4개 서브클래스는 메서드를 표기하지 않고 상속만 표시했다면 **박스 변경 없음**(IceTower의 전략 주입은 관계 엣지로 표현).
  메서드를 표기했었다면 `createProjectile()` 한 개만 남도록 정리.
- 상속 관계(`→ Tower`)는 변경 없음.

---

## 3. 관계(엣지) 변경

### ➕ 추가할 엣지

| 관계 | 표기 | draw.io style | 의미 |
|------|------|---------------|------|
| `MostAdvancedTargeting` → `ITargetingStrategy` | Realization (점선+빈삼각형) | `dashed=1;endArrow=block;endFill=0;` | 인터페이스 구현 |
| `StrongestTargeting` → `ITargetingStrategy` | Realization (점선+빈삼각형) | `dashed=1;endArrow=block;endFill=0;` | 인터페이스 구현 |
| `Tower` ◆→ `ITargetingStrategy` | Composition | `startArrow=diamondThin;startFill=1;endArrow=none;` | `unique_ptr` 단독 소유 멤버 |
| `ITargetingStrategy` ⇢ `Monster` | Dependency | `dashed=1;endArrow=open;` | `selectTarget` 파라미터/반환 |
| `MostAdvancedTargeting` ⇢ `Monster` | Dependency | `dashed=1;endArrow=open;` | 알고리즘 내부에서 Monster 조회 |
| `StrongestTargeting` ⇢ `Monster` | Dependency | `dashed=1;endArrow=open;` | `getHealth()`로 체력 비교 |
| `Tower` ⇢ `MostAdvancedTargeting` *(선택)* | Dependency | `dashed=1;endArrow=open;` | 생성자에서 기본 전략 주입(`make_unique`) |
| `IceTower` ⇢ `StrongestTargeting` | Dependency | `dashed=1;endArrow=open;` | 생성자에서 전략 주입(`make_unique`) |

### (유지) 변경 없는 엣지

- `Tower` → `GameObject` (Inheritance)
- `Tower` ◆→ `TowerDescription` (Composition)
- `Tower` ⇢ `Projectile` (Dependency, `createProjectile`)
- `BasicTower`/`IceTower`/`SniperTower`/`ExplosionTower` → `Tower` (Inheritance)

> **참고**: `Tower ◆→ ITargetingStrategy`(Composition) + `Tower ⇢ MostAdvancedTargeting`(Dependency)는
> "추상에 합성·의존하되 기본 구현 1개를 생성자에서 주입"하는 Strategy 패턴의 전형적 표기다.

---

## 4. 영향받는 다이어그램 파일

아래 파일 모두 위 변경을 반영해야 한다 (Tower 계층 포함):

- `ObjectOrientedDefense_Entity_ClassDiagram.drawio` — Tower 계층이 있는 엔티티 다이어그램. 클래스 박스 3개 추가(`ITargetingStrategy`/`MostAdvancedTargeting`/`StrongestTargeting`) + Tower·Monster 박스 갱신 + 엣지 추가
- `ObjectOrientedDefense_ClassDiagram.drawio` — 전체 통합 다이어그램. 동일 반영
- 워크트리 `classdiagram.md` 학습 노트:
  - **3-3 타워 계층**: Tower 속성/메서드/순수가상 갱신, `ITargetingStrategy`·`MostAdvancedTargeting`·`StrongestTargeting` 항목 신설
  - **3-4 몬스터**: Monster에 `getHealth()` 추가
  - **4 관계 요약표**: Realization에 `MostAdvancedTargeting → ITargetingStrategy`, `StrongestTargeting → ITargetingStrategy` 추가, Composition에 `Tower ◆→ ITargetingStrategy` 추가, Dependency에 `ITargetingStrategy ⇢ Monster`, `StrongestTargeting ⇢ Monster`, `IceTower ⇢ StrongestTargeting` 등 추가, 기존 `Tower ⇢ Projectile` 유지
  - **3-1 인터페이스**: `ITargetingStrategy` 추가
  - 클래스 총개수(40 → 43)·엣지 개수 갱신

---

## 5. 검증

- 위 Before/After가 실제 코드와 일치하는지 대조:
  - `src/Tower.h` — `targetingStrategy` 멤버, `selectTarget`(private), `setTargetingStrategy`(protected), 순수가상 `createProjectile`만 존재 확인
  - `src/ITargetingStrategy.h` — `selectTarget(origin, range, monsters)` 시그니처 확인
  - `src/MostAdvancedTargeting.h/.cpp` — `ITargetingStrategy` 구현 확인
  - `src/StrongestTargeting.h/.cpp` — `ITargetingStrategy` 구현, `getHealth()` 최대 선택 로직 확인
  - `src/Monster.h` — `getHealth()` getter 확인
  - `src/IceTower.cpp` — 생성자에서 `setTargetingStrategy(std::make_unique<StrongestTargeting>())` 호출 확인
  - `src/BasicTower.h` 외 3개 — `getTarget`/`fire` 부재, `createProjectile`만 override 확인
