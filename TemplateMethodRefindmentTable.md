# Refinement Table — #1 Tower 서브클래스 중복 제거 Template Method 패턴 적용

> **대상**: `DesignRefinement.md` 1절 — Tower 서브클래스 중복 제거
> **핵심 변경**: `Tower::getTarget()` / `fire()` (2개 순수 가상 hook, 4개 서브클래스가 100% 동일 중복) → 제거 후 `Tower::update()`가 **Template Method**로 골격 일원화, 가변점은 `createProjectile()` 단 하나
> **선행 작업**: #3(타게팅 Strategy) 적용 완료 상태 기준 — 타겟 선정은 `selectTarget()`이 `ITargetingStrategy`에 위임

---

## 1. Before — 설계 Classifier

| Classifier | 종류 | 역할 |
|-----------|------|------|
| `Tower` | Concrete Class (추상 베이스) | 발사 사이클 골격(`update()`: 쿨다운 → 타겟 선정 → 발사) 보유. **가변 단계를 `getTarget()` / `fire()` 2개 순수 가상 함수로 분리** |
| `BasicTower` / `IceTower` / `SniperTower` / `ExplosionTower` | Concrete Subclass | `getTarget()` → `selectTarget(monsters)` 호출, `fire()` → `createProjectile(target)` 호출. **4개 서브클래스가 이 두 메서드를 글자 한 자 다르지 않게 중복 구현** |

**구조적 특징**
- `update()`는 골격을 갖되, 가변 단계가 **`getTarget` / `fire` / `createProjectile` 3단 hook**으로 과분할됨
- `getTarget`, `fire`는 사실상 다른 함수(`selectTarget`, `createProjectile`)로 **그대로 위임(pass-through)** 만 하는 빈 껍데기
- 결과적으로 **총 8개 메서드(4 서브클래스 × 2)** 가 의미 없는 중복 → 발사 흐름을 바꾸려면 4곳을 동시 수정
- 발사 경로에 가상 호출 3회(`getTarget` → 내부에서 `selectTarget`, `fire` → 내부에서 `createProjectile`)

```cpp
// BasicTower / IceTower / SniperTower / ExplosionTower 모두 동일
std::shared_ptr<Monster> XxxTower::getTarget(const std::vector<...>& monsters) const {
    return selectTarget(monsters);     // 4곳 동일
}
void XxxTower::fire(const std::shared_ptr<Monster>& target) {
    createProjectile(target);          // 4곳 동일
}
```

---

## 2. After — 설계 Classifier(s)

