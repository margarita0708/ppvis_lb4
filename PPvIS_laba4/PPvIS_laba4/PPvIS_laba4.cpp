
#include <iostream>
#include <vector> 
#include <string> 

using namespace std;
template <typename T>
class Node {//узел
private:
	T object;
public:
	Node(T _object = T()) {
		object = _object;
	}
	T getObject() {
		return object;
	}
};

class Edge {//ребро
	short begin, end;
public:
	Edge(short _begin = 0, short _end = 0) {
		begin = _begin;
		end = _end;
	}
	short getBegin() {
		return begin;
	}
	short getEnd() {
		return end;
	}
	void setBegin(short _begin) {
		begin = _begin;
	}
	void setEnd(short _end) {
		end = _end;
	}
};

template <typename T>
class Graph { // oriented list of edges 
private:
	vector <Node <T>> node;//вектор узлов любого типа
	vector<Edge> edge;//вектор ребер
public:
	Graph(void) {};
	~Graph(void) {};

	bool empty(void) {
		if (node.size() == 0) { // or ... && edge.size() == 0 ?? 
			return true;
		}
		return false;
	}
	void clear(void) {
		node.clear();
		edge.clear();
	}

	void addNode(T _nodeObject) {
		if (isNodeExist(_nodeObject) == -1) {
			node.push_back(Node<T>(_nodeObject));
		}
	};
	void deleteNode(T _nodeObject) {
		short _nodeNumber = isNodeExist(_nodeObject);
		if (_nodeNumber != -1) {
			node.erase(node.begin() + _nodeNumber);
			for (int i = 0; i < edge.size(); i++) {
				if (isEdgeExist(i, _nodeNumber)) {
					deleteEdge(i, _nodeNumber);
				}
			}
		}
	};

	void addEdge(short i, short j) {
		if (isEdgeExist(i, j) == false) {
			edge.push_back(Edge(i, j));
		}
	};
	void addEdge(T iObject, T jObject) {
		int i = isNodeExist(iObject), j = isNodeExist(jObject);
		if (i != -1 && j != -1 && isEdgeExist(i, j) == false) {
			edge.push_back(Edge(isNodeExist(iObject), isNodeExist(jObject)));
		}
	};
	void deleteEdge(short i, short j) {
		for (int k = 0; k < edge.size(); k++) {
			if (isEdgeExist(i, j) == true || isEdgeExist(j, i) == true) {
				edge.erase(edge.begin() + k);
				for (int m = k; m < edge.size() - 1; m++) {
					edge[m] = edge[m + 1];
				}
				edge.pop_back();
				if (edge.size() != 0) {
					edge.pop_back();
				}
			}
		}
	};
	void deleteEdge(T iObject, T jObject) {
		for (int k = 0; k < edge.size(); k++) {
			if (isEdgeExist(iObject, jObject) != -1) {
				edge.erase(edge.begin() + k);
			}
		}
	};

	short nodeDegree(T _nodeObject) {//степень узла(сколько раз уч-вует в составл ребра)
		short degree = 0;
		short nodeNumber = isNodeExist(_nodeObject);
		if (nodeNumber != -1) {
			for (int i = 0; i < node.size(); i++) {
				bool isExist = isEdgeExist(i, nodeNumber);
				degree += isExist == true ? 1 : 0;
			}
			return isEdgeExist(nodeNumber, nodeNumber) == true ? ++degree : degree;
		}
		else {
			return -1;
		}
	};


	bool isEdgeExist(short i, short j) {//существует ли ребро
		for (int k = 0; k < edge.size(); k++) {
			if ((edge[k].getBegin() == i && edge[k].getEnd() == j) || (edge[k].getBegin() == j && edge[k].getEnd() == i)) {
				return true;
			}
		}
		return false;
	};
	short isEdgeExist(T iObject, T jObject) {
		for (int k = 0; k < edge.size(); k++) {
			if ((node[edge[k].getBegin()].getObject() == iObject && node[edge[k].getEnd()].getObject() == jObject) ||
				(node[edge[k].getBegin()].getObject() == jObject && node[edge[k].getEnd()].getObject() == iObject)) {
				return k;
			}
		}
		return -1;
	};
	//перегруженные
	short isNodeExist(T _nodeObject) {//сущ ли узел
		for (int i = 0; i < node.size(); i++) {
			if (node[i].getObject() == _nodeObject) {
				return i;
			}
		}
		return -1;
	};
	bool isNodeExist(short _nodeNumber) {
		return _nodeNumber < node.size();
	};

