#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unordered_map>

#define NUM_LINES 6
#define NUMBER_EDGES 400
#define N_NODES 200

// data structures
typedef struct node_t node_t;
typedef struct edge_t edge_t;
typedef struct hashKey_t hashKey_t;

struct edge_t{
  node_t *nextNode; // target node of the edge
  edge_t *next; // for the linked list 
  int cost; // cost of the edge  
};

struct node_t{
  // data-specific elements
  //std::string name;
  char* name;
  char line;
  int stoppingTime;
  int crossOvers;
  int transferTime[NUM_LINES];
  char transferToLine[NUM_LINES];

 // Graph and Dijkstra's algorithm variales
  edge_t *edge;
  node_t *via;
  int dist; // distance from the source 
  int head_idx;

};

/*
struct Key{
  char line;
  char* name;
  bool operator==(const Key &other) const{
    return (line=other.line && *name=);
  }
};
*/
edge_t *edge_root ;
edge_t *e_next=0;
// Constructing 400 edges as a guess right now,
// will make it more accurate later. 
void edges_init(){
  edge_root = (edge_t*)malloc(sizeof(edge_t)* 400);
  //edge_next = edge_root + NUMBER_EDGES - 1;
}

char* getString(char* str, int st, int end){
  char* subString = 0;
  subString = (char*)malloc(end-st+1);
  memcpy(subString, str+st, end-st+1);
  subString[end-st+1]=0;
  printf("%s--%s", str, subString);
  return subString;
}

void addEdge(node_t* from, node_t* to, int cost){

}


int main(int argc, char* argv[]){
  //std::unordered_map<hashKey_t, node_t> hashTest;

  char str[100], stationData[200];
  FILE *fp;
  char* token ;
  const char delim[2] = " ";
  char* previousStopName = 0; 
  //node_t *nodes = calloc(sizeof(node_t), N_NODES);
  node_t *nodes = (node_t*)malloc(sizeof(node_t)*N_NODES);
  int nodeId=-1; 
  edges_init();
  char route;

  printf("Reading the metro data and setting up the graph..\n");
  fp = fopen ("metro.txt","r");

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
         ++nodeId;
        // reading a (station) stop data
        fgets(stationData, 100, (FILE *)fp);
        token = strtok(stationData, delim );
        int tokenId=0;
        int stEdgeCost=0;

        while (token != NULL){
          if (tokenId==0){
            printf ("\t%s", token);
            nodes[nodeId].line = route;
            char* stationName = token;
            nodes[nodeId].name = strdup(token);
          }
          else if (tokenId==1){
            nodes[nodeId].crossOvers = atoi(token);
          }
          else if (tokenId==2){
            stEdgeCost+= (atoi(token) - previousStoppingTime); 
            previousStoppingTime = atoi(token);
            stEdgeCost+= previousWaitingTime;
          }
          else if (tokenId==4 || ( stopId==0 || stopId==numberOfStops-1)){
            int cross=0;
            for(; cross < nodes[nodeId].crossOvers; cross++){
             //printf("\t%s\t", token);
             char newRoute = token[0];
             token = strtok(NULL, delim);
             printf("\tedge : from %c to %c, cost: %d\t", nodes[nodeId].line, newRoute, atoi(token));
             token = strtok(NULL, delim);
            }
         }
          else {
            previousWaitingTime = atoi(token);
          }
          token = strtok(NULL, delim );
          ++tokenId;
        }
        // finished reading a stop's data
        //printf("\t%d\n", stEdgeCost);
        if (stopId >0){
          //printf("\n\t\t\tedge : from %s to %s, cost : %d\n", previousStopName, nodes[nodeId].name, stEdgeCost);
        }
        //printf(" %s %s %d ", nodes[nodeId].name, nodes[0].name, nodeId);
        //previousStopName=nodes[nodeId].name;
        printf("\n");
      } 
      // finished reading all stops for a route/color
      fgets(str, 100, (FILE *)fp);
    }
  }
  fclose(fp);
  return 0;
}
