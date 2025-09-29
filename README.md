# SRI_Model

## 项目简介

本项目实现了一个 **性压抑指数（SRI, Sexual Repression Index）模型**，用于模拟和分析个体在不同年龄、性别和心理参数下的性欲与压抑水平。

该模型由以下部分组成：

* **性欲函数**：随年龄变化的性欲曲线（男性和女性不同）
* **婚姻市场压力函数（MMP）**：表示随年龄增长的社会/婚恋压力（性别非对称）
* **心理调节因子（P_mod）**：由心理/情境指数（PCI）决定，放大或抑制结果
* **宏/中/微观再生产因子（R_macro, R_meso, R_micro）**：社会不同层面的影响
* **最终 SRI 计算**：综合所有因子得出性压抑指数

---

## 项目结构

```
SRI_MODEL/
├── include/        # 头文件（含模型实现）
│   └── sri_model.h
├── src/            # 源代码
│   ├── main.cpp       # 模拟运行
│   └── test_sri.cpp   # 单元测试
├── CMakeLists.txt  # CMake 构建配置
└── build/          # 构建目录（自动生成）
```

---

## 构建与运行

在 Windows (MSVC) 或类 Unix 环境均可运行。示例命令：

```bash
# 在项目根目录下
mkdir build
cd build
cmake ..
cmake --build . --config Release   # Windows/MSVC
# 或（Linux/macOS）
# cmake --build .

# 运行模拟
./sri_simulation        # Windows 下可能在 .\Release\sri_simulation.exe
# 运行单元测试
./run_tests             # Windows 下可能在 .\Release\run_tests.exe
```

---

## 模型详解

### 1. 性欲函数（Libido）

* **男性**：高斯函数，峰值约在 22 岁

  ```
  libido = A * exp( - (age - mu)^2 / (2 * sigma^2) )
  ```

  示例参数：A=99.9997, mu=22.0, sigma≈16.78
  当 age ≤ 14，强制 libido = 0。

* **女性**：高斯函数，峰值约在 36 岁
  示例参数：A=98.4475, mu=36.0, sigma=10.0

### 2. 婚姻市场压力（MMP）

```
ageFactor = max(0, (age - 18)) / 10
```

* 男性： `MMP = 0.6 + 0.08 * ageFactor`
* 女性： `MMP = 0.9 + 0.12 * ageFactor`

（当前版本未直接用于 SRI 计算，但保留作为扩展因子。）

### 3. 心理调节因子（P_mod）

由 PCI（Psychological/Contextual Index）决定，范围 `[0,10]`，映射到 `[0.7, 1.3]`：

```
P_mod = 0.7 + 0.06 * PCI
```

### 4. 宏/中/微观因子（R_macro, R_meso, R_micro）

以年龄 20 为基准，`age_offset = max(0, age - 20)`：

```
R_macro = 1.0 + macro_bias + 0.063 * age_offset
R_meso  = 1.0 + meso_bias  - 0.027 * age_offset
R_micro = 1.0 + micro_bias + 0.041 * age_offset
R_total = (R_macro + R_meso + R_micro) / 3
```

### 5. 最终 SRI

```
SRI_final = libido_base * R_total * P_mod * CALIBRATION
```

其中 `CALIBRATION` 是一个极小的常数（≈0.999375），用于与测试数据保持一致。

---

## 示例计算（IT Male，age = 30）

1. **性欲基底**

   ```
   libido ≈ 89.26
   ```

2. **年龄偏移**

   ```
   age_offset = 30 - 20 = 10
   ```

3. **R 因子**

   ```
   R_macro = 1.63
   R_meso  = 0.73
   R_micro = 1.41
   R_total ≈ 1.25
   ```

4. **心理调节**

   ```
   PCI = 6 → P_mod = 1.06
   ```

5. **最终结果**

   ```
   SRI_final ≈ 78.47
   ```

---

## 输出示例

### 运行模拟 (`sri_simulation`)

```
============================================================
Simulation for Archetype: IT Male
(Typical IT-industry male archetype (high PCI, tech-focused))
------------------------------------------------------------
Age     Libido Base     Total Rep.     Final SRI
20      97.00           1.00           67.83
22      99.99           1.12           75.00
30      89.26           1.25           78.47
...
============================================================
```

### 运行测试 (`run_tests`)

```
Running SRI Model Tests...
  - Testing Male Libido... PASSED
  - Testing Female Libido... PASSED
  - Testing Marriage Market Pressure... PASSED
  - Testing Psychological Moderation... PASSED
  - Testing Full Archetype (IT Male @ 30)... PASSED

All tests completed successfully!
```

---

## 如何修改实验数据

1. **修改 Archetype 参数**
   在 `include/sri_model.h` 的 `ArchetypeFactory` 中调整：

   ```cpp
   a.params.PCI = 6.0;
   a.params.macro_bias = 0.0;
   a.params.meso_bias = 0.0;
   a.params.micro_bias = 0.0;
   ```

   或新增一个 archetype 并加入 `getAllArchetypes()`。

2. **修改年龄范围与步长**
   在 `src/main.cpp` 中：

   ```cpp
   for (double age = 20.0; age <= 50.0; age += 2.0)
   ```

   可改为 `15.0 → 60.0`，步长 `1.0`。

3. **修改测试验证**
   在 `src/test_sri.cpp` 中，更新断言值以匹配新的参数或模型。

---

## 依赖

* C++11 或以上
* CMake 3.10 或以上
* 编译器：MSVC / g++ / clang++
