#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int degree(float radian){
	int angle = (radian * 180.0) / 3.14159265;
	return angle;
}

struct returnItem{
	int endNodeReturn;
	int currentOrientationReturn;
};

int pathLength = 0, path[50] = {0};
int graph[49][4] = {
	{0, 0, 0, 0},
	{24, 2, 0, 0},
	{1, 3, 0, 0},
	{2, 4, 35, 36},
	{3, 5, 0, 0},
	{4, 6, 0, 0},
	{5, 7, 0, 0},
	{6, 8, 27, 28},
	{7, 9, 0, 0},
	{8, 10, 0, 0},
	{9, 11, 0, 0},
	{10, 12, 39, 40},
	{11, 13, 0, 0},
	{12, 14, 0, 0},
	{13, 15, 0, 0},
	{14, 16, 30, 31},
	{15, 17, 0, 0},
	{16, 18, 0, 0},
	{17, 19, 0, 0},
	{18, 20, 43, 44},
	{19, 21, 0, 0},
	{20, 22, 0, 0},
	{21, 23, 0, 0},
	{22, 24, 25, 33},
	{23, 1, 0, 0},
	{23, 34, 0, 0},
	{34, 47, 0, 0},
	{7, 37, 0, 0},
	{7, 38, 0, 0},
	{38, 48, 0, 0},
	{15, 41, 0, 0},
	{15, 42, 0, 0},
	{42, 46, 0, 0},
	{23, 45, 0, 0},
	{25, 26, 35, 45},
	{3, 34, 36, 0},
	{3, 35, 37, 0},
	{27, 36, 47, 38},
	{28, 29, 39, 37},
	{11, 38, 40, 0},
	{11, 39, 41, 0},
	{40, 48, 42, 30},
	{41, 43, 31, 32},
	{19, 42, 44, 0},
	{19, 43, 45, 0},
	{33, 34, 44, 46},
	{32, 45, 0, 0},
	{26, 37, 0, 0},
	{29, 41, 0, 0}
};
int similarNodes[9][6] = {
	{1, 35, 34, 25, 0, 0},
	{35, 36, 37, 47, 26, 34},
	{5, 27, 37, 36, 0, 0},
	{9, 39, 38, 28, 0, 0},
	{29, 38, 39, 40, 41, 48},
	{13, 30, 41, 40, 0, 0},
	{17, 43, 42, 31, 0, 0},
	{32, 42, 43, 44, 45, 46},
	{21, 33, 45, 44, 0, 0}
};
int directions[49][2] = {
	{0 ,0},
	{0,300},
	{10, 225},
	{40, 150},
	{87, 87},
	{150, 40},
	{225, 10},
	{300, 0},
	{375, 10},
	{450, 40},
	{513, 87},
	{560, 150},
	{590, 225},
	{600, 300},
	{590, 375},
	{560, 450},
	{513, 513},
	{450, 560},
	{375, 590},
	{300, 600},
	{225, 590},
	{150, 560},
	{87, 513},
	{40, 450},
	{10, 375},
	{85, 375},
	{210, 300},
	{260, 70},
	{340, 70},
	{345, 225},
	{525, 375},
	{475, 450},
	{345, 375},
	{120, 450},
	{120, 300},
	{85, 225},
	{120, 150},
	{210, 150},
	{385, 150},
	{475, 150},
	{525, 225},
	{475, 300},
	{385, 450},
	{340, 530},
	{260, 530},
	{210, 450},
	{225, 375},
	{225, 224},
	{385, 300}
};

void bfs(int start, int endList[], int endListLen, int graphCopy[48][4]){
	int storage[49][2] = {0};
	int top = 0, queue[50] ={0};
	int currentNode, i, j, hop, minHop, endPoint, current;
	storage[start][0]=0;
	storage[start][1]=0;
	queue[top] = start;
	top++;
	/*
	printf("\nstart=%d\nendList : ",start);
	for(i=0;i<endListLen;i++){
		printf("%d ",endList[i]);
	}
	printf("\n");
	*/
	while (top) {
		/*
		printf("Queue=");
		for(i=0;i<top;i++){
			printf("%d ",queue[i]);
		}
		printf("\n");
		*/
		currentNode = queue[0];
		for(i = 0;i < top - 1; i++){
			queue[i] = queue[i+1];
		}
		top--;
		hop = storage[currentNode][0];
		for(i = 0; i < 4; i++){
			if(graphCopy[currentNode][i] != 0){
				if(storage[graphCopy[currentNode][i]][0] == 0 && graphCopy[currentNode][i] != start){
					storage[graphCopy[currentNode][i]][0] = hop + 1;
					storage[graphCopy[currentNode][i]][1] = currentNode;
					queue[top] = graphCopy[currentNode][i];
					top++;
				}	
			}
		}
		
	}
	//for(i = 0;i < 49;i++){
	//	printf("%d : %d %d\n", i, storage[i][0], storage[i][1]);
	//}
	minHop = 1000;
	endPoint =  -1;
	for(i = 0; i < endListLen; i++){
		if(endList[i] != 0){
	 		if (minHop > storage[endList[i]][0]) {
	 			minHop = storage[endList[i]][0];
	 			endPoint = endList[i];
	 		}		
	 	}
	}
	//printf("min %d %d\n", minHop, endPoint);
	pathLength = minHop;
	current = endPoint;
	while (current != start){
	 	path[minHop-1] = current;
	 	current = storage[current][1];
	 	minHop--;
	}
}

