
//MyQueue<Type>q;
//定义了一个固定长度的队列， 不能动态增长
    //构造时不传参数，队列大小为1e5，传入参数时为自定义大小
    //如果队列不为空，front返回队首元素，
    //如果队列为空，pop无效，front返回NULL
    //clear将队列清空, 供多次使用
    //如果push时产生冲突，即队列已满， 将加入失败
template <class T>
class MyQueue
{
private:
    T* que;
    int si, fr, re;
    void setValue(int _size) {
        fr = 0; re = 0;
        si = _size;
        que = (T*)malloc(si * sizeof(T));
    }
public:
    MyQueue() {
        this->setValue(100005);
    }
    MyQueue(int _size) {
        this->setValue(_size);
    }
    T front() {
        if(fr != re)
            return que[fr];
        return NULL;
    }
    void pop() {
        if(fr != re)
            fr = (fr + 1) % si;
    }
    void push(T e) {
        if((re + 1) % si == fr) return ;
        que[re] = e;
        re = (re + 1) % si;
    }
    bool empty() {
        if(fr == re) return 1;
        return 0;
    }
    void clear() {
        fr = 0;
        re = 0;
    }
};
