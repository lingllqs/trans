### 终端翻译工具

**结合[大佬的字典](https://github.com/skywind3000/ECDICT)**

### ecdict.csv文件字段格式

| 单词 | 音标     | 释义       | 译文        | pos | 柯林斯  | 牛津   | 标签 | bnc | 词频 | exchange | 详述   | 音频  |
|------|----------|------------|-------------|-----|---------|--------|------|-----|------|----------|--------|-------|
| word | phonetic | definition | translation | pos | collins | oxford | tag  | bnc | frq  | exchange | detail | audio |

### 使用方法

```bash
git clone https://github.com/lingllqs/trans
去这个仓库(https://github.com/skywind3000/ECDICT)下载ecdict.csv文件
cd trans
gcc -o trans ./src/main.c
运行`./trans <想要查询的单词>`
```
