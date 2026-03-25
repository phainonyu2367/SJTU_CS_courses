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

// ========== BFS 寻路数据结构 ==========
// 地图最大 30x20 = 600 个格子
int bfsQueueX[600];
int bfsQueueY[600];
int bfsFront = 0;
int bfsRear = 0;

// 访问标记和路径记录（用一维数组模拟二维）
int visited[600];
int parentX[600];   // 记录每个位置的前驱X坐标
int parentY[600];   // 记录每个位置的前驱Y坐标
int parentDir[600]; // 记录到达该位置的方向

// 将二维坐标转换为一维索引
int toIndex(int x, int y) {
    return y * 30 + x;
}

// 检查某个位置是否可通行（用于BFS遍历）
// 注意：BFS遍历时允许穿过负食物区域，但最终路径要避开
int isWalkable(int x, int y) {
    int cell = getMapCell(x, y);
    // 墙壁(1)、蛇身(3)、蛇头(2)不可通行
    if (cell == 1 || cell == 3 || cell == 2) {
        return 0;
    }
    return 1;
}

// 检查某个位置是否安全（用于最终移动决策）
int isSafe(int x, int y) {
    if (isWalkable(x, y) == 0) {
        return 0;
    }
    // 额外检查：不能走到负食物上
    int cell = getMapCell(x, y);
    if (cell == 5) {
        return 0;
    }
    return 1;
}

// 重置BFS数据结构
void resetBFS() {
    bfsFront = 0;
    bfsRear = 0;
    for (int i = 0; i < 600; i = i + 1) {
        visited[i] = 0;
        parentX[i] = -1;
        parentY[i] = -1;
        parentDir[i] = -1;
    }
}

// BFS入队
void bfsEnqueue(int x, int y) {
    bfsQueueX[bfsRear] = x;
    bfsQueueY[bfsRear] = y;
    bfsRear = bfsRear + 1;
}

// BFS出队
void bfsDequeue(int resultX[], int resultY[]) {
    resultX[0] = bfsQueueX[bfsFront];
    resultY[0] = bfsQueueY[bfsFront];
    bfsFront = bfsFront + 1;
}

// 检查BFS队列是否为空
int bfsIsEmpty() {
    return bfsFront >= bfsRear;
}

// BFS寻路：从起点找到到终点的最短路径
// 返回起点的下一步方向，如果找不到路径返回-1
int bfs(int startX, int startY, int targetX, int targetY) {
    resetBFS();

    // 将起点加入队列
    bfsEnqueue(startX, startY);
    visited[toIndex(startX, startY)] = 1;
    parentX[toIndex(startX, startY)] = startX;
    parentY[toIndex(startX, startY)] = startY;
    parentDir[toIndex(startX, startY)] = -1;

    int curXArr[1];
    int curYArr[1];

    // BFS主循环
    while (bfsIsEmpty() == 0) {
        bfsDequeue(curXArr, curYArr);
        int curX = curXArr[0];
        int curY = curYArr[0];

        // 如果到达目标
        if (curX == targetX && curY == targetY) {
            // 回溯找到第一步的方向
            int curIdx = toIndex(curX, curY);
            while (parentX[curIdx] != startX || parentY[curIdx] != startY) {
                int px = parentX[curIdx];
                int py = parentY[curIdx];
                curIdx = toIndex(px, py);
            }
            return parentDir[curIdx];
        }

        // 遍历四个方向
        for (int d = 0; d < 4; d = d + 1) {
            int nx = curX + dx[d];
            int ny = curY + dy[d];
            int nIdx = toIndex(nx, ny);

            // 检查边界
            if (nx < 0 || nx >= 30 || ny < 0 || ny >= 20) {
                continue;
            }

            // 检查是否可通行且未访问
            if (isWalkable(nx, ny) == 1 && visited[nIdx] == 0) {
                visited[nIdx] = 1;
                parentX[nIdx] = curX;
                parentY[nIdx] = curY;
                parentDir[nIdx] = d;
                bfsEnqueue(nx, ny);
            }
        }
    }

    // 没找到路径
    return -1;
}

// 计算两点之间的曼哈顿距离
int getDistance(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// 决策函数：返回蛇下一步的移动方向 (0-3)
// 使用BFS寻路算法
int decideDirection() {
    if (initialized == 0) {
        initSnake();
        initialized = 1;
    }

    int headX = getSnakeX(0);
    int headY = getSnakeY(0);
    int foodX = getFoodX();
    int foodY = getFoodY();

    // 第一步：尝试用BFS找到到正食物的最短路径
    int dir = bfs(headX, headY, foodX, foodY);

    // 如果找到了路径，检查第一步是否安全
    if (dir != -1) {
        int nx = headX + dx[dir];
        int ny = headY + dy[dir];
        if (isSafe(nx, ny) == 1) {
            return dir;
        }
    }

    // 第二步：BFS找不到路径或路径不安全，使用贪心策略
    // 选择能安全接近食物的方向
    int bestDir = -1;
    int minDist = 10000;

    for (int d = 0; d < 4; d = d + 1) {
        int nx = headX + dx[d];
        int ny = headY + dy[d];
        if (isSafe(nx, ny) == 1) {
            int dist = getDistance(nx, ny, foodX, foodY);
            if (dist < minDist) {
                minDist = dist;
                bestDir = d;
            }
        }
    }

    if (bestDir != -1) {
        return bestDir;
    }

    // 第三步：选择任意安全方向
    for (int d = 0; d < 4; d = d + 1) {
        int nx = headX + dx[d];
        int ny = headY + dy[d];
        if (isSafe(nx, ny) == 1) {
            return d;
        }
    }

    // 第四步：实在没办法，选择不撞墙的方向
    for (int d = 0; d < 4; d = d + 1) {
        int nx = headX + dx[d];
        int ny = headY + dy[d];
        int cell = getMapCell(nx, ny);
        if (cell != 1) {
            return d;
        }
    }

    // 兜底：默认向右
    return 1;
}
