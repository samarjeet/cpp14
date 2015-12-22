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

struct hashKey_t{
  char line;
  char* name;
};

edge_t *edge_root ;
edge_t *e_next=0;
// Constructing 400 edges as a guess right now,
// will make it more accurate later. 
void edges_init(){
  edge_root = malloc(sizeof(edge_t)* 400);
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

int main(int argc, char* argv[]){

  char str[100], stationData[200];
  FILE *fp;
  char* token ;
  const char delim[2] = " ";

  node_t *nodes = calloc(sizeof(node_t), N_NODES);
  int nodeId=-1; 
  edges_init();
  char route;

  printf("Reading the metro data and setting up the graph..\n");
  fp = fopen ("metro.txt","r");

  while(fgets(str, 100, (FILE *)fp)){
    //printf("%s", str);
    route=str[0];
    printf("%c\n", route);
    char* strPos = strchr(str, '(');
    if (strPos==NULL){
      printf("%s\n", "Error in input !\n");
    }
    else {
      char* strPos2 = strchr(str, ')');
      if (strPos2==NULL){
        printf("%s\n", "Error in input !\n");
      }
      int pos1 = strPos - str +1;
      int pos2 = strPos2 - str+1;
      char* subString = 0;
      subString = (char *)malloc(pos2-pos1+1);
      memcpy(subString, strPos+1, pos2-pos1-1);
      subString[pos2-pos1+1]=0;
      //char * s2 = getString(str, pos1, pos2);
      
      int i=0;
      int numberOfStops = atoi(subString);

      ++nodeId;
      for(i=0; i< numberOfStops; ++i){
        fgets(stationData, 100, (FILE *)fp);
        token = strtok(stationData, delim );
        int tokenId=0;
        while (token != NULL){
          if (tokenId==0){
            printf ("\t%s\n", token);
            nodes[nodeId].line = route;
            nodes[nodeId].name = token;
          }
          else if (tokenId==1){
            nodes[nodeId].crossOvers = atoi(token);
          }
          token = strtok(NULL, delim );
          ++tokenId;
        }
      }
      fgets(str, 100, (FILE *)fp);
      
    }
  }
  
  fclose(fp);
  return 0;
}
