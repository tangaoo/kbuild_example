## kbuild example

`kbuild/kconfig` 是 Linux Kernel 的构建系统，且基于 GNU `Make/Makefile`系统。本项目主要把 `kbuild/kconfig` 构建系统从复杂的 Linux Kernel 中剥离出来给应用程序使用。

## 目录结构

kbuild/kconfig 部分：
* `configs/`， 自动生成的工程配置信息，方便查看。
* `Documentation/`， 文档，直接来至 Linux Kernel。
* `scripts/`， 实现 `kbuild/kconfig` 构建系统的主要脚步与工具。Makefile.* 文件提供构建系统解析 `kbuild makefile` 的规则。 
  * `scripts/kconfig/`，实现对工程中 kconfig 配置文件的解析和生成。
  * `scripts/basic/`，编译时，编译器会根据选项-MD自动生成依赖文件*.d，用fixdep更新*.d文件生成新的依赖文件.*.cmd。
* `Makefile`，顶层 Makefile，由 Make 调用。
* `Kconfig`，顶层配置文件。
项目源代码部分：
* `include/`，项目头文件。
* `lib/`，项目引用库。
* `src/`，项目源代码。

## 编译

```shell
make config    # 生成 ".config"
make           # 构建可执行文件
make help      # 查看编译帮助
```

## 如何使用

* 更改应用程序名

替换顶级 `Makefile` 里的 “example”，执行如下命令即可：
```shell
sed -i "s/example/yourname/g" `grep "example" -rl ./`
```
* 指定编译源码目录

在顶级 `Makefile` 文件里修改，本项目示例如下：
```shell
 objs-y          := src
 libs-y          := lib
```

在 `src` 每个子目录下生成 `builtin.o`， 在 `lib` 目录下生成 `lib.a` 文件，最后在链接成 `example` 文件。详细的子目录下 `Makefile` 和 `Kconfig` 编写规范见 Documentation 目录。

Kbuild/Kconfig 在 Linux 中的构建过程参考[这篇](https://tangaoo.github.io/2022/06/26/Kbuild/)。

