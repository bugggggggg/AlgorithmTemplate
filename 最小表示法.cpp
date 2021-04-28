int min_exp(const vector<pair<PII,int> >&Hash)
{
    int n=Hash.size();
    int k = 0, i = 0, j = 1;
    while (k < n && i < n && j < n) {
      if (Hash[(i + k) % n] == Hash[(j + k) % n]) {
        k++;
      } else {
        Hash[(i + k) % n] > Hash[(j + k) % n] ? i = i + k + 1 : j = j + k + 1;
        if (i == j) i++;
        k = 0;
      }
    }
    i = min(i, j);
    return i;
}