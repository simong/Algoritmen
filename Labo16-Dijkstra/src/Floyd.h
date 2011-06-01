#include <iostream>

using namespace std;

int floyd() {
    int N, E;
    int graph[100][100];
    int ouders[100][100];
    int start, end;

    cout << "#Nodes - #Edges?" << endl;
    cin >> N >> E;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            graph[i][j] = 9999; // Equal to NO path
            ouders[i][j] = -1;
            if (i == j) {
                graph[i][j] = 0; // No distance from a node to that same node
                ouders[i][j] = 0;
            }
        }
    }

    cout << "Kost?" << endl;
    // Kost per verbinding.
    for (int i = 0; i < E; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        graph[x - 1][y - 1] = graph[y - 1][x - 1] = d;
    }

    // Kortste pad berekenen.
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {

                // graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);

                int kost = graph[i][k] + graph[k][j];
                if (kost < graph[i][j]) {
                    // Kortere weg gevonden.
                    ouders[i][j] = k;
                    graph[i][j] = kost;
                }
            }
        }
    }

    cout << "Start?" << endl;
    while (true) { // Prints out the shortest distances between nodes until the program is terminated
        cin >> start >> end;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << graph[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << ouders[i][j] << " ";
            }
            cout << endl;
        }
        int i = start - 1;
        int j = end - 1;
        cout << graph[i][j] << endl;
        cout << "Pad: " << end << " ";
        while (j != i) {
            int k = ouders[i][j];
            //cout << k << " ";
            j = k;
        }
        cout << start;
    }
    return 0;
}