struct returnItem currentBest(int start, int end, int currentOrientation){
	struct returnItem result;
	int i, endList[6]={0, 0, 0, 0, 0, 0}, endListLen = 0;
	int graphCopy[48][4];
	char block = 'n';
	int j, endNode, currentNode, nextNode, angleDirection;
	float directionToMove[2];
	//printf("****** %d\n", currentOrientation);
	//printf("%d %d\n", start, end);
	if(end >= 25 && end <= 33) {
		for(i=0; i<6; i++){
				endList[i] = similarNodes[end-25][i];
		}
	}
	else {
		endList[0] = end; 
	}
	for(i = 0; i < 6; i++){
		//printf("%d ", endList[i]);
		if(endList[i] != 0){
			endListLen++;
		}
	}
	printf("\n");
	for(i=0; i < 48; i++){
		for(j=0; j<4; j++){
			graphCopy[i][j] = graph[i][j];
		}
	}
	bfs(start, endList, endListLen, graph);
	//printf("pathlen%d\n", pathLength);
	//for(i=0; i<pathLength; i++){
	//	printf("%d ",path[i]);
	//}

	if(pathLength){
		endNode = path[pathLength-1];
	}
	else{
		endNode = 0;
	}
	currentNode = start;

	while(pathLength){
		nextNode = path[0];
		for(i = 0; i < pathLength; i++){
			path[i] = path[i+1];
		}
		pathLength--;
		//printf("\n next node %d\n", nextNode);
		
		//Pop from path
		printf("\nFrom %d To %d\n", currentNode, nextNode);		
		directionToMove[0] = directions[currentNode][0]-directions[nextNode][0];
		directionToMove[1] = directions[currentNode][1]-directions[nextNode][1];
		angleDirection = degree(atan((directionToMove[1])/(directionToMove[0])));
		//printf("angle direction %d\n", angleDirection);

		if(angleDirection > -3 && angleDirection < 3){
			if(directionToMove[0] > 0)
				angleDirection = 180;
		}
		else if(directionToMove[1] < 0){
			if(angleDirection > 0)
				angleDirection = (360 - angleDirection);
			else if (angleDirection < 0)
				angleDirection = (180 + abs(angleDirection));
		}
		else{
			if (angleDirection > 0)
				angleDirection = (180 - angleDirection);
			else if (angleDirection < 0)
				angleDirection = abs(angleDirection);
		}

		angleDirection = angleDirection - currentOrientation;
		if (angleDirection < 0)
			angleDirection = 360 + angleDirection;
		if (angleDirection >= 360)
			angleDirection = angleDirection % 360;

		printf("***************Actual Move : ");
		if (angleDirection < 20 || angleDirection > 340)
			printf("Straight\n");
		else if (angleDirection > 160 && angleDirection < 200)
			printf("Reverse\n");
		else if (angleDirection < 90)
			printf("Soft Left\n");
		else if (angleDirection < 180)
			printf("Hard Left\n");
		else if (angleDirection < 270)
			printf("Hard Right\n");
		else
			printf("Soft Right\n");

		currentOrientation = currentOrientation + angleDirection;
		if (currentOrientation < 0)
			currentOrientation = 360 + currentOrientation;
		if (currentOrientation >= 360)
			currentOrientation = currentOrientation % 360;
		//printf("angle deviation : %d  current : %d",angleDirection, currentOrientation);
	 	printf("Blocked or not: Y/N");
	 	scanf("%c", &block);
	 	if (block == 'Y'||block == 'y'){
	 		for(i=0; i < 48; i++){
				for(j=0; j<4; j++){
					graphCopy[i][j] = graph[i][j];
				}
			}
			
	 		//printf("copied\n");
	 		for(i=0;i<4;i++){
	 			if(graphCopy[currentNode][i] == nextNode){
	 				graphCopy[currentNode][i]=0;
	 				break;
	 			}
	 		}
	 		//for(i = 0; i < 49; i++){
			//	printf("%d : %d %d %d %d\n", i, graphCopy[i][0], graphCopy[i][1], graphCopy[i][2], graphCopy[i][3]);
			//}
	 		for(i=0; i<pathLength; i++){
				path[i] = 0;
			}
			pathLength = 0;
			//printf("path%d\n", pathLength);
	 		currentOrientation += 180;
	 		if (currentOrientation < 0)
	 			currentOrientation = currentOrientation + 360;
	 		if (currentOrientation >= 360)
	 			currentOrientation = currentOrientation % 360;
	 		printf("***************Actual Move: Reverse");
	 		bfs(currentNode, endList, endListLen, graphCopy);
	 		//printf("path%d\n", pathLength);
			//for(i=0; i<pathLength; i++){
			//	printf("%d ",path[i]);
			//}
	 		continue;
	 	}
	 	if (block == 'e')
	 		return result;
	 	currentNode = nextNode;

	}
	result.endNodeReturn = 0;
	if (endNode > 0){
		result.endNodeReturn = endNode;
		// return end_node, current_orientation
	}
	result.currentOrientationReturn = currentOrientation;
	return result;
	// return None, current_orientation
}

int main(){
	/*
	int s = 1;
	int e[] = {29},i;
	for(i=0;i<50;i++){
		printf("%d ", path[i]);
	}
	bfs(s,e,1,graph);
	printf("\n");
	for(i=0;i<50;i++){
		printf("%d ", path[i]);
	}
	*/
	int start = 1, stringLength = 9, string[10] = {7, 29, 26, 18, 24, 13, 30, 16, 20}, currentOrientation = 0;
	int i=0, s, end;
	struct returnItem resultGet;
	for(i = 0; i < stringLength; i++) {
		//printf("\n%d %d", start, string[i]);
		end = string[i];
		resultGet = currentBest(start, end, currentOrientation);
		s = resultGet.endNodeReturn;
		currentOrientation = resultGet.currentOrientationReturn; 
		if(s){
			start = s;
		}
		printf("beep\n");
	}
	return 0;
}
