《数据结构（荣誉）》课程线性表进阶实践作业
自动贪吃蛇
一、作业目标
本作业要求你实现一个自动贪吃蛇的核心逻辑。蛇在一个有墙壁的地图中自动移动， 你需要编写代码维护蛇身坐标队列，并实现移动和方向决策。

核心知识点：蛇身坐标序列本质上是一个队列—— 蛇头对应队尾（rear端），蛇尾对应队头（front端）。 蛇头前进时，新坐标从 rear 端入队；蛇尾缩短时，旧坐标从 front 端出队。

二、游戏规则
地图大小：30×20，四周为墙壁，内部有随机固定墙壁
蛇的初始长度为 3，从地图中央开始
每帧蛇自动移动一格，方向由你的 decideDirection() 函数决定
正食物（金色）：地图上同时只有 1 个，吃到后蛇身增长 1 格
负食物（紫色）：地图上同时最多 3 个，吃到后蛇身缩短 1 格
撞墙或撞到自身则游戏结束
蛇长度达到 50 则通关
三、你需要实现的函数
函数签名	功能	输入	输出
enqueue(x, y)	将坐标(x,y)加入队列的rear端	x, y: 坐标	无
dequeue()	从队列的front端移除一个元素	无	无
moveForward(dir)	普通移动，蛇长度不变	dir: 方向(0-3)	无
moveAndGrow(dir)	吃到正食物时的移动，蛇身增长1格	dir: 方向(0-3)	无
moveAndShrink(dir)	吃到负食物时的移动，蛇身缩短1格	dir: 方向(0-3)	无
decideDirection()	决策函数，返回蛇下一步的移动方向	无	int: 0=上 1=右 2=下 3=左
四、系统已提供的函数
以下函数已在模板中实现，你可以直接调用：

函数	功能
initSnake()	初始化蛇身队列（已在 decideDirection 中调用）
getSnakeBodyX(i)	获取蛇身第i节的X坐标（0=蛇头）
getSnakeBodyY(i)	获取蛇身第i节的Y坐标（0=蛇头）
getQueueLength()	获取队列当前长度
checkSelfCollision(nx, ny)	检测坐标(nx,ny)是否与蛇身碰撞，返回1表示碰撞
五、可调用的引擎内置函数
以下函数由游戏引擎提供：

函数	返回值	说明
getMapWidth()	int	地图宽度（30）
getMapHeight()	int	地图高度（20）
getMapCell(x, y)	int	获取(x,y)处的地图值
getSnakeLength()	int	蛇的当前长度（引擎维护）
getSnakeX(i)	int	蛇身第i节的X坐标（引擎维护，0=蛇头）
getSnakeY(i)	int	蛇身第i节的Y坐标（引擎维护，0=蛇头）
getFoodX()	int	正食物X坐标
getFoodY()	int	正食物Y坐标
getNegFoodCount()	int	当前负食物数量（最多3个）
getNegFoodXAt(i)	int	第i个负食物的X坐标
getNegFoodYAt(i)	int	第i个负食物的Y坐标
abs(x)	int	绝对值
min(a, b)	int	返回a和b中的较小值
max(a, b)	int	返回a和b中的较大值
randomInt(n)	int	返回 [0, n) 范围内的随机整数
地图值含义
值	含义
0	空地（可通行）
1	墙壁（不可通行）
2	蛇头
3	蛇身（不可通行）
4	正食物
5	负食物
六、使用说明
点击 TEMPLATE 按钮下载代码模板 solution.cpp
在本地编辑器或左侧代码编辑器中编写你的C++代码
点击 UPLOAD 按钮上传代码，或直接在左侧编辑器中修改
点击 START 按钮开始游戏，观察蛇的行为
可以调整速度来加快或减慢游戏，方便调试
注意：本系统内置了一个轻量级C++子集解释器，支持基本的C++语法 （变量声明、数组、if/else、for/while、函数定义和调用等）。 不支持 STL 容器（如 vector、queue）、指针、结构体等高级特性。 请使用数组来实现队列。