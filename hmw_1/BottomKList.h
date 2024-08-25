#ifndef BOTTOMKLIST_H
#define BOTTOMKLIST_H
template<typename T, int k>

class BottomKList {
private:
    T** arr;
public:     //constructor
    BottomKList(){
       arr = new T*[k];
        for (int i = 0; i < k; ++i) {
            arr[i] = nullptr; // baþlangýçta hepsini null yaptým
        }
    }
    ~BottomKList(){
     //   delete arr; silmeye gerek yok
    }

    void addElement(T* element){
     //   cout << "Gelen sayi : " << *element << endl;
        for (int i=0; i<k; i++)
        {
            if (arr[i] == nullptr)
            {
                arr[i] = element;
                return ;
            }
            else if (*element < *arr[i])
            {
                for (int j=k-1; j>=i+1; j--)
                {
                    arr[j] = arr[j-1];
                }
                arr[i] = element;
                return ;
            }
        }
    }
    T* getBottomXthElement ( int x ) const{
    	if(x>=k || x < 0 ) {
    		return nullptr;
    	}
    	return arr[x];
	}	
    
#endif

