#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <utility>

#define INF 399999999
using namespace std;

int number_of_nodes;
int number_of_edges;
map <int, int> node_values;
map <int, vector <int> > node_neighbours;
map < pair <int,int>, int> edge_lengths;
set <int> visited_nodes;
map <int, int> predecessor_nodes;

struct my_compare{
  bool operator()(const int& first, const int& second) const{
    if(node_values[first] < node_values[second])
      return true;
    return false;
  }
};
multiset <int, my_compare> unvisited_nodes;


//Guaranteed that predecessor node map is filled, prints the path from first node to last node.
void smallest_path(int start_index, int end_index){
    //Initialize vector for ordered path.
    vector <int> ordered_path;
    //Fills vector for ordered path.
    int current_node = end_index;
    while(true){
        ordered_path.push_back(current_node);
        if(current_node == start_index)
            break;
        current_node = predecessor_nodes[current_node];
    }
    //Prints ordered path.
    for(int i = ordered_path.size() - 1; i >= 0; i--){
        int current_node = ordered_path[i];
        cout<<current_node<<" ";
    }
}

//Finds the node with the lowest value by iterating 
//over unvisited nodes and seeing every node's value.                   !!!CHANGED THIS!!!
int find_node_with_lowest_value(){
  return *(unvisited_nodes.begin());
}

//Relaxes two nodes, if current node length + length from current node to neighbour is lower
//than neighbours value changes neighbours value to it and sets the current node as the
//predecessor of its neighbour
void relax_neighbour(int current_node, int current_node_neighbour){
    //Vertice between current node and neighbour.
    pair <int,int> current_vertice (current_node,current_node_neighbour);
    //Value of the current vertice.
    int distance_from_the_first_node = node_values[current_node] + edge_lengths[current_vertice];
    //If the value is less then neighbours previous tenative value,
    //assign neighbours tenative value to new value and set current node
    //neighbours predecessor.
    if(distance_from_the_first_node < node_values[current_node_neighbour]){
        node_values[current_node_neighbour] = distance_from_the_first_node;
        predecessor_nodes[current_node_neighbour] = current_node;
    }
}

//Provided the graph is initialized, given source and destination,
//finds and returns minimum path between them in the graph.
//Also fills the predecessor nodes array to make it possible to print the shortest path.
int dijkstra(int first_index, int last_index){
    //Assign start node tenative value of 0.
    node_values[first_index] = 0;

    //Assign every other node's tenative to 'infinity'.
    //Insert every node to unvisited nodes set.
    for(int i = 0; i < number_of_nodes; i++){
        if(i != first_index){
            node_values[i] = INF;
        }
        unvisited_nodes.insert(i);
    }

    //Make loop until we find the shortest path
    while(true){
      //Get the current node.
      int current_node = find_node_with_lowest_value();
      //Get the neighbours of the current node.
      vector <int>& current_node_neighbours = node_neighbours[current_node];
      
      //Relax each unvisited neighbour.
      for(auto current_node_neighbour : current_node_neighbours){
	if(visited_nodes.find(current_node_neighbour) == visited_nodes.end())
	  relax_neighbour(current_node, current_node_neighbour);
      }
      //After considering all of the current node's neighbours,
      //insert it into visited set and remove from unvisited set.          !!!CHANGED THIS!!!
      unvisited_nodes.erase(unvisited_nodes.begin());
      visited_nodes.insert(current_node);
								 
      //Check if we found destination
      if(visited_nodes.find(last_index) != visited_nodes.end()){
	//If we did, return the smalles length
	return node_values[last_index];
      }
    }
}

int main(){
    //Input of number of nodes and number of edges.
    cin >> number_of_nodes >> number_of_edges;

    //Input edges.
    for(int i = 0; i < number_of_edges; i ++){
        //Initialization of first, second nodes and length between them.
        int first_node, second_node, path_length;
        //Input the previous variables.
        cin >> first_node >> second_node >> path_length;

        //push them as each others neighbours.
        node_neighbours[first_node].push_back(second_node);
        node_neighbours[second_node].push_back(first_node);

        //Put them in map of lengths between nodes.
        pair <int, int> node_relation_l_r (first_node, second_node);
        pair <int, int> node_relation_r_l (first_node, second_node);
        edge_lengths[node_relation_l_r] = path_length;
        edge_lengths[node_relation_r_l] = path_length;
    }

    //Input starting index and destination (between which the shortest path is required).
    int first_index,last_index;
    cin >> first_index >> last_index;

    //Make dijkstra
    cout << "Smalles path length was: " << dijkstra(first_index, last_index) << endl;
    //Print smallest path
    cout << "Smalles path was: ";
    smallest_path(first_index, last_index);
}
