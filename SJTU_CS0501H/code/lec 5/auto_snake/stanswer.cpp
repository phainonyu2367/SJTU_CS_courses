//
// 《数据结构（荣誉）》课程线性表进阶实践作业
// 自动贪吃蛇 - 参考答案 (solution.cpp)
//

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

// ===== 以下函数由系统提供, 无需修改 =====

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
    initialized = 1;
}

int getSnakeBodyX(int index) {
    int pos = (rear - 1 - index + MAX_SIZE) % MAX_SIZE;
    return queueX[pos];
}

int getSnakeBodyY(int index) {
    int pos = (rear - 1 - index + MAX_SIZE) % MAX_SIZE;
    return queueY[pos];
}

int getQueueLength() {
    return queueSize;
}

int checkSelfCollision(int x, int y) {
    for (int i = 0; i < queueSize; i = i + 1) {
        int pos = (front + i) % MAX_SIZE;
        if (queueX[pos] == x) {
            if (queueY[pos] == y) {
                return 1;
            }
        }
    }
    return 0;
}

// ===== 以下 6 个函数为学生需实现部分 =====

void enqueue(int x, int y) {
    queueX[rear] = x;
    queueY[rear] = y;
    rear = (rear + 1) % MAX_SIZE;
    queueSize = queueSize + 1;
}

void dequeue() {
    front = (front + 1) % MAX_SIZE;
    queueSize = queueSize - 1;
}

void moveForward(int dir) {
    int headX = getSnakeBodyX(0);
    int headY = getSnakeBodyY(0);
    int newX = headX + dx[dir];
    int newY = headY + dy[dir];
    enqueue(newX, newY);
    dequeue();
}

void moveAndGrow(int dir) {
    int headX = getSnakeBodyX(0);
    int headY = getSnakeBodyY(0);
    int newX = headX + dx[dir];
    int newY = headY + dy[dir];
    enqueue(newX, newY);
}

void moveAndShrink(int dir) {
    int headX = getSnakeBodyX(0);
    int headY = getSnakeBodyY(0);
    int newX = headX + dx[dir];
    int newY = headY + dy[dir];
    enqueue(newX, newY);
    dequeue();
    if (queueSize > 1) {
        dequeue();
    }
}

int decideDirection() {
    if (initialized == 0) {
        initSnake();
    }
    int W = getMapWidth();
    int H = getMapHeight();
    int headX = getSnakeX(0);
    int headY = getSnakeY(0);

    int foodX = getFoodX();
    int foodY = getFoodY();

    // BFS 寻路到正食物
    int visited[600];
    int parentDir[600];
    int bfsQX[600];
    int bfsQY[600];
    int bfsFront = 0;
    int bfsRear = 0;

    for (int i = 0; i < 600; i = i + 1) {
        visited[i] = 0;
        parentDir[i] = -1;
    }

    visited[headY * W + headX] = 1;
    bfsQX[bfsRear] = headX;
    bfsQY[bfsRear] = headY;
    bfsRear = bfsRear + 1;

    int found = 0;

    while (bfsFront < bfsRear) {
        int cx = bfsQX[bfsFront];
        int cy = bfsQY[bfsFront];
        bfsFront = bfsFront + 1;

        if (cx == foodX) {
            if (cy == foodY) {
                found = 1;
                int tx = foodX;
                int ty = foodY;
                while (1) {
                    int pd = parentDir[ty * W + tx];
                    int prevX = tx - dx[pd];
                    int prevY = ty - dy[pd];
                    if (prevX == headX) {
                        if (prevY == headY) {
                            return pd;
                        }
                    }
                    tx = prevX;
                    ty = prevY;
                }
            }
        }

        for (int d = 0; d < 4; d = d + 1) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (nx >= 0) {
                if (nx < W) {
                    if (ny >= 0) {
                        if (ny < H) {
                            int cell = getMapCell(nx, ny);
                            if (visited[ny * W + nx] == 0) {
                                if (cell != 1) {
                                    if (cell != 2) {
                                        if (cell != 3) {
                                            visited[ny * W + nx] = 1;
                                            parentDir[ny * W + nx] = d;
                                            bfsQX[bfsRear] = nx;
                                            bfsQY[bfsRear] = ny;
                                            bfsRear = bfsRear + 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // BFS 找不到路径, 选一个安全方向
    for (int d = 0; d < 4; d = d + 1) {
        int nx = headX + dx[d];
        int ny = headY + dy[d];
        if (nx >= 0) {
            if (nx < W) {
                if (ny >= 0) {
                    if (ny < H) {
                        int cell = getMapCell(nx, ny);
                        if (cell != 1) {
                            if (cell != 2) {
                                if (cell != 3) {
                                    return d;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}