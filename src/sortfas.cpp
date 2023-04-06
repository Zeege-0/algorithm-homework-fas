#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

namespace lkx{
struct Node {
    int dest;
    struct Node* next;
};

class Graph {
private:
    int n; // 图的顶点数
    struct Node** adj_list; // 邻接链表数组
    int* A; //vector of nodes to be sorted 

public:
    Graph(int n) {
        this->n = n;
        adj_list = new Node*[n];
        for (int i = 0; i < n; i++) {
            adj_list[i] = nullptr;
        }

        //初始化vectors of node
        A = new int[n];
		for(int i = 0; i < n; i++) {
      		A[i] = i;
		}
    }

    /*
    添加边
    */
    void add_edge(int src, int dest) {
        // 将一条从 src 到 dest 的边添加到邻接链表中
        struct Node* node = new Node;
        node->dest = dest;
        node->next = adj_list[src]; //头插法
        adj_list[src] = node;
    }


    /*
    计算某个节点的出度
    */
   int outdegree(int u){
        struct Node* node = adj_list[u];
        int num=0;
        while(node!=nullptr){
            node = node->next;
            num++;
        }
        return num;
   }


    /*
    打印图
    */
    void print_graph() {
        cout<<"print graph"<<endl;
        for (int i = 0; i < n; i++) {
            struct Node* node = adj_list[i];
            cout << i << ": ";
            while (node != nullptr) {
                cout << node->dest << " ";
                node = node->next;
            }
            cout << endl;
        }
    }

    /* 
     *   判断有向边(u,w)是否存在于邻接矩阵
    */
   bool hasDirectedEdge(int u,int w){
        Node *u_list = adj_list[u]; //节点u到其他节点的链表
        
        struct Node* node = u_list;

        while(node!=nullptr){
            if (node->dest == w){
                return true;
            }else{
                node = node->next;
            }
        }
        return false;

   }


    /* 
    *   计算节点w出现在节点u的邻接矩阵中的第几个位置
    */
   int neighbor(int w, int u){
        struct Node* node = adj_list[u];
        int loc = 1;

        while(node!=nullptr){
            if (node->dest == w){
                break;
            }else{
                loc++;
            }
            node = node->next;
        }
        return loc;
   }

    /* 对A进行sort
    * assume 0 back edges initially
	* each time we see an edge from curr to j we decrement i.e. lose a back edge by swapping
	* each time we see an edge from j to curr we increment i.e. gain a back edge by swapping
	* looking for valley, or min value, in sequence to locate swap pos
    */
    void sort(){
        for (int i=0;i<n;i++){
            int curr =  A[i];
            int val = 0;
            int min =0;
            int loc = i;    

            //check all candidate positions from i to 0
            for (int j=i-1;j>=0;j--){
                if (hasDirectedEdge(curr, A[j])){//检查有向图中从点u到w是否存在一条有向边
                    val--;
                } else if (hasDirectedEdge(A[j], curr)){ //后向边
                    val++;
                }

                if (val<=min){
                    min = val;
                    loc = j;
                }
            }

            //shift over values and insert
            for (int t=i-1;t>=loc;t--){
                A[t+1] = A[t];
            }
            A[loc] = curr;
        }
    }

    /*
    * 输出sort后的A
    */
    void printA(){
        cout<<" Print A: ";
        for (int i=0;i<n;i++){
            cout<<A[i]<<" ";
        }
        cout<<endl;
    }

    /* 
    * 计算FAS的大小
    */
    long computeFAS(){
        sort(); 
        printA();
        cout<<"-------"<<endl;
        
        //建立映射关系
        int* varray = new int[n];

        for(int u=0;u<n;u++){
            varray[A[u]] = u;
        }
        
        // 检查varray
        cout<<"varray: ";
        for(int i =0;i<n;i++){
            cout<<varray[i]<<" ";
        }
        cout<<endl;

        // bitset<100> fvs; //假设有100位，这里应该设置为节点数量，但是bitset只能设置为常数
        long fas = 0;
        int self = 0;

        //遍历图中的n-1个节点
        for (int i = 0; i < n-1; i++) {
            //i就是节点
            int v = i;

            //遍历节点的所有出边
            struct Node* node = adj_list[v]; //节点的邻接链表

            while (node != nullptr) {
                int edge_dest = node->dest;
                
                //self loop
                if (v==edge_dest){
                    self++;
                    continue;
                }

                //检查边是否需要被删除
                if (varray[v] > varray[edge_dest]){
                    // fvs.set(v);
                    fas++;
                    cout<<"edge needed to be removed: "<<v<<"->"<<edge_dest<<endl;
                }
                node = node->next;

            }
        }

        cout<<"fas size = "<<fas<<endl;
        cout<<"self loop = "<<self<<endl;

        return fas;
    }
};

Graph readGraph(const std::string &filename, int numVer) {
  try {
    std::ifstream fin(filename);
    if (!fin) {
      std::cout << "Error open " << filename << "\n";
      exit(1);
    }
    std::string line;
    Graph graph(numVer);
    while (fin >> line) {
      int comma = line.find(',');
      int u = std::stoi(line.substr(0, comma));
      int v = std::stoi(line.substr(comma + 1));
      graph.add_edge(u, v);
    }
    fin.close();
    return graph;
  } catch (std::exception &e) {
    std::cout << "Error reading " << filename << ": " << e.what() << "\n";
    exit(1);
  }
}

}


// int main() {
//     // 从文件中读取边信息并添加到邻接链表图中
//     ifstream infile("3.txt");
//     if (!infile) {
//         cout << "Error opening file!" << endl;
//         return 0;
//     }

//     int n, src, dest;
//     infile >> n; // 读取顶点数
//     Graph g(n);

//     while (infile >> src >> dest) {
//         g.add_edge(src, dest);
//     }

//     infile.close();

//     // 打印邻接链表图
//     g.print_graph();
//     cout<<"-------"<<endl;
    
//     //测试某条有向边的是否存在
//     // cout<<g.hasDirectedEdge(0,1);
    
//     //输出fas
//     cout<<g.computeFAS()<<endl;


//     cout<<endl;

//     return 0;
// }