	/*short countOfLoops() {//
		short count = 0;
		for (int i = 0; i < node.size(); i++) {
			count
				+= isEdgeExist(i, i) == true ? 1 : 0;
		}
		return count;
	}*/

	short countOfNodes() {
		return node.size();
	};
	short countOfEdges() {
		return edge.size();
	};

	void showNodes() {
		cout << '\n';
		for (int i = 0; i < node.size(); i++) {
			cout << '\t' << i << " - " << node[i].getObject() << '\n';
		}
	};
	void showEdges() {
		cout << '\n';
		for (int i = 0; i < edge.size(); i++) {
			cout << '\t' << node[edge[i].getBegin()].getObject() << " - " << node[edge[i].getEnd()].getObject() << '\n';
		}
	};
	bool operator ==(const Graph<T>& right)
	{

		if (node.size() == right.node.size())
		{
			for (int i = 0; i < node.size(); i++)
			{
				if (node[i].getObject() != right.node[i].getObject())
					return false;
			}
		}
		if (edge.size() == right.edge.size())
		{
			for (int i = 0; i < edge.size(); i++)
			{
				if (edge[i].getBegin() != right.edge[i].getBegin() || edge[i].getEnd() != right.edge[i].getEnd())
					return false;
			}

		}

		return true;
	}
	bool operator !=(const Graph<T>& right)
	{
		return !(*this == right);
	}
	bool operator >(const Graph<T>& right)
	{
		return this->node.size() > right.node.size();
	}
	bool operator <(const Graph<T>& right)
	{
		return this->node.size() < right.node.size();
	}
	bool operator >=(const Graph<T>& right)
	{
		return this->node.size() >= right.node.size();
	}
	bool operator <=(const Graph<T>& right)
	{
		return this->node.size() <= right.node.size();
	}
	Graph<T> operator =(const Graph<T>& right)
	{
		Graph<T> new_graph;

		new_graph.node = right.node;
		new_graph.edge = right.node;

		return new_graph;
	}
	class Node_Iterator//почитать про итераторы
	{
	private:
		Graph<T>* graphForIteration;
		int index;
	public:
		Node_Iterator(Graph<T>& graph)
		{
			graphForIteration = &graph;
			index = 0;
		}

		bool next()
		{
			if (graphForIteration->node.size() <= index + 1) {
				return false;
			}
			index++;
			return true;
		}
		bool prev()
		{
			if (index == 0)
			{
				return false;
			}
			index--;
			return true;
		}

		void getAdjacentNodes()//смежные вершины
		{
			short countOfAdjacent = 0;
			cout << "\n\t\t";
			for (int i = 0; i < graphForIteration->node.size(); i++)
			{
				if (graphForIteration->isEdgeExist(index, i) == true) {
					countOfAdjacent++;
					cout << graphForIteration->node[i].getObject() << ' ';
				}
			}
			if (countOfAdjacent == 0) {
				cout << "No nodes adjacent to this node";
			}
			cout << '\n';
		}
		void getIncidentEdges()//инцидентные ребра
		{
			cout << '\n';
			short countOfIncident = 0;
			for (int i = 0; i < graphForIteration->node.size(); i++)
			{
				if (graphForIteration->isEdgeExist(index, i) == true) {
					countOfIncident++;
					cout << "\t\t" << graphForIteration->node[index].getObject() << " - " << graphForIteration->node[i].getObject() << '\n';
				}
			}
			if (countOfIncident == 0) {
				cout << "\t\tNo edges incident to this node";
			}
			cout << '\n';
		}
	};

	class Edge_iterator {
	private:
		Graph<T>* graphForIteration;
		int index;

	public:
		Edge_iterator(Graph<T>& graph)
		{
			graphForIteration = &graph;
			index = 0;
		}
		bool next()
		{
			if (graphForIteration->edge.size() <= index + 1) {
				return false;
			}
			index++;
			return true;
		}
		bool prev()
		{
			if (index == 0)
			{
				return false;
			}
			index--;
			return true;
		}
	};
};

