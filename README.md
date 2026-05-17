# CardGame - Cocos2d-x 卡牌匹配游戏

基于 Cocos2d-x 3.17 + C++ 开发的卡牌匹配小游戏，采用 MVC 架构。

1.环境要求

- Cocos2d-x 3.17
- CMake 3.1+
- Visual Studio 2022（Windows）/ Xcode（macOS）

2.构建步骤

获取 Cocos2d-x 引擎

将 Cocos2d-x 3.17 解压到项目根目录，重命名为 `cocos2d`：

CardGame/
├── cocos2d/          ← 引擎源码（需自行下载）
├── Classes/
├── Resources/
├── CMakeLists.txt
└── ...


3.CMake 构建（Windows）

打开 Windows 的 CMD 命令提示符 / PowerShell，进入游戏项目根目录（就是存放 CMakeLists.txt 的文件夹），然后输入以下4行命令。

mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A Win32
cmake --build . --config Debug

4. 运行

编译完成后，在 `build/bin/Debug/` 目录下运行 `Cardgame.exe`

5.项目结构

Classes/
├── configs/       配置层（枚举、资源路径、关卡加载）
├── models/        模型层（CardModel、GameModel、UndoModel）
├── views/         视图层（CardView、PlayFieldView、StackView、GameView）
├── controllers/   控制器层（GameController、CardController等）
├── managers/      管理器（UndoManager）
├── services/      服务层（UndoService、GameModelFromLevelGenerator）
└── utils/         工具类（CardUtils）
