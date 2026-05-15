# CardGame 卡牌匹配游戏 

作者：yanghang  
日期：2026-05-15  
技术栈：Cocos2d-x 3.17 / C++ / CMake / Visual Studio 2022


# 1. 项目简介

本项目是基于 Cocos2d-x 3.17 开发的 2D 卡牌小游戏，核心玩法为手牌区翻牌替换、桌面牌与手牌顶部牌匹配、操作回退，采用 MVC 架构实现数据、视图、逻辑分离，保证代码可维护性与扩展性。

需求1：手牌区翻牌替换
点击手牌区♥A，♥A会平移（简单MoveTo）到手牌区的顶部牌（♣4）并替换它作为新的顶部牌

需求2：桌面牌和手牌区顶部牌匹配
点击桌面牌的♦️3，卡牌会和手牌区顶部的♣4进行匹配【桌面牌区的牌只要和手牌区顶部牌点数差1就可以匹配，无花色要求】，点击的桌面牌（♦️3）会平移到手牌区的顶部牌（♣4）并替换它作为新的手牌区的顶部牌

需求3：回退功能
场景：点击♦️3 -> 点击♥A -> 点击♠2 后；连续多次点击 回退按钮 ，各卡牌需要反着平移（简单MoveTo）到原位置；直到无回退记录可回退；

# 2. MVC架构说明

采用MVC（模型 - 视图 - 控制器）架构：
Model（模型）：存储游戏动态数据，无业务逻辑；
View（视图）：负责 UI 展示与用户输入捕获，无业务逻辑；
Controller（控制器）：协调模型与视图，处理业务逻辑；
附加层：configs（静态配置）、managers（管理器）、services（服务）、utils（工具）。


# 3. 目录结构

D:\CardGame\Classes\
│
├── configs/           【配置】静态数据，不随游戏变化
│   ├── loaders/
│   │   └── LevelConfigLoader    从JSON文件读取关卡配置
│   └── models/
│       ├── CardEnums            花色(♠♥♦♣)和点数(A-K)的定义
│       ├── CardResConfig        卡牌图片路径对照表
│       └── LevelConfig          关卡数据结构
│
├── models/            【数据】游戏运行时的动态数据
│   ├── CardModel              一张牌的数据（花色、点数、ID）
│   ├── GameModel              所有牌的集合（主牌6张+堆牌3张）
│   └── UndoModel              撤销操作的快照（记录"从哪移到哪"）
│
├── views/             【显示】UI界面相关
│   ├── CardView               一张牌的画面+点击事件
│   ├── PlayFieldView          上半部分（6张牌的排列）
│   ├── StackView              下半部分（备用牌+底牌）
│   └── GameView               总容器（背景+组装上面的子视图+回退按钮）
│
├── controllers/       【控制】处理业务逻辑
│   ├── GameController         总指挥（持有所有其他组件）
│   ├── PlayFieldController    主牌区的交互逻辑
│   ├── StackController        堆牌区的翻牌逻辑
│   └── CardController         判断规则（两张牌能不能匹配）
│
├── managers/          【管理】有状态的服务
│   └── UndoManager           撤销记录的管理器（类似一个"后悔药箱子"）
│
├── services/          【服务】无状态的工具方法
│   ├── UndoService            创建撤销记录的工具（全是静态方法）
│   └── GameModelFromLevelGenerator  根据JSON生成初始游戏数据
│
└── utils/             【工具】通用小功能
    └── CardUtils             判断两张牌是否匹配的方法