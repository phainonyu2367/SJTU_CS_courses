// =============================================
// 《数据结构（荣誉）》课程线性表进阶实践作业
// 自动贪吃蛇 - 学生代码模板 (solution.cpp)
// =============================================
//
// 【作业要求】
// 蛇身坐标序列本质上是一个队列：
//   蛇头对应队尾（rear端），蛇尾对应队头（front端）。
//   蛇头前进时，新坐标从 rear 端入队；
//   蛇尾缩短时，旧坐标从 front 端出队。
//
// 你需要实现以下 6 个函数（其余函数已由系统提供）：
//   1. enqueue(x, y)        - 入队
//   2. dequeue()             - 出队
//   3. moveForward(dir)      - 普通移动
//   4. moveAndGrow(dir)      - 吃到正食物时的移动
//   5. moveAndShrink(dir)    - 吃到负食物时的移动
//   6. decideDirection()     - 决策函数（决定蛇的移动方向）
//
// 【可调用的内置函数】（由游戏引擎提供，无需实现）：
//   getMapWidth()          返回地图宽度 (30)
//   getMapHeight()         返回地图高度 (20)
//   getMapCell(x, y)       返回地图(x,y)处的值
//                          0=空地 1=墙壁 2=蛇头 3=蛇身
//                          4=正食物 5=负食物
//   getSnakeLength()       返回蛇的当前长度
//   getSnakeX(i)           返回引擎维护的蛇身第i节X坐标
//   getSnakeY(i)           返回引擎维护的蛇身第i节Y坐标
//   getFoodX()             返回正食物X坐标
//   getFoodY()             返回正食物Y坐标
//   getNegFoodCount()      返回当前负食物数量
//   getNegFoodXAt(i)       返回第i个负食物的X坐标
//   getNegFoodYAt(i)       返回第i个负食物的Y坐标
//   abs(x)                 绝对值
//   min(a, b)              返回a和b中的较小值
//   max(a, b)              返回a和b中的较大值
//   randomInt(n)           返回[0, n)范围内的随机整数
//
// 【方向常量】
//   0=上(y-1)  1=右(x+1)  2=下(y+1)  3=左(x-1)
//
// 【坐标系】左上角(0,0)，x向右增大，y向下增大
//
// =============================================

// ========== 蛇身队列数据结构 ==========
int queueX[2000];
int queueY[2000];
int front = 0;
int rear = 0;
int queueSize = 0;
const int MAX_SIZE = 2000;
int initialized = 0;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

// ========== 以下函数由系统提供，无需修改 ==========

// 初始化蛇身队列：将引擎维护的初始蛇身坐标加入队列
// 蛇尾先入队（对应front端），蛇头最后入队（对应rear端）
void initSnake() {
    front = 0;
    rear = 0;
    queueSize = 0;
    int len = getSnakeLength();
    for (int i = len - 1; i >= 0; i = i - 1) {
        queueX[rear] = getSnakeX(i);
        queueY[rear] = getSnakeY(i);
        rear = (rear + 1) % MAX_SIZE;
        queueSize = queueSize + 1;
    }
}

// 获取蛇身第i节的X坐标（0=蛇头，即队列的rear端倒数第1个）
int getSnakeBodyX(int i) {
    int idx = (rear - 1 - i + MAX_SIZE) % MAX_SIZE;
    return queueX[idx];
}

// 获取蛇身第i节的Y坐标（0=蛇头，即队列的rear端倒数第1个）
int getSnakeBodyY(int i) {
    int idx = (rear - 1 - i + MAX_SIZE) % MAX_SIZE;
    return queueY[idx];
}

// 获取队列当前长度
int getQueueLength() {
    return queueSize;
}

// 检测坐标(nx, ny)是否与蛇身碰撞
int checkSelfCollision(int nx, int ny) {
    for (int i = 0; i < queueSize; i++) {
        if (getSnakeBodyX(i) == nx && getSnakeBodyY(i) == ny) {
            return 1;
        }
    }
    return 0;
}

// ========== 以下函数需要你实现 ==========

// 入队操作：将坐标(x,y)加入队列的rear端
void enqueue(int x, int y) {
    // TODO: 请实现
    queueX[rear] = x;
    queueY[rear] = y;
    rear = (rear + 1) % MAX_SIZE;
    queueSize++;
}

// 出队操作：从队列的front端移除一个元素
void dequeue() {
    // TODO: 请实现
    front = (front + 1) % MAX_SIZE;
    queueSize--;
}

// 普通移动：蛇长度不变
// 参数 dir: 方向 (0=上 1=右 2=下 3=左)
void moveForward(int dir) {
    // TODO: 请实现
    enqueue(getSnakeBodyX(0) + dx[dir], 
            getSnakeBodyY(0) + dy[dir]);
    dequeue();
}

// 吃到正食物时的移动：蛇身增长1格
// 参数 dir: 方向
void moveAndGrow(int dir) {
    // TODO: 请实现
    enqueue(getSnakeBodyX(0) + dx[dir], 
            getSnakeBodyY(0) + dy[dir]);
}

// 吃到负食物时的移动：蛇身缩短1格
// 参数 dir: 方向
void moveAndShrink(int dir) {
    // TODO: 请实现
    moveForward(dir);
    dequeue();
}

// 辅助函数，用于判断当前方向是否可以走
int _checkAvailablity(int dir) {
    /* 返回三种状态
        0: 当前方向没有问题
        -1: 当前方向绝对不能走
        1: 当前方向会撞上负食物（有商量余地）
    */
    int nextX = getSnakeBodyX(0) + dx[dir];
    int nextY = getSnakeBodyY(0) + dy[dir];

    // 判断是否与自身碰撞
    if (checkSelfCollision(nextX, nextY) == 1) return -1;

    // 判断是否与墙壁碰撞，由于边界有墙壁，所以用墙壁统一判断
    if (getMapCell(nextX, nextY) == 1) return -1;

    // 判断是否是负食物
    if (getMapCell(nextX, nextY) == 5) return 1;

    return 0;
}

// 辅助函数，用于确定初始最佳方向，方便后续旋转操作
int _getInitialDir(int m_dx, int m_dy) {
    switch (m_dx) {
        case 1:
            switch (m_dy) {
                case 1: return 0;
                case -1: return 1;
                case 0: return 1;
            }
        case 0: 
            switch (m_dy) {
                case 1: return 0;
                case -1: return 2;
        }
        case -1:
            switch (m_dy) {
                case 1: return 3;
                case -1: return 2;
                case 0: return 3;
            }

    }
}

// 决策函数：返回蛇下一步的移动方向 (0-3)
// 本次可通过简单策略实现，后续作业将要求更高级的寻路算法
int decideDirection() {
    if (initialized == 0) {
        initSnake();
        initialized = 1;
    }

    // TODO: 请实现你的决策逻辑
    int foodX = getFoodX();
    int foodY = getFoodY();
    int curX = getSnakeBodyX(0);
    int curY = getSnakeBodyY(0);
    int bestDir = 0;
    
    int m_dx = foodX - curX;
    int m_dy = foodY - curY;

    bestDir = _getInitialDir(m_dx, m_dy);
    int temp = bestDir;
    bool alter = true; // 用于判断前面是否有次优解存在
    for (int i = 0; i < 4; i++) {
        if (_checkAvailablity(temp) == 0) {
            return temp;
        } else if (_checkAvailablity(temp) == 1 && alter) {
                alter = false;
                bestDir = temp;
        }
    }
    

    return bestDir;
}
