
//MyQueue<Type>q;
//������һ���̶����ȵĶ��У� ���ܶ�̬����
    //����ʱ�������������д�СΪ1e5���������ʱΪ�Զ����С
    //������в�Ϊ�գ�front���ض���Ԫ�أ�
    //�������Ϊ�գ�pop��Ч��front����NULL
    //clear���������, �����ʹ��
    //���pushʱ������ͻ�������������� ������ʧ��
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
