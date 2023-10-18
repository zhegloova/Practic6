#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int p[100000]; //для номеров предков
int rk[100000]; //для рангов вершин

void init_dsu() { //инициализация
	for (int i = 0; i < 100000; i++) {
		p[i] = i;
		rk[i] = 1;

	}
}
int get_root(int v) { //поиск корня для вершины
	if (p[v] == v)
		return v;
	else
		return p[v] = get_root(p[v]);
}

bool merge(int a, int b) { //находились ли до вызова функции a и b в разных деревьях
	int ra = get_root(a);
	int rb = get_root(b);
	if (ra == rb)
		return false;
	else {
		if (rk[ra] < rk[rb])
			p[ra] = rb; //подвешиваем всё дерево a к корню дерева b.
		else if (rk[rb] < rk[ra])
			p[rb] = ra; //подвешиваем b к a
		else {
			p[ra] = rb; //подвешиваем
			rk[rb]++; //увеличиваем ранг
		}
		return true;
	}

}
struct edge { //структура ребра
	int a, b, len;
	bool operator<(const edge& other) { //пергрузка оператора
		return len < other.len; //сравнение по длине
	}
};
int main() {
	vector<edge> edges; //создание вектора ребер
	int n;
	cout << "Enter number of nodes:" << endl;
	cin >> n; //ввод количества вершин
	cout << "Enter adjacency matrix:" << endl;
	for (int j = 1; j <= n; j++) //ввод матрицы смежности
		for (int i = 1; i <= n; i++) {
			int x;
			cin >> x; //ввод длины
			if (x != 0) { //если существует ребро 
				edge c;
				c.a = i;
				c.b = j;
				c.len = x;
				edges.push_back(c); //добавляем ребро в вектор
			}
		}

	sort(edges.begin(), edges.end()); //сортируем ребра по длине
	init_dsu(); //инициализируем DSU
	for (edge e : edges) { //для всех ребер
		if (merge(e.a, e.b)) { //проверка на нахождение в разных деревьях
			cout << e.a << " --> " << e.b << " = " << e.len << endl; //вывод ребра дерева
		}
	}
}