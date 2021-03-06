#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

template<class T>
class Heap{
private:
  int heapCapacitySize;
  int heapType;
  int cnt;
  vector<T> array;

  int leftChild(int i){
    int left = 2*i + 1;
    if(left>=cnt)
      return -1;
    return left;
  }

  int rightChild(int i){
    int right = (i+1)<<1;
    if(right>=cnt)
      return -1;
    return right;
  }

  void Heapify(int i){
    if(heapType==0)
      maxHeapify(i);
    else
      minHeapify(i);
  }

  void maxHeapify(int i){
    int max_point;
    int l = leftChild(i);
    int r = rightChild(i);
    if(l!=-1 && array[l] > array[i]){
      max_point = l;
    } else {
      max_point = i;
    }
    if(r!=-1 && array[r] > array[max_point]){
      max_point = r;
    }
    if(max_point != i){
      swap(array[i],array[max_point]);
      maxHeapify(max_point);
    }
  }

  void minHeapify(int i){
    int min_point;
    int l = leftChild(i);
    int r = rightChild(i);
    if(l!=-1 && array[l] < array[i])
      min_point = l;
    else
      min_point = i;
    if(r!=-1 && array[r] < array[min_point])
      min_point = r;

    if(min_point != i){
      swap(array[i],array[min_point]);
      minHeapify(min_point);
    }
  }

public:
  Heap():heapCapacitySize(100),heapType(0),cnt(0){}
  Heap(int _heapType):heapCapacitySize(100),heapType(_heapType),cnt(0){
    array.resize(100);
  }

  void Insert(T data){
    if(cnt == heapCapacitySize){
      heapCapacitySize <<= 1;
      array.resize(heapCapacitySize);
    }
    int i = cnt;
    cnt++;
    if(heapType==0){
      while(i>0 && data > array[(i-1)/2]){
	array[i] = array[(i-1)/2];
	i = (i-1)/2;
      }
      array[i] = data;
    } else {
      while(i > 0 && data < array[(i-1)/2]){
	array[i] = array[(i-1)/2];
	i = (i-1)/2;
      }
      array[i] = data;
    }

  }

  T Delete(){
    T data;
    if(cnt==0){
      return -1;
    }
    data = array[0];
    array[0] = array[cnt-1];
    cnt--;
    if(heapType==0)
      maxHeapify(0);
    else
      minHeapify(0);
    return data;
  }

  T pop(){
    if(heapCapacitySize>0){
      return array[0];
    } else {
     return -1;
    }
  }

  int size(){
    return cnt;
  }

};


template<class T>
class MedianHeap{
private:
  Heap<T> *MaxHeap;
  Heap<T> *MinHeap;

public:
  MedianHeap(){
    MaxHeap = new Heap<T>(0);
    MinHeap = new Heap<T>(1);
  }

  ~MedianHeap(){
    delete MaxHeap;
    delete MinHeap;
  }

  void insert(T data){
    if(MaxHeap->size()==0){
      MaxHeap->Insert(data);
      return;
    }

    T maxHeap = MaxHeap->pop();
    T minHeap = MinHeap->pop();

    if(data < maxHeap){
      MaxHeap->Delete();
      MaxHeap->Insert(data);
      swap( maxHeap, data);
    }

    if(MinHeap->size()==0){
      MinHeap->Insert(data);
      return;
    }

    if(data > minHeap){
      MinHeap->Delete();
      MinHeap->Insert(data);
      swap(data,minHeap);
    }

    if(MaxHeap->size() > MinHeap->size())
      MinHeap->Insert(data);
    else
      MaxHeap->Insert(data);
  }

  T pop(){
    if( (MaxHeap->size() + MinHeap->size() ) & 1 )
      return MaxHeap->pop();
    else
      return (MaxHeap->pop() + MinHeap->pop()) / 2;
  }
};

int main(){
  ll temp;
  MedianHeap<ll> mheap;
  while(cin >> temp){
    mheap.insert(temp);
    cout << mheap.pop() << endl;
  }
}
