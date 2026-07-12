#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N, C;
        cin >> N >> C;

        vector<pair<int, int>> rare(C);

        for (int i = 0; i < C; i++)
        {
            cin >> rare[i].first >> rare[i].second;

            // convert to 0-based indexing
            rare[i].first--;
            rare[i].second--;
        }

        vector<vector<int>> grid(N, vector<int>(N));

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cin >> grid[i][j];
            }
        }

        int answer = INT_MAX;

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        // Try every road cell as research center
        for (int sr = 0; sr < N; sr++)
        {
            for (int sc = 0; sc < N; sc++)
            {
                if (grid[sr][sc] == 0)
                    continue;

                vector<vector<int>> dist(N, vector<int>(N, -1));

                queue<pair<int, int>> q;

                q.push({sr, sc});
                dist[sr][sc] = 0;

                while (!q.empty())
                {
                    auto current = q.front();
                    q.pop();

                    int r = current.first;
                    int c = current.second;

                    for (int k = 0; k < 4; k++)
                    {
                        int nr = r + dr[k];
                        int nc = c + dc[k];

                        if (nr < 0 || nr >= N || nc < 0 || nc >= N)
                            continue;

                        if (grid[nr][nc] == 0)
                            continue;

                        if (dist[nr][nc] != -1)
                            continue;

                        dist[nr][nc] = dist[r][c] + 1;
                        q.push({nr, nc});
                    }
                }

                int farthest = 0;
                bool possible = true;

                // Distance to every rare element
                for (int i = 0; i < C; i++)
                {
                    int x = rare[i].first;
                    int y = rare[i].second;

                    if (dist[x][y] == -1)
                    {
                        possible = false;
                        break;
                    }

                    farthest = max(farthest, dist[x][y]);
                }

                if (possible)
                    answer = min(answer, farthest);
            }
        }

        cout << answer << endl;
    }

    return 0;
}