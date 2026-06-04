#include <iostream>

void partition(int* ids, int* theos, int* exps, int low, int high) {
    int i, j, id, exp, theo, total;
    while (low < high) {
        i = low;
        j = high;
        id = ids[low];
        exp = exps[low];
        theo = theos[low];
        total = exp + theo;
        while (i < j) {

            while (theos[j] + exps[j] < total || (theos[j] + exps[j] == total && (exps[j] < exp || (exps[j] == exp && ids[j] > id)))) {
                j -= 1;
            }
            exps[i] = exps[j];
            theos[i] = theos[j];
            ids[i] = ids[j];
            
            while (i < j && (theos[i] + exps[i] > total || (theos[i] + exps[i] == total && (exps[i] > exp || (exps[i] == exp && ids[i] < id))))) {
                i += 1;
            }
            exps[j] = exps[i];
            theos[j] = theos[i];
            ids[j] = ids[i];
        }
        exps[i] = exp;
        ids[i] = id;
        theos[i] = theo;
        partition(ids, theos, exps, low, i - 1);
        low = i + 1;
    }
}

void quickSort(int* ids, int* theo, int* exp, int size) {
    partition(ids, theo, exp, 0, size - 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    int *ids, *theo, *exp;
    ids = new int[n];
    theo = new int[n];
    exp = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> ids[i] >> theo[i] >> exp[i];
    }

    quickSort(ids, theo, exp, n);
    for (int i = 0; i < n; ++i) {
        std::cout << ids[i] << ' ' << theo[i] + exp[i] << '\n';
    }
}
