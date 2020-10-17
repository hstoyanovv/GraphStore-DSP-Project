#include "GraphStore.h"

int getCommand(std::string command);
void CREATEType(GraphStore & graphstore);
void ARCInput(GraphStore & graphstore);
void USEGRAPH(GraphStore & graphstore);
void DELETEType(GraphStore & graphstore);
void SEARCHType(GraphStore & graphstore);
void Run(char* path);
