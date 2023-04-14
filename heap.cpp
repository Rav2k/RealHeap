/*
  I fount the link below on how to print the tree out, so I read through it to make sure I understood how it worked and implented it in my code.
  Link: https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/?ref=gcse
 */
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

void insertNum(int *&heap, int number);
void fileNums(int *&heap);
void UserInput(int *&heap);
void remove(int *&heap, int index);
void printHeap(int *&heap, int index, int layer);
int leftChild(int *&heap, int index);
int rightChild(int *&heap, int index);
int parentHeap(int *&heap, int index);
void remove(int *&heap);

int main(){
  char* generate = new char[20];
  int* heap = new int[101];//space for null
  for (int i = 0; i < 101; i++) {//setting all heap values to zero
    heap[i] = 0;
  }
  bool loop = true;
  int size;
  do{
  cout<<"type 'gen' to generate 70 numbers and 'add' to add numbers yourself and type 'RemoveHeap' to remove the heap and 'print' to print and 'quit' to quit"<<endl;
  cin>>generate;
  if(strcmp(generate, "gen") == 0){
    if(sizeof(heap)<100){
      fileNums(heap);
    }else{
      cout<<"Heap is Full..."<<" "<<"...consider deleting"<<endl;
    }
  }
  else if(strcmp(generate, "add") == 0){
    if(sizeof(heap)<100){
      UserInput(heap);
    }else{
      cout<<"Heap is Full..."<<" "<<"...consider deleting"<<endl;
    }
  }
  else if(strcmp(generate, "RemoveHeap") == 0){
    while(heap[1] !=0){//removes till nothing left
      remove(heap);
    }
    cout<<"done"<<endl;
  }
  else if (strcmp(generate, "print") == 0) {
      if (heap[1] == 0) {
	cout << "No numbers in heap" << endl;
      }
      else {
	printHeap(heap, 1, 0);
      }
    }
  
  }while(strcmp(generate, "quit") != 0);
}


void insertNum(int *&heap, int number) {
  int index = 0;
  if (heap[1] == 0) {//if the first index in the heap is zero then...
    heap[1] = number;//...put the number there and then you'll be done
  }
  else {
    for (int i = 1; i < 101; i++) {//goes through the int pointer
      if (heap[i] == 0) {//if the spot in the int pointer has no input aka is zero then...
	heap[i] = number;//...put the number in that spot
	index = i;//then make the index start from that spot so we don't have to begin from the start
	break;//exit the loop because you're done inserting the number into the heap 
      }
    }
  }
  int parentInx = parentHeap(heap, index);//finding the parent index
  while (parentInx!=0 && heap[index]>heap[parentInx]) {//while the parentIndex exists and the number is greater than the parent index then swap it and rerun the program till everything is arranged.
    int temp = heap[index];
    heap[index]= heap[parentInx];
    heap[parentInx] = temp;
    index = parentInx;
    parentInx = parentHeap(heap, index);
   }
}


void fileNums(int *&heap){
  ifstream inFile("numbers.txt");
  //I will put the numbers in an array to make it easy to add the individual numbers to the heap
  int numHold = 0;
  int loop = 0;
  if(inFile.is_open()){
    while(!inFile.eof()){
      inFile>>numHold;
      heap[loop] = numHold;
      loop++;
    }
    inFile.close();
  }else{
    cout<<"file can't be opened"<<endl;
  }
  for(int i = 0; i<70; i++){
    insertNum(heap, heap[i]);
  }
  cout<<"done adding the generated number"<<endl;

 }


void UserInput(int *&heap) {
  int numInput = 0;
  cout << "Enter a number: "<<endl;
  cin >> numInput;
  cin.get();
  insertNum(heap, numInput);
}

void printHeap(int *&heap, int index, int layer){
  if (index == 0 || heap[index] == 0) {//if there is nothing there then do stop
    return;
  }
  //calling the program to print out the right children of the index
  printHeap(heap, rightChild(heap, index), layer + 1);
  //for structure
  for (int i = 0; i < layer; i++) {
    cout << "    ";
  }
  //printing the numbers
  cout << heap[index] << endl;
  //printing the left side.
  printHeap(heap, leftChild(heap, index), layer + 1);
}

int leftChild(int *&heap, int index){
  int leftIndex;
  leftIndex = index *2;
  if(index!=0&&index<101){
    return leftIndex;
  }else{
    return 0;
  }
}

int rightChild(int *&heap, int index){
  int rightIndex;
  rightIndex = (index * 2) + 1;
  if(index !=0&&index<101){
    return rightIndex;
  }else{
    return 0;
  }
}

int parentHeap(int *&heap, int index){
  int temp;
  int switching;
  int num = floor(index/2);
   if (index == 1) {
    return 0;
   }
   else{
     return floor(index/2);
   }
}


void remove(int *&heap){
  int rootIndex = 1;
  int left = 0;
  int right = 0;
  int temp = 0;
  int switching = 0;
  while(!(left!=0 && heap[rootIndex]>heap[left]&&right!=0&&heap[rootIndex]>heap[right])){
    left = leftChild(heap, rootIndex);
    right = rightChild(heap, rootIndex);

    if (left != 0 && right != 0) {
      if (heap[left] > heap[right]) {//taking the bigger number to switch with the root
	switching = left;
      }
      else {
	switching = right;
      }
    }
    else if (right != 0 && left == 0) { //only right child exists then switch the right 
      switching = right;
    }
    else if (left != 0 && right == 0) { //only left child exists then switch the left
      switching = left;
    }
    else {//no children exist, we reached the end of the tree
      heap[rootIndex] = 0;
      return;
    }
    //replacing the left or right child with the root and removing it by making it 0 
    temp = heap[rootIndex];
    heap[rootIndex] = heap[switching];
    heap[switching] = temp;
    rootIndex = switching;
    cout<<endl;
    cout<<endl;
  printHeap(heap, 1, 0);  
  }
  heap[switching] = 0;
  
}