| Classifier | 종류 | 역할 |
|-----------|------|------|
| `Tower` | **Template Method 보유 베이스** | `update()`가 발사 알고리즘의 **불변 골격(template method)** 을 정의: 쿨다운 → `selectTarget()` → `createProjectile()` → 재충전. 단일 primitive hook만 노출 |
| `createProjectile()` | **Primitive Operation (hook)** | 서브클래스가 반드시 구현하는 유일한 가변점. "어떤 투사체를 만들지"만 책임 (사실상 **Factory Method** 성격) |
| `selectTarget()` | private 비가상 helper | `ITargetingStrategy`에 위임(#3 결과). protected→**private 강등** (서브클래스가 더 이상 호출하지 않음) |
| `BasicTower` / `IceTower` / `SniperTower` / `ExplosionTower` | Concrete Subclass | **생성자(스탯 설정) + `createProjectile()` 만 보유**. `getTarget` / `fire` 완전 제거 |

**구조적 특징**
- 발사 알고리즘의 골격이 `Tower::update()` **단 한 곳(Single Source of Truth)** 에 집중됨
- 가변점이 3단(`getTarget`/`fire`/`createProjectile`)에서 **1단(`createProjectile`)** 으로 축소
- 서브클래스는 "스탯과 투사체만 다른 4개 변형"이라는 본래 의도가 코드 구조에 그대로 드러남
- 발사 경로 가상 호출 3회 → 2회(`selectTarget` 내부 strategy 1회 + `createProjectile` 1회)

```cpp
// Tower.cpp — Template Method
void Tower::update() {
    fireCooldown -= Time::getDeltaTime();
    if (fireCooldown > 0.f || !monstersProvider) return;
    auto target = selectTarget(monstersProvider());   // 불변 단계 (strategy 위임)
    if (!target) return;
    createProjectile(target);                          // 가변 단계 (primitive hook)
    fireCooldown = 1.0f / description.fireRate;
}
```

---

## 3. 적용한 설계 개념

### Design Pattern (GoF)

- **Template Method Pattern (템플릿 메서드 패턴)**
  - 부모 클래스가 알고리즘의 **불변 골격**을 정의하고, 가변 단계만 primitive operation(hook)으로 서브클래스에 위임
  - 본 적용: `Tower::update()` = 템플릿 메서드(쿨다운·타겟선정·재충전의 불변 순서), `createProjectile()` = 유일한 primitive operation
- **보조 관찰 — Factory Method 성격 겸함**
  - 유일한 hook인 `createProjectile()`이 객체(Projectile)를 생성해 반환하므로, 이 hook은 동시에 **Factory Method**다. "골격은 Template Method, 그 안의 hook은 Factory Method"라는 전형적 합성 구조

### GRASP 원칙

| 강화되는 원칙 | 적용 양상 |
|-------------|---------|
| **High Cohesion (높은 응집도)** | 발사 사이클 로직이 `Tower::update()` 한 곳에 응집. 서브클래스는 "투사체 생성"이라는 단일 관심사만 보유 |
| **Polymorphism (다형성)** | 타워별 차이를 if/switch가 아닌 **단일 virtual hook(`createProjectile`)** 으로 처리. 신규 타워 추가 시 골격은 무수정 |
| **Protected Variations (보호된 변화)** | "어떤 투사체를 쏠지"라는 변화 지점을 `createProjectile` 인터페이스 뒤로 격리. 발사 골격은 이 변화로부터 보호됨 |
| **Don't Repeat Yourself (중복 제거)** | 동일한 pass-through 메서드 8개(`getTarget`/`fire` × 4)를 제거하여 중복을 0으로 축소 |

### SOLID 부수 효과

- **DRY**: 의미 없이 위임만 하던 `getTarget`/`fire` 8개 메서드 제거 → 중복 8 → 0
- **OCP (개방-폐쇄)**: 신규 타워 = `createProjectile()` 하나만 구현하면 됨. 발사 골격(`update()`)은 닫혀 있음(무수정)
- **SRP (단일 책임)**: `Tower` = 발사 사이클 제어, 서브클래스 = 투사체 종류 결정으로 책임이 분리됨
- **LSP (리스코프 치환)**: hook 계약이 `createProjectile` 하나로 명확해져, 모든 서브클래스가 동일 골격 하에서 안전하게 치환됨

---

## 4. Architecture Design Rationale (합리성)

### 각 Classifier의 시스템 내 역할

| Classifier | 시스템 내 역할 | 합리성 |
|-----------|-------------|------|
| `Tower::update()` (Template Method) | 모든 타워가 공유하는 **불변 발사 시퀀스 컨트롤러**. 쿨다운 감소·타겟 유무 가드·재충전 타이밍을 일괄 관리 | 발사 "절차"는 타워 종류와 무관하게 동일하다는 사실을 코드가 강제. 절차 변경(예: 쿨다운 정책, 다중 발사) 시 단 한 곳만 수정 |
| `createProjectile()` (Primitive Hook) | 타워 종류별로 **유일하게 달라지는 가변점** — Normal/Ice/Explosion 투사체와 속도·`monstersProvider` 전달 여부 결정 | 가변점을 단 하나로 좁혔기 때문에 "타워 간 차이"가 이 메서드 하나에 모두 응축됨. 신규 타워 추가 비용 = 메서드 1개 |
| `selectTarget()` (private helper) | 타겟 선정을 `ITargetingStrategy`(#3)에 위임하는 내부 단계 | Template Method 적용 후 서브클래스가 호출할 일이 없어 private로 강등 → 외부 노출 표면 최소화(캡슐화 강화) |
| Tower 서브클래스 | 타워별 외형·스탯·투사체 종류만 차별화 | `getTarget`/`fire` 제거로 "스탯과 투사체만 다른 4개 변형"이라는 본래 의도가 구조에 직접 드러남 |

### 왜 Template Method인가 (대안 대비)

- **현행 유지(`getTarget`/`fire` 보존)** → 의미 없는 pass-through 중복 8개가 영구히 남고, 발사 흐름 변경 시 4곳 동시 수정 필요. 명백한 열위
- **Strategy로 처리** → 투사체 생성 정책을 외부 전략 객체로 빼는 방식. 그러나 "어떤 투사체를 쏘는가"는 타워의 **정체성에 1:1로 종속**된 가변점이다(BasicTower는 항상 Normal 투사체). 타워 타입과 직교(orthogonal)하지 않으므로 별도 전략 축으로 분리할 동기가 없음 → 오히려 객체 수만 늘리는 **과설계(over-engineering)**
- **대조 — #3 타게팅은 왜 Strategy였나** → 타게팅 알고리즘은 "타워 4종 × 타게팅 N종" 처럼 **타워 타입과 직교**하는 축이라 Strategy가 적합했다. 반면 #1의 투사체 생성은 타워 타입에 종속된 단일 축이므로 **Template Method/Factory Method**가 정석. 두 패턴이 같은 클래스에서 서로 다른 가변 축에 올바르게 배치된 사례
- **결론**: 변화 축이 타워 타입과 1:1인 가변점은 서브클래스 오버라이드(Template Method)가 가장 단순하고 정확함

### Template Method가 주는 가치

발사 시퀀스 자체를 바꾸는 요구(예: "쿨다운 중에도 타겟을 미리 조준", "한 번에 2발 발사", "발사 전 사운드 트리거")가 생기면 `Tower::update()` **한 곳만** 수정하면 모든 타워에 일괄 반영된다. Before 구조에서는 골격이 서브클래스 hook들에 분산되어 이런 변경의 영향 반경이 넓었다.

---

## 5. NFR / QA 영향 분석

| NFR / QA 속성 | 영향 방향 | 분석 |
|--------------|---------|------|
| **Maintainability (유지보수성)** | ✅ **대폭 향상** | 동일 코드 8개 메서드 제거. 발사 흐름의 Single Source of Truth가 `update()` 한 곳으로 확정 → 변경 시 일관성 깨질 위험 소멸 |
| **Understandability (이해 용이성)** | ✅ **향상** | 서브클래스가 생성자 + `createProjectile` 하나로 축소되어 "타워별 차이 = 투사체뿐"이라는 의도가 한눈에 보임. 3단 hook → 1단 hook으로 호출 흐름 단순화 |
| **Modifiability (수정 용이성)** | ✅ **향상** | 발사 알고리즘 골격 변경의 영향 반경이 `update()` 단일 메서드로 한정됨 |
| **Extensibility (확장성)** | ✅ 향상 | 신규 타워 추가 비용 = 생성자 + `createProjectile` 1개. 발사 골격 무수정(OCP) |
| **Reliability (신뢰성)** | ➖ **중립** | 동작 변경 없는 순수 구조 리팩토링(중복 제거 + 위임 단계 축소). 타게팅·투사체 생성 로직은 그대로 보존 |
| **Performance (성능)** | ✅ **미세 개선** | 발사 경로의 가상 호출이 3회(`getTarget`+`fire`+`createProjectile`)에서 2회(`selectTarget` 내부 strategy + `createProjectile`)로 감소. 체감 불가 수준이나 방향은 개선 |
| **Memory (메모리)** | ➖ **중립** | 멤버·객체 추가 없음. vtable 엔트리 2종(`getTarget`/`fire`) 감소 |
| **Testability (테스트 용이성)** | ✅ 소폭 향상 | 검증해야 할 가변 동작이 `createProjectile` 하나로 좁혀짐 |
| **Coupling (결합도)** *(GRASP)* | ✅ 향상 | `selectTarget` private 강등으로 서브클래스→베이스 결합 표면 축소 |
| **Cohesion (응집도)** *(GRASP)* | ✅ 향상 | `Tower`는 발사 사이클, 서브클래스는 투사체 생성으로 책임이 깔끔히 분리 |

### 부정적 영향 요약

- 실질적 손실 거의 없음 — 의미 없는 중복을 걷어낸 순수 정리 작업
- 굳이 꼽자면: `createProjectile`이 private virtual hook이라 호출이 `update()` 내부에 감춰짐 → 호출 흐름을 처음 보는 사람은 "어디서 createProjectile이 불리는가"를 한 단계 따라가야 함(약한 indirection). 단, Template Method 패턴의 본질적 특성이며 IDE 환경에서 비용 미미

### 종합 평가

비용이 사실상 없는 **순편익(net positive)** 리팩토링. 중복 8개 메서드 제거로 유지보수성·이해 용이성이 명확히 개선되고, 성능·메모리·신뢰성은 중립 또는 미세 개선. 특히 선행한 #3(타게팅 Strategy)와 결합되어 `Tower::update()`가 "불변 골격 + 위임 단계(타게팅 Strategy) + primitive hook(투사체 Factory Method)"로 구성된 **완성형 Template Method**로 정리되었다 — Strategy와 Template Method가 같은 클래스에서 각자 적합한 가변 축을 담당하는 모범 사례.
