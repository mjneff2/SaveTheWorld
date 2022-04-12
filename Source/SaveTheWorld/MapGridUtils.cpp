// Fill out your copyright notice in the Description page of Project Settings.


#include "MapGridUtils.h"
#include "Math/UnrealMathUtility.h"
#include "Containers/Queue.h"

TArray<int32> UMapGridUtils::GenerateGrid(int32 size) {
	TArray<int32> grid;
	grid.Init(0, size * size);
	int32 startX = 0;
	int32 startY = 0;
	int32 endX = size - 1;
	int32 endY = size - 1;
	int32 counter = 1;
	grid[startX * size + startY] = counter;
	int32 nextX = startX;
	int32 nextY = startY;
	int32 iterations = 0;
	while (nextX != endX || nextY != endY) {
		if (iterations++ > 1000) {
			return grid;
		}
		int32 oldX = nextX;
		int32 oldY = nextY;
		switch (FMath::RandRange(0, 3)) {
			case 0:
				nextX += 1;
				break;
			case 1:
				nextX -= 1;
				break;
			case 2:
				nextY += 1;
				break;
			case 3:
				nextY -= 1;
				break;
		}
		//UE_LOG(LogTemp, Warning, TEXT("Current %d %d"), nextX, nextY);
		TQueue<TPair<int32,  int32>> queue;
		queue.Enqueue(TPair<int32, int32>(nextX, nextY));
		bool endReached = false;
		int32 bfs_iterations = 0;
		TSet<int32> visited;
		while (!queue.IsEmpty()) {
			if (bfs_iterations++ > 1000) {
				return grid;
			}
			int32 currentX = queue.Peek()->Key;
			int32 currentY = queue.Peek()->Value;
			if (currentX == endX && currentY == endY) {
				endReached = true;
				break;
			}
			queue.Pop();
			if (currentX >= 0 && currentY >= 0 && currentX < size && currentY < size && grid[currentX * size + currentY] == 0 && !visited.Contains(currentX * size + currentY)) {
				//UE_LOG(LogTemp, Warning, TEXT("BFS Current %d %d"), currentX, currentY);
				visited.Add(currentX * size + currentY);
				queue.Enqueue(TPair<int32, int32>(currentX + 1, currentY));
				queue.Enqueue(TPair<int32, int32>(currentX - 1, currentY));
				queue.Enqueue(TPair<int32, int32>(currentX, currentY + 1));
				queue.Enqueue(TPair<int32, int32>(currentX, currentY - 1));
			}
		}
		if (endReached) {
			UE_LOG(LogTemp, Warning, TEXT("Next %d %d %d %d"), endReached, nextX, nextY, iterations);
			grid[nextX * size + nextY] = ++counter;
		}
		else {
			nextX = oldX;
			nextY = oldY;
		}

	}

	return grid;
}

