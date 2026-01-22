### 终端翻译工具

**结合[大佬的字典](https://github.com/skywind3000/ECDICT)**

### ecdict.csv文件字段格式

| 单词 | 音标     | 释义       | 译文        | pos | 柯林斯  | 牛津   | 标签 | bnc | 词频 | exchange | 详述   | 音频  |
|------|----------|------------|-------------|-----|---------|--------|------|-----|------|----------|--------|-------|
| word | phonetic | definition | translation | pos | collins | oxford | tag  | bnc | frq  | exchange | detail | audio |

### 使用方法

```bash
# 克隆本仓库
git clone https://github.com/lingllqs/trans

# 进入仓库目录
cd trans

# 下载字典文件
curl -fLo ./data/ecdict.csv https://raw.githubusercontent.com/skywind3000/ECDICT/refs/heads/master/ecdict.csv

# 编译
make

# 查询，也可以将二进制文件添加到环境变量(PATH)中
./trans <想要查询的单词>
```
