# Maxwell's Dino
## 一、平台与环境
1. `dino0.exe`可以直接在 **Windows** 下运行（无需配置环境）;
2. `Dino.exe`需要配置环境后才能运行，且必须与 **picture** 在同一个目录下才能运行；
3. 关于环境: 需要配置好`SDL2`+`SDL2_image`+`SDL2_ttf`的环境;
4. 命令行编译: `gcc .\main.c -o Dino -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf`;
5. 使用 **Clion** 需要注意将 **工作目录** 改为该文件的绝对路径. ~~关于其他IDE我要不知道需要注意些啥QAQ~~
## 二、游戏操作
1. 打开游戏, 可以点击 **PLAY** 或者按 **回车** 或 **空格** 开始, 按 **Esc** 或点击 **×** 退出;
2. 游戏进行时, 按 **上下键** 或 **空格键** 操纵小恐龙, 按 **Esc** 游戏暂停;
3. 游戏暂停做得非常简陋 ~~可不要以为是卡了~~ , 按 **Esc** 回到开始的界面, 按 **回车** 或 **空格** 继续游戏;
4. 游戏结束时, 可直接点击结束界面的按钮进行操作, 也可按 **回车** 或 **空格** 重新开始或按 **Esc** 回到开始界面；
## 三、一些感想~~bug~~
1. 最高分只能记录程序运行时的最高分，关闭程序再重新运行最高分归零；
2. 分数最高为9999， 由于时间有限， 作者并不知道障碍的速度会不会达到人类不能结束的地步，~~总之我最高1568~~；
3. 游戏的大部分障碍均来自 [饥荒](https://www.klei.com/games/dont-starve) ， 若出现恶心或恐怖的障碍请不要责怪作者；
4. 游戏中有小概率出现一个不得了的障碍~~其实看一下 picture 文件夹就知道了QAQ~~。
5. 跳起时如果未等小恐龙落下就按 **↓** 键，小恐龙会直接进入低头的状态，~~也许可以通过这样做出一些很秀的操作。~~
