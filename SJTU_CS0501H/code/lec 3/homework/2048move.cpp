// ============================================
// 2048 游戏核心逻辑 - 请实现以下四个函数
// ============================================
// 
// 棋盘是一个 4x4 的二维数组 board[4][4]
// 值为 0 表示空格，其他值为 2 的幂次（2, 4, 8, ...）
//
// 每个函数需要：
//   1. 将所有非零元素向指定方向"平移"（去掉中间的空格）
//   2. 将相邻且相同的元素"合并"（求和），每个元素每次移动只能合并一次
//   3. 合并后再次平移，填充空位
//   4. 返回本次移动获得的分数（所有合并产生的值之和）
//
// 提示：可以先实现一个"处理单行向左压缩"的辅助函数，
//       然后其他三个方向都可以通过"转换→处理→转换回"来实现。

// 辅助函数：将一行向左压缩并合并
// 参数：arr[4] 是一行的数据，len 固定为 4
// 返回值：本次压缩获得的分数
void __helper(int arr[], int len) {
    int idx = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] != 0) {
            if (i != idx) {
            arr[idx] = arr[i];
            arr[i] = 0;
            }
            idx += 1;
        }
    }
}

int compressLeft(int arr[], int len) {
    int score = 0;

    // TODO: 第一步 - 将所有非零元素移到左边（去掉中间的0）
    __helper(arr, 4);
    // unittest pass

    // TODO: 第二步 - 合并相邻的相同元素
    for (int i = 0; i < len - 1; i++) {
        if (arr[i] == 0) continue;
        if (arr[i] == arr[i + 1]) {
            arr[i] *= 2;
            score += arr[i];
            arr[i + 1] = 0;
        }
    }
    // TODO: 第三步 - 再次将非零元素移到左边
    __helper(arr, 4);
    return score;
}

// 向左移动
int moveLeft(int board[4][4]) {
    int score = 0;
    for (int i = 0; i < 4; i++) {
        score += compressLeft(board[i], 4);
    }
    return score;
}

// 向右移动
int moveRight(int board[4][4]) {
    int score = 0;
    // TODO: 提示 - 可以先把每行翻转，调用 compressLeft，再翻转回来
    int temp[4];
    for (int i = 0; i < 4; i++) {
        int idx = 0;
        for (int j = 3; j >= 0; j--) {
            temp[idx] = board[i][j];
            idx++;
        }
        score += compressLeft(temp, 4);
        idx = 0;
        for (int j = 3; j >= 0; j--) {
            board[i][j] = temp[idx];
            idx++;
        }
    }
    return score;
}

// 向上移动
int moveUp(int board[4][4]) {
    int score = 0;
    // TODO: 提示 - 可以提取每一列作为临时数组，调用 compressLeft，再放回去
    for (int i = 0; i < 4; i++) {
        int temp[4];
        int idx = 0;
        for (int j = 0; j < 4; j++) {
            temp[idx] = board[j][i];
            idx++;
        }
        score += compressLeft(temp, 4);
        idx = 0;
        for (int j = 0; j < 4; j++) {
            board[j][i] = temp[idx];
            idx++;
        }
    }
    return score;
}

// 向下移动
int moveDown(int board[4][4]) {
    int score = 0;
    // TODO: 提示 - 类似向上，但需要先翻转列
    for (int i = 0; i < 4; i++) {
        int temp[4];
        int idx = 0;
        for (int j = 3; j >= 0; j--) {
            temp[idx] = board[j][i];
            idx++;
        }
        score += compressLeft(temp, 4);
        idx = 0;
        for (int j = 3; j >= 0; j--) {
            board[j][i] = temp[idx];
            idx++;
        }
    }
    return score;
}