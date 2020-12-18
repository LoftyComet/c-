#include <iostream>
#include <math.h>
using namespace std;

#include <iostream>
using namespace std;

template <typename E> class heap {
private:
    E* Heap;
    int maxsize;
    int n;
    void siftdown(int pos){
        while (!isLeaf(pos)){
            int j = leftchild(pos);
            int rc = rightchild(pos);
            if ((rc < n) && Heap[rc]<Heap[j])
                j = rc;
            if (Heap[pos]<Heap[j])
                return;

            E temp = Heap[j];
            Heap[j] = Heap[pos];
            Heap[pos] = temp;

            pos = j;
        }
    }

public:
    heap(E* h, int num, int max){
        Heap = h;
        n = num;
        maxsize = max;
        builtHeap();
    }

    int size() const {
        return n;
    }

    bool isLeaf(int pos) const {
        return (pos>=n/2&&pos<n);
    }

    int leftchild(int pos) const {
        return 2*pos + 1;
    }

    int rightchild(int pos) const {
        return 2*pos + 2;
    }

    int parent(int pos) const {
        return (pos-1) /2;
    }

    void builtHeap(){
        for (int i=n/2-1;i>=0;i--)
            siftdown(i);
    }

    void insert(const E& it){
        int curr = n++;
        Heap[curr] = it;
        while (curr!=0&&Heap[curr]<Heap[parent(curr)]) {
            swap(Heap,curr,parent(curr));
            curr = parent(curr);
        }
    }

    E removefirst(){
        n--;
//        swap(Heap,0,--n);
        E temp = Heap[n];
        Heap[n] = Heap[0];
        Heap[0] = temp;
        if (n !=0)
            siftdown(0);
        return Heap[n];
    }

    E remove(int pos){
        if (pos == n-1)
            n--;
        else {
            swap(Heap,pos,--n);
            while ((pos!=0)&&(Heap[pos]<Heap[parent(pos)])){
                swap(Heap,pos,parent(pos));
                pos = parent(pos);
            }
            if (n != 0)
                siftdown(0);
            return Heap[n];
        }
    }

    void printheap(){
        for (int i=0;i<maxsize;i++){
            cout << Heap[i] << "  ";
        }
        cout << endl;
    }//输出堆
};

class Rational{
    friend bool operator<(const Rational& r1, const Rational& r2) {
//        if (r1.N>0&&r2.N<0){
//            return false;
//        }
//        else if (r1.N<0&&r2.N>0) {
//            return true;
//        }
//        else if (r1.N>0&&r2.N>0) {
//            return r1.N*r2.D<r2.N*r1.D;
//        }
        return r1.N*r2.D<r2.N*r1.D;//类似于通分，下面同理
    }
    friend bool operator<=(const Rational& r1, const Rational& r2) {
        return r1.N*r2.D<=r2.N*r1.D;
    }
    friend bool operator>(const Rational& r1, const Rational& r2) {
        return r1.N*r2.D>r2.N*r1.D;
    }
    friend bool operator>=(const Rational& r1, const Rational& r2) {
        return r1.N*r2.D>=r2.N*r1.D;
    }
    friend bool operator==(const Rational& r1, const Rational& r2) {
        return r1.N*r2.D==r2.N*r1.D;
    }
    friend bool operator!=(const Rational& r1, const Rational& r2) {
        return r1.N*r2.D!=r2.N*r1.D;
    }
    friend ostream& operator<<(ostream& o, const Rational& c){
        if (c.D==1)
            o << c.N;
        else {
            o << c.N << "/" << c.D;
        }
        return o;
      }
private:

    int measure(int x, int y)
    {
        int z = y;
        while(x%y!=0)
        {
            z = x%y;
            x = y;
            y = z;
        }
        return z;
    }//找出两个数的最大公因数
public:
    int N;//分子
    int D;//分母 要求大于0
    Rational(){
        N = 0;
        D = 9999;
    }//default constructor
    Rational(int n){
        N = n;
        D = 1;
    }//constructor for integer value
    Rational(int n,int d){
        while (measure(d,n)!=1) {
            d/=measure(d,n);
            n/=measure(d,n);
        }
        D=d;
        N=n;
    }//normal constructor
    Rational(const Rational& r){
        this->D = r.D;
        this->N = r.N;
    } //copy constructor
    Rational& operator=(const Rational& r) {
        this->D = r.D;
        this->N = r.N;
        return *this;
    } // assignment override
    void yuefen(){
        while (measure(D,N)!=1) {
            int a = D,b = N;

            D/=measure(a,b);

            N/=measure(a,b);
        }
    }//函数如其名，约分
};


void heapsort(Rational A[],int n){
    Rational minval;
    heap<Rational> H(A,n,n);
    for (int i=0;i<n;i++){
        minval = H.removefirst();
        cout << minval << "  ";
    }
    cout << endl;//堆排序并输出结果
}

int main()
{
    int T=0;
    cin >> T;
    Rational rationals[T];
    for (int i=0;i<T;i++){
        int a=0,b=0;
        cin >> a >> b;
        rationals[i].N = a;
        rationals[i].D = b;
        rationals[i].yuefen();
    }
    heap<Rational> H(rationals,T,T);
    H.printheap();
    heapsort(rationals,T);

    return 0;
}