int main(void) {
	short choose = 1;
	string forUse_1 = " ";
	string forUse_2 = " ";
	Graph<string>* G = new Graph<string>();

	while (true) {
		cout << "\n1. Add node\t\t\t2. Delete node\n3. Add edge\t\t\t4. Delete edge\n5. Number of edges and nodes\n";
		cout << "6. Show nodes\t\t\t7. Show edges\n8. Degree of node\t\t9. Bidirectional iterator for nodes\n10. Is node exist\t\t";
		cout << "11. Bidirectional iterator for edges\n12. Is edge exist\t\t13. Is empty\n14. Clear\t\t\t0. Exit\n\nYou choose: ";


		cin >> choose;
		switch (choose)
		{
		case 0: {
			return 0;
		}
		case 1: {
			cout << "\n\tEnter node \"name\": ";
			cin >> forUse_1;
			G->addNode(forUse_1);
			break;
		}
		case 2:
		{
			cout << "\n\tEnter node \"name\": ";
			cin >> forUse_1;
			G->deleteNode(forUse_1);
			break;
		}
		case 3:
		{
			cout << "\n\tEnter nodes' \"names\": ";
			cin >> forUse_1 >> forUse_2;
			G->addEdge(forUse_1, forUse_2);
			break;
		}
		case 4:
		{
			cout << "\n\tEnter nodes' \"names\": ";
			cin >> forUse_1 >> forUse_2;
			G->deleteEdge(forUse_1, forUse_2);
			break;
		}
		case 5: {
			cout << "\n\tNodes: " << G->countOfNodes() << "\n\tEdges: " << G->countOfEdges() << '\n';
			break;
		}
		case 6: {
			if (G->countOfNodes() == 0) {
				cout << "No nodes\n";
				break;
			}
			G->showNodes();
			break;
		}
		case 7: {
			if (G->countOfEdges() == 0) {
				cout << "No edges\n";
				break;
			}
			G->showEdges();
			break;
		}
		case 8: {
			cout << "\n\tEnter a node \"name\": ";
			cin >> forUse_1;
			short degree = G->nodeDegree(forUse_1);
			if (degree == -1) {
				cout << "\tNo node with this name\n";
			}
			else {
				cout << "\tNode degree: " << degree;
			}
			break;
		}
		case 9: {
			Graph<string>::Node_Iterator G_iterator(*G);
			while (choose != 5)
			{
				cout << "\n\t1. Next node\t\t2. Previous node\n\t3. Get adjacent nodes\t4. Get incident edges\n\t5. Exit from iterator\n\n\t\tYou choose: ";
				cin >> choose;

				switch (choose)
				{
				case 1: {
					if (G_iterator.next() == false) {
						cout << "\n\t\tIterator is on the last node\n";
					}
					else
					{
						cout << "\n\t\tIterator moved to next node\n";
					}
					break;
				}
				case 2: {
					if (G_iterator.prev() == false) {
						cout << "\n\t\tIterator is on the first node\n";
					}
					else
					{
						cout << "\n\t\tIterator moved to previous node\n";
					}
					break;
				}
				case 3: {
					G_iterator.getAdjacentNodes();
					break;
				}
				case 4: {
					G_iterator.getIncidentEdges();
					break;
				}
				default:
					break;
				}
			}
			break;
		}
		case 10: {
			cout << "\n\tEnter a node \"name\": ";
			cin >> forUse_1;
			if (G->isNodeExist(forUse_1) != -1) {
				cout << "\n\tThis node exist\n";
			}
			else
			{
				cout << "\n\tThis node doesn't exist\n";
			}
			break;
		}
		case 11: {
			Graph<string>::Node_Iterator G_iterator(*G);
			while (choose != 3)
			{
				cout << "\n\t1. Next edge\t\t2. Previous edge\n\t3. Exit from iterator\n\n\t\tYou choose: ";
				cin >> choose;

				switch (choose)
				{
				case 1: {
					if (G_iterator.next() == false) {
						cout << "\n\t\tIterator is on the last edge\n";
					}
					else
					{
						cout << "\n\t\tIterator moved to next edge\n";
					}
					break;
				}
				case 2: {
					if (G_iterator.prev() == false) {
						cout << "\n\t\tIterator is on the first edge\n";
					}
					else
					{
						cout << "\n\t\tIterator moved to previous edge\n";
					}
					break;
				}
				default:
					break;
				}
			}
			break;
		}
		case 12: {
			cout << "\n\tEnter a nodes \"names\": ";
			cin >> forUse_1 >> forUse_2;
			if (G->isEdgeExist(forUse_1, forUse_2) != -1) {
				cout << "\n\tThis edge exist\n";
			}
			else
			{
				cout << "\n\tThis edge doesn't exist\n";
			}
			break;
		}
		case 13: {
			(G->empty() == true) ? cout << "\n\tEmpty\n" : cout << "\n\tNot empty\n";
			break;
		}
		case 14: {
			G->clear();
			break;
		}
		default: break;
		}
	}
}