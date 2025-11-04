#include <iostream>
#include <vector>

class FenwickTree{
  public:
    explicit FenwickTree(int n)
      : n_(n), tree_(n + 1, 0), a_(n + 1, 0) {}

    static int f(int i) { return i - (i & -i); }
    static int G(int i) { return i + (i & -i); }
    
    int GetSum(int l, int r) const {
        return PrefixSum(r) - PrefixSum(l-1);
    }

    void Update(int idx, int val) {
      int delta = val - a_[idx];
      a_[idx] = val;
      UpdateDelta(idx, delta);
    }

    void UpdateDelta(int idx, int delta) {
        for (; idx <= n_; idx = G(idx))
            tree_[idx] += delta;
    } 

    int PrefixSum(int idx) const {
      int ans = 0;
      for (; idx > 0; idx = f(idx))
          ans += tree_[idx];
      return ans;
    }

  private:
    int n_;
    std::vector<int> tree_;
    std::vector<int> a_;
};


class FenwickTree2D {
public:
    FenwickTree2D(int n, int m)
      : n_(n), m_(m),
      tree_(n + 1, std::vector<int>(m + 1, 0)),
      a_(n + 1, std::vector<int>(m + 1, 0)) {}

    static int f(int i) { return i - (i & -i); }
    static int G(int i) { return i + (i & -i); }

    void Update(int x, int y, int val) {
      int delta = val - a_[x][y];
      a_[x][y] = val;
      UpdateDelta(x, y, delta);
    }

    void UpdateDelta(int x, int y, int delta) {
      for (int i = x; i <= n_; i = G(i))
        for (int j = y; j <= m_; j = G(j))
          tree_[i][j] += delta;
    }

    int PrefixSum(int x, int y) const {
      int ans = 0;
      for (int i = x; i > 0; i = f(i))
        for (int j = y; j > 0; j = f(j))
          ans += tree_[i][j];
      return ans;
    }

    int GetSum(int x1, int y1, int x2, int y2) const {
      return PrefixSum(x2, y2)
         - PrefixSum(x1 - 1, y2)
         - PrefixSum(x2, y1 - 1)
         + PrefixSum(x1 - 1, y1 - 1);
    }

private:
    int n_, m_;
    std::vector<std::vector<int>> tree_;
    std::vector<std::vector<int>> a_;
};


int main() {

  FenwickTree2D ft2(3, 3);
  ft2.Update(1, 1, 5);
  ft2.Update(1, 2, 3);
  ft2.Update(2, 2, 2);
  ft2.Update(3, 3, 7);

  std::cout << "Sum(1,1,2,2) = " << ft2.GetSum(1, 1, 2, 2) << " (ожидается 10)\n";
  std::cout << "Sum(1,1,3,3) = " << ft2.GetSum(1, 1, 3, 3) << " (ожидается 17)\n";

  ft2.Update(2, 2, 5);
  std::cout << "После Update(2,2,5): Sum(1,1,2,2) = " << ft2.GetSum(1, 1, 2, 2) << " (ожидается 13)\n";

  return 0;
}
