# SRI_Model

## 项目简介

本项目实现了一个 **性压抑指数（SRI, Sexual Repression Index）模型**，用于模拟和分析个体在不同年龄、性别和心理参数下的性欲与压抑水平。

模型包括：

* 男性与女性的性欲函数
* 婚姻市场压力函数（MMP）
* 心理调节因子（P_mod）
* 综合 SRI 分解与计算

## 项目结构

```
SRI_MODEL/
├── include/        # 头文件
│   └── sri_model.h
├── src/            # 源代码
│   ├── main.cpp       # 模拟运行
│   └── test_sri.cpp   # 单元测试
├── CMakeLists.txt  # CMake 构建配置
```

## 构建与运行

1. 创建并进入构建目录：

   ```bash
   mkdir build
   cd build
   ```
2. 使用 CMake 构建：

   ```bash
   cmake ..
   cmake --build .
   ```
3. 执行可执行文件：

   * 运行模拟：

     ```bash
     ./sri_simulation
     ```
   * 运行单元测试：

     ```bash
     ./run_tests
     ```

## 输出示例

`sri_simulation` 将输出一个表格，展示某个 archetype 在 20~50 岁的性欲、总修正值和最终 SRI：

```
Age     Libido Base     Total Rep.     Final SRI
20      85.34           1.20           102.41
22      99.99           1.18           118.34
...
```

`run_tests` 将输出：

```
Running SRI Model Tests...
  - Testing Male Libido... PASSED
  - Testing Female Libido... PASSED
  - Testing Marriage Market Pressure... PASSED
  - Testing Psychological Moderation... PASSED
  - Testing Full Archetype (IT Male @ 30)... PASSED

All tests completed successfully!
```

## 依赖

* C++11 或以上
* CMake 3.10 或以上
