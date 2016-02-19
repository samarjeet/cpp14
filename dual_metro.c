#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unordered_map>
#include<string>
#include<algorithm>

#define NUM_ROUTES 6
#define N_EDGES 600
#define N_NODES 300

// data structures
typedef struct node_t node_t, *heap_t;
typedef struct edge_t edge_t;
typedef struct Key Key;

struct edge_t{
  node_t *nextNode; // target node of the edge
  edge_t *next; // for the linked list 
  int cost; // cost of the edge  
};

struct node_t{
  // data-specific elements
  //std::string name;
  char* name;
  char route;
  int stoppingTime;
  int crossOvers;
  int transferTime[NUM_ROUTES];
  char transferToRoute[NUM_ROUTES];
  int state; // 0 for arrival 1 for departure

 // Graph and Dijkstra's algorithm variales
  edge_t *edge;
  node_t *via;
  int dist; // distance from the source 
  int heap_idx;

};

edge_t *edge_root ;
edge_t *edge_next;
void edges_init(){
  edge_root = (edge_t*)calloc(sizeof(edge_t), N_EDGES);
  edge_next = edge_root ;//+ NUMBER_EDGES - 1;
}

char* getString(char* str, int st, int end){
  char* subString = 0;
  subString = (char*)malloc(end-st+1);
  memcpy(subString, str+st, end-st+1);
  subString[end-st+1]=0;
  printf("%s--%s", str, subString);
  return subString;
}
int edge_count = 0;
void addEdge(node_t* from, node_t* to, int cost){
  edge_count++;
  printf("\n\t\t\t\t%s(%c,%d) -->%s(%c,%d)[%d] ", from->name, from->route, from->state, to->name, to->route,to->state,  cost);
  edge_next->nextNode=to;
  edge_next->cost=cost;
  edge_next->next=from->edge;
  from->edge=edge_next;
  edge_next++;
}
int heap_len;
heap_t *heap;

void setDistance(node_t *nd, node_t *via, int d){
  int i,j; 

  if(nd->via && d >=nd->dist ) return;
  nd->dist = d;
  nd->via = via;

  i=nd->heap_idx;
  if(!i) i = ++heap_len;

  for(; i>1 && nd->dist < heap[j=i/2]->dist; i=j)
    (heap[i]=heap[j])->heap_idx = i;
  heap[i] = nd;
  nd->heap_idx = i;
}


node_t* popQueue(){
  node_t *nd, *tmp;
  int i, j;

  if(!heap_len) return 0;
  nd = heap[1];
  tmp=heap[heap_len--];

  for(i=1; i<heap_len && (j=i*2) <= heap_len; i=j){
    if(j<heap_len && heap[j]->dist > heap[j+1]->dist)
      j++;
    if(heap[j]->dist >= tmp->dist)
      break;
    (heap[i]=heap[j])->heap_idx = i;
  }

  heap[i]=tmp;
  tmp->heap_idx=i;
  return nd;
}

void showPath(node_t *nd){
  if(nd->via == nd)
    printf("%s(%c,%d)", nd->name, nd->route, nd->state);
  else if (!nd->via)
    printf("%s(%c)(unreached)", nd->name, nd->route);
  else {
    showPath(nd->via);
    printf("-> %s(%c,%d)[%d]", nd->name, nd->route, nd->state, nd->dist);
  }
}

struct Key{
  char route;
  std::string name;
  int state;
  bool operator==(const Key &other) const{
    return (route==other.route && name== other.name && state==other.state);
  }
};
namespace std{
  template<>
  struct hash<Key>{
    size_t operator()(const struct Key &d) const{
      return (std::hash<char>()(d.route) + std::hash<string>()(d.name));
    }
  };
}


int main(int argc, char* argv[]){
  std::unordered_map<Key, node_t*> hashNodes;

  char str[100], stationData[200];
  FILE *fp;
  char* token ;
  char* currentStopName;
  char* prevStopName;

  const char delim[2] = " ";
  char* previousStopName = 0; 
  node_t *nodes = (node_t*)calloc(sizeof(node_t), N_NODES);
  //node_t *nodes = (node_t*)malloc(sizeof(node_t)*N_NODES);
  int nodeId=-1; 
  edges_init();
  char route;

  printf("Reading the metro data and setting up the graph..\n");
  fp = fopen ("metro.txt","r");
  //fp = fopen ("b.txt","r");

  while(fgets(str, 100, (FILE *)fp)){
    // reading a route's data
    route=str[0];
    printf("%c\n", route);
    char* strPos = strchr(str, '(');
    if(0){}
    else {
      char* strPos2 = strchr(str, ')');
      int pos1 = strPos - str +1;
      int pos2 = strPos2 - str+1;
      char* subString = 0;
      subString = (char *)malloc(pos2-pos1+1);
      memcpy(subString, strPos+1, pos2-pos1-1);
      subString[pos2-pos1+1]=0;
      //char * s2 = getString(str, pos1, pos2);
      int stopId=0;
      int numberOfStops = atoi(subString);

      int previousStoppingTime=0;
      int previousWaitingTime=0;

      //loop over all the stations for a route/color
      for(; stopId< numberOfStops; ++stopId){
         //++nodeId;
        // reading a (station) stop data
        int currentWaitingTime = 0;
        fgets(stationData, 100, (FILE *)fp);
        token = strtok(stationData, delim );
        int tokenId=0;
        int stEdgeCost=0;
        int currentCrossOvers;
        while (token != NULL){
          if (tokenId==0){
            currentStopName = strdup(token);
            Key k0 = Key{route, std::string(token) , 0};
            Key k1 = Key{route, std::string(token) , 1};
            printf ("\t%s", token);
            if (hashNodes.count(k0)){
              //printf ("\t%s\t%d", token, hashNodes.find(k1));
              printf("\t%s(%c, %d) already created..\t", currentStopName, route, 0);
            }
            else {
              ++nodeId;
              nodes[nodeId].route = route;
              nodes[nodeId].name = strdup(token);
              nodes[nodeId].state = 0;
              hashNodes[k0]=nodes+nodeId;
            }
            if (hashNodes.count(k1)){
              //printf ("\t%s\t%d", token, hashNodes.find(k1));
              printf("\t%s(%c, %d) already created..\t", currentStopName, route, 1);
            }
            else {
              ++nodeId;
              nodes[nodeId].route = route;
              nodes[nodeId].name = strdup(token);
              nodes[nodeId].state = 1;
              hashNodes[k1]=nodes+nodeId;
            }
          }
          else if (tokenId==1){
            nodes[nodeId].crossOvers = atoi(token);
            currentCrossOvers=atoi(token);
          }
          else if (tokenId==2){
            stEdgeCost+= (atoi(token) - previousStoppingTime); 
            previousStoppingTime = atoi(token);
            //stEdgeCost+= previousWaitingTime;
          }
          else if (tokenId==4 || ( stopId==0 || stopId==numberOfStops-1)){
            int cross=0;
            for(; cross < currentCrossOvers; cross++){
             char newRoute = token[0];
             Key knew = Key{newRoute, currentStopName, 1};
             if (hashNodes.count(knew)){
               printf("\n\t\t\t\t%s(%c, %d) already exists\t", currentStopName, newRoute, 1 );
             }
             else {
              ++nodeId;
              nodes[nodeId].route=newRoute;
              nodes[nodeId].name=strdup(currentStopName);
              nodes[nodeId].state=1;
              hashNodes[knew]=nodes+nodeId;
             }
             token = strtok(NULL, delim);
             int crossOverEdgeCost = atoi(token);
             Key kCurrent = Key{route, std::string(currentStopName), 0};
             printf("..CroosOver from %c to %c stop : %s\t", route, newRoute, currentStopName);
             addEdge(hashNodes[kCurrent], hashNodes[knew], crossOverEdgeCost);
             token = strtok(NULL, delim);
            }
         }
          else {
            previousWaitingTime = atoi(token);
            currentWaitingTime  = atoi(token);
          }
          token = strtok(NULL, delim );
          ++tokenId;
        }
        // finished reading a stop's data
        if (stopId >0){
          //printf("\n\t\t\tedge : from %s to %s, cost : %d\n", previousStopName, nodes[nodeId].name, stEdgeCost);
          printf("...Connecting %s and %s on route %c..", prevStopName, currentStopName, route);
          Key ka = Key{route, std::string(prevStopName), 1};
          Key kb = Key{route, std::string(currentStopName), 0};
          addEdge(hashNodes[ka], hashNodes[kb], stEdgeCost);
          ka = Key{route, std::string(prevStopName), 0};
          kb = Key{route, std::string(currentStopName), 1};
          addEdge(hashNodes[kb], hashNodes[ka], stEdgeCost);
        }
        Key ka = Key{route, std::string(currentStopName), 0};
        Key kb = Key{route, std::string(currentStopName), 1};
        addEdge(hashNodes[ka], hashNodes[kb], currentWaitingTime);
        prevStopName = strdup(currentStopName);
        printf("\n");
      } 
      // finished reading all stops for a route/color
      fgets(str, 100, (FILE *)fp);
    }
  }
  fclose(fp);
  heap = (node_t**)calloc(sizeof(heap_t), N_NODES+1);
  heap_len=0;
  node_t *lead;
  edge_t *e;

  Key k1 = {'g', "College_Park", 1};
  Key k2 = {'r', "Takoma", 0};
  //Key k2 = {'g', "College_Park", 0};
  //Key k1 = {'r', "Takoma", 1};

  //Key k1 = {'r', "Takoma", 1};
  //Key k2 = {'r', "Gallery_Place", 0};
  //Key k2 = {'r', "Takoma", 0};
  //Key k1 = {'r', "Gallery_Place", 1};

  //Key k1 = {'g', "Waterfront", 1};
  //Key k2 = {'g', "Navy_Yard_Ballpark", 0};
  //Key k2 = {'g', "Waterfront", 0};
  //Key k1 = {'g', "Navy_Yard_Ballpark", 1};

  //Key k1 = {'r', "Glenmont", 1};
  //Key k2 = {'r', "Shady_Grove", 0};
  //Key k2 = {'r', "Glenmont", 0};
  //Key k1 = {'r', "Shady_Grove", 1};

  //Key k1 = {'r', "Metro_Center", 1};
  //Key k2 = {'b', "King_St_Old_Town", 0};
  //Key k1 = {'s', "McLean", 1};
  //Key k2 = {'r', "Wheaton", 0};

  //Key k1 = {'s', "Wiehle_Reston", 1};
  //Key k2 = {'g', "College_Park", 0};

  //Key k1 = {'y', "Shaw_Howard_U", 0};
  //Key k2 = {'y', "Columbia_Heights", 0};

  //Key k1 = {'y', "U_St"};
  //Key k1 = {'r', "Glenmont"};
  //Key k2 = {'r', "Shady_Grove"};
  //Key k1 = {'r', "Union_Station"};
  //Key k2 = {'r', "Twinbrook"};
  //Key k2 = {'b', "King_St_Old_Town"};
  //Key k1 = {'r', "Metro_Center"};

  setDistance(hashNodes[k1], hashNodes[k1], 0);
  while((lead =popQueue())){
    for(e=lead->edge; e; e=e->next)
      setDistance(e->nextNode, lead, lead->dist + e->cost);
  }
  //showPath(nodes+15);
  showPath(hashNodes[k2]);
  printf("\n");
  free(nodes);
  free(edge_root);
  free(heap);
  printf("Nodes: %d Edges: %d\n", nodeId, edge_count);
  return 0;
}
